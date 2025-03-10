// Copyright 2024 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2024-10-19
// https://github.com/Aleksandr3Bocharov/RefalAB

//----------- file RFRUN2.H -----------------
//      Refal-interpretator (part 2)
//-------------------------------------------

#ifndef RFRUN2_H
#define RFRUN2_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "refal.def"

typedef struct wjs
{ // jump stack structure  
    T_LINKCB *jsb1;
    T_LINKCB *jsb2;
    size_t jsnel;
    uint8_t *jsvpc;
} T_WJS;

typedef struct ts
{ // translation stack structure 
    T_LINKCB *ts0;
    T_LINKCB *ts1;
    T_LINKCB *ts2;
} T_TS;

typedef struct spcs
{
    bool spls;
    uint8_t *svpc;
} T_SPCS;

extern void link(T_LINKCB *x, T_LINKCB *y);
extern bool spc(T_SPCS *pspcsp, const uint8_t *vpc, const T_LINKCB *b);

extern void getjs(const T_WJS *jsp, T_LINKCB **ab1, T_LINKCB **ab2, size_t *anel, uint8_t **avpc);
extern void putjs(T_WJS *jsp, T_LINKCB **ab1, T_LINKCB **ab2, const size_t *anel, uint8_t **avpc);
extern void getts(const T_TS *tsp, T_LINKCB **ax, T_LINKCB **ay, T_LINKCB **az);
extern void putts(T_TS *tsp, T_LINKCB **ax, T_LINKCB **ay, T_LINKCB **az);

#endif
