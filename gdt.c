// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <ctype.h>
#include <string.h>
#include "extern.h"
#include "common.h"

// Game debugging tool
void gdt(void) {
#ifdef ALLOW_GDT
// Initialized data
   const int cmdmax = 38;
   const char dbgcmd[2 * 38] =
      "DR" "DO" "DA" "DC" "DX" "DH" "DL" "DV" "DF" "DS" "AF" "HE" "NR" "NT" "NC" "ND" "RR" "RT" "RC"
      "RD" "TK" "EX" "AR" "AO" "AA" "AC" "AX" "AV" "D2" "DN" "AN" "DM" "DT" "AH" "DP" "PD" "DZ" "AZ";
   const int argtyp[38] = {
      2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 0, 3, 3, 3, 3, 1, 3, 2, 2, 1, 2, 1, 0, 0, 0, 0, 1
   };

   const char Format0[] = "  RANGE   CONTENTS\n";
   const char Format1[] = "Old= %c      New= ";
   const char Format2[] = "Old= %6d      New= ";

// System generated locals
   int i__1, i__2;

// Local variables
   int i, j, k, l, l1;
   char cmd[2];
   int fmax, smax;
   char buf[80];

// GDT, PAGE 2

// FIRST, VALIDATE THAT THE CALLER IS AN IMPLEMENTER.

   fmax = 46;
// 						!SET ARRAY LIMITS.
   smax = 22;

   if (debug.gdtflg != 0) {
      goto L2000;
   }
// 						!IF OK, SKIP.
   more_output("You are not an authorized user.\n");
// 						!NOT AN IMPLEMENTER.
   return;
// 						!BOOT HIM OFF

// GDT, PAGE 2A

// HERE TO GET NEXT COMMAND

L2000:
   printf("GDT>"), fflush(stdout);
// 						!OUTPUT PROMPT.
   more_input(buf, sizeof buf), strncpy(cmd, buf, sizeof cmd);
// 						!GET COMMAND.
   if (cmd[0] == '\0' || strncmp(cmd, "  ", sizeof cmd) == 0) {
      goto L2000;
   }
// 						!IGNORE BLANKS.
// 	  check for lower case command, as well
   if (islower(cmd[0]))
      cmd[0] = toupper(cmd[0]);
   if (islower(cmd[1]))
      cmd[1] = toupper(cmd[1]);
   i__1 = cmdmax;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOK IT UP.
      if (strncmp(cmd, &dbgcmd[i - 1 << 1], sizeof cmd) == 0) {
         goto L2300;
      }
// 						!FOUND?
// L2100:
   }
L2200:
   more_output("?\n");
// 						!NO, LOSE.
   goto L2000;

//L230:
//L240:
//L225:
//L235:
//L245:

L2300:
   switch (argtyp[i - 1] + 1) {
      case 1:
         goto L2400;
      case 2:
         goto L2500;
      case 3:
         goto L2600;
      case 4:
         goto L2700;
   }
// 						!BRANCH ON ARG TYPE.
   goto L2200;
// 						!ILLEGAL TYPE.

L2700:
   printf("Idx,Ary:  "), fflush(stdout);
// 						!TYPE 3, REQUEST ARRAY COORDS.
   more_input(buf, sizeof buf); for (char *BP = buf; *BP != '\0'; BP++) if (*BP == ',') *BP = ' ';
   j = 0, k = 0, sscanf(buf, "%d %d", &j, &k);
   goto L2400;

L2600:
   printf("Limits:   "), fflush(stdout);
// 						!TYPE 2, READ BOUNDS.
   more_input(buf, sizeof buf); for (char *BP = buf; *BP != '\0'; BP++) if (*BP == ',') *BP = ' ';
   j = 0, k = 0, sscanf(buf, "%d %d", &j, &k);
   if (k == 0) {
      k = j;
   }
   goto L2400;

