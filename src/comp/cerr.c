
//-------------  file  --  CERR.C  --------------- 
//               Print error file                           
//------------------------------------------------ 

#include <stdio.h>
#include "refal.def"
#include "cerr.h"
#include "refal.h"

void pchosh(const char *s)
{
    oshibka();
    char tmp[255];
    sprintf(tmp, "***** %s\n", s);
    if (sysprint != NULL)
        fputs(tmp, sysprint);
    fputs(tmp, systerm);
    return;
}

void pchosj(const char *s, const char *sid, size_t lsid, const char *s1)
{
    oshibka();
    char tmp1[255];
    for (size_t i = 0; i < lsid; i++)
        tmp1[i] = *(sid + i);
    tmp1[lsid] = '\0';
    char tmp[512];
    sprintf(tmp, "***** %s %s %s\n", s, tmp1, s1);
    if (sysprint != NULL)
        fputs(tmp, sysprint);
    fputs(tmp, systerm);
    return;
}

/*void pchosx(const char *s, const char *sid, size_t lsid, const char *s1)
{
    oshibka();
    char tmp1[255];
    for (size_t i = 0; i < lsid; i++)
        tmp1[i] = *(sid + i);
    tmp1[lsid] = '\0';
    char tmp[512];
    sprintf(tmp, "***** %s %s %s\n", s, tmp1, s1);
    if (sysprint != NULL)
        fputs(tmp, sysprint);
    fputs(tmp, systerm);
    return;
}*/

void pchosa(const char *s, const char c)
{
    oshibka();
    char tmp[255];
    sprintf(tmp, "***** %s %c\n", s, c);
    if (sysprint != NULL)
        fputs(tmp, sysprint);
    fputs(tmp, systerm);
    return;
}

/*static void pchosi(const char *s, const char *t)
{
    oshibka();
    char tmp[255];
    sprintf(tmp, "***** %s %s\n", s, t);
    if (sysprint != NULL)
        fputs(tmp, sysprint);
    fputs(tmp, systerm);
    return;
}*/

/*static void pchose(const char *s, const char *t, size_t lt)
{
    oshibka();
    char tmp1[255];
    for (size_t i = 0; i < lt; i++)
        tmp1[i] = *(t + i);
    tmp1[lt] = '\0';
    char tmp[255];
    sprintf(tmp, "***** %s %s\n", s, tmp1);
    if (sysprint != NULL)
        fputs(tmp, sysprint);
    fputs(tmp, systerm);
    return;
}*/
//--------  end  of  file  CERR.C  --------- 
