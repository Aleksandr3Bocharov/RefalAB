// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-07-30
// https://github.com/Aleksandr3Bocharov/RefalAB

//-----------  file  --  RFINTF.C ------------------
//           C-interface functions
//--------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "refalab.h"
#include "rfintf.h"
#include "rfrun.h"

T_REFAL refal;

static T_LINKCB *last_block = NULL;
static bool rf_init = true;
static T_LINKCB hd;

static bool lgcl(void);
static void rflist(T_LINKCB *par, size_t n);

void rfabe(const char *amsg)
{
    printf(" *** refal-abend *** %s\n", amsg);
    exit(1);
    return;
}

bool lincrm(void)
{
    size_t n = 0;
    if (last_block != NULL)
    {
        const T_LINKCB *first_free = refal.flhead->next;
        const bool was_coll = lgcl();
        if (was_coll)
        {
            const T_LINKCB *p = refal.flhead->next;
            n = 0;
            while (p != first_free && n != 1000)
            {
                n++;
                p = p->next;
            }
            if (n == 1000)
                return true;
        }
    }
    T_LINKCB *new_block = malloc(1001 * sizeof(T_LINKCB));
#ifdef mdebug
    fprintf(stderr, "lincrm: n=%zu after new_block=%p\n", n, (void *)new_block);
#endif
    if (new_block == NULL)
        return false;
    new_block->prev = last_block;
    last_block = new_block;
    rflist(new_block + 1, 1000);
    return true;
}

//  check a number of items in free items list
bool lrqlk(size_t l)
{
    const T_LINKCB *p = refal.flhead;
    for (size_t n = 0; n < l; n++)
    {
        p = p->next;
        if (p == refal.flhead)
            return false;
    }
    return true;
}

bool lins(T_LINKCB *p, size_t l)
{
    if (l < 1)
        return true;
    T_LINKCB *q1 = refal.flhead;
    for (size_t n = 0; n < l; n++)
    {
        q1 = q1->next;
        if (q1 == refal.flhead)
            return false;
        q1->tag = TAGO;
        q1->info.codep = NULL;
    }
    T_LINKCB *r = q1->next;
    T_LINKCB *q = refal.flhead->next;
    refal.flhead->next = r;
    r->prev = refal.flhead;
    T_LINKCB *p1 = p->next;
    q1->next = p1;
    p1->prev = q1;
    p->next = q;
    q->prev = p;
    return true;
}

bool slins(T_LINKCB *p, size_t k)
{
    while (!lrqlk(k))
        if (!lincrm())
        {
            refal.upshot = 3;
            return false;
        }
    return lins(p, k);
}

bool linskd(T_ST *ast, uint8_t *f)
{
    if (!lexist(ast))
        rfabe("linskd: process doesn't exist still");
    if (ast->dot != NULL)
        rfabe("linskd: there are '<'-signes in view field");
    if (!slins(ast->view, 3))
        return false;
    T_LINKCB *p = ast->view->next;
    T_LINKCB *r = p->next;
    T_LINKCB *q = ast->view->prev;
    p->tag = TAGK;
    q->tag = TAGD;
    q->info.codep = p;
    r->tag = TAGF;
    r->info.codef = f;
    ast->dot = q;
    return true;
}

void rfinit(void)
{
    rf_init = false;
    T_REFAL *p = &refal;
    p->crprev = (T_ST *)&refal;
    p->crnext = (T_ST *)&refal;
    p->upshot = 1;
    p->currst = NULL;
    p->svar = NULL;
    p->dvar = NULL;
    p->flhead = &hd;
    T_LINKCB *phd = &hd;
    phd->prev = phd;
    phd->next = phd;
    phd->tag = TAGO;
    phd->info.codep = NULL;
    p->tm.mode = true;
    if (p->tm.mode)
        timespec_get(&p->tm.start, TIME_UTC);
    return;
}

