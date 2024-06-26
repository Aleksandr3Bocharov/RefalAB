#ifndef REFAL_H
#define REFAL_H

#include "cgop.h"

extern struct
{ /* compiling   options */
    unsigned int source : 1;
    unsigned int mincomp : 1;
    unsigned int stmnmb : 1;
    unsigned int extname : 1;
    unsigned int multmod : 1;
    unsigned int asmb : 1;
    unsigned int names : 1;
} options;

extern struct
{ /* the table for corresponding with scanner */
    unsigned int nomkar;
    char modname_var[40]; /* module name */ /*  !!! */
    unsigned int modnmlen;                  /* module name length */
    unsigned int curr_stmnmb;
} scn_;

extern struct
{                         /* current statement element */
    unsigned short int t; /*    element type           */
    char ci;              /*    variable index         */
    unsigned int v;
    struct linkti code;
    struct linkti spec;
} scn_e;

extern FILE *sysprint, *systerm;
extern FILE *syslin; /* for assem */
extern FILE *systxt; /* for module names */

extern unsigned short int nommod;
extern char parm_i[]; /* sourse file name */
extern char vers_i[]; /* compiler version */
extern char mod_i[];  /* module name      */

extern void oshibka();
extern void scan();

#endif