// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Resident subroutines for dungeon

// Output random message routine
// Called as:
// 	rspeak(MsgNum);
void rspeak(int n) {
   rspsb2(n, 0, 0);
}

// Output random message with substitutable argument
// Called as:
// 	rspsub(MsgNum, SubNum);
void rspsub(int n, int s1) {
   rspsb2(n, s1, 0);
}

// Output random message with up to two substitutable arguments
// Called as:
// 	rspsb2(MsgNum, SubNum1, SubNum2);
void rspsb2(int n, int s1, int s2) {
// System generated locals
   int i__1;

// Local variables
   int i, j, x, y, z;
   char b1[74], b2[74], b3[74];
   int k1, k2, x1;
   short jrec, oldrec, newrec;

// CONVERT ALL ARGUMENTS FROM DICTIONARY NUMBERS (IF POSITIVE)
// TO ABSOLUTE RECORD NUMBERS.

   x = n;
// 						!SET UP WORK VARIABLES.
   y = s1;
   z = s2;
   if (x > 0) {
      x = rmsg.rtext[x - 1];
   }
// 						!IF >0, LOOK UP IN RTEXT.
   if (y > 0) {
      y = rmsg.rtext[y - 1];
   }
   if (z > 0) {
      z = rmsg.rtext[z - 1];
   }
   x = abs(x);
// 						!TAKE ABS VALUE.
   y = abs(y);
   z = abs(z);
   if (x == 0) {
      return;
   }
// 						!ANYTHING TO DO?
   play.telflg = true;
// 						!SAID SOMETHING.

// read(unit:chan.dbch, rec:x, &oldrec, b1); //F
   BegInDU(chan.dbch, x), DoUio(1, &oldrec, sizeof oldrec), DoUio(1, b1, sizeof b1), EndInDU();

L100:
   for (i = 1; i <= 74; ++i) {
      x1 = (x & 31) + i;
      b1[i - 1] = (char)(b1[i - 1] ^ x1);
// L150:
   }

L200:
   if (y == 0) {
      goto L400;
   }
// 						!ANY SUBSTITUTABLE?
   for (i = 1; i <= 74; ++i) {
// 						!YES, LOOK FOR #.
      if (b1[i - 1] == '#') {
         goto L1000;
      }
// L300:
   }

L400:
   for (i = 74; i >= 1; --i) {
// 						!BACKSCAN FOR BLANKS.
      if (b1[i - 1] != ' ') {
         goto L600;
      }
// L500:
   }

L600:
// write(chan.outch, "%1X%74A1", (b1[j - 1], j = 1, i)); //F
   BegExSF(chan.outch, "(1x,74a1)");
   i__1 = i;
   for (j = 1; j <= i__1; ++j) DoFio(1, &b1[j - 1], 1*sizeof b1[0]);
   EndExSF();
   ++x;
// 						!ON TO NEXT RECORD.
// read(unit:chan.dbch, rec:1, &newrec, b1); //F
   BegInDU(chan.dbch, x), DoUio(1, &newrec, sizeof newrec), DoUio(1, b1, sizeof b1), EndInDU();
   if (oldrec == newrec) {
      goto L100;
   }
// 						!CONTINUATION?
   return;
// 						!NO, EXIT.

// SUBSTITUTION WITH SUBSTITUTABLE AVAILABLE.
// I IS INDEX OF # IN B1.
// Y IS NUMBER OF RECORD TO SUBSTITUTE.

// PROCEDURE:
//   1) COPY REST OF B1 TO B2
//   2) READ SUBSTITUTABLE OVER B1
//   3) RESTORE TAIL OF ORIGINAL B1

// THE IMPLICIT ASSUMPTION HERE IS THAT THE SUBSTITUTABLE STRING
// IS VERY SHORT (i.e. MUCH LESS THAN ONE RECORD).

L1000:
   k2 = 1;
// 						!TO
   for (k1 = i + 1; k1 <= 74; ++k1) {
// 						!COPY REST OF B1.
      b2[k2 - 1] = b1[k1 - 1];
      ++k2;
// L1100:
   }

//   READ SUBSTITUTE STRING INTO B3, AND DECRYPT IT:

// read(unit:chan.dbch, rec:y, &jrec, b3); //F
   BegInDU(chan.dbch, y), DoUio(1, &jrec, sizeof jrec), DoUio(1, b3, sizeof b3), EndInDU();
   for (k1 = 1; k1 <= 74; ++k1) {
      x1 = (y & 31) + k1;
      b3[k1 - 1] = (char)(b3[k1 - 1] ^ x1);
// L1150:
   }

//   FILL REMAINDER OF B1 WITH CHARACTERS FROM B3:

   k2 = 1;
   for (k1 = i; k1 <= 74; ++k1) {
      b1[k1 - 1] = b3[k2 - 1];
      ++k2;
// L1180:
   }

//   FIND END OF SUBSTITUTE STRING IN B1:

   for (j = 74; j >= 1; --j) {
// 						!ELIM TRAILING BLANKS.
      if (b1[j - 1] != ' ') {
         goto L1300;
      }
// L1200:
   }

//   PUT TAIL END OF B1 (NOW IN B2) BACK INTO B1 AFTER SUBSTITUTE STRING:

L1300:
   k1 = 1;
// 						!FROM
   for (k2 = j + 1; k2 <= 74; ++k2) {
// 						!COPY REST OF B1 BACK.
      b1[k2 - 1] = b2[k1 - 1];
      ++k1;
// L1400:
   }

   y = z;
// 						!SET UP FOR NEXT
   z = 0;
// 						!SUBSTITUTION AND
   goto L200;
// 						!RECHECK LINE.
}

