// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <ctype.h>
#include <stdlib.h> // For system(); // C99 is assumed.
#include "extern.h"
#include "common.h"

static Bool lex(char *, int *, int *, Bool);

// Read input line
void rdline(char *buffer, size_t length, int who) {
// Local variable
   char *zpast;

// Function Body
L5:
   switch (who + 1) {
      case 1:
         goto L90;
      case 2:
         goto L10;
   }
// 						!SEE WHO TO PROMPT FOR.
L10:
// write(outch, ">%$"); //F
   printf(">"), fflush(stdout);
// 						!PROMPT FOR GAME.
L90:
// read(inpch, "%78A1", buffer); //F
   if (more_input(buffer, length) == NULL) exit_();
   zpast = buffer;
   for (char *z = buffer; *z != '\0' && *z != '\n'; z++) {
      if (*z != ' ') {
         zpast = z + 1;
      }
// L200:
   }
   *zpast = '\0';
   if (zpast == buffer) {
      goto L5;
// 						!TRY AGAIN.
   }

//L250:
// 	check for shell escape here before things are
// 	converted to upper case

// NO SHELL ESCAPE /+TAA+/
   if (buffer[0] == '!') {
      system(buffer + 1);
      goto L5;
   }

//L300:
// CONVERT TO UPPER CASE
   for (char *z = buffer; *z != '\0' && *z != '\n'; z++) {
      if (islower(*z)) {
         *z = toupper(*z);
      }
// L400:
   }
   prsvec.prscon = 1;
// 						!RESTART LEX SCAN.
}

// Top level parse routine
// This routine details on bit 0 of prsflg
Bool parse(char *inbuf, Bool vbflag) {
// System generated locals
   int SparseRet;
   Bool ret_val;

// Local variables
#if 0
   int x; //(@) Actually unused.
#endif
   int outbuf[40], outlnt;

#ifdef ALLOW_GDT
// dflag = (debug.prsflg & 1) != 0; //F
#endif

// Function Body
   ret_val = false;
// 						!ASSUME FAILS.
   prsvec.prsa = 0;
// 						!ZERO OUTPUTS.
   prsvec.prsi = 0;
   prsvec.prso = 0;

   if (!lex(inbuf, outbuf, &outlnt, vbflag)) {
      goto L100;
   }
   SparseRet = sparse(outbuf, outlnt, vbflag);
   if (SparseRet < 0) goto L100; else if (SparseRet > 0) goto L300;/* else if (SparseRet == 0) goto L200;*/
// 						!DO SYN SCAN.

// PARSE REQUIRES VALIDATION

L200:
   if (!(vbflag)) {
      goto L350;
   }
// 						!ECHO MODE, FORCE FAIL.
   if (!synmch(/*x*/)) {
      goto L100;
   }
// 						!DO SYN MATCH.
   if (prsvec.prso > 0 && prsvec.prso < MinDX) {
      last.lastit = prsvec.prso;
   }

// SUCCESSFUL PARSE OR SUCCESSFUL VALIDATION

L300:
   ret_val = true;
L350:
   orphan(0, 0, 0, 0, 0);
// 						!CLEAR ORPHANS.
#ifdef ALLOW_GDT
// if (dflag) write(0, *, "parse good"); //F
// if (dflag) print("PARSE RESULTS- %L7%3I7", ret_val, prsvec.prsa, prsvec.prso, prsvec.prsi); //F
#endif
   return ret_val;

// PARSE FAILS, DISALLOW CONTINUATION

L100:
   prsvec.prscon = 1;
#ifdef ALLOW_GDT
// if (dflag) write(0, *, "parse failed"); //F
// if (dflag) print("PARSE RESULTS- %L7%3I7", ret_val, prsvec.prsa, prsvec.prso, prsvec.prsi); //F
#endif
   return ret_val;
}

// Set up new orphans
void orphan(int o1, int o2, int o3, int o4, int o5) {
   orphs.oflag = o1;
// 						!SET UP NEW ORPHANS.
   orphs.oact = o2;
   orphs.oslot = o3;
   orphs.oprep = o4;
   orphs.oname = o5;
}

