// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <stdio.h>
#include "extern.h"
#include "common.h"

// Resident subroutines for dungeon
#ifndef SEEK_SET
#   define SEEK_SET (0)
#endif

extern FILE *dbfile;

static void rspsb2nl(int, int, int, Bool);

// Output random message routine
// Called as:
// 	rspeak(MsgNum);
void rspeak(int n) {
   rspsb2nl(n, 0, 0, 1);
}

// Output random message with substitutable argument
// Called as:
// 	rspsub(MsgNum, SubNum);
void rspsub(int n, int s1) {
   rspsb2nl(n, s1, 0, 1);
}

// Output random message with up to two substitutable arguments
// Called as:
// 	rspsb2(MsgNum, SubNum1, SubNum2);
void rspsb2(int n, int s1, int s2) {
   rspsb2nl(n, s1, s2, 1);
}

// Display a substitutable message with an optional newline
static void rspsb2nl(int n, int y, int z, Bool nl) {
   const char *zkey = "IanLanceTaylorJr";
   long x;

   x = (long)n;

   if (x > 0) {
      x = rmsg_1.rtext[x - 1];
   }
// 						!IF >0, LOOK UP IN RTEXT.
   if (x == 0) {
      return;
   }
// 						!ANYTHING TO DO?
   play_1.telflg = true;
// 						!SAID SOMETHING.

   x = ((-x) - 1) * 8;
   if (fseek(dbfile, x + (long)rmsg_1.mrloc, SEEK_SET) == EOF) fprintf(stderr, "Error seeking database loc %d\n", x), exit_();

   if (nl)
      more_output(NULL);

   while (1) {
      int i;

      i = getc(dbfile);
      if (i == EOF) {
         fprintf(stderr, "Error reading database loc %d\n", x);
         exit_();
      }
      i ^= zkey[x & 0xf] ^ (x & 0xff);
      x = x + 1;
      if (i == '\0')
         break;
      else if (i == '\n') {
         putchar('\n');
         if (nl)
            more_output(NULL);
      } else if (i == '#' && y != 0) {
         long iloc;

         iloc = ftell(dbfile);
         rspsb2nl(y, 0, 0, 0);
         if (fseek(dbfile, iloc, SEEK_SET) == EOF) fprintf(stderr, "Error seeking database loc %d\n", iloc), exit_();
         y = z;
         z = 0;
      } else
         putchar(i);
   }

   if (nl)
      putchar('\n');
}

// Apply objects from parse vector
Bool objact(/*int x*/) {
// System generated locals
   Bool ret_val;

   ret_val = true;
// 						!ASSUME WINS.
   if (prsvec_1.prsi == 0) {
      goto L100;
   }
// 						!IND OBJECT?
   if (oappli(objcts_1.oactio[prsvec_1.prsi - 1], 0)) {
      return ret_val;
   }
// 						!YES, LET IT HANDLE.

L100:
   if (prsvec_1.prso == 0) {
      goto L200;
   }
// 						!DIR OBJECT?
   if (oappli(objcts_1.oactio[prsvec_1.prso - 1], 0)) {
      return ret_val;
   }
// 						!YES, LET IT HANDLE.

L200:
   ret_val = false;
// 						!LOSES.
   return ret_val;
}

// Report fatal system error
// Called as:
// 	bug(No, Par);
void bug(int a, int b) {
// Local variables

// print(" PROGRAM ERROR %I2, PARAMETER=%I6", a, b); //F
   more_output(NULL), printf("PROGRAM ERROR %d, PARAMETER=%d\n", a, b);
   if (debug_1.dbgflg != 0) {
      return;
   }
   exit_();
}

// Set new status for object
// Called as:
// 	newsta(Object, String, NewRoom, NewCon, NewAdv);
void newsta(int o, int r, int rm, int cn, int ad) {
   rspeak(r);
   objcts_1.oroom[o - 1] = rm;
   objcts_1.ocan[o - 1] = cn;
   objcts_1.oadv[o - 1] = ad;
}

