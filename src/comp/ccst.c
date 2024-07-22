//----------   file  CCST1.C  --------------
//      Compiler file
//      Last edition date : 11.07.24
//------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "refal.def"
#include "ccst.h"
#include "cerr.h"
#include "cs.h"
#include "cgop.h"
#include "cj.h"
#include "refal.h"

#define t_sc 1
#define t_lb 2
#define t_rb 3
#define t_s 4
#define t_w 5
#define t_e 6
#define t_k 7
#define t_p 8

static struct
{ // left part buffer elements
    uint16_t p, q, t, ind;
    T_LINKTI code;
    uint16_t next;
    uint16_t pair;
    T_LINKTI spec;
    uint16_t v;
    uint16_t eoemrk;
    uint16_t e_level;
} x[100];

// ???whole list
static struct
{ // ???variable table elements
    uint16_t _t, _q;
    uint16_t rem;
    uint16_t last;
    char ci;
    uint16_t _v;
} v[50];

// ???variable table elements
static struct
{
    uint16_t _next;
    uint16_t n1, n2;
} h[30];

static T_LINKTI xncode;  // work structure
static T_LINKTI funcptr; // work pointer

static uint16_t n, n1, n2;     // left part element pointers
static uint16_t ind, ie;       // element index
static uint16_t nel;           // current element number
static uint16_t e_level;       // counter of the longing levels
static uint16_t not_nil;       // working variables
static uint16_t nh;            // current whole number
static uint16_t kol_per;       // subprogram of search in variable table
                               // table pointer
static uint16_t nh_x, nh_y;    // hole numbers (under enter in brackets)
static uint16_t lrbxy;         // stoped bracket flag
static uint16_t lastb, lastb1; // variables for brackets linkage
static uint16_t kol_lit;       // counter of the symbol number
static uint16_t diff_e_level;
static unsigned int kol_skob[100]; // stack for counting of the brackets balance
static unsigned int ur_skob;
static char buf_lit[80]; // buffer for generating of the "text" statement
static uint16_t k;
static uint16_t fh;      // free segment number in the whole  list
static uint16_t next_nh; // next whole number

static void isk_v();
static void gen_bsb();
static void comp_error();
static void pch300();
static void pch303();
static void pch406();
static bool lsg_p();
static bool rsg_p();
static bool ortgn(uint16_t n1, uint16_t n2);
static void gpev(char op1, char op2);

