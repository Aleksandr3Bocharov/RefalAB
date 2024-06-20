/*------------ file -- D.H--------------------*/
/*       Definitions for REFAL-Debugger       */
/*        Last modification : 19.06.24        */
/*--------------------------------------------*/
#ifndef D_H
#define D_H

#include "refal.def"

typedef struct DET_TAB
{
    struct DET_TAB *det_next;
    char gt;
    char ge;
    char eq;
    char ne;
    char lt;
    char le;
    char tr;
    char *det_id;
} DET_TAB;
static DET_TAB *last_det = NULL;
static DET_TAB *det_table;
static DET_TAB dummy_det_table = {NULL, 0, 0, 0, 0, 0, 0, 0, NULL};

static short trace_cond = 0;
static short trap_cond = 0;
static short ge_all = 1;
static short eq_all = 1;
static short e1empty = 0;
static long s_from = 0L;
static long s_upto = 0L;
static long s_stop = 2147483647L;
static int nogcl = 0; /* garbage collection counter */
static int s_arg;
static int l_arg;
static char buff_id[100];
static char buff[100];
static char *arg = buff;
static long printed_step;
static long curr_step;
static long euc_step;
static long res_step;
static short was_ge;
static short was_le;
static short was_eq;
static long curr_step1;
static long curr_step2;
static linkcb *nextk;
static linkcb *res_prevk;
static linkcb *res_nextd;
static linkcb *pk, *prevk, *nextd;
static linkcb *dot1, *prevk1, *nextd1;
static linkcb *dot2, *prevk2, *nextd2;
static int i, c2;

#ifdef VIDEO
/*----------------------------------*/
#include "\refal\debug\mnw\mnw.def"
#include "\refal\debug\mnw\mankey.def"

#define TITUL 3
#define MESSAGE 3
#define PARAM 5
#define RFABEND 8
#define WORK_MES 9
#define DEF_PARM 10
#define PSEUDO_PARM 11
#define PSEUDO_PARM1 110

#define ALL_PARM -1
#define REDEFINE_PARM 1
#define QUIT 2
#define NORMAL_STEP 4
#define RESTART 8

#define NO_SWITCH 0
#define SWITCH 1

extern int video_page;
int rd_deb_screen();
void rd_deb_file();
void wr_deb_file();
int besc();
static char *word[] = {"Execute", "> ", ">=", "= ", "!=", "< ", "<=",
                       "TRAP", "STOP", "FROM", "TO", "E1 ="};
static char modif = '-';
static char key_code1 = K_ESC;
static int (*key_b1)() = besc;
static key_list f1 = {1, &key_code1, &key_b1};
static read_field inf = {1, 78, 1, BLACK, "", 12, 2};
static FILE *dfile = NULL;
static FILE *wrfile;
/*==================================*/
#endif

extern void (*dba)();
extern void rfdbg(st *s_st);

#endif
/*---------  end of file DEBUG.DEF -----------*/