// Test for object in room
Bool qhere(int obj, int rm) {
// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   int i;

   ret_val = true;
   if (objcts_1.oroom[obj - 1] == rm) {
      return ret_val;
   }
// 						!IN ROOM?
   i__1 = oroom2_1.r2lnt;
   for (i = 1; i <= i__1; ++i) {
// 						!NO, SCH ROOM2.
      if (oroom2_1.oroom2[i - 1] == obj && oroom2_1.rroom2[i - 1] == rm) {
         return ret_val;
      }
// L100:
   }
   ret_val = false;
// 						!NOT PRESENT.
   return ret_val;
}

// Test for object empty
Bool qempty(int obj) {
// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   int i;

   ret_val = false;
// 						!ASSUME LOSE.
   i__1 = objcts_1.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts_1.ocan[i - 1] == obj) {
         return ret_val;
      }
// 						!INSIDE TARGET?
// L100:
   }
   ret_val = true;
   return ret_val;
}

// You are dead
void jigsup(int desc) {
// Initialized data
   static const int rlist[9] = { 8, 6, 36, 35, 34, 4, 34, 6, 5 };

// System generated locals
   int i__1;

// Local variables
   int nonofl;
   Bool f;
   int i, j;

// JIGSUP, PAGE 2

   rspeak(desc);
// 						!DESCRIBE SAD STATE.
   prsvec_1.prscon = 1;
// 						!STOP PARSER.
   if (debug_1.dbgflg != 0) {
      return;
   }
// 						!IF DBG, EXIT.
   advs_1.avehic[play_1.winner - 1] = 0;
// 						!GET RID OF VEHICLE.
   if (play_1.winner == aindex_1.player) {
      goto L100;
   }
// 						!HIMSELF?
   rspsub(432, objcts_1.odesc2[advs_1.aobj[play_1.winner - 1] - 1]);
// 						!NO, SAY WHO DIED.
   newsta(advs_1.aobj[play_1.winner - 1], 0, 0, 0, 0);
// 						!SEND TO HYPER SPACE.
   return;

L100:
   if (findex_1.endgmf) {
      goto L900;
   }
// 						!NO RECOVERY IN END GAME.
#if 1
// always exit for plopbot's purposes
   goto L1000;
#else
   if (state_1.deaths >= 2) {
      goto L1000;
   }
#endif
// 						!DEAD TWICE? KICK HIM OFF.
   if (!yesno(10, 9, 8)) {
      goto L1100;
   }
// 						!CONTINUE?

   i__1 = objcts_1.olnt;
   for (j = 1; j <= i__1; ++j) {
// 						!TURN OFF FIGHTING.
      if (qhere(j, play_1.here)) {
         objcts_1.oflag2[j - 1] &= ~FiteO;
      }
// L50:
   }

   ++state_1.deaths;
   scrupd(-10);
// 						!CHARGE TEN POINTS.
   f = moveto(rindex_1.fore1, play_1.winner);
// 						!REPOSITION HIM.
   findex_1.egyptf = true;
// 						!RESTORE COFFIN.
   if (objcts_1.oadv[oindex_1.coffi - 1] == play_1.winner) {
      newsta(oindex_1.coffi, 0, rindex_1.egypt, 0, 0);
   }
   objcts_1.oflag2[oindex_1.door - 1] &= ~TChO;
   objcts_1.oflag1[oindex_1.robot - 1] = (objcts_1.oflag1[oindex_1.robot - 1] | VisiO) & ~NDscO;
   if (objcts_1.oroom[oindex_1.lamp - 1] != 0 || objcts_1.oadv[oindex_1.lamp - 1] == play_1.winner) {
      newsta(oindex_1.lamp, 0, rindex_1.lroom, 0, 0);
   }

// NOW REDISTRIBUTE HIS VALUABLES AND OTHER BELONGINGS.

// THE LAMP HAS BEEN PLACED IN THE LIVING ROOM.
// THE FIRST 8 NON-VALUABLES ARE PLACED IN LOCATIONS AROUND THE HOUSE.
// HIS VALUABLES ARE PLACED AT THE END OF THE MAZE.
// REMAINING NON-VALUABLES ARE PLACED AT THE END OF THE MAZE.

   i = 1;
   i__1 = objcts_1.olnt;
   for (j = 1; j <= i__1; ++j) {
// 						!LOOP THRU OBJECTS.
      if (objcts_1.oadv[j - 1] != play_1.winner || objcts_1.otval[j - 1] != 0) {
         goto L200;
      }
      ++i;
      if (i > 9) {
         goto L400;
      }
// 						!MOVE TO RANDOM LOCATIONS.
      newsta(j, 0, rlist[i - 1], 0, 0);
   L200:
      ;
   }

L400:
   i = rooms_1.rlnt + 1;
// 						!NOW MOVE VALUABLES.
   nonofl = AirR + WaterR + SacrdR + EndR;
// 						!DONT MOVE HERE.
   i__1 = objcts_1.olnt;
   for (j = 1; j <= i__1; ++j) {
      if (objcts_1.oadv[j - 1] != play_1.winner || objcts_1.otval[j - 1] == 0) {
         goto L300;
      }
   L250:
      --i;
// 						!FIND NEXT ROOM.
      if ((rooms_1.rflag[i - 1] & nonofl) != 0) {
         goto L250;
      }
      newsta(j, 0, i, 0, 0);
// 						!YES, MOVE.
   L300:
      ;
   }

   i__1 = objcts_1.olnt;
   for (j = 1; j <= i__1; ++j) {
// 						!NOW GET RID OF REMAINDER.
      if (objcts_1.oadv[j - 1] != play_1.winner) {
         goto L500;
      }
   L450:
      --i;
// 						!FIND NEXT ROOM.
      if ((rooms_1.rflag[i - 1] & nonofl) != 0) {
         goto L450;
      }
      newsta(j, 0, i, 0, 0);
   L500:
      ;
   }
   return;

// CAN'T OR WON'T CONTINUE, CLEAN UP AND EXIT.

L900:
   rspeak(625);
// 						!IN ENDGAME, LOSE.
   goto L1100;

L1000:
   rspeak(7);
// 						!INVOLUNTARY EXIT.
L1100:
   score(false);
// 						!TELL SCORE.
// close(chan_1.dbch); //F
   (void)fclose(dbfile);
   exit_();
}