// read left part
// and full array X
void cst(bool dir, char *lbl, unsigned int lblleng)
// dir;     matching feature :left to right or otherwise
// lbl;   sentence label
// lblleng; sentence label length
{
    kol_per = 0;
    n = 0;
    lastb = 0;
    nel = 0;
    while (true)
    { // read left part element
        n++;
        scan();
        x[n].t = scn_e.t;
        x[n].code.tag = scn_e.code.tag;
        x[n].code.info.codef = scn_e.code.info.codef;
        x[n].spec.tag = scn_e.spec.tag;
        x[n].spec.info.codef = scn_e.spec.info.codef;
        x[n].v = scn_e.v;
        x[n].next = 0;
        x[n].pair = 0;
        x[n].eoemrk = 0;
        x[n].e_level = 0;
        bool rcg = false;
        switch (scn_e.t)
        {
        case 0:
            // scanner error
            fndef(lbl, lblleng);
            pch300();
            return;
        case 1:
            // constant symbol
            nel++;
            break;
        case 2:
            // left bracket
            nel++;
            x[n].pair = lastb;
            lastb = n;
            break;
        case 3:
            // right bracket
            if (lastb == 0)
            {
                pchosh("302 too many ')' in left part");
                n--;
            }
            else
            {
                nel++;
                lastb1 = x[lastb].pair;
                x[lastb].pair = n;
                x[n].pair = lastb;
                lastb = lastb1;
            }
            break;
        case 4:
            // s-varyable
            isk_v();
            x[n].ind = ind;
            switch (v[ind]._t)
            {
            case 0:
                v[ind]._t = 1; // yet isn't faced
                break;
            case 1:
                ++(v[ind].rem); // next position
                break;
            default: // invalid type pointer
                pch303();
                n--;
            }
            nel++;
            break;
        case 5:
            // w-varyable
            isk_v();
            x[n].ind = ind;
            switch (v[ind]._t)
            {
            case 0:
                v[ind]._t = 2; // yet isn't faced
                break;
            case 2:
                ++(v[ind].rem); // next position
                break;
            default: // invalid type pointer
                pch303();
                n--;
            }
            nel += 2;
            break;
        case 6:
            // e- or v-varyable
            isk_v();
            x[n].ind = ind;
            if (v[ind]._t == 0) // yet is't faced
                v[ind]._t = 3;
            else if ((v[ind]._t == 3) && (v[ind]._v == scn_e.v))
                ++(v[ind].rem);
            else // invalid type pointer
            {
                pch303();
                n--;
            };
            nel += 2;
            break;
        case 7:
            // sign 'k'
            pchosh("306 sign 'k' in left part");
            n--;
            break;
        case 8:
            // sign '.'
            pchosh("307 sign '.' in left part");
            n--;
            break;
        case 9:
            // left part end
            if (lastb == 0)
            {
                rcg = true;
                break;
            }
            pchosh("301 too many '(' in left part");
            fndef(lbl, lblleng);
            pch300();
            return;
        case 10:
            // sentence end
            pchosh("304 under left part default sign '=' ");
            fndef(lbl, lblleng);
            return;
        default:
            // scanner error
            fndef(lbl, lblleng);
            pch300();
            return;
        }
        if (rcg)
            break;
        // end of element processing
        if (nel <= 252)
            continue;
        pchosh("305 very large left part");
        fndef(lbl, lblleng);
        pch300();
        return;
    }
    //--------------------------------------------
    //         left part compilation
    //--------------------------------------------
    fndef(lbl, lblleng);
    n1 = 0;
    n2 = n;
    nel = 4;
    x[n1].p = x[n1].q = 3;
    x[n2].p = x[n2].q = 2;
    h[28]._next = 0;
    nh = 1;
    h[1]._next = 28;
    fh = 2;
    e_level = 0;
    if (dir)
        goto RCGL;
    else
        goto RCGR;

    //    hard element projection from left part of current hole

RCGL:
    n = n1 + 1;
    if (n == n2)
        goto NIL;
    switch (x[n].t)
    {
    case 1:
        //        constant symbol
        if (x[n].code.tag == TAGO)
        {
            kol_lit = 1;
            while (true)
            {
                n++;
                if ((n == n2) || (x[n].t != t_sc) || (x[n].code.tag != TAGO))
                {
                    if (kol_lit == 1)
                    {
                        n = n1 + 1;
                        gopn(n_lsco, x[n].code.info.infoc[0]);
                        goto L1;
                    }
                    n = n1;
                    gopn(n_ltxt, (char)kol_lit);
                    while (true)
                    {
                        n++;
                        jbyte(x[n].code.info.infoc[0]);
                        x[n].p = x[n].q = nel;
                        nel++;
                        kol_lit--;
                        if (kol_lit != 0)
                            continue;
                        break;
                    }
                    n1 = n;
                    goto RCGL;
                }
                kol_lit++;
            }
        }
        gops(n_lsc, &x[n].code);
        goto L1;
    case 2:
        //  left bracket
        n1 = n;
        n = x[n1].pair;
        if (n1 + 1 == n)
        {
            jbyte(n_lbnil);
            x[n1].p = x[n1].q = nel;
            n1 = n;
            x[n1].p = x[n1].q = nel + 1;
            nel += 2;
            goto RCGL;
        }
        if (n1 + 2 != n)
            goto GEN_LB;
        n = n1 + 1;
        if (x[n].t != t_e)
            goto GEN_LB;
        ind = x[n].ind;
        if (v[ind].last != 0)
            goto GEN_LB;
        nel += 2;
        jbyte(n_lbce);
        v[ind]._q = nel + 1;
        x[n].next = v[ind].last;
        v[ind].last = n;
        (v[ind].rem)--;
        if (x[n].v != 0)
            jbyte(n_nnil);
        if (x[n].spec.info.codef != NULL)
            gopl(n_espc, x[n].spec.info.codef);
        x[n].p = nel;
        x[n].q = nel + 1;
        nel += 2;
        x[n1].p = x[n1].q = nel - 4;
        n1 += 2;
        x[n1].p = x[n1].q = nel - 3;
        goto RCGL;
    case 3:
        //                      place of compiler's error
        comp_error();
        return;
    case 4:
        //    s-variable
        ind = x[n].ind;
        if (v[ind].last != 0)
            gopn(n_lsd, (char)v[ind]._q);
        else
        {
            jbyte(n_ls);
            v[ind]._q = nel;
        };
        goto LSMD;
    case 5:
        //   w-variable
        ind = x[n].ind;
        if (v[ind].last != 0)
            goto LED;
        jbyte(n_lw);
        v[ind]._q = nel + 1;
        x[n].next = v[ind].last;
        v[ind].last = n;
        (v[ind].rem)--;
        if (x[n].spec.info.codef != NULL)
            gopl(n_wspc, x[n].spec.info.codef);
        goto L2;
    case 6:
        //   e-variable
        ind = x[n].ind;
        if (v[ind].last != 0)
            goto LED;
        if (dir)
            goto RCGR;
        if (n + 1 == n2)
            goto CE;
        else
            goto IMPASSE;
    };
LSMD:
    x[n].next = v[ind].last;
    v[ind].last = n;
    (v[ind].rem)--;
    if (x[n].spec.info.codef != NULL)
        gopl(n_wspc, x[n].spec.info.codef);
    goto L1;
L1:
    x[n].p = x[n].q = nel;
    nel++;
    n1 = n;
    goto RCGL;
LED:
    gopn(n_led, (char)v[ind]._q);
    goto LEMD;
LEMD:
    x[n].next = v[ind].last;
    v[ind].last = n;
    (v[ind].rem)--;
    if (x[n].spec.info.codef != NULL)
        gopl(n_espc, x[n].spec.info.codef);
    goto L2;
L2:
    x[n].p = nel;
    x[n].q = nel + 1;
    nel += 2;
    n1 = n;
    goto RCGL;
GEN_LB:
    n = n1;
    lrbxy = 1;
    goto LB1;
LB1:
    if (dir)
    {
        nh_x = nh;
        nh_y = fh;
    }
    else
    {
        nh_x = fh;
        nh_y = nh;
    };
    h[fh]._next = h[nh]._next;
    h[nh]._next = fh;
    fh++;
    n1 = n;
    n = n2;
    n2 = x[n1].pair;
    nh = nh_x;
    h[nh_y].n1 = n2;
    h[nh_y].n2 = n;
    x[n1].p = x[n1].q = nel;
    x[n2].p = x[n2].q = nel + 1;
    nel += 2;
    goto HSCH;

    //                 hard element projection
    //                 from  right board of
    //                    current hole

RCGR:
    n = n2 - 1;
    if (n == n1)
        goto NIL;
    switch (x[n].t)
    {
    case 1:
        //   constant symbol
        if (x[n].code.tag == TAGO)
        {
            kol_lit = 1;
            while (true)
            {
                n--;
                if ((n == n1) || (x[n].t != t_sc) || (x[n].code.tag != TAGO))
                {
                    if (kol_lit == 1)
                    {
                        n = n2 - 1;
                        gopn(n_rsco, x[n].code.info.infoc[0]);
                        goto R1;
                    }
                    n = n2;
                    gopn(n_rtxt, (char)kol_lit);
                    while (true)
                    {
                        n--;
                        jbyte(x[n].code.info.infoc[0]);
                        x[n].p = x[n].q = nel;
                        nel++;
                        kol_lit--;
                        if (kol_lit != 0)
                            continue;
                        break;
                    }
                    n2 = n;
                    goto RCGR;
                }
                kol_lit++;
            }
        }
        gops(n_rsc, &x[n].code);
        goto R1;
    case 2:
        //                      place of compiler's error
        comp_error();
        return;
    case 3:
        //     right bracket
        n2 = n;
        n = x[n2].pair;
        if (n + 1 == n2)
        {
            jbyte(n_rbnil);
            x[n2].p = x[n2].q = nel + 1;
            n2 = n;
            x[n2].p = x[n2].q = nel;
            nel += 2;
            goto RCGR;
        }
        if (n + 2 != n2)
            goto GEN_RB;
        n = n2 - 1;
        if (x[n].t != t_e)
            goto GEN_RB;
        ind = x[n].ind;
        if (v[ind].last != 0)
            goto GEN_RB;
        nel += 2;
        jbyte(n_rbce);
        v[ind]._q = nel + 1;
        x[n].next = v[ind].last;
        v[ind].last = n;
        (v[ind].rem)--;
        if (x[n].v != 0)
            jbyte(n_nnil);
        if (x[n].spec.info.codef != NULL)
            gopl(n_espc, x[n].spec.info.codef);
        x[n].p = nel;
        x[n].q = nel + 1;
        nel += 2;
        x[n2].p = x[n2].q = nel - 3;
        n2 -= 2;
        x[n2].p = x[n2].q = nel - 4;
        goto RCGR;
    case 4:
        //     s_variable
        ind = x[n].ind;
        if (v[ind].last != 0)
            gopn(n_rsd, (char)v[ind]._q);
        else
        {
            jbyte(n_rs);
            v[ind]._q = nel;
        };
        goto RSMD;
    case 5:
        //    w_variable
        ind = x[n].ind;
        if (v[ind].last != 0)
            goto RED;
        jbyte(n_rw);
        v[ind]._q = nel + 1;
        x[n].next = v[ind].last;
        v[ind].last = n;
        (v[ind].rem)--;
        if (x[n].spec.info.codef != NULL)
            gopl(n_wspc, x[n].spec.info.codef);
        goto R2;
    case 6:
        //    e-variable
        ind = x[n].ind;
        if (v[ind].last != 0)
            goto RED;
        if (!dir)
            goto RCGL;
        if (n1 + 1 == n)
            goto CE;
        else
            goto IMPASSE;
    };
RSMD:
    x[n].next = v[ind].last;
    v[ind].last = n;
    (v[ind].rem)--;
    if (x[n].spec.info.codef != NULL)
        gopl(n_wspc, x[n].spec.info.codef);
    goto R1;
R1:
    x[n].p = x[n].q = nel;
    nel++;
    n2 = n;
    goto RCGR;
RED:
    gopn(n_red, (char)v[ind]._q);
    goto REMD;
REMD:
    x[n].next = v[ind].last;
    v[ind].last = n;
    (v[ind].rem)--;
    if (x[n].spec.info.codef != NULL)
        gopl(n_espc, x[n].spec.info.codef);
    goto R2;
R2:
    x[n].p = nel;
    x[n].q = nel + 1;
    nel += 2;
    n2 = n;
    goto RCGR;
GEN_RB:
    n = n2;
    lrbxy = 2;
    goto RB1;
RB1:
    if (!dir)
    {
        nh_x = nh;
        nh_y = fh;
    }
    else
    {
        nh_x = fh;
        nh_y = nh;
    };
    h[fh]._next = h[nh]._next;
    h[nh]._next = fh;
    fh++;
    n2 = n;
    n = n1;
    n1 = x[n2].pair;
    nh = nh_x;
    h[nh_y].n1 = n;
    h[nh_y].n2 = n1;
    x[n1].p = x[n1].q = nel;
    x[n2].p = x[n2].q = nel + 1;
    nel += 2;
    goto HSCH;
NIL: //     empty hole
    jbyte(n_nil);
    next_nh = h[nh]._next;
    h[nh]._next = h[next_nh]._next;
    h[nh].n1 = h[next_nh].n1;
    h[nh].n2 = h[next_nh].n2;
    nh = next_nh;
    goto IMPASSE;
CE: //   closed including
    if (x[n].eoemrk != 0)
        goto IMPASSE;
    goto CE1;
CE1:
    if (x[n].spec.info.codef == NULL)
    {
        ind = x[n].ind;
        v[ind]._q = nel + 1;
        jbyte(n_ce);
        x[n].next = v[ind].last;
        v[ind].last = n;
        (v[ind].rem)--;
        if (x[n].v == 1)
            jbyte(n_nnil);
        x[n].p = nel;
        x[n].q = nel + 1;
        nel += 2;
        next_nh = h[nh]._next;
        h[nh]._next = h[next_nh]._next;
        h[nh].n1 = h[next_nh].n1;
        h[nh].n2 = h[next_nh].n2;
        nh = next_nh;
        goto IMPASSE;
    }
    if (dir)
        goto LMAX;
    else
        goto RMAX;

//
//          It is impossible movement
//          on hard element here or
//          hole ended here
IMPASSE:
    lrbxy = 0;
    nh_x = nh;
    goto HSCH;
//          Search of hole with hard
//          elements on its boards.
//          If it not exist than project
//          e-variable from first hole.
HSCH:
    h[nh].n1 = n1;
    h[nh].n2 = n2;
    nh = 1;
    if (h[nh]._next == 0)
        goto RCGFIN;
    goto NHOLE;
NHOLE:
    n1 = h[nh].n1;
    n2 = h[nh].n2;
    n = n1 + 1;
    if (n == n2)
    {
        gen_bsb();
        goto NIL;
    };
    if (x[n].t != t_e)
        goto RIGID;
    ind = x[n].ind;
    if (v[ind].last != 0)
        goto RIGID;
    if (n + 1 == n2)
    {
        if (v[ind].rem == 1)
            goto NHOLE1;
        gen_bsb();
        goto CE1;
    };
    n = n2 - 1;
    if (x[n].t != t_e)
        goto RIGID;
    ind = x[n].ind;
    if (v[ind].last != 0)
        goto RIGID;
    goto NHOLE1;
NHOLE1:
    nh = h[nh]._next;
    if (h[nh]._next == 0)
    {
        //  opened e_variable processing
        nh = 1;
        n1 = h[nh].n1;
        n2 = h[nh].n2;
        gen_bsb();
        if (dir)
            n = n1 + 1;
        else
            n = n2 - 1;
        ind = x[n].ind;
        if (x[n].eoemrk)
        {
            diff_e_level = e_level - x[n].e_level;
            if (diff_e_level == 1)
                jbyte(n_eoei);
            else
                gopn(n_eoe, (char)diff_e_level);
            e_level = x[n].e_level;
            x[n].eoemrk = 0;
            x[n].e_level = 0;
        };
        if (n1 + 2 == n2)
            goto CE1;
        if (dir)
            n = n2 - 1;
        else
            n = n1 + 1;
        if (x[n].spec.info.codef == NULL)
            goto OE1;
        while (true)
        {
            ind = x[n].ind;
            if ((v[ind].last != 0) || (v[ind].rem != 1))
                goto OE1;
            if (dir)
            {
                n--;
                if (n == n1)
                {
                    n = n2 - 1;
                    ind = x[n].ind;
                    goto RMAX;
                }
            }
            else
            {
                n++;
                if (n == n2)
                {
                    n = n1 + 1;
                    ind = x[n].ind;
                    goto LMAX;
                }
            };
            if ((x[n].t != t_e) || (x[n].v == 1))
                goto OE1;
        }
    }
    else
        goto NHOLE;
RIGID: //  hard element on the both hole boards
    gen_bsb();
    if (dir)
        goto RCGL;
    else
        goto RCGR;
RMAX:
    gopl(n_rmax, x[n].spec.info.codef);
    if (x[n].v == 1)
        jbyte(n_nnil);
    x[n].spec.info.codef = NULL;
    v[ind]._q = nel + 1;
    goto REMD;
LMAX:
    gopl(n_lmax, x[n].spec.info.codef);
    if (x[n].v == 1)
        jbyte(n_nnil);
    x[n].spec.info.codef = NULL;
    v[ind]._q = nel + 1;
    goto LEMD;
OE1:
    if (dir)
    {
        n = n1 + 1;
        ie = x[n].ind;
        //         attempt to extract left support group
        if (lsg_p())
        {
            n = n1 + 1;
            switch (x[n].t)
            {
            case 1:
                //  ei 'a' . . .
                xncode.tag = x[n].code.tag;
                xncode.info.codef = x[n].code.info.codef;
                n++;
                if ((not_nil == 0) && (x[n].eoemrk == 1))
                {
                    x[n].eoemrk = 0;
                    x[n].e_level = 0;
                    e_level--;
                    gops(n_lsrch, &xncode);
                }
                else
                {
                    gpev(n_plesc, n_plvsc);
                    gops(n_lesc, &xncode);
                };
                n--;
                goto L1;
            case 2:
                //   ei ( . . . ) . . .
                gpev(n_pleb, n_plvb);
                jbyte(n_leb);
                lrbxy = 0;
                goto LB1;
            case 3:
                //                 place compiler error
                comp_error();
                return;
            case 4:
                //  ei sj . . .
                ind = x[n].ind;
                if (v[ind].last == 0)
                    goto LE;
                gpev(n_plesc, n_plvsc);
                gopn(n_lesd, (char)v[ind]._q);
                goto LSMD;
            case 5:
            case 6:
                //  ei . . .
                goto LE;
            };
        }
        else
            goto RCGL;
    }
    else
    {
        n = n2 - 1;
        ie = x[n].ind;
        //                 attempt to extract right support group
        if (rsg_p())
        {
            n = n2 - 1;
            switch (x[n].t)
            {
            case 1:
                //    . . .  'a' ei
                xncode.tag = x[n].code.tag;
                xncode.info.codef = x[n].code.info.codef;
                n--;
                if ((not_nil == 0) && (x[n].eoemrk == 1))
                {
                    x[n].eoemrk = 0;
                    x[n].e_level = 0;
                    e_level--;
                    gops(n_rsrch, &xncode);
                }
                else
                {
                    gpev(n_presc, n_prvsc);
                    gops(n_resc, &xncode);
                };
                n++;
                goto R1;
            case 2:
                //                 place compiler error
                comp_error();
                return;
            case 3:
                // . . .  ( . . .  ) ei
                gpev(n_preb, n_prvb);
                jbyte(n_reb);
                lrbxy = 0;
                goto RB1;
            case 4:
                //  . . . sj ei
                ind = x[n].ind;
                if (v[ind].last == 0)
                    goto RE;
                gpev(n_presc, n_prvsc);
                gopn(n_resd, (char)v[ind]._q);
                goto RSMD;
            case 5:
            case 6:
                // . . .  ei
                goto RE;
            };
        }
        else
            goto RCGR;
    }
LE:
    gpev(n_ple, n_plv);
    jbyte(n_le);
    goto RCGL;
RE:
    gpev(n_pre, n_prv);
    jbyte(n_re);
    goto RCGR;
    //                 identification end
RCGFIN:
    jbyte(n_eor);

    //--------------------------------------------
    //         right part compilation
    //--------------------------------------------

    ur_skob = 1;
    kol_skob[ur_skob] = 0;

    //  read next element of right part

GET_RPE:
    scan();
    goto SW_RPE;
SW_RPE:
    switch (scn_e.t)
    {
    case 0:
        // scanner error
        pch300();
        return;
    case 1:
        goto RPE1;
    case 2:
        goto RPE2;
    case 3:
        goto RPE3;
    case 4:
        goto RPE4;
    case 5:
        goto RPE5;
    case 6:
        goto RPE6;
    case 7:
        goto RPE7;
    case 8:
        goto RPE8;
    case 9:
        goto RPE9;
    case 10:
        goto RPE10;
    default:
        // scanner error
        pch300();
        return;
    };
RPE1: // symbol-constant
    if (scn_e.code.tag == TAGO)
        goto TEXT;
    gops(n_ns, &scn_e.code);
    goto GET_RPE;
TEXT:
    kol_lit = 0;
    goto TEXT1;
TEXT1:
    kol_lit++;
    buf_lit[kol_lit] = scn_e.code.info.infoc[0];
    scan();
    if ((kol_lit < 80) && (scn_e.t == t_sc) && (scn_e.code.tag == TAGO))
        goto TEXT1;
    if (kol_lit == 1)
        gopn(n_nso, buf_lit[1]);
    else
    {
        gopn(n_text, kol_lit);
        for (k = 1; k <= kol_lit; k++)
            jbyte(buf_lit[k]);
    };
    goto SW_RPE;
RPE2: // left bracket
    scan();
    if (scn_e.t == t_rb)
    {
        jbyte(n_blr);
        goto GET_RPE;
    };
    kol_skob[ur_skob]++;
    if ((scn_e.t == t_sc) && (scn_e.code.tag == TAGF))
    {
        funcptr.info.codef = scn_e.code.info.codef;
        gopl(n_blf, funcptr.info.codef);
        goto GET_RPE;
    }
    else
    {
        jbyte(n_bl);
        goto SW_RPE;
    };
RPE3: // right bracket
    jbyte(n_br);
    if (kol_skob[ur_skob] == 0)
        pchosh("402 too many ')' in right part");
    else
        kol_skob[ur_skob]--;
    goto GET_RPE;
RPE4: // s - varyable
    isk_v();
    switch (v[ind]._t)
    {
    case 0:
        pch406();
        break;
    case 1:
        gopn(n_muls, v[ind]._q);
        break;
    default:
        pch303();
    };
    goto GET_RPE;
RPE5: // w - varyable
    isk_v();
    switch (v[ind]._t)
    {
    case 0:
        pch406();
        break;
    case 2:
        n = v[ind].last;
        if (n == 0)
            gopn(n_mule, v[ind]._q);
        else
        {
            gopn(n_tplv, x[n].q);
            v[ind].last = x[n].next;
        };
        break;
    default:
        pch303();
    };
    goto GET_RPE;
RPE6: // e- or v-varyable
    isk_v();
    if (v[ind]._t == 0)
        pch406();
    else if ((v[ind]._t == 3) && (v[ind]._v == scn_e.v))
    {
        n = v[ind].last;
        if (n == 0)
            gopn(n_mule, v[ind]._q);
        else
        {
            if (v[ind]._v == 1)
                gopn(n_tplv, x[n].q);
            else
                gopn(n_tple, x[n].q);
            v[ind].last = x[n].next;
        };
    }
    else
        pch303();
    goto GET_RPE;
RPE7: // sign "k"
    if (ur_skob > 511)
    {
        pchosh("407 including of the signs 'k' > 511");
        pch300();
        return;
    };
    kol_skob[++ur_skob] = 0;
    scan();
    if ((scn_e.t == t_sc) && (scn_e.code.tag == TAGF))
    {
        funcptr.info.codef = scn_e.code.info.codef;
        funcptr.tag = 0;
        gopl(n_blf, funcptr.info.codef);
        goto GET_RPE;
    }
    else
    {
        jbyte(n_bl);
        goto SW_RPE;
    };
RPE8: // sign '.'
    if (ur_skob == 1)
        pchosh("404 too many sign '.' in right part");
    else
    {
        if (kol_skob[ur_skob] != 0)
            pchosh("401 too many '(' in right part");
        jbyte(n_bract);
        ur_skob--;
    };
    goto GET_RPE;
RPE9: // sign '=' in right part
    pchosh("405 sign '=' in right part");
    goto GET_RPE;
RPE10: // sentence end
    scn_.curr_stmnmb++;
    if (options.stmnmb == 1)
    {
        jbyte(n_eossn);
        ghw(scn_.curr_stmnmb);
    }
    else
        jbyte(n_eos);
    if (ur_skob != 1)
        pchosh("403 too many signs 'k' in right part");
    if (kol_skob[ur_skob] != 0)
        pchosh("401 too many '(' in right part");
    return;
}

