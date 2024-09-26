
//-------------- file -- XMO.C -------------
//                 General MO:
//     p1, m1, numb, symb, first, last,
//     lengr, lengw, multe, crel, delf
//------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "refal.def"
#include "rfintf.h"

static void p1_(void)
{
    T_LINKCB *p = refal.preva->next;
    uint32_t l;
    bool neot = false;
    if (p->next != refal.nexta || p->tag != TAGN)
        neot = true;
    else
    {

        l = gcoden(p) + 1;
        if (l > 16777215)
            neot = true;
    }
    if (neot)
    {
        refal.upshot = 2;
        return;
    }
    pcoden(p, l);
    rftpl(refal.prevr, p->prev, p->next);
    return;
}
void (*p1_1)(void) = p1_;
G_L_B char p1 = '\122';
char p1_0[] = {Z2 'P', '1', '\002'};

static void m1_(void)
{
    T_LINKCB *p = refal.preva->next;
    int32_t l;
    bool neot = false;
    if (p->next != refal.nexta || p->tag != TAGN)
        neot = true;
    else
    {
        l = (int32_t)gcoden(p) - 1;
        if (l < 0)
            neot = true;
    }
    if (neot)
    {
        refal.upshot = 2;
        return;
    }
    pcoden(p, (uint32_t)l);
    rftpl(refal.prevr, p->prev, p->next);
    return;
}
void (*m1_1)(void) = m1_;
G_L_B char m1 = '\122';
char m1_0[] = {Z2 'M', '1', '\002'};

/*static int32_t cmpstr(size_t n, const char *s1, const char *s2)
{
    // comparison two string . if s1<s2 then return < 0
    // if s1 = s2 return 0. if s1>s2 then return > 0
    for (size_t i = 0; i < n; i++, s1++, s2++)
        if (*s1 != *s2)
            return *s1 - *s2;
    return 0;
}*/

static void numb_(void)
{
    T_LINKCB *p = refal.preva->next;
    const char zn = p->info.infoc;
    const T_LINKCB *pz = p;
    if (p->tag == TAGO && (zn == '-' || zn == '+'))
    {
        p = p->next;
        if (zn == '+')
            pz = p;
    }
    T_LINKCB *pp = p;
    while (p->tag == TAGO && p->info.infoc == '0')
        p = p->next;
    char str[12];
    size_t i;
    bool neot = false;
    for (i = 0; p != refal.nexta; i++)
    {
        if (p->tag != TAGO || i == 11)
        {
            neot = true;
            break;
        }
        str[i] = p->info.infoc;
        if (str[i] < '0' || str[i] > '9')
        {
            neot = true;
            break;
        }
        if (i == 9 && strncmp(str, "2147483647", i + 1) > 0)
        {
            neot = true;
            break;
        }
        p = p->next;
    }
    if (neot)
    {
        refal.upshot = 2;
        return;
    }
    str[i] = '\0';
    if (strlen(str) == 0)
    {
        if (!slins(refal.nexta->prev, 1))
            return;
        pp = refal.nexta->prev;
        pz = pp;
    }
    uint32_t l = (uint32_t)atol(str);
    pp->tag = TAGN;
    if (l > 16777215)
    {
        pcoden(pp, l >> 24);
        pp = pp->next;
        pp->tag = TAGN;
        l &= 0xffffff;
    }
    pcoden(pp, l);
    rftpl(refal.prevr, pz->prev, pp->next);
    return;
}
void (*numb_1)(void) = numb_;
G_L_B char numb = '\122';
char numb_0[] = {Z4 'N', 'U', 'M', 'B', '\004'};