// Get actor associated with object
int oactor(int obj) {
// System generated locals
   int ret_val = 1, i__1;

// Local variables
   int i;

   i__1 = advs_1.alnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP THRU ACTORS.
      ret_val = i;
// 						!ASSUME FOUND.
      if (advs_1.aobj[i - 1] == obj) {
         return ret_val;
      }
// 						!FOUND IT?
// L100:
   }
   bug(40, obj);
// 						!NO, DIE.
   return ret_val;
}

// Compute probability
Bool prob(int g, int b) {
// System generated locals
   Bool ret_val;

// Local variables
   int i;

   i = g;
// 						!ASSUME GOOD LUCK.
   if (findex_1.badlkf) {
      i = b;
   }
// 						!IF BAD, TOO BAD.
   ret_val = rnd(100) < i;
// 						!COMPUTE.
   return ret_val;
}

// Print room description
// rmdesc() prints a description of the current room.
// It is also the processor for verbs ‛LOOK’ and ‛EXAMINE’.
Bool rmdesc(int full) {
// System generated locals
   Bool ret_val, L__1;

// Local variables
   int i, ra;

// FULL=	0/1/2/3=	SHORT/OBJ/ROOM/FULL

// RMDESC, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (prsvec_1.prso < xsrch_1.xmin) {
      goto L50;
   }
