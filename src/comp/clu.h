#ifndef CLU_H
#define CLU_H

struct refw
{
    struct refw *next;    /* on the next usage list */
    unsigned int numb[6]; /* usage list element     */
};
typedef struct refw T_REFW;

struct u
{
    union
    {
        unsigned int infon;
        struct u *infop;
    } info;
    char mode;
    /* mode field :                      */
    /*  00 - no defined;                          */
    /*  01 - internal; infon = offset from start  */
    /*  10 - external; infon = member or extern   */
    /*       reference;                           */
    /*  11 - equivalent; infop =  reference on    */
    /*       other label;                         */
    /*  xx1 - entry point;                        */
    /*  xxx1 - too many definition;               */
    /*                                            */
    char type;             /* type field : 00 - unknown type  */
                           /*              01 - function      */
                           /*              10 - specifier     */
    unsigned int l;        /* identifier length */
    struct u *i;           /* left reference */
    struct u *j;           /* right reference */
    T_REFW *last_ref; /* on the end of using list */
    T_REFW ref;       /* where used */
    unsigned int def;      /* where defined */
    char k;                /* kren feature:      '00'B - kren no    */
                           /*                    '01'B - left kren  */
                           /*                    '10'B - right kren */
    char *id;              /* identifier */
};
typedef struct u T_U;

extern T_U *lookup(const char *idp, unsigned int lid);
extern void luterm();
extern void through(void (*prog)(const T_U *));
extern void uns_sto();

#endif