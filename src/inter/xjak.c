//-------------- file -- XJAK.C ------------
//       MO: br, dg, dgall, rp, cp
//           gtr, rdr, wtr, swr, new
//      Last edition date : 11.07.2024
//------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "refal.def"
#include "rfintf.h"

#define N_SWAP 0116

static bool enter(bool emp, T_LINKCB **pp, T_LINKCB **rp)
{
    T_LINKCB *r = refal.preva->next;
    if (r == refal.nexta)
        return false;
    if (emp && (r->next != refal.nexta))
        return true;
    T_LINKCB *p;
    if (r->tag == TAGR)
        p = r->info.codep;
    else if (r->tag == TAGF)
    {
        const uint8_t *q = r->info.codef;
        if (*q != N_SWAP)
            return false;
        q++;
        p = (T_LINKCB *)q; // eg
        if (p->prev == NULL)
        {
            p->prev = p->next = p;
            p->info.codep = refal.svar;
            p->tag = 0;
            refal.svar = p;
        }
    }
    else
        return false;
    *pp = p;
    *rp = r;
    return true;
}

static void br_()
{
    const T_ST *ast = refal.currst;
    const T_LINKCB *p = refal.preva;
    while ((p->tag != TAGO) || (p->info.infoc != '='))
    {
        p = p->next;
        if (p == refal.nexta)
        {
            refal.upshot = 2;
            return;
        }; // FAIL
    }
    if (!lins(ast->store, 2))
    {
        refal.upshot = 3;
        return;
    }; // LACK
    T_LINKCB *pl = ast->store->next;
    T_LINKCB *pr = pl->next;
    pl->info.codep = pr;
    pl->tag = TAGLB;
    pr->info.codep = pl;
    pr->tag = TAGRB;
    rftpl(pl, refal.preva, refal.nexta);
    return;
}
void (*br_1)() = br_;
G_L_B char br = '\122';
char br_0[] = {Z2 'B', 'R', '\002'};

static void dg_()
{
    const T_ST *ast = refal.currst;
    T_LINKCB *pr = ast->store;
    T_LINKCB *q, *pl;
    while (true)
    {
        pl = pr->next;
        if (pl == ast->store)
            return;
        if (pl->tag != TAGLB)
        {
            refal.upshot = 2;
            return;
        }; // FAIL
        pr = pl->info.codep;
        q = lldupl(refal.preva, refal.nexta, pl);
        if (q == NULL)
            continue;
        if ((q->tag != TAGO) || (q->info.infoc != '='))
            continue;
        break;
    }
    rftpl(refal.prevr, q, pr);
    pl = pl->prev;
    pr = pr->next;
    rfdel(pl, pr);
    return;
}
void (*dg_1)() = dg_;
G_L_B char dg = '\122';
char dg_0[] = {Z2 'D', 'G', '\002'};

static void dgall_()
{
    const T_ST *ast = refal.currst;
    if (refal.preva->next != refal.nexta)
        refal.upshot = 2; // FAIL
    else
        rftpl(refal.prevr, ast->store, ast->store);
    return;
}
void (*dgal_1)() = dgall_;
G_L_B char dgall = '\122';
char dgal_0[] = {Z5 'D', 'G', 'A', 'L', 'L', '\005'};

static void gtr_()
{
    const bool emp = true;
    T_LINKCB *p = NULL, *r;
    if (!enter(emp, &p, &r))
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    rftpl(refal.prevr, p, p);
    return;
}
void (*gtr_1)() = gtr_;
G_L_B char gtr = '\122';
char gtr_0[] = {Z3 'G', 'T', 'R', '\003'};

static void rdr_()
{
    const bool emp = true;
    T_LINKCB *p = NULL, *r;
    if (!enter(emp, &p, &r))
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    if (!lcopy(refal.prevr, p, p))
    {
        refal.upshot = 3;
        return;
    }; // LACK
    return;
}
void (*rdr_1)() = rdr_;
G_L_B char rdr = '\122';
char rdr_0[] = {Z3 'R', 'D', 'R', '\003'};

static void ptr_()
{
    const bool emp = false;
    T_LINKCB *p, *r;
    if (!enter(emp, &p, &r))
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    T_LINKCB *q = p->prev;
    rftpl(q, r, refal.nexta);
    return;
}
// BLF
#ifdef UNIX
void (*ptr_1)() = ptr_;
G_L_B char pt_ = '\122';
char ptr_0[] = {Z3 'P', 'T', '_', '\003'};
#else
void (*ptr_1)() = ptr_;
G_L_B char ptr = '\122';
char ptr_0[] = {Z3 'P', 'T', 'R', '\003'};
#endif

