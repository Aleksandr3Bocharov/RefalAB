// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-04-14
// https://github.com/Aleksandr3Bocharov/RefalAB

//-----------  file  --  REFAL.H -------------
//      The main file of RefalAB compiler
//--------------------------------------------

#ifndef REFAL_H
#define REFAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "cgop.h"

#define MAX_ID_LEN 40
#define MAX_EXT_ID_LEN 32

typedef struct opt_
{ // compiling   options
    bool source;
    bool extname;
    bool names;
} T_OPT;

extern T_OPT options;

typedef struct scn_
{ // the table for corresponding with scanner
    uint32_t nomkar;
    char modname_var[MAX_ID_LEN]; // module name
    size_t modnmlen;              // module name length
} T_SCN;

extern T_SCN scn_;

typedef struct scn_e_
{                        // current statement element
    uint32_t t;          //    element type
    char si[MAX_ID_LEN]; //    variable idenfifier
    size_t si_leng;      // variable identifier length
    bool v;
    T_LINKTI code;
    T_LINKTI spec;
} T_SCN_E;

extern T_SCN_E scn_e;

extern FILE *sysprint, *systerm;
extern FILE *syslin; // for assem
extern FILE *systxt; // for module names

extern uint32_t nommod;

extern void oshibka(void);
extern void scan(void);

#endif