// Apply objects from parse vector
Bool objact(/*int x*/) {
// System generated locals
   Bool ret_val;

   ret_val = true;
// 						!ASSUME WINS.
   if (prsvec.prsi == 0) {
      goto L100;
   }
// 						!IND OBJECT?
   if (oappli(objcts.oactio[prsvec.prsi - 1], 0)) {
      return ret_val;
   }
// 						!YES, LET IT HANDLE.

L100:
   if (prsvec.prso == 0) {
      goto L200;
   }
// 						!DIR OBJECT?
   if (oappli(objcts.oactio[prsvec.prso - 1], 0)) {
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
   BegExSF(6, "(\2 PROGRAM ERROR \2,i2,\2, PARAMETER=\2,i6)");
   DoFio(1, &a, sizeof a), DoFio(1, &b, sizeof b);
   EndExSF();
   if (debug.dbgflg != 0) {
      return;
   }
   exit_();
}

// Set new status for object
// Called as:
// 	newsta(Object, String, NewRoom, NewCon, NewAdv);
void newsta(int o, int r, int rm, int cn, int ad) {
   rspeak(r);
   objcts.oroom[o - 1] = rm;
   objcts.ocan[o - 1] = cn;
   objcts.oadv[o - 1] = ad;
}

// Test for object in room
Bool qhere(int obj, int rm) {
// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   int i;

   ret_val = true;
   if (objcts.oroom[obj - 1] == rm) {
      return ret_val;
   }
// 						!IN ROOM?
   i__1 = oroom2_.r2lnt;
   for (i = 1; i <= i__1; ++i) {
// 						!NO, SCH ROOM2.
      if (oroom2_.oroom2[i - 1] == obj && oroom2_.rroom2[i - 1] == rm) {
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
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts.ocan[i - 1] == obj) {
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
   prsvec.prscon = 1;
// 						!STOP PARSER.
   if (debug.dbgflg != 0) {
      return;
   }
// 						!IF DBG, EXIT.
   advs.avehic[play.winner - 1] = 0;
// 						!GET RID OF VEHICLE.
   if (play.winner == PlayerAX) {
      goto L100;
   }
// 						!HIMSELF?
   rspsub(432, objcts.odesc2[advs.aobj[play.winner - 1] - 1]);
// 						!NO, SAY WHO DIED.
   newsta(advs.aobj[play.winner - 1], 0, 0, 0, 0);
// 						!SEND TO HYPER SPACE.
   return;

L100:
   if (findex.endgmf) {
      goto L900;
   }
// 						!NO RECOVERY IN END GAME.
#if 0
// always exit for plopbot's purposes
   goto L1000;
#else
   if (state.deaths >= 2) {
      goto L1000;
   }
#endif
// 						!DEAD TWICE? KICK HIM OFF.
   if (!yesno(10, 9, 8)) {
      goto L1100;
   }
// 						!CONTINUE?

   i__1 = objcts.olnt;
   for (j = 1; j <= i__1; ++j) {
// 						!TURN OFF FIGHTING.
      if (qhere(j, play.here)) {
         objcts.oflag2[j - 1] &= ~FiteO;
      }
// L50:
   }

   ++state.deaths;
   scrupd(-10);
// 						!CHARGE TEN POINTS.
   f = moveto(Fore1RX, play.winner);
// 						!REPOSITION HIM.
   findex.egyptf = true;
// 						!RESTORE COFFIN.
   if (objcts.oadv[CoffiOX - 1] == play.winner) {
      newsta(CoffiOX, 0, EgyptRX, 0, 0);
   }
   objcts.oflag2[DoorOX - 1] &= ~TChO;
   objcts.oflag1[RobotOX - 1] = (objcts.oflag1[RobotOX - 1] | VisiO) & ~NDscO;
   if (objcts.oroom[LampOX - 1] != 0 || objcts.oadv[LampOX - 1] == play.winner) {
      newsta(LampOX, 0, LRoomRX, 0, 0);
   }

// NOW REDISTRIBUTE HIS VALUABLES AND OTHER BELONGINGS.

// THE LAMP HAS BEEN PLACED IN THE LIVING ROOM.
// THE FIRST 8 NON-VALUABLES ARE PLACED IN LOCATIONS AROUND THE HOUSE.
// HIS VALUABLES ARE PLACED AT THE END OF THE MAZE.
// REMAINING NON-VALUABLES ARE PLACED AT THE END OF THE MAZE.

   i = 1;
   i__1 = objcts.olnt;
   for (j = 1; j <= i__1; ++j) {
// 						!LOOP THRU OBJECTS.
      if (objcts.oadv[j - 1] != play.winner || objcts.otval[j - 1] != 0) {
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
   i = rooms.rlnt + 1;
// 						!NOW MOVE VALUABLES.
   nonofl = AirR + WaterR + SacrdR + EndR;
// 						!DONT MOVE HERE.
   i__1 = objcts.olnt;
   for (j = 1; j <= i__1; ++j) {
      if (objcts.oadv[j - 1] != play.winner || objcts.otval[j - 1] == 0) {
         goto L300;
      }
   L250:
      --i;
// 						!FIND NEXT ROOM.
      if ((rooms.rflag[i - 1] & nonofl) != 0) {
         goto L250;
      }
      newsta(j, 0, i, 0, 0);
// 						!YES, MOVE.
   L300:
      ;
   }

   i__1 = objcts.olnt;
   for (j = 1; j <= i__1; ++j) {
// 						!NOW GET RID OF REMAINDER.
      if (objcts.oadv[j - 1] != play.winner) {
         goto L500;
      }
   L450:
      --i;
// 						!FIND NEXT ROOM.
      if ((rooms.rflag[i - 1] & nonofl) != 0) {
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
// close(chan.dbch); //F
   CloseF(chan.dbch);
   exit_();
}

// Get actor associated with object
int oactor(int obj) {
// System generated locals
   int ret_val = 1, i__1;

// Local variables
   int i;

   i__1 = advs.alnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP THRU ACTORS.
      ret_val = i;
// 						!ASSUME FOUND.
      if (advs.aobj[i - 1] == obj) {
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
   if (findex.badlkf) {
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
   if (prsvec.prso < MinDX) {
      goto L50;
   }
// 						!IF DIRECTION,
   screen.fromdr = prsvec.prso;
// 						!SAVE AND
   prsvec.prso = 0;
// 						!CLEAR.
L50:
   if (play.here == advs.aroom[PlayerAX - 1]) {
      goto L100;
   }
// 						!PLAYER JUST MOVE?
   rspeak(2);
// 						!NO, JUST SAY DONE.
   prsvec.prsa = WalkIW;
// 						!SET UP WALK IN ACTION.
   return ret_val;

L100:
   if (lit(play.here)) {
      goto L300;
   }
// 						!LIT?
   rspeak(430);
// 						!WARN OF GRUE.
   ret_val = false;
   return ret_val;

L300:
   ra = rooms.ractio[play.here - 1];
// 						!GET ROOM ACTION.
   if (full == 1) {
      goto L600;
   }
// 						!OBJ ONLY?
   i = rooms.rdesc2 - play.here;
// 						!ASSUME SHORT DESC.
// The following comment, in the 1991 C translation, was inherited from a later version of the original Fortran source.
// 2021/09/22 Darth Spectra
// The next line means that when you request VERBOSE mode, you only get long room descriptions 20% of the time.
// I don't either like or understand this, so the mod. ensures VERBOSE works all the time.
// 1987/10/22 jmh@ukc.ac.uk
#if 0
   if (full == 0 && (findex.superf || (rooms.rflag[play.here - 1] & SeenR) != 0 && findex.brieff)) {
      goto L400;
   }
#else
   if (full == 0 && (findex.superf || (rooms.rflag[play.here - 1] & SeenR) != 0 && (findex.brieff || prob(80, 80)))) {
      goto L400;
   }
#endif
   i = rooms.rdesc1[play.here - 1];
// 						!USE LONG.
   if (i != 0 || ra == 0) {
      goto L400;
   }
// 						!IF GOT DESC, SKIP.
   prsvec.prsa = LookW;
// 						!PRETEND LOOK AROUND.
   if (!rappli(ra)) {
      goto L100;
   }
// 						!ROOM HANDLES, NEW DESC?
   prsvec.prsa = FooW;
// 						!NOP PARSER.
   goto L500;

L400:
   rspeak(i);
// 						!OUTPUT DESCRIPTION.
L500:
   if (advs.avehic[play.winner - 1] != 0) {
      rspsub(431, objcts.odesc2[advs.avehic[play.winner - 1] - 1]);
   }

L600:
   if (full != 2) {
      L__1 = full != 0;
      princr(L__1, play.here);
   }
   rooms.rflag[play.here - 1] |= SeenR;
   if (full != 0 || ra == 0) {
      return ret_val;
   }
// 						!ANYTHING MORE?
   prsvec.prsa = WalkIW;
// 						!GIVE HIM A SURPISE.
   if (!rappli(ra)) {
      goto L100;
   }
// 						!ROOM HANDLES, NEW DESC?
   prsvec.prsa = FooW;
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
