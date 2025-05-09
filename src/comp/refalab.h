// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2024-04-28
// https://github.com/Aleksandr3Bocharov/RefalAB

//--------------- file -- REFALAB.H -----------------
//          Compiler version
//---------------------------------------------------

#ifndef REFALAB_H
#define REFALAB_H

#include <stdint.h>

#define TAGO 0
#define TAGF 2
#define TAGN 4
#define TAGR 6
#define TAGLB 1
#define TAGRB 3
#define TAGK 5
#define TAGD 7

#define Wbin "wb"
#define Rbin "rb"

#define ZBLL sizeof(uint16_t)
#define LBLL sizeof(void *)
#define SMBL (ZBLL + LBLL)

#define MAX_NUMBER 0xFFFFFF

#endif

//-------  end of file REFALAB.H ---------