static void isk_v()
{
    for (ind = 1; ind <= kol_per; ind++)
        if (v[ind].ci == scn_e.ci)
            return;
    ind = ++kol_per;
    v[ind].ci = scn_e.ci;
    v[ind]._t = 0;
    v[ind].rem = 1;
    v[ind].last = 0;
    v[ind]._v = scn_e.v;
    return;
}

//   generation of stoped brackets and setting boards
static void gen_bsb()
{
    switch (lrbxy)
    {
    case 0: // no stoped brackets
        if (nh != nh_x)
            break;
        return;
    case 1: // left stoped brackets
        if (nh == nh_x)
            jbyte(n_lb);
        else if (nh == nh_y)
            jbyte(n_lby);
        else
        {
            jbyte(n_lb);
            break;
        };
        return;
    case 2: // right stoped brackets
        if (nh == nh_x)
            jbyte(n_rb);
        else if (nh == nh_y)
            jbyte(n_rby);
        else
        {
            jbyte(n_rb);
            break;
        };
        return;
    };
    gopnm(n_sb1b2, (char)x[n1].q, (char)x[n2].p);
    return;
}

static void comp_error()
{
    //                      place of compiler's error
    printf("Compiler's error\n");
    exit(1);
    return;
}

static void pch300()
{
    pchosh("300 sentence is't scanned");
    return;
}