L2500:
   printf("Entry:    "), fflush(stdout);
// 						!TYPE 1, READ ENTRY NO.
   more_input(buf, sizeof buf), j = 0, sscanf(buf, "%d", &j);
L2400:
   switch (i) {
      case 1:
         goto L10000;
      case 2:
         goto L11000;
      case 3:
         goto L12000;
      case 4:
         goto L13000;
      case 5:
         goto L14000;
      case 6:
         goto L15000;
      case 7:
         goto L16000;
      case 8:
         goto L17000;
      case 9:
         goto L18000;
      case 10:
         goto L19000;
      case 11:
         goto L20000;
      case 12:
         goto L21000;
      case 13:
         goto L22000;
      case 14:
         goto L23000;
      case 15:
         goto L24000;
      case 16:
         goto L25000;
      case 17:
         goto L26000;
      case 18:
         goto L27000;
      case 19:
         goto L28000;
      case 20:
         goto L29000;
      case 21:
         goto L30000;
      case 22:
         goto L31000;
      case 23:
         goto L32000;
      case 24:
         goto L33000;
      case 25:
         goto L34000;
      case 26:
         goto L35000;
      case 27:
         goto L36000;
      case 28:
         goto L37000;
      case 29:
         goto L38000;
      case 30:
         goto L39000;
      case 31:
         goto L40000;
      case 32:
         goto L41000;
      case 33:
         goto L42000;
      case 34:
         goto L43000;
      case 35:
         goto L44000;
      case 36:
         goto L45000;
      case 37:
         goto L46000;
      case 38:
         goto L47000;
   }
   goto L2200;
// 						!WHAT???
// GDT, PAGE 3

// DR-- DISPLAY ROOMS

L10000:
   if (!(j > 0 && j <= rooms.rlnt && (k > 0 && k <= rooms.rlnt) && j <= k)) {
      goto L2200;
   }
// 						!ARGS VALID?
   more_output("RM#  DESC1  DESC2  EXITS ACTION  VALUE  FLAGS\n");
// 						!COL HDRS.
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      printf("%3d", i);
      for (l = 0; l < 6; l++) printf(" %6d", eqr[i - 1 + 200 * l]);
      more_output("\n");
// L10100:
   }
   goto L2000;

// DO-- DISPLAY OBJECTS

L11000:
   if (!(j > 0 && j <= objcts.olnt && (k > 0 && k <= objcts.olnt) && j <= k)) {
      goto L2200;
   }
// 						!ARGS VALID?
   more_output("OB# DESC1 DESC2 DESCO ACT FLAGS1 FLAGS2 FVL TVL  SIZE CAPAC ROOM ADV CON  READ\n");
// 						!COL HDRS
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      more_output("%3d%6d%6d%6d%4d%7d%7d%4d%4d%6d%6d %4d%4d%4d%6d\n", i,
         eqo[i - 1 + 220 * 0], eqo[i - 1 + 220 * 1], eqo[i - 1 + 220 * 2],
         eqo[i - 1 + 220 * 3],
         eqo[i - 1 + 220 * 4], eqo[i - 1 + 220 * 5],
         eqo[i - 1 + 220 * 6], eqo[i - 1 + 220 * 7],
         eqo[i - 1 + 220 * 8], eqo[i - 1 + 220 * 9],
         eqo[i - 1 + 220 * 10], eqo[i - 1 + 220 * 11], eqo[i - 1 + 220 * 12],
         eqo[i - 1 + 220 * 13]
      );
// L11100:
   }
   goto L2000;

// DA-- DISPLAY ADVENTURERS

L12000:
   if (!(j > 0 && j <= advs.alnt && (k > 0 && k <= advs.alnt) && j <= k)) {
      goto L2200;
   }
// 						!ARGS VALID?
   more_output("AD#   ROOM  SCORE  VEHIC OBJECT ACTION  STREN  FLAGS\n");
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      printf("%3d", i);
      for (l = 0; l < 7; l++) printf(" %6d", eqa[i - 1 + (l << 2)]);
      more_output("\n");