void rfcanc(const T_ST *ast)
{
    if (rf_init)
        rfinit();
    if (!lexist(ast))
        rfabe("rfcanc: process doesn't exist");
    if (ast->state == 4)
        rfabe("rfcanc: process is in job yet");
    ast->stprev->stnext = ast->stnext;
    ast->stnext->stprev = ast->stprev;
    T_LINKCB *flhead1 = refal.flhead->prev;
    T_LINKCB *view1 = ast->view->prev;
    T_LINKCB *store1 = ast->store->prev;
    flhead1->next = ast->view;
    ast->view->prev = flhead1;
    view1->next = ast->store;
    ast->store->prev = view1;
    store1->next = refal.flhead;
    refal.flhead->prev = store1;
    return;
}

//    delete part of list and add it to free memory list
void rfdel(T_LINKCB *p, T_LINKCB *q)
{
    T_LINKCB *p1 = p->next;
    if (p1 == q)
        return;
    T_LINKCB *q1 = q->prev;
    T_LINKCB *r = refal.flhead->prev;
    p->next = q;
    q->prev = p;
    q1->next = refal.flhead;
    refal.flhead->prev = q1;
    r->next = p1;
    p1->prev = r;
    return;
}

void rftermm(void)
{
    while (last_block != NULL)
    {
        T_LINKCB *new_block = last_block;
        last_block = new_block->prev;
#ifdef mdebug
        fprintf(stderr, "lincrm: free new_block=%p\n", (void *)new_block);
#endif
        free(new_block);
    }
}

void rfexec(uint8_t *func)
{
    T_ST s_st;
    if (rf_init)
        rfinit();
    bool lack = false;
    if (!lincrm())
        lack = true;
    else if (!lcre(&s_st))
        lack = true;
    else if (!linskd(&s_st, func))
        lack = true;
    if (lack)
    {
        printf("\nNo enough memory for initialization\n");
        rftermm();
        return;
    }
    s_st.stop = MAX_STOP;
#ifdef mdebug
    const uint32_t s_stop = s_st.stop;
#endif
    enum
    {
        AGAIN,
        DONE,
        ABEND,
        EOJ,
        RET
    } ex_state = AGAIN;
    while (true)
        switch (ex_state)
        {
        case AGAIN:
#ifdef mdebug
            //	step by step execution with full debug trace information
            if (s_st.dot == NULL)
            {
                ex_state = DONE;
                break;
            }
            if (s_st.state != 1 || s_st.step >= s_stop)
            {
                bool go = false;
                if (s_st.state == 3)
                    if (lincrm())
                        go = true;
                if (s_st.step >= s_stop)
                {
                    s_st.step = 0;
                    go = true;
                }
                if (!go)
                {
                    ex_state = ABEND;
                    break;
                }
            }
            s_st.stop = s_st.step + 1;
            const T_LINKCB *pk = s_st.dot->info.codep;
            const T_LINKCB *prevk = pk->prev;
            const T_LINKCB *nextd = s_st.dot->next;
            printf(" Step: %d\n", s_st.stop);
            rfpexm(" Term: ", prevk, nextd, true);
            rfrun(&s_st);
            if (s_st.state == 1)
                rfpexm(" Result: ", prevk, nextd, true);
            break;
#else
            // no debug info
            rfrun(&s_st);
            if (s_st.state == 3)
                if (lincrm())
                    break;
            if (s_st.state == 1 && s_st.dot != NULL)
            {
                s_st.step = 0;
                break;
            }
            if (s_st.dot != NULL)
            {
                ex_state = ABEND;
                break;
            }
            ex_state = DONE;
            break;
#endif
        case DONE:
#ifdef mdebug
            printf("Concretization is executed\n");
            ex_state = EOJ;
#else
            ex_state = RET;
#endif
            break;
        case ABEND:
            switch (s_st.state)
            {
            case 2:
                printf("Recognition impossible\n");
                break;
            case 3:
                printf("Free memory exhausted\n");
            }
            ex_state = EOJ;
            break;
        case EOJ:
            printf("Total steps number = %u\n", s_st.step);
            if (s_st.view->next != s_st.view)
            {
                printf("View field:\n");
                rfpexm("            ", s_st.view, s_st.view, true);
            }
            if (s_st.store->next != s_st.store)
            {
                printf("Burried:\n");
                rfpexm("         ", s_st.store, s_st.store, true);
            }
            if (refal.tm.mode)
            {
                timespec_get(&refal.tm.stop, TIME_UTC);
                int32_t in = (int32_t)(refal.tm.stop.tv_nsec - refal.tm.start.tv_nsec);
                uint32_t is = (uint32_t)difftime(refal.tm.stop.tv_sec, refal.tm.start.tv_sec);
                if (in < 0)
                {
                    in += 1000000000;
                    is--;
                }
                uint32_t im = is / 60;
                is %= 60;
                const uint32_t ih = im / 60;
                im %= 60;
                char s[30];
                sprintf(s, "%02u:%02u:%02u.%09d", ih, im, is, in);
                printf("Elapsed time = %s\n", s);
            }
            ex_state = RET;
            break;
        case RET:
            rfcanc(&s_st);
            rftermm();
            return;
        }
}

