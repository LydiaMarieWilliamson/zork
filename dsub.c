// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <stdio.h> // Particularly for: SEEK_SET and fseek().
#include <string.h> // For memcpy().
#include "extern.h"
#include "common.h"

// Resident subroutines for dungeon
bool GetRec(FILE *InF, long *locp, size_t *np, char buf[]) {
// inirnd(0xe1e26d38); // Seed: (3789712696) 0xe1e26d38: 1984-12-28 03:30 UTC
// for (int x = 0; x < 0x100; x++) key[x] = rnd(0x100);
   static unsigned char key[0x100] = {
      0x31, 0x5f, 0x58, 0xd7, 0x99, 0x0e, 0xc2, 0x79, 0xf5, 0xa1, 0xcf, 0x23, 0xb6, 0x7e, 0xe4, 0x86,
      0xdb, 0x3e, 0x65, 0x09, 0xa0, 0xc3, 0xdd, 0xd5, 0xee, 0x3c, 0xb5, 0xe6, 0x1c, 0x5c, 0x04, 0x3a,
      0x62, 0xcf, 0x19, 0x5e, 0x34, 0x61, 0x18, 0x8f, 0xa7, 0x08, 0xbc, 0x57, 0x8c, 0x64, 0xd8, 0x12,
      0x7d, 0xa0, 0xfa, 0xf7, 0x3e, 0xd5, 0x84, 0x91, 0xa0, 0x88, 0xbd, 0x48, 0xd4, 0xef, 0x6b, 0xf8,
      0xf8, 0x2f, 0xe4, 0x82, 0x2a, 0x08, 0xd3, 0xdd, 0xa1, 0x8a, 0xc8, 0xd8, 0xfd, 0x78, 0x76, 0x73,
      0xf5, 0x98, 0x12, 0x7f, 0xc6, 0x69, 0x36, 0x28, 0xc7, 0xb9, 0x0f, 0xe0, 0xbd, 0x26, 0xdb, 0x5e,
      0xd2, 0x4b, 0x4e, 0x2e, 0x8a, 0xfa, 0x03, 0x82, 0x07, 0x6c, 0x25, 0x7d, 0x70, 0xda, 0x5c, 0x52,
      0xb0, 0x6d, 0x82, 0x2a, 0x0a, 0x2f, 0x2d, 0x5c, 0x5d, 0xd3, 0xc9, 0x4d, 0xe5, 0x9e, 0xef, 0x4d,
      0x6b, 0xd6, 0x41, 0xe3, 0xe6, 0x95, 0xe9, 0xe8, 0x4d, 0x49, 0xaf, 0xfc, 0x81, 0x25, 0x17, 0xec,
      0x77, 0x60, 0xe0, 0xc3, 0x40, 0xb7, 0xe7, 0xb9, 0xba, 0x6c, 0xad, 0xd1, 0x15, 0x8b, 0x29, 0xa5,
      0x70, 0x18, 0xf6, 0x29, 0x3c, 0xd3, 0x5c, 0x1c, 0xe3, 0x46, 0x53, 0xc6, 0xc8, 0xd3, 0x5b, 0xa1,
      0xe2, 0x0c, 0x8d, 0x0a, 0x2c, 0x2d, 0x39, 0xcf, 0xcd, 0x26, 0xec, 0x88, 0x0d, 0xab, 0xb7, 0xcd,
      0x67, 0x8e, 0xf5, 0x7c, 0x7b, 0x17, 0x12, 0xff, 0xcc, 0x81, 0x63, 0xf7, 0xc9, 0xec, 0x3d, 0x3a,
      0xac, 0x31, 0x44, 0x8b, 0x32, 0xad, 0xac, 0x59, 0x5d, 0x52, 0x96, 0xa9, 0x6d, 0x80, 0xb5, 0x1f,
      0x07, 0x5f, 0x00, 0x6a, 0x51, 0x6c, 0xfb, 0xc7, 0xda, 0xc5, 0x88, 0xa9, 0x0b, 0x2d, 0xe2, 0x96,
      0xba, 0x6e, 0xec, 0xef, 0x41, 0x56, 0x92, 0xc4, 0x0d, 0x1a, 0x0d, 0x9c, 0xca, 0x0b, 0x95, 0xaa
   };
   long loc = *locp - 1;
   if (fseek(StoryF, loc, SEEK_SET) == EOF) fprintf(stderr, "Error seeking database at #%ld\n", loc), exit_();
   unsigned char ix;
   if (fread(&ix, sizeof ix, 1, InF) != 1) fprintf(stderr, "Error reading string size at #%ld\n", loc), exit_();
   else loc++;
   size_t n = ix & ~0x80; bool last = ix & 0x80;
   if (fread(buf, 1, n, InF) != n) fprintf(stderr, "Error reading string line at #%ld\n", loc), exit_();
   for (int i = 0; i < n; i++, loc++) buf[i] ^= key[loc & 0xff];
   buf[n] = '\0';
   *locp = loc;
   *np = n;
   return last;
}

// CONVERT ARGUMENT FROM DICTIONARY NUMBER (IF POSITIVE)
// TO ABSOLUTE RECORD NUMBER.
static long DeRef(int N) {
   long X = N;
// 						!SET UP WORK VARIABLE.
   if (X > 0) {
      X = rmsg.rtext[X - 1];
   }
// 						!IF >0, LOOK UP IN RTEXT.
   return abs(X);
// 						!TAKE ABS VALUE.
}