// Lexical analyzer
// This routine details on bit 1 of prsflag
static Bool lex(char *inbuf, int *outbuf, int *op, Bool vbflag) {
// Initialized data
   static const char dlimit[9] = { 'A', 'Z', 'A' - 1, '1', '9', '1' - 31, '-', '-', '-' - 27 };

// System generated locals
   Bool ret_val;

// Local variables
   int i;
   char j;
   int k, j1, j2, cp;

// Parameter adjustments
   --outbuf;
   --inbuf;

// Function Body

   for (i = 1; i <= 40; ++i) {
// 						!CLEAR OUTPUT BUF.
      outbuf[i] = 0;
// L100:
   }

#ifdef ALLOW_GDT
// dflag = (debug.prsflg & 2) != 0; //F
#endif
   ret_val = false;
// 						!ASSUME LEX FAILS.
   *op = -1;
// 						!OUTPUT PTR.
L50:
   *op += 2;
// 						!ADV OUTPUT PTR.
   cp = 0;
// 						!CHAR PTR=0.

L200:
   j = inbuf[prsvec.prscon];
// 						!GET CHARACTER
   if (j == '\0') {
      goto L1000;
   }
// 						!END OF INPUT?
   ++prsvec.prscon;
// 						!ADVANCE PTR.
   if (j == '.') {
      goto L1000;
   }
// 						!END OF COMMAND?
   if (j == ',') {
      goto L1000;
   }
// 						!END OF COMMAND?
   if (j == ' ') {
      goto L6000;
   }
// 						!SPACE?
   for (i = 1; i <= 9; i += 3) {
// 						!SCH FOR CHAR.
      if (j >= dlimit[i - 1] && j <= dlimit[i]) {
         goto L4000;
      }
// L500:
   }

   if (vbflag) {
      rspeak(601);
   }
// 						!GREEK TO ME, FAIL.
   return ret_val;

// END OF INPUT, SEE IF PARTIAL WORD AVAILABLE.

L1000:
   if (inbuf[prsvec.prscon] == '\0') {
      prsvec.prscon = 1;
   }
// 						!FORCE PARSE RESTART.
   if (cp == 0 && *op == 1) {
      return ret_val;
   }
   if (cp == 0) {
      *op += -2;
   }
// 						!ANY LAST WORD?
   ret_val = true;
#ifdef ALLOW_GDT
// if (dflag) print("LEX RESULTS- %3I7%/%1X%10I7", cp, *op, prsvec.prscon, (outbuf[i - 1], i = 1, *op + 1)); //F
#endif
   return ret_val;

// LEGITIMATE CHARACTERS: LETTER, DIGIT, OR HYPHEN.

L4000:
   j1 = j - dlimit[i + 1];
#ifdef ALLOW_GDT
// if (dflag) print("LEX- CHAR= %A1%2I7", j, j1, cp); //F
#endif
   if (cp >= 6) {
      goto L200;
   }
// 						!IGNORE IF TOO MANY CHAR.
   k = *op + cp / 3;
// 						!COMPUTE WORD INDEX.
   switch (cp % 3 + 1) {
      case 1:
         goto L4100;
      case 2:
         goto L4200;
      case 3:
         goto L4300;
   }
// 						!BRANCH ON CHAR.
L4100:
   j2 = j1 * 780;
// 						!CHAR 1... *780
   outbuf[k] = outbuf[k] + j2 + j2;
// 						!*1560 (40 ADDED BELOW).
L4200:
   outbuf[k] += j1 * 39;
// 						!*39 (1 ADDED BELOW).
L4300:
   outbuf[k] += j1;
// 						!*1.
   ++cp;
   goto L200;
// 						!GET NEXT CHAR.

// SPACE

L6000:
   if (cp == 0) {
      goto L200;
   }
// 						!ANY WORD YET?
   goto L50;
// 						!YES, ADV OP.
}