// 						!IF DIRECTION,
   screen_1.fromdr = prsvec_1.prso;
// 						!SAVE AND
   prsvec_1.prso = 0;
// 						!CLEAR.
L50:
   if (play_1.here == advs_1.aroom[aindex_1.player - 1]) {
      goto L100;
   }
// 						!PLAYER JUST MOVE?
   rspeak(2);
// 						!NO, JUST SAY DONE.
   prsvec_1.prsa = vindex_1.walkiw;
// 						!SET UP WALK IN ACTION.
   return ret_val;

L100:
   if (lit(play_1.here)) {
      goto L300;
   }
// 						!LIT?
   rspeak(430);
// 						!WARN OF GRUE.
   ret_val = false;
   return ret_val;

L300:
   ra = rooms_1.ractio[play_1.here - 1];
// 						!GET ROOM ACTION.
   if (full == 1) {
      goto L600;
   }
// 						!OBJ ONLY?
   i = rooms_1.rdesc2[play_1.here - 1];
// 						!ASSUME SHORT DESC.
// The following comment, in the 1991 C translation, was inherited from a later version of the original Fortran source.
// 2021/09/22 Darth Spectra
// The next line means that when you request VERBOSE mode, you only get long room descriptions 20% of the time.
// I don't either like or understand this, so the mod. ensures VERBOSE works all the time.
// 1987/10/22 jmh@ukc.ac.uk
#if 1
   if (full == 0 && (findex_1.superf || (rooms_1.rflag[play_1.here - 1] & SeenR) != 0 && findex_1.brieff)) {
      goto L400;
   }
#else
   if (full == 0 && (findex_1.superf || (rooms_1.rflag[play_1.here - 1] & SeenR) != 0 && (findex_1.brieff || prob(80, 80)))) {
      goto L400;
   }
#endif
   i = rooms_1.rdesc1[play_1.here - 1];
// 						!USE LONG.
   if (i != 0 || ra == 0) {
      goto L400;
   }
// 						!IF GOT DESC, SKIP.
   prsvec_1.prsa = vindex_1.lookw;
// 						!PRETEND LOOK AROUND.
   if (!rappli(ra)) {
      goto L100;
   }
// 						!ROOM HANDLES, NEW DESC?
   prsvec_1.prsa = vindex_1.foow;
// 						!NOP PARSER.
   goto L500;

L400:
   rspeak(i);
// 						!OUTPUT DESCRIPTION.
L500:
   if (advs_1.avehic[play_1.winner - 1] != 0) {
      rspsub(431, objcts_1.odesc2[advs_1.avehic[play_1.winner - 1] - 1]);
   }

L600:
   if (full != 2) {
      L__1 = full != 0;
      princr(L__1, play_1.here);
   }
   rooms_1.rflag[play_1.here - 1] |= SeenR;
   if (full != 0 || ra == 0) {
      return ret_val;
   }
// 						!ANYTHING MORE?
   prsvec_1.prsa = vindex_1.walkiw;
// 						!GIVE HIM A SURPISE.
   if (!rappli(ra)) {
      goto L100;
   }
// 						!ROOM HANDLES, NEW DESC?
   prsvec_1.prsa = vindex_1.foow;
   return ret_val;
}

// Routing routine for room applicables
Bool rappli(int ri) {
// Initialized data
   const int newrms = 38;

// System generated locals
   Bool ret_val;

   ret_val = true;
// 						!ASSUME WINS.
   if (ri == 0) {
      return ret_val;
   }
// 						!IF ZERO, WIN.
   if (ri < newrms) {
      ret_val = rappl1(ri);
   }
// 						!IF OLD, PROCESSOR 1.
   if (ri >= newrms) {
      ret_val = rappl2(ri);
   }
// 						!IF NEW, PROCESSOR 2.
   return ret_val;
}