static void symb_(void)
{
    T_LINKCB *p = refal.preva->next;
    const char zn = p->info.infoc;
    T_LINKCB *pz = p;
    if (p->tag == TAGO && (zn == '-' || zn == '+'))
    {
        p = p->next;
        if (zn == '+')
            pz = p;
    }
    T_LINKCB *pp = p;
    while (p->tag == TAGN && gcoden(p) == 0)
        p = p->next;
    size_t i;
    bool neot = false;
    for (i = 0; p != refal.nexta; i++, p = p->next)
        if (p->tag != TAGN || i == 2)
        {
            neot = true;
            break;
        }
    if (!neot)
    {
        p = p->prev;
        if (i == 2 && gcoden(pp) >= 128)
            neot = true;
    }
    if (neot)
    {
        refal.upshot = 2;
        return;
    }
    uint32_t l = gcoden(p);
    if (i == 2)
        l += 16777216 * gcoden(pp);
    if (i == 0 || l == 0)
    {
        pz = pp;
        l = 0;
    }
    char str[12];
    sprintf(str, "%u", l);
    const size_t j = strlen(str);
    if (!lrqlk(j))
        if (!lincrm())
        {
            refal.upshot = 3;
            return;
        }
    if (pz != refal.nexta)
        lins(pp, j);
    else
    {
        pz = pz->prev;
        lins(pz, j);
        pz = pz->next;
        pp = pz;
    }
    for (i = 0, p = pp; i < j; i++, p = p->next)
    {
        p->tag = TAGO;
        p->info.codep = NULL;
        p->info.infoc = str[i];
    }
    rftpl(refal.prevr, pz->prev, p);
    return;
}
void (*symb_1)(void) = symb_;
G_L_B char symb = '\122';
char symb_0[] = {Z4 'S', 'Y', 'M', 'B', '\004'};

static void first_(void)
{
    T_LINKCB *pn = refal.preva->next;
    if (pn == refal.nexta || pn->tag != TAGN)
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    const uint32_t n = gcoden(pn); // eg
    T_LINKCB *p = pn;
    for (size_t k = 1; k <= n; k++)
    {
        p = p->next;
        if (p == refal.nexta)
        {
            pn->info.codep = NULL;
            pn->info.infoc = '*';
            pn->tag = TAGO;
            rftpl(refal.prevr, refal.preva, refal.nexta);
            return;
        }
        if (p->tag == TAGLB)
            p = p->info.codep;
    }
    p = p->next;
    refal.preva->tag = TAGLB;
    refal.preva->info.codep = pn;
    pn->tag = TAGRB;
    pn->info.codep = refal.preva;
    rftpl(refal.preva, pn, p);
    rftpl(refal.prevr, refal.nextr, refal.nexta);
    return;
}
void (*first_1)(void) = first_;
G_L_B char first = '\122';
char first_0[] = {Z5 'F', 'I', 'R', 'S', 'T', '\005'};

static void last_(void)
{
    T_LINKCB *pn = refal.preva->next;
    if (pn == refal.nexta || pn->tag != TAGN)
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    const uint32_t n = gcoden(pn); // eg
    T_LINKCB *p = refal.nexta;
    for (size_t k = 1; k <= n; k++)
    {
        p = p->prev;
        if (p == pn)
        {
            pn->tag = TAGO;
            pn->info.codep = NULL;
            pn->info.infoc = '*';
            rftpl(refal.prevr, pn, refal.nexta);
            p = refal.nextr->prev;
            rftpl(p, refal.preva, refal.nexta);
            return;
        }
        if (p->tag == TAGRB)
            p = p->info.codep;
    }
    p = p->prev;
    refal.preva->tag = TAGLB;
    refal.preva->info.codep = pn;
    pn->tag = TAGRB;
    pn->info.codep = refal.preva;
    rftpl(refal.preva, p, refal.nexta);
    rftpl(refal.prevr, pn, refal.nexta);
    p = refal.nextr->prev;
    rftpl(p, refal.nextr, refal.nexta);
    return;
}
void (*last_1)(void) = last_;
G_L_B char last = '\122';
char last_0[] = {Z4 'L', 'A', 'S', 'T', '\004'};

static void lengr_(void)
{
    uint32_t n = 0; // kras
    const T_LINKCB *p = refal.preva->next;
    while (p != refal.nexta)
    {
        n++;
        p = p->next;
    }
    refal.preva->tag = TAGN;
    pcoden(refal.preva, n);
    rftpl(refal.prevr, refal.nextr, refal.nexta);
    return;
}
void (*lengr_1)(void) = lengr_;
G_L_B char lengr = '\122';
char lengr_0[] = {Z5 'L', 'E', 'N', 'G', 'R', '\005'};

