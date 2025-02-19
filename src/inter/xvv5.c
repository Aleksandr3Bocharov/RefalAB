// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-01-27
// https://github.com/Aleksandr3Bocharov/RefalAB

//-----------  file  --  XVV5.C ------------
//           MO: file input/output
//------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "refal.def"
#include "rfintf.h"

#define fmax 5

static FILE *f;
static FILE *uniput[fmax] = {NULL, NULL, NULL, NULL, NULL};
static FILE *uniget[fmax] = {NULL, NULL, NULL, NULL, NULL};

static void xopen_(void)
{
   char namf[255];
   const T_LINKCB *p = refal.preva->next;
   bool neot1 = false;
   do
   {
      if (p->tag != TAGO)
         break;
      const char c = p->info.infoc;
      p = p->next;
      uint32_t j;
      if (p->tag != TAGN)
         break;
      j = gcoden(p);
      p = p->next;
      if (j >= fmax)
         break;
      char s[2];
      s[1] = '\0';
      if (c == 'R' || c == 'r')
         s[0] = 'r';
      else if (c == 'W' || c == 'w')
         s[0] = 'w';
      else if (c == 'A' || c == 'a')
         s[0] = 'a';
      else
         break;
      bool neot = false;
      size_t i;
      for (i = 0; p != refal.nexta; i++)
      {
         if (p->tag != TAGO || i == 254)
         {
            neot = true;
            break;
         }
         namf[i] = p->info.infoc;
         p = p->next;
      }
      if (neot)
         break;
      namf[i] = '\0';
      f = fopen(namf, s);
      if (f == NULL)
      {
         printf("\n xopen: can't open file %s", namf);
         neot1 = true;
         break;
      }
      if (s[0] == 'r')
         uniget[j] = f;
      else
         uniput[j] = f;
      return;
   } while (false);
   if (!neot1)
      printf("\n xopen: format error");
   refal.upshot = 2;
   return;
}
char xopen_0[] = {Z5 'X', 'O', 'P', 'E', 'N', '\005'};
G_L_B uint8_t xopen = '\122';
void (*xopen_1)(void) = xopen_;

static void xclose_(void)
{
   const T_LINKCB *p = refal.preva->next;
   do
   {
      if (p->tag != TAGO)
         break;
      const char c = p->info.infoc;
      p = p->next;
      if (p->tag != TAGN)
         break;
      const uint32_t j = gcoden(p);
      if (j >= fmax)
         break;
      if (p->next != refal.nexta)
         break;
      if (c == 'R' || c == 'r')
      {
         f = uniget[j];
         uniget[j] = NULL;
      }
      else if (c == 'W' || c == 'w')
      {
         f = uniput[j];
         uniput[j] = NULL;
      }
      else
         break;
      fclose(f);
      return;
   } while (false);
   printf("\nxclose: format error");
   refal.upshot = 2;
   return;
}
char xclose_0[] = {Z6 'X', 'C', 'L', 'O', 'S', 'E', '\006'};
G_L_B uint8_t xclose = '\122';
void (*xclose_1)(void) = xclose_;

static void xget_(void)
{
   T_LINKCB *p = refal.preva->next;
   bool neot1 = false;
   do
   {
      if (p->tag != TAGN)
         break;
      const uint32_t j = gcoden(p);
      if (j >= fmax)
         break;
      if (p->next != refal.nexta)
         break;
      f = uniget[j];
      if (f == NULL)
      {
         char namf[11];
         strcpy(namf, "REFAL0.DAT");
         namf[5] = (char)j + '0';
         f = fopen(namf, "r");
         if (f == NULL)
         {
            printf("\nxget: can't open file %s", namf);
            neot1 = true;
            break;
         }
         uniget[j] = f;
      }
      p = refal.prevr;
      int c = getc(f);
      while (c != '\n')
      {
         if (!slins(p, 1))
            return;
         p = p->next;
         p->info.codep = NULL;
         if (c == EOF || c == '\032')
         {
            p->tag = TAGN;
            return;
         }
         p->tag = TAGO;
         p->info.infoc = (char)c;
         c = getc(f);
      }
      return;
   } while (false);
   if (!neot1)
      printf("\nxget: format error");
   refal.upshot = 2;
   return;
}
char xget_0[] = {Z4 'X', 'G', 'E', 'T', '\004'};
G_L_B uint8_t xget = '\122';
void (*xget_1)(void) = xget_;

static void xput_(void)
{
   const T_LINKCB *p = refal.preva->next;
   bool neot1 = false;
   do
   {
      if (p->tag != TAGN)
         break;
      const uint32_t j = gcoden(p);
      p = p->next;
      if (j >= fmax)
         break;
      f = uniput[j];
      if (f == NULL)
      {
         char namf[11];
         strcpy(namf, "REFAL0.DAT");
         namf[5] = (char)j + '0';
         f = fopen(namf, "w");
         if (f == NULL)
         {
            printf("\nxput: can't open file %s", namf);
            neot1 = true;
            break;
         }
         uniput[j] = f;
      }
      const T_LINKCB *q = p;
      bool neot2 = false;
      while (q != refal.nexta)
      {
         if (q->tag != TAGO && q->tag != TAGLB && q->tag != TAGRB)
         {
            neot2 = true;
            break;
         }
         q = q->next;
      }
      if (neot2)
         break;
      while (p != refal.nexta)
      {
         int cc;
         if (p->tag == TAGLB)
            cc = '(';
         else if (p->tag == TAGRB)
            cc = ')';
         else
            cc = p->info.infoc;
         putc(cc, f);
         p = p->next;
      }
      putc('\n', f);
      return;
   } while (false);
   if (!neot1)
      printf("\nxput: format error");
   refal.upshot = 2;
   return;
}
char xput_0[] = {Z4 'X', 'P', 'U', 'T', '\004'};
G_L_B uint8_t xput = '\122';
void (*xput_1)(void) = xput_;

//----------  end of file XVV5.C  -----------