static void rspeak2(long, long, long);

// Output random message routine
// Called as:
// 	rspeak(MsgNum);
void rspeak(int n) {
   rspeak2(DeRef(n), 0, 0);
}

// Output random message with substitutable argument
// Called as:
// 	rspsub(MsgNum, SubNum);
void rspsub(int n, int s1) {
   rspeak2(DeRef(n), DeRef(s1), 0);
}

// Output random message with up to two substitutable arguments
// Called as:
// 	rspsb2(MsgNum, SubNum1, SubNum2);
void rspsb2(int n, int s1, int s2) {
   rspeak2(DeRef(n), DeRef(s1), DeRef(s2));
}

// Display a substitutable message.
static void rspeak2(long x, long y, long z) {
// Local variables
   size_t n1, n2, n3;
   char b1[2*0x80], b2[0x80], *b3;
   bool last;

   if (x == 0L) return;
// 						!ANYTHING TO DO?
   play.telflg = true;
// 						!SAID SOMETHING.
   do {
      last = GetRec(StoryF, &x, &n1, b1);
// 						!ANY SUBSTITUTABLE?
//    L200:
// 						!YES, LOOK FOR #.
      while (y != 0L && (b3 = index(b1, '#')) != NULL) {
//       SUBSTITUTION WITH SUBSTITUTABLE AVAILABLE.
//          B3 IS LOCATION OF # IN B1.
//          Y IS LOCATION OF RECORD TO SUBSTITUTE.

//       PROCEDURE:
//          1) COPY REST OF B1 TO B2
//          2) READ SUBSTITUTABLE OVER B1 AT B3
//          3) RESTORE TAIL OF ORIGINAL B1

//       THE IMPLICIT ASSUMPTION HERE IS THAT THE SUBSTITUTABLE STRING
//       IS VERY SHORT (i.e. MUCH LESS THAN ONE RECORD).

//       memcpy(A, B, strlen(B) + 1) is equivalent to strcpy(A, B), but is more Fortran-friendly.
         n2 = b1 + n1 - b3;
         memcpy(b2, b3 + 1, n2);
// 						!COPY REST OF B1 TO B2.
//       READ SUBSTITUTE STRING INTO REMAINDER OF B1, AND DECRYPT IT:
         (void)GetRec(StoryF, &y, &n3, b3);
//       FIND END OF SUBSTITUTE STRING IN B1:
         b3 += n3;
//       PUT TAIL END OF B1 (NOW IN B2) BACK INTO B1 AFTER SUBSTITUTE STRING:
         memcpy(b3, b2, n2);
// 						!COPY REST OF B1 BACK FROM B2.
         y = z;
// 						!SET UP FOR NEXT
         z = 0L;
// 						!SUBSTITUTION AND
//       goto L200;
// 						!RECHECK LINE.
      }
      more_output("%s\n", b1);
      x++;
// 						!ON TO NEXT RECORD.
   } while (!last);
// 						!CONTINUATION?
// 						!NO, EXIT.
}

// Apply objects from parse vector
bool objact(void) {
// System generated locals
   bool ret_val;

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

   more_output("PROGRAM ERROR %d, PARAMETER=%d\n", a, b);
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
bool qhere(int obj, int rm) {
// System generated locals
   int i__1;
   bool ret_val;

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
bool qempty(int obj) {
// System generated locals
   int i__1;
   bool ret_val;

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
   bool f;
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
   if (findex_0.endgmf) {
      goto L900;
   }
// 						!NO RECOVERY IN END GAME.
#if 1
   if (state.deaths >= 2) {
      goto L1000;
   }
// 						!DEAD TWICE? KICK HIM OFF.
#else
// always exit for plopbot's purposes
   goto L1000;
#endif
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
   findex_0.egyptf = true;
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
   (void)fclose(StoryF);
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
bool prob(int g, int b) {
// System generated locals
   bool ret_val;

// Local variables
   int i;

   i = g;
// 						!ASSUME GOOD LUCK.
   if (findex_0.badlkf) {
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
bool rmdesc(int full) {
// System generated locals
   bool ret_val;

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
   i = rooms.rdesc2[play.here - 1];
// 						!ASSUME SHORT DESC.
// The following comment, in the 1991 C translation, was inherited from a later version of the original Fortran source.
// 2021/09/22 Darth Spectra
#if 0
// The next line means that when you request VERBOSE mode, you only get long room descriptions 20% of the time.
// I don't either like or understand this, so the mod. ensures VERBOSE works all the time.
// 1987/10/22 jmh@ukc.ac.uk
   if (full == 0 && (findex_0.superf || (rooms.rflag[play.here - 1] & SeenR) != 0 && findex_0.brieff)) {
      goto L400;
   }
#else
   if (full == 0 && (findex_0.superf || (rooms.rflag[play.here - 1] & SeenR) != 0 && (findex_0.brieff || prob(80, 80)))) {
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
      princr(full != 0, play.here);
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
bool rappli(int ri) {
// Initialized data
   const int newrms = 38;

// System generated locals
   bool ret_val;

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