// L12100:
   }
   goto L2000;

// DC-- DISPLAY CLOCK EVENTS

L13000:
   if (!(j > 0 && j <= cevent.clnt && (k > 0 && k <= cevent.clnt) && j <= k)) {
      goto L2200;
   }
// 						!ARGS VALID?
   more_output("CL#   TICK ACTION  FLAG\n");
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      printf("%3d", i);
      for (l = 0; l < 2; l++) printf(" %6d", eqc[i - 1 + 25 * l]);
      more_output("     %c\n", cevent.cflag[i - 1] ? 'T' : 'F');
// L13100:
   }
   goto L2000;

// DX-- DISPLAY EXITS

L14000:
   if (!(j > 0 && j <= exits.xlnt && (k > 0 && k <= exits.xlnt) && j <= k)) {
      goto L2200;
   }
// 						!ARGS VALID?
   more_output(Format0);
// 						!COL HDRS.
   i__1 = k;
   for (i = j; i <= i__1; i += 10) {
// 						!TEN PER LINE.
// Computing MIN
      i__2 = i + 9;
      l = min(i__2, k);
// 						!COMPUTE END OF LINE.
      printf("%3d-%3d   ", i, l);
      for (l1 = i; l1 <= l; ++l1) printf("%7d", exits.travel[l1 - 1]);
      more_output("\n");
// L14100:
   }
   goto L2000;

// DH-- DISPLAY HACKS

L15000:
   more_output("THFPOS= %d, THFFLG= %c, THFACT= %c\n", hack.thfpos, hack.thfflg ? 'T' : 'F', hack.thfact ? 'T' : 'F');
   more_output("SWDACT= %c, SWDSTA= %d\n", hack.swdact ? 'T' : 'F', hack.swdsta);
   goto L2000;

// DL-- DISPLAY LENGTHS

L16000:
   more_output("R=%d, X=%d, O=%d, C=%d\n", rooms.rlnt, exits.xlnt, objcts.olnt, cevent.clnt);
   more_output("V=%d, A=%d, M=%d, R2=%d\n", vill.vlnt, advs.alnt, rmsg.mlnt, oroom2_.r2lnt);
   more_output("MBASE=%d, STRBIT=%d\n", star.mbase, star.strbit);
   goto L2000;

// DV-- DISPLAY VILLAINS

L17000:
   if (!(j > 0 && j <= vill.vlnt && (k > 0 && k <= vill.vlnt) && j <= k)) {
      goto L2200;
   }
// 						!ARGS VALID?
   more_output("VL# OBJECT   PROB   OPPS   BEST  MELEE\n");
// 						!COL HDRS
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      printf("%3d", i);
      for (l = 0; l < 5; l++) printf(" %6d", eqv[i - 1 + (l << 2)]);
      more_output("\n");
// L17100:
   }
   goto L2000;

// DF-- DISPLAY FLAGS

L18000:
   if (!(j > 0 && j <= fmax && (k > 0 && k <= fmax) && j <= k)) {
      goto L2200;
   }
// 						!ARGS VALID?
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      more_output("Flag #%-2d = %c\n", i, flags[i - 1] ? 'T' : 'F');
// L18100:
   }
   goto L2000;

// DS-- DISPLAY STATE

L19000:
   more_output("Parse vector= %6d %6d %6d      %c %6d\n", prsvec.prsa, prsvec.prso, prsvec.prsi, prsvec.prswon ? 'T' : 'F', prsvec.prscon);
   more_output("Play vector=  %6d %6d      %c\n", play.winner, play.here, play.telflg ? 'T' : 'F');
   more_output("State vector= %6d %6d %6d %6d %6d %6d %6d %6d %6d\n", state.moves, state.deaths, state.rwscor, state.mxscor, state.mxload, state.ltshft, state.bloc, state.mungrm, state.hs);
   more_output("              %6d %6d\n", state.egscor, state.egmxsc);
   more_output("Scol vector=  %6d %6d %6d\n", screen.fromdr, screen.scolrm, screen.scolac);
   goto L2000;