void rfpex(const char *pt, const T_LINKCB *pr, const T_LINKCB *pn, const bool nl)
{
    printf("%s", pt);
    while (pr != pn->prev)
    {
        const T_LINKCB *pr1 = pr;
        pr = pr->next;
        if (pr1 != pr->prev)
            rfabe("\nrfpex: list structure violation");
        if (pr->tag == TAGO)
            putchar(pr->info.infoc);
        else if (pr->tag == TAGK)
            putchar('<');
        else if (pr->tag == TAGD)
            putchar('>');
        else if (pr->tag == TAGLB)
            putchar('(');
        else if (pr->tag == TAGRB)
            putchar(')');
        else if (pr->tag == TAGN)
            printf("'%u'", gcoden(pr));
        else if (pr->tag == TAGF)
        {
            putchar('\'');
            const char *f = (char *)(pr->info.codef) - 1;
            const uint8_t l = (uint8_t)*f;
            f -= l;
            for (size_t k = 1; k <= l; k++, f++)
                putchar(toupper(*f));
            putchar('\'');
        }
        else if (pr->tag == TAGR)
            printf("'%%%p'", (void *)pr->info.codep);
        else if ((pr->tag & 0001) != TAGO)
            rfabe("\nrfpex: unknown bracket type");
        else
            printf("'%x,%p'", pr->tag, (void *)pr->info.codep);
    }
    if (nl)
        printf("\n");
    return;
}

void rfpexs(const char *pt, const T_LINKCB *pr, const T_LINKCB *pn, const bool nl)
{
    printf("%s", pt);
    while (pr != pn->prev)
    {
        const T_LINKCB *pr1 = pr;
        pr = pr->next;
        if (pr1 != pr->prev)
            rfabe("\nrfpexs: list structure violation");
        if (pr->tag == TAGO)
            putchar(pr->info.infoc);
        else if (pr->tag == TAGK)
            putchar('<');
        else if (pr->tag == TAGD)
            putchar('>');
        else if (pr->tag == TAGLB)
            putchar('(');
        else if (pr->tag == TAGRB)
            putchar(')');
        else if (pr->tag == TAGN)
            printf("%u", gcoden(pr));
        else if (pr->tag == TAGF)
        {
            const char *f = (char *)(pr->info.codef) - 1;
            const uint8_t l = (uint8_t)*f;
            f -= l;
            for (size_t k = 1; k <= l; k++, f++)
                putchar(toupper(*f));
        }
        else if (pr->tag == TAGR)
            printf("%%%p", (void *)pr->info.codep);
        else if ((pr->tag & 0001) != TAGO)
            rfabe("\nrfpexs: unknown bracket type");
        else
            printf("%x,%p", pr->tag, (void *)pr->info.codep);
    }
    if (nl)
        printf("\n");
    return;
}