static void wtr_()
{
    const bool emp = false;
    T_LINKCB *p, *r;
    if (!enter(emp, &p, &r))
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    rfdel(p, p);
    rftpl(p, r, refal.nexta);
    return;
}
void (*wtr_1)() = wtr_;
G_L_B char wtr = '\122';
char wtr_0[] = {Z3 'W', 'T', 'R', '\003'};

static void swr_()
{
    const bool emp = false;
    T_LINKCB *p, *r;
    if (!enter(emp, &p, &r))
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    rftpl(refal.prevr, p, p);
    rftpl(p, r, refal.nexta);
    return;
}
void (*swr_1)() = swr_;
G_L_B char swr = '\122';
char swr_0[] = {Z3 'S', 'W', 'R', '\003'};

static void rp_()
{
    const T_ST *ast = refal.currst;
    T_LINKCB *p = refal.preva;
    bool fail = false;
    while ((p->tag != TAGO) || (p->info.infoc != '='))
    {
        p = p->next;
        if (p == refal.nexta)
        {
            fail = true;
            break;
        }
    };
    if (!fail)
    {
        T_LINKCB *pr = ast->store;
        while (true)
        {
            T_LINKCB *pl = pr->next;
            if (pl == ast->store)
            {
                if (!lins(ast->store, 2))
                {
                    refal.upshot = 3;
                    return;
                }; // LACK
                pl = ast->store->next;
                pr = pl->next;
                pl->info.codep = pr;
                pl->tag = TAGLB;
                pr->info.codep = pl;
                pr->tag = TAGRB;
                rftpl(pl, refal.preva, refal.nexta);
            }
            else
            {
                if (pl->tag != TAGLB)
                    break;
                pr = pl->info.codep;
                T_LINKCB *q = lldupl(refal.preva, p, pl);
                if (q == NULL)
                    continue;
                if ((q->tag != TAGO) || (q->info.infoc != '='))
                    continue;
                rfdel(q, pr);
                rftpl(q, p, refal.nexta);
            }
            return;
        }
    }
    refal.upshot = 2;
    return;
}

// BLF
#ifdef UNIX
void (*rp_1)() = rp_;
G_L_B char r_ = '\122';
char rp_0[] = {Z2 'R', '_', '\002'};
#else
void (*rp_1)() = rp_;
G_L_B char rp = '\122';
char rp_0[] = {Z2 'R', 'P', '\002'};
#endif

static void cp_()
{
    const T_ST *ast = refal.currst;
    const T_LINKCB *pr = ast->store;
    const T_LINKCB *q;
    while (true)
    {
        const T_LINKCB *pl = pr->next;
        if (pl == ast->store)
            return;
        if (pl->tag != TAGLB)
        {
            refal.upshot = 2;
            return;
        }; // FAIL
        pr = pl->info.codep;
        q = lldupl(refal.preva, refal.nexta, pl);
        if (q == NULL)
            continue;
        if ((q->tag != TAGO) || (q->info.infoc != '='))
            continue;
        break;
    }
    if (!lcopy(refal.prevr, q, pr))
        refal.upshot = 3; // LACK
    return;
}
void (*cp_1)() = cp_;
G_L_B char cp = '\122';
char cp_0[] = {Z2 'C', 'P', '\002'};

static void new_()
{
    if (!lins(refal.prevr, 1))
    {
        refal.upshot = 3;
        return;
    }; // LACK
    T_LINKCB *r = refal.prevr->next;
    r->info.codep = refal.preva;
    r->tag = TAGR;
    T_LINKCB *p = refal.nexta->prev;
    p->next = refal.preva;
    refal.preva->prev = p;
    refal.nextr->next = refal.nexta;
    refal.nexta->prev = refal.nextr;
    refal.preva->info.codep = refal.dvar;
    refal.preva->tag = 0;
    refal.dvar = refal.preva;
    return;
}
void (*new_1)() = new_;
G_L_B char new = '\122';
char new_0[] = {Z3 'N', 'E', 'W', '\003'};

//----------------- end of file  XJAK.C ----------------