// GDT, PAGE 4

// AF-- ALTER FLAGS

L20000:
   if (!(j > 0 && j <= fmax)) {
      goto L2200;
   }
// 						!ENTRY NO VALID?
   printf(Format1, flags[j - 1] ? 'T' : 'F'), fflush(stdout);
// 						!TYPE OLD, GET NEW.
   more_input(buf, sizeof buf);
   for (char *BP = buf, Ch; (Ch = tolower(*BP)) != '\0'; BP++)
      if (!isspace(Ch)) {
         if (Ch == 't') flags[j - 1] = true;
         else if (Ch == 'f') flags[j - 1] = false;
         break;
      }
   goto L2000;

// 21000-- HELP

L21000:
   more_output("Valid commands are:\n");
   more_output("AA- Alter ADVS        AC- Alter CEVENT      AF- Alter FINDEX\n");
   more_output("AH- Alter HERE        AN- Alter switches    AO- Alter OBJCTS\n");
   more_output("AR- Alter ROOMS       AV- Alter VILLS       AX- Alter EXITS\n");
   more_output("AZ- Alter PUZZLE      DA- Display ADVS      DC- Display CEVENT\n");
   more_output("DF- Display FINDEX    DH- Display HACKS     DL- Display lengths\n");
   more_output("DM- Display RTEXT     DN- Display switches  DO- Display OBJCTS\n");
   more_output("DP- Display parser    DR- Display ROOMS     DS- Display state\n");
   more_output("DT- Display text      DV- Display VILLS     DX- Display EXITS\n");
   more_output("DZ- Display PUZZLE    D2- Display ROOM2     EX- Exit\n");
   more_output("HE- Type this message NC- No cyclops        ND- No deaths\n");
   more_output("NR- No robber         NT- No troll          PD- Program detail\n");
   more_output("RC- Restore cyclops   RD- Restore deaths    RR- Restore robber\n");
   more_output("RT- Restore troll     TK- Take.\n");
   goto L2000;

// NR-- NO ROBBER

L22000:
   hack.thfflg = false;
// 						!DISABLE ROBBER.
   hack.thfact = false;
   newsta(ThiefOX, 0, 0, 0, 0);
// 						!VANISH THIEF.
   more_output("No robber.\n");
   goto L2000;

// NT-- NO TROLL

L23000:
   findex_0.trollf = true;
   newsta(TrollOX, 0, 0, 0, 0);
   more_output("No troll.\n");
   goto L2000;

// NC-- NO CYCLOPS

L24000:
   findex_0.cyclof = true;
   newsta(CycloOX, 0, 0, 0, 0);
   more_output("No cyclops.\n");
   goto L2000;

// ND-- IMMORTALITY MODE

L25000:
   debug.dbgflg = 1;
   more_output("No deaths.\n");
   goto L2000;

// RR-- RESTORE ROBBER

L26000:
   hack.thfact = true;
   more_output("Restored robber.\n");
   goto L2000;

// RT-- RESTORE TROLL

L27000:
   findex_0.trollf = false;
   newsta(TrollOX, 0, MTrolRX, 0, 0);
   more_output("Restored troll.\n");
   goto L2000;

// RC-- RESTORE CYCLOPS

L28000:
   findex_0.cyclof = false;
   findex_0.magicf = false;
   newsta(CycloOX, 0, MCyclRX, 0, 0);
   more_output("Restored cyclops.\n");
   goto L2000;

// RD-- MORTAL MODE

L29000:
   debug.dbgflg = 0;
   more_output("Restored deaths.\n");
   goto L2000;

// GDT, PAGE 5

