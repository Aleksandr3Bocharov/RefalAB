// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-03-18
// https://github.com/Aleksandr3Bocharov/RefalAB

//-------------- file -- XIO.C ------------
//           MO: input/output
//-----------------------------------------

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "refalab.h"
#include "rfintf.h"

static void card_(void)
{
    if (refal.preva->next != refal.nexta)
        rfpex("", refal.preva, refal.nexta);
    T_LINKCB *p = refal.prevr;
    int c = getchar();
    while (c != '\n')
    {
        if  (!slins(p, 1))
            return;
        p = p->next;
        p->info.codep = NULL;
        if (c == EOF)
        {
            p->tag = TAGN;
            return;
        }
        p->tag = TAGO;
        p->info.infoc = (char)c;
        c = getchar();
    }
    return;
}
char card_0[] = {Z4 'C', 'A', 'R', 'D', (char)4};
G_L_B uint8_t refalab_card = '\122';
void (*card_1)(void) = card_;

static void pr1_(void)
{
    rfpex("", refal.preva, refal.nexta);
    rftpl(refal.prevr, refal.preva, refal.nexta);
    return;
}
char pr1_0[] = {Z5 'P', 'R', 'I', 'N', 'T', (char)5};
G_L_B uint8_t refalab_print = '\122';
void (*pr1_1)(void) = pr1_;

static void pr2_(void)
{
    rfpexm("", refal.preva, refal.nexta);
    rftpl(refal.prevr, refal.preva, refal.nexta);
    return;
}
char pr2_0[] = {Z6 'P', 'R', 'I', 'N', 'T', 'M', (char)6};
G_L_B uint8_t refalab_printm = '\122';
void (*pr2_1)(void) = pr2_;

static void pr3_(void)
{
    rfpex("", refal.preva, refal.nexta);
    return;
}
char pr3_0[] = {Z5 'P', 'R', 'O', 'U', 'T', (char)5};
G_L_B uint8_t refalab_prout = '\122';
void (*pr3_1)(void) = pr3_;

static void pr4_(void)
{
    rfpexm("", refal.preva, refal.nexta);
    return;
}
char pr4_0[] = {Z6 'P', 'R', 'O', 'U', 'T', 'M', (char)6};
G_L_B uint8_t refalab_proutm = '\122';
void (*pr4_1)(void) = pr4_;

//------------------ end of file  XIO.C ----------------
