// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Find exit from room
bool findxt(int dir, int rm) {
// System generated locals
   bool ret_val;

// Local variables
   int i, xi;

   ret_val = true;
// 						!ASSUME WINS.
   xi = rooms.rexit[rm - 1];
// 						!FIND FIRST ENTRY.
   if (xi == 0) {
      goto L1000;
   }
// 						!NO EXITS?

L100:
   i = exits.travel[xi - 1];
// 						!GET ENTRY.
   curxt.xroom1 = i & xpars.xrmask;
// mask to 16-bits to get rid of sign extension problems with 32-bit ints 
   curxt.xtype = ((i & ~xpars.xlflag & 0xffff) / xpars.xfshft & xpars.xfmask) + 1;
   switch (curxt.xtype) {
      case 1:
         goto L110;
      case 2:
         goto L120;
      case 3:
         goto L130;
      case 4:
         goto L130;
   }
// 						!BRANCH ON ENTRY.
   bug(10, curxt.xtype);

L130:
   curxt.xobj = exits.travel[xi + 1] & xpars.xrmask;
   curxt.xactio = exits.travel[xi + 1] / xpars.xashft;
L120:
   curxt.xstrng = exits.travel[xi];
// 						!DOOR/CEXIT/NEXIT - STRING.
L110:
   xi += xpars.xelnt[curxt.xtype - 1];
// 						!ADVANCE TO NEXT ENTRY.
   if ((i & xpars.xdmask) == dir) {
      return ret_val;
   }
   if ((i & xpars.xlflag) == 0) {
      goto L100;
   }
L1000:
   ret_val = false;
// 						!YES, LOSE.
   return ret_val;
}

// Find what I mean
int fwim(int f1, int f2, int rm, int con, int adv, bool nocare) {
// System generated locals
   int ret_val, i__1, i__2;

// Local variables
   int i, j;

   ret_val = 0;
// 						!ASSUME NOTHING.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP
      if ((rm == 0 || objcts.oroom[i - 1] != rm) && (adv == 0 || objcts.oadv[i - 1] != adv) && (con == 0 || objcts.ocan[i - 1] != con)) {
         goto L1000;
      }

// OBJECT IS ON LIST... IS IT A MATCH?

      if ((objcts.oflag1[i - 1] & VisiO) == 0) {
         goto L1000;
      }
//    if ((~(nocare) & (objcts.oflag1[i - 1] & TakeO) == 0) || ⋯) {
      if (!(nocare) && (objcts.oflag1[i - 1] & TakeO) == 0 || (objcts.oflag1[i - 1] & f1) == 0 && (objcts.oflag2[i - 1] & f2) == 0) {
         goto L500;
      }
      if (ret_val == 0) {
         goto L400;
      }
// 						!ALREADY GOT SOMETHING?
      ret_val = -ret_val;
// 						!YES, AMBIGUOUS.
      return ret_val;

   L400:
      ret_val = i;
// 						!NOTE MATCH.

// DOES OBJECT CONTAIN A MATCH?

   L500:
      if ((objcts.oflag2[i - 1] & OpenO) == 0) {
         goto L1000;
      }
      i__2 = objcts.olnt;
      for (j = 1; j <= i__2; ++j) {
// 						!NO, SEARCH CONTENTS.
         if (objcts.ocan[j - 1] != i || (objcts.oflag1[j - 1] & VisiO) == 0 || (objcts.oflag1[j - 1] & f1) == 0 && (objcts.oflag2[j - 1] & f2) == 0) {
            goto L700;
         }
         if (ret_val == 0) {
            goto L600;
         }
         ret_val = -ret_val;
         return ret_val;

      L600:
         ret_val = j;
      L700:
         ;
      }
   L1000:
      ;
   }
   return ret_val;
}

// Obtain yes/no answer
// Called as:
// 	YesIsTrue = yesno(Question, YesString, NoString);
bool yesno(int q, int y, int n) {
// System generated locals
   bool ret_val;

// Local variables
   char buf[100];
   char ans;

L100:
   rspeak(q), fflush(stdout);
// 						!ASK
   more_input(buf, sizeof buf), ans = buf[0];
// 						!GET ANSWER
   if (ans == 'Y' || ans == 'y') {
      goto L200;
   }
   if (ans == 'N' || ans == 'n') {
      goto L300;
   }
   rspeak(6);
// 						!SCOLD.
   goto L100;

L200:
   ret_val = true;
// 						!YES,
   rspeak(y);
// 						!OUT WITH IT.
   return ret_val;

L300:
   ret_val = false;
// 						!NO,
   rspeak(n);
// 						!LIKEWISE.
   return ret_val;
}