// TK-- TAKE

L30000:
   if (!(j > 0 && j <= objcts.olnt)) {
      goto L2200;
   }
// 						!VALID OBJECT?
   newsta(j, 0, 0, 0, play.winner);
// 						!YES, TAKE OBJECT.
   more_output("Taken.\n");
// 						!TELL.
   goto L2000;

// EX-- GOODBYE

L31000:
   prsvec.prscon = 1;
   return;

// AR--	ALTER ROOM ENTRY

L32000:
   if (!(j > 0 && j <= rooms.rlnt && (k > 0 && k <= 5))) {
      goto L2200;
   }
// 						!INDICES VALID?
   printf(Format2, eqr[j - 1 + 200 * (k - 1)]), fflush(stdout);
// 						!TYPE OLD, GET NEW.
   more_input(buf, sizeof buf), sscanf(buf, "%d", &eqr[j - 1 + 200 * (k - 1)]);
   goto L2000;

// AO-- ALTER OBJECT ENTRY

L33000:
   if (!(j > 0 && j <= objcts.olnt && (k > 0 && k <= 14))) {
      goto L2200;
   }
// 						!INDICES VALID?
   printf(Format2, eqo[j - 1 + 220 * (k - 1)]), fflush(stdout);
   more_input(buf, sizeof buf), sscanf(buf, "%d", &eqo[j - 1 + 220 * (k - 1)]);
   goto L2000;

// AA-- ALTER ADVS ENTRY

L34000:
   if (!(j > 0 && j <= advs.alnt && (k > 0 && k <= 7))) {
      goto L2200;
   }
// 						!INDICES VALID?
   printf(Format2, eqa[j - 1 + ((k - 1) << 2)]), fflush(stdout);
   more_input(buf, sizeof buf), sscanf(buf, "%d", &eqa[j - 1 + ((k - 1) << 2)]);
   goto L2000;

// AC-- ALTER CLOCK EVENTS

L35000:
   if (!(j > 0 && j <= cevent.clnt && (k > 0 && k <= 3))) {
      goto L2200;
   }
// 						!INDICES VALID?
   if (k == 3) {
      goto L35500;
   }
// 						!FLAGS ENTRY?
   printf(Format2, eqc[j - 1 + 25 * (k - 1)]), fflush(stdout);
   more_input(buf, sizeof buf), sscanf(buf, "%d", &eqc[j - 1 + 25 * (k - 1)]);
   goto L2000;

L35500:
   printf(Format1, cevent.cflag[j - 1] ? 'T' : 'F'), fflush(stdout);
   more_input(buf, sizeof buf);
   for (char *BP = buf, Ch; (Ch = tolower(*BP)) != '\0'; BP++)
      if (!isspace(Ch)) {
         if (Ch == 't') cevent.cflag[j - 1] = true;
         else if (Ch == 'f') cevent.cflag[j - 1] = false;
         break;
      }
   goto L2000;
// GDT, PAGE 6

// AX-- ALTER EXITS

L36000:
   if (!(j > 0 && j <= exits.xlnt)) {
      goto L2200;
   }
// 						!ENTRY NO VALID?
   printf(Format2, exits.travel[j - 1]), fflush(stdout);
   more_input(buf, sizeof buf), sscanf(buf, "%d", &exits.travel[j - 1]);
   goto L2000;

// AV-- ALTER VILLAINS

L37000:
   if (!(j > 0 && j <= vill.vlnt && (k > 0 && k <= 5))) {
      goto L2200;
   }
// 						!INDICES VALID?
   printf(Format2, eqv[j - 1 + ((k - 1) << 2)]), fflush(stdout);
   more_input(buf, sizeof buf), sscanf(buf, "%d", &eqv[j - 1 + ((k - 1) << 2)]);
   goto L2000;

// D2-- DISPLAY ROOM2 LIST