void rfpexm(const char *pt, const T_LINKCB *pr, const T_LINKCB *pn, const bool nl)
{
    printf("%s", pt);
    bool fr = false;
    while (pr != pn->prev)
    {
        const T_LINKCB *pr1 = pr;
        pr = pr->next;
        if (pr->prev != pr1)
            rfabe("\nrfpexm: list structure violation");
        if (pr->tag == TAGO)
        {
            if (!fr)
            {
                fr = true;
                putchar('\'');
            };
            putchar(pr->info.infoc);
        }
        else
        {
            if (fr)
            {
                fr = false;
                putchar('\'');
            };
            if (pr->tag == TAGK)
                printf("< ");
            else if (pr->tag == TAGD)
                putchar('>');
            else if (pr->tag == TAGLB)
                putchar('(');
            else if (pr->tag == TAGRB)
                putchar(')');
            else if (pr->tag == TAGN)
            {
                printf("%u", gcoden(pr));
                if (pr->next->tag == TAGN)
                    putchar(' ');
            }
            else if (pr->tag == TAGF)
            {
                putchar('&');
                const char *f = (char *)(pr->info.codef) - 1;
                const uint8_t l = (uint8_t)*f;
                f -= l;
                for (size_t k = 1; k <= l; k++, f++)
                    putchar(toupper(*f));
                if (pr->next->tag == TAGN)
                    putchar(' ');
            }
            else if (pr->tag == TAGR)
                printf("/%%%p/", (void *)pr->info.codep);
            else if ((pr->tag & 0001) != TAGO)
                rfabe("\nrfpexm: unknown bracket type");
            else
                printf("/%x,%p/", pr->tag, (void *)pr->info.codep);
        }
    }
    if (fr)
        putchar('\'');
    if (nl)
        printf("\n");
    return;
}

void rftpl(T_LINKCB *r, T_LINKCB *p, T_LINKCB *q)
{
    T_LINKCB *p1 = p->next;
    if (p1 == q)
        return;
    T_LINKCB *r1 = r->next;
    T_LINKCB *q1 = q->prev;
    p->next = q;
    q->prev = p;
    q1->next = r1;
    r1->prev = q1;
    r->next = p1;
    p1->prev = r;
    return;
}

//  copy expression and add it to nessecary place
bool lcopy(T_LINKCB *r, const T_LINKCB *p, const T_LINKCB *q)
{
    T_LINKCB *f = refal.flhead;
    T_LINKCB *f0 = p->next;
    T_LINKCB *f1, *lastb = NULL;
    while (f0 != q)
    {
        f = f->next;
        if (f == refal.flhead)
            return false;
        switch (f0->tag)
        {
        case TAGLB:
            f->info.codep = lastb;
            lastb = f;
            break;
        case TAGRB:
            f->info.codep = lastb;
            f->tag = TAGRB;
            f1 = lastb->info.codep;
            lastb->info.codep = f;
            lastb->tag = TAGLB;
            lastb = f1;
            break;
        default:
            f->tag = f0->tag;
            f->info.codep = f0->info.codep;
        }
        f0 = f0->next;
    }
    if (refal.flhead == f)
        return true;
    f0 = refal.flhead->next;
    f1 = f->next;
    refal.flhead->next = f1;
    f1->prev = refal.flhead;
    T_LINKCB *r1 = r->next;
    f->next = r1;
    r1->prev = f;
    r->next = f0;
    f0->prev = r;
    return true;
}

bool lexist(const T_ST *ast)
{
    const T_REFAL *p = &refal;
    do
    {
        p = (T_REFAL *)(p->crnext);
        if (p == (T_REFAL *)ast)
            return true;
    } while (p != &refal);
    return false;
}