static void pch303()
{
    pchosa("303 differents for variable ", v[ind].ci);
    return;
}

static void pch406()
{
    pchosa("406 in left part missing variable ", v[ind].ci);
    return;
}

//    attempt to extract left support group
static bool lsg_p()
{
    while (true)
    {
        n++;
        if (n == n2)
            break;
        if (x[n].t != t_lb)
        {
            if (x[n].t != t_e)
                continue;
            ind = x[n].ind;
            if ((ind == ie) || (v[ind].last != 0))
                continue;
            if ((x[n].spec.info.codef != NULL) || (v[ind].rem != 1))
                break;
            if (!ortgn(n1, n))
                break;
            x[n].eoemrk = 1;
            x[n].e_level = e_level;
            break;
        }
        n = x[n].pair;
    }
    n1++;
    n = n1;
    ind = x[n].ind;
    v[ind]._q = nel + 1;
    x[n].next = v[ind].last;
    v[ind].last = n;
    (v[ind].rem)--;
    x[n].p = nel;
    x[n].q = nel + 1;
    nel += 2;
    e_level++;
    not_nil = x[n].v;
    if (x[n].spec.info.codef == NULL)
        return true;
    gpev(n_plespc, n_plv);
    gopl(n_lespc, x[n].spec.info.codef);
    return false;
}