L38000:
   if (!(j > 0 && j <= oroom2_.r2lnt && (k > 0 && k <= oroom2_.r2lnt) && j <= k)) {
      goto L2200;
   }
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      more_output("#%2d   Room=%6d   Obj=%6d\n", i, oroom2_.rroom2[i - 1], oroom2_.oroom2[i - 1]);
// L38100:
   }
   goto L2000;

// DN-- DISPLAY SWITCHES

L39000:
   if (!(j > 0 && j <= smax && (k > 0 && k <= smax) && j <= k)) {
      goto L2200;
   }
// 						!VALID?
   i__1 = k;
   for (i = j; i <= i__1; ++i) {
      more_output("Switch #%-2d = %d\n", i, switch_[i - 1]);
// L39100:
   }
   goto L2000;

// AN-- ALTER SWITCHES

L40000:
   if (!(j > 0 && j <= smax)) {
      goto L2200;
   }
// 						!VALID ENTRY?
   printf(Format2, switch_[j - 1]), fflush(stdout);
   more_input(buf, sizeof buf), sscanf(buf, "%d", &switch_[j - 1]);
   goto L2000;

// DM-- DISPLAY MESSAGES

L41000:
   if (!(j > 0 && j <= rmsg.mlnt && (k > 0 && k <= rmsg.mlnt) && j <= k)) {
      goto L2200;
   }
// 						!VALID LIMITS?
   more_output(Format0);
   i__1 = k;
   for (i = j; i <= i__1; i += 10) {
// Computing MIN
      i__2 = i + 9;
      l = min(i__2, k);
      printf("%3d-%3d   ", i, l);
      for (l1 = i; l1 <= l; ++l1) printf(" %6d", rmsg.rtext[l1 - 1]);
      more_output("\n");
// L41100:
   }
   goto L2000;

// DT-- DISPLAY TEXT

L42000:
   rspeak(j);
   goto L2000;

// AH--	ALTER HERE

L43000:
   printf(Format2, play.here), fflush(stdout);
   more_input(buf, sizeof buf), sscanf(buf, "%d", &play.here);
   eqa[0] = play.here;
   goto L2000;

// DP--	DISPLAY PARSER STATE

L44000:
   more_output("ORPHS= %7d%7d%7d%7d%7d%7d\n", orp[0], orp[1], orp[2], orp[3], orp[4], last.lastit);
   more_output("PV=    %7d%7d%7d%7d%7d\n", pvec[0], pvec[1], pvec[2], pvec[3], pvec[4]);
   more_output("SYN=   %7d%7d%7d%7d%7d%7d\n", syn[0], syn[1], syn[2], syn[3], syn[4], syn[5]);
   more_output("              %7d%7d%7d%7d%7d\n", syn[6], syn[7], syn[8], syn[9], syn[10]);
   goto L2000;

// PD--	PROGRAM DETAIL DEBUG

L45000:
   printf(Format2, debug.prsflg), fflush(stdout);
// 						!TYPE OLD, GET NEW.
   more_input(buf, sizeof buf), sscanf(buf, "%d", &debug.prsflg);
   goto L2000;

// DZ--	DISPLAY PUZZLE ROOM

L46000:
   for (i = 1; i <= 64; i += 8) {
// 						!DISPLAY PUZZLE
      printf(" ");
      for (j = i; j <= i + 7; ++j) printf("%3d", puzzle.cpvec[j - 1]);
      more_output("\n");
// L46100:
   }
   goto L2000;

// AZ--	ALTER PUZZLE ROOM

L47000:
   if (!(j > 0 && j <= 64)) {
      goto L2200;
   }
// 						!VALID ENTRY?
   printf(Format2, puzzle.cpvec[j - 1]), fflush(stdout);
// 						!OUTPUT OLD,
   more_input(buf, sizeof buf), sscanf(buf, "%d", &puzzle.cpvec[j - 1]);
   goto L2000;
#endif
}