bool lcre(T_ST *ast)
{
    if (rf_init)
        rfinit();
    if (lexist(ast))
        rfabe("lcre: process already exists");
    ast->view = refal.flhead->next;
    if (ast->view == refal.flhead)
        return false;
    ast->store = ast->view->next;
    if (ast->store == refal.flhead)
        return false;
    T_LINKCB *flhead1 = ast->store->next;
    refal.flhead->next = flhead1;
    flhead1->prev = refal.flhead;
    ast->view->next = ast->view;
    ast->view->prev = ast->view;
    ast->store->next = ast->store;
    ast->store->prev = ast->store;
    T_ST *q = refal.crprev;
    ast->stnext = (T_ST *)&refal;
    refal.crprev = ast;
    q->stnext = ast;
    ast->stprev = q;
    ast->state = 1;
    ast->dot = NULL;
    ast->step = 0;
    ast->stop = MAX_STOP;
    return true;
}

static void mark(T_LINKCB *root)
{
    T_LINKCB *p = root;
    T_LINKCB *h = p;
    while (true)
    {
        T_LINKCB *q;
        if (p->next != h)
        {
            p = p->next;
            if (p->tag != TAGR)
                continue;
            q = p->info.codep;
            if (q->tag != TAGO)
                continue;
            q->tag = 0xFFFF;
            p->info.codep = h;
            q->prev = p;
            p = q;
            h = p;
            continue;
        }
        if (h == root)
            return;
        q = h->prev;
        h->prev = p;
        T_LINKCB *r = h;
        h = q->info.codep;
        q->info.codep = r;
        q->tag = TAGR;
        p = q;
    }
}

static bool lgcl(void)
{
    T_LINKCB hdvar;
    T_LINKCB *hdp = &hdvar;
    if (refal.dvar == NULL)
        return false;
    // mark boxes achieved from view field & burriage
    bool was_coll = false;
    const T_LINKCB *pzero = NULL;
    const T_ST *p = refal.crnext;
    while (p != (T_ST *)&refal)
    {
        mark(p->view);
        mark(p->store);
        p = p->stnext;
    }
    // mark boxes achieved from static boxes
    if (refal.svar != NULL)
    {
        T_LINKCB *r = refal.svar;
        do
        {
            mark(r);
            r = r->info.codep;
        } while (r != pzero);
        //   remove garbage
        hdp->info.codep = refal.dvar;
        T_LINKCB *p1 = hdp;
        T_LINKCB *q = refal.dvar;
        do
        {
            if (q->tag != TAGO)
            { // box isn't removed
                q->tag = TAGO;
                p1 = q;
            }
            else
            { // remove box
                was_coll = true;
                p1->info.codep = q->info.codep;
                p1->tag = q->tag;
                r = q->prev;
                T_LINKCB *flhead1 = refal.flhead->next;
                r->next = flhead1;
                flhead1->prev = r;
                refal.flhead->next = q;
                q->prev = refal.flhead;
            }
            q = p1->info.codep;
        } while (q != pzero);
        if (hdp->info.codep == pzero)
            refal.dvar = NULL;
        else
            refal.dvar = hdp->info.codep;
    }
    return was_coll;
}

static void rflist(T_LINKCB *par, size_t n)
{
    if (rf_init)
        rfinit();
    T_LINKCB *q = par;
    T_LINKCB *p = refal.flhead->prev;
    for (size_t k = 0; k < n; k++)
    {
        p->next = q;
        q->prev = p;
        q->tag = TAGO;
        q->info.codep = NULL;
        p = q;
        q++;
    }
    p->next = refal.flhead;
    refal.flhead->prev = p;
    return;
}

T_LINKCB *lldupl(const T_LINKCB *p, const T_LINKCB *q, const T_LINKCB *u)
{
    const T_LINKCB *x = p->next;
    T_LINKCB *y = u->next;
    while (x != q)
    {
        if (x->tag != y->tag)
            return NULL;
        if (x->info.codep != y->info.codep)
            if (x->tag != TAGLB && x->tag != TAGRB)
                return NULL;
        x = x->next;
        y = y->next;
    }
    return y;
}

//----------- end of file  RFINTF.C ------------