//        attempt to extract right support group
static bool rsg_p()
{
    while (true)
    {
        n--;
        if (n == n1)
            break;
        if (x[n].t != t_rb)
        {
            if (x[n].t != t_e)
                continue;
            ind = x[n].ind;
            if ((ind == ie) || (v[ind].last != 0))
                continue;
            if ((x[n].spec.info.codef != NULL) ||
                (v[ind].rem != 1))
                break;
            if (!ortgn(n, n2))
                break;
            x[n].eoemrk = 1;
            x[n].e_level = e_level;
            break;
        }
        n = x[n].pair;
    }
    n2--;
    n = n2;
    ind = x[n].ind;
    v[ind]._q = nel + 1;
    x[n].next = v[ind].last;
    v[ind].last = n;
    (v[ind].rem)--;
    x[n].p = nel;
    x[n].q = nel + 1;
    nel += 2;
    e_level++;
    not_nil = x[n].v;
    if (x[n].spec.info.codef == NULL)
        return true;
    gpev(n_prespc, n_prv);
    gopl(n_respc, x[n].spec.info.codef);
    return false;
}

//    check ortogonality of this sentence against left part
static bool ortgn(uint16_t n1, uint16_t n2)
{
    uint16_t n = n1;
    uint16_t i;
    while (true)
    {
        n++;
        if (n == n2)
            break;
        if (x[n].t <= 3)
            continue;
        i = x[n].ind;
        if (v[i].last != 0)
            continue;
        (v[i].rem)--;
    }
    bool res = true;
    n = n1;
    while (true)
    {
        n++;
        if (n == n2)
            break;
        if (x[n].t <= 3)
            continue;
        i = x[n].ind;
        if (v[i].last != 0)
            continue;
        if (v[i].rem == 0)
            continue;
        res = false;
        break;
    };
    n = n1;
    while (true)
    {
        n++;
        if (n == n2)
            break;
        if (x[n].t <= 3)
            continue;
        i = x[n].ind;
        if (v[i].last != 0)
            continue;
        (v[i].rem)++;
    }
    return res;
}

static void gpev(char op1, char op2)
{
    if (not_nil)
        jbyte(op2);
    else
        jbyte(op1);
}