static void lengw_(void)
{
    uint32_t n = 0; // kras
    const T_LINKCB *p = refal.preva->next;
    while (p != refal.nexta)
    {
        n++;
        if (p->tag == TAGLB)
            p = p->info.codep;
        p = p->next;
    }
    refal.preva->tag = TAGN;
    pcoden(refal.preva, n);
    rftpl(refal.prevr, refal.nextr, refal.nexta);
    return;
}
void (*lengw_1)(void) = lengw_;
G_L_B char lengw = '\122';
char lengw_0[] = {Z5 'L', 'E', 'N', 'G', 'W', '\005'};

static void multe_(void)
{
    const T_LINKCB *pn = refal.preva->next;
    if (pn == refal.nexta || pn->tag != TAGN)
    {
        refal.upshot = 2;
        return;
    }; // FAIL
    uint32_t n = gcoden(pn);
    if (n == 0)
        return;
    T_LINKCB *p = pn->next;
    if (p == refal.nexta)
        return;
    if (p->next != refal.nexta)
    {
        do
        {
            p = refal.nextr->prev;
            if (!lcopy(p, pn, refal.nexta))
            {
                refal.upshot = 3;
                return;
            }; // LACK
            n--;
        } while (n >= 1);
    }
    else
    {
        if (!slins(refal.prevr, n))
            return; //  LACK
        T_LINKCB *q = refal.prevr;
        for (uint32_t k = 0; k < n; k++)
        {
            q = q->next;
            q->tag = p->tag;
            pcoden(q, gcoden(p));
        }
    }
    return;
}
void (*multe_1)(void) = multe_;
G_L_B char multe = '\122';
char multe_0[] = {Z5 'M', 'U', 'L', 'T', 'E', '\005'};

static void delf_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    } // FAIL
    const T_LINKCB *dot = refal.nexta;
    const T_LINKCB *dot1 = refal.nextr->info.codep;
    const T_LINKCB *sk;
    T_LINKCB *nd;
    while (true)
    {
        sk = dot->info.codep;
        if (sk == NULL)
            rfabe("delf: sign '#' missing ");
        dot = sk->info.codep;
        nd = dot->next;
        if (nd->info.infoc != '#')
            continue;
        break;
    }
    while (dot1 != dot)
    {
        sk = dot1->info.codep;
        nd = sk->info.codep;
        rfdel(sk->prev, dot1->next);
        dot1 = nd;
    }
    sk = dot1->info.codep;
    nd = sk->info.codep;
    dot1 = dot1->next;
    rfdel(sk->prev, dot1->next);
    refal.nextr->info.codep = nd;
    return;
}
void (*delf_1)(void) = delf_;
G_L_B char delf = '\122';
char delf_0[] = {Z4 'D', 'E', 'L', 'F', '\004'};

static void crel_(void)
{
    T_LINKCB *p = refal.preva->next;
    do
    {
        if (p->tag != TAGLB)
            break;
        const T_LINKCB *pp = p->info.codep;
        p = p->next;
        T_LINKCB *q = pp->next;
        const T_LINKCB *q1 = refal.nexta;
        char c = '=';
        bool fail = false;
        for (; c == '=' && p != pp && q != q1; p = p->next, q = q->next)
        {
            if (p->tag == TAGLB)
            {
                if (q->tag != TAGLB)
                    fail = true;
                break;
            }
            if (p->tag == TAGRB)
            {
                if (q->tag != TAGRB)
                    fail = true;
                break;
            }
            if (p->info.coden < q->info.coden)
                c = '<';
            if (p->info.coden > q->info.coden)
                c = '>';
        }
        if (fail)
            break;
        if (p == pp && q != q1)
            c = '<';
        if (q == q1 && p != pp)
            c = '>';
        for (; p != pp; p = p->next)
            if (p->tag == TAGLB)
            {
                fail = true;
                break;
            }
        if (fail)
            break;
        for (; q != q1; q = q->next)
            if (q->tag == TAGLB)
            {
                fail = true;
                break;
            }
        if (fail)
            break;
        p = refal.preva->next;
        p->tag = TAGO;
        p->info.codep = NULL;
        p->info.infoc = c;
        q = p->next;
        rftpl(refal.prevr, refal.preva, q);
        return;
    } while (false);
    refal.upshot = 2;
    return;
}
void (*crel_1)(void) = crel_;
G_L_B char crel = '\122';
char crel_0[] = {Z4 'C', 'R', 'E', 'L', '\004'};

//-------------------- end of file  XMO.C ----------------
