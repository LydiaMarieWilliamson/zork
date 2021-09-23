// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

static void lookto(int, int, int, int, int);
static void ewtell(int, int);

// Special purpose room routines, part 2
Bool rappl2(int ri) {
// Initialized data
   const int newrms = 38;

// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   int i;
   int j;

// RAPPL2, PAGE 2

   ret_val = true;
   switch (ri - newrms + 1) {
      case 1:
         goto L38000;
      case 2:
         goto L39000;
      case 3:
         goto L40000;
      case 4:
         goto L41000;
      case 5:
         goto L42000;
      case 6:
         goto L43000;
      case 7:
         goto L44000;
      case 8:
         goto L45000;
      case 9:
         goto L46000;
      case 10:
         goto L47000;
      case 11:
         goto L48000;
      case 12:
         goto L49000;
      case 13:
         goto L50000;
      case 14:
         goto L51000;
      case 15:
         goto L52000;
      case 16:
         goto L53000;
      case 17:
         goto L54000;
      case 18:
         goto L55000;
      case 19:
         goto L56000;
      case 20:
         goto L57000;
      case 21:
         goto L58000;
      case 22:
         goto L59000;
      case 23:
         goto L60000;
   }
   bug(70, ri);
   return ret_val;

// R38--	MIRROR D ROOM

L38000:
   if (prsvec.prsa == LookW) {
      lookto(FDoorRX, MrGrX, 0, 682, 681);
   }
   return ret_val;

// R39--	MIRROR G ROOM

L39000:
   if (prsvec.prsa == WalkIW) {
      jigsup(685);
   }
   return ret_val;

// R40--	MIRROR C ROOM

L40000:
   if (prsvec.prsa == LookW) {
      lookto(MrGrX, MrBrX, 683, 0, 681);
   }
   return ret_val;

// R41--	MIRROR B ROOM

L41000:
   if (prsvec.prsa == LookW) {
      lookto(MrCrX, MrArX, 0, 0, 681);
   }
   return ret_val;

// R42--	MIRROR A ROOM

L42000:
   if (prsvec.prsa == LookW) {
      lookto(MrBrX, 0, 0, 684, 681);
   }
   return ret_val;
// RAPPL2, PAGE 3

// R43--	MIRROR C EAST/WEST

L43000:
   if (prsvec.prsa == LookW) {
      ewtell(play.here, 683);
   }
   return ret_val;

// R44--	MIRROR B EAST/WEST

L44000:
   if (prsvec.prsa == LookW) {
      ewtell(play.here, 686);
   }
   return ret_val;

// R45--	MIRROR A EAST/WEST

L45000:
   if (prsvec.prsa == LookW) {
      ewtell(play.here, 687);
   }
   return ret_val;

// R46--	INSIDE MIRROR

L46000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(688);
// 						!DESCRIBE

// NOW DESCRIBE POLE STATE.

// CASES 1,2--	MDIR=270 & MLOC=MRB, POLE IS UP OR IN HOLE
// CASES 3,4--	MDIR=0 V MDIR=180, POLE IS UP OR IN CHANNEL
// CASE 5--	POLE IS UP

   i = 689;
// 						!ASSUME CASE 5.
   if (findex.mdir == 270 && findex.mloc == MrBrX) {
      i = min(findex.poleuf, 1) + 690;
   }
   if (findex.mdir % 180 == 0) {
      i = min(findex.poleuf, 1) + 692;
   }
   rspeak(i);
// 						!DESCRIBE POLE.
   i__1 = findex.mdir / 45 + 695;
   rspsub(694, i__1);
// 						!DESCRIBE ARROW.
   return ret_val;
// RAPPL2, PAGE 4

// R47--	MIRROR EYE ROOM

L47000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 704;
// 						!ASSUME BEAM STOP.
   i__1 = objcts.olnt;
   for (j = 1; j <= i__1; ++j) {
      if (qhere(j, play.here) && j != RBeamOX) {
         goto L47200;
      }
// L47100:
   }
   i = 703;
L47200:
   rspsub(i, objcts.odesc2[j - 1]);
// 						!DESCRIBE BEAM.
   lookto(MrArX, 0, 0, 0, 0);
// 						!LOOK NORTH.
   return ret_val;

// R48--	INSIDE CRYPT

L48000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 46;
// 						!CRYPT IS OPEN/CLOSED.
   if ((objcts.oflag2[TombOX - 1] & OpenO) != 0) {
      i = 12;
   }
   rspsub(705, i);
   return ret_val;

// R49--	SOUTH CORRIDOR

L49000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(706);
// 						!DESCRIBE.
   i = 46;
// 						!ODOOR IS OPEN/CLOSED.
   if ((objcts.oflag2[ODoorOX - 1] & OpenO) != 0) {
      i = 12;
   }
   if (findex.lcell == 4) {
      rspsub(707, i);
   }
// 						!DESCRIBE ODOOR IF THERE.
   return ret_val;

// R50--	BEHIND DOOR

L50000:
   if (prsvec.prsa != WalkIW) {
      goto L50100;
   }
// 						!WALK IN?
   cevent.cflag[FolCX - 1] = true;
// 						!MASTER FOLLOWS.
   cevent.ctick[FolCX - 1] = -1;
   return ret_val;

L50100:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 46;
// 						!QDOOR IS OPEN/CLOSED.
   if ((objcts.oflag2[QDoorOX - 1] & OpenO) != 0) {
      i = 12;
   }
   rspsub(708, i);
   return ret_val;
// RAPPL2, PAGE 5

// R51--	FRONT DOOR

L51000:
   if (prsvec.prsa == WalkIW) {
      cevent.ctick[FolCX - 1] = 0;
   }
// 						!IF EXITS, KILL FOLLOW.
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   lookto(0, MrDrX, 709, 0, 0);
// 						!DESCRIBE SOUTH.
   i = 46;
// 						!PANEL IS OPEN/CLOSED.
   if (findex.inqstf) {
      i = 12;
   }
// 						!OPEN IF INQ STARTED.
   j = 46;
// 						!QDOOR IS OPEN/CLOSED.
   if ((objcts.oflag2[QDoorOX - 1] & OpenO) != 0) {
      j = 12;
   }
   rspsb2(710, i, j);
   return ret_val;

// R52--	NORTH CORRIDOR

L52000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 46;
   if ((objcts.oflag2[CDoorOX - 1] & OpenO) != 0) {
      i = 12;
   }
// 						!CDOOR IS OPEN/CLOSED.
   rspsub(711, i);
   return ret_val;

// R53--	PARAPET

L53000:
   if (prsvec.prsa == LookW) {
      i__1 = findex.pnumb + 712;
      rspsub(712, i__1);
   }
   return ret_val;

// R54--	CELL

L54000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 721;
// 						!CDOOR IS OPEN/CLOSED.
   if ((objcts.oflag2[CDoorOX - 1] & OpenO) != 0) {
      i = 722;
   }
   rspeak(i);
   i = 46;
// 						!ODOOR IS OPEN/CLOSED.
   if ((objcts.oflag2[ODoorOX - 1] & OpenO) != 0) {
      i = 12;
   }
   if (findex.lcell == 4) {
      rspsub(723, i);
   }
// 						!DESCRIBE.
   return ret_val;

// R55--	PRISON CELL

L55000:
   if (prsvec.prsa == LookW) {
      rspeak(724);
   }
// 						!LOOK?
   return ret_val;

// R56--	NIRVANA CELL

L56000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 46;
// 						!ODOOR IS OPEN/CLOSED.
   if ((objcts.oflag2[ODoorOX - 1] & OpenO) != 0) {
      i = 12;
   }
   rspsub(725, i);
   return ret_val;
// RAPPL2, PAGE 6

// R57--	NIRVANA AND END OF GAME

L57000:
   if (prsvec.prsa != WalkIW) {
      return ret_val;
   }
// 						!WALKIN?
   rspeak(726);
   score(false);
// moved to exit routine	CLOSE(DBCH)
   exit_();

// R58--	TOMB ROOM

L58000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 46;
// 						!TOMB IS OPEN/CLOSED.
   if ((objcts.oflag2[TombOX - 1] & OpenO) != 0) {
      i = 12;
   }
   rspsub(792, i);
   return ret_val;

// R59--	PUZZLE SIDE ROOM

L59000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 861;
// 						!ASSUME DOOR CLOSED.
   if (findex.cpoutf) {
      i = 862;
   }
// 						!OPEN?
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

// R60--	PUZZLE ROOM

L60000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   if (findex.cpushf) {
      goto L60100;
   }
// 						!STARTED PUZZLE?
   rspeak(868);
// 						!NO, DESCRIBE.
   if ((objcts.oflag2[WarniOX - 1] & TChO) != 0) {
      rspeak(869);
   }
   return ret_val;

L60100:
   cpinfo(880, findex.cphere);
// 						!DESCRIBE ROOM.
   return ret_val;
}

// Describe view in mirror hallway
static void lookto(int nrm, int srm, int nt, int st, int ht) {
// System generated locals
   int i__1;

// Local variables
   int i, m1, dir, mrbf;

// LOOKTO, PAGE 2

   rspeak(ht);
// 						!DESCRIBE HALL.
   rspeak(nt);
// 						!DESCRIBE NORTH VIEW.
   rspeak(st);
// 						!DESCRIBE SOUTH VIEW.
   dir = 0;
// 						!ASSUME NO DIRECTION.
   if ((i__1 = findex.mloc - play.here, abs(i__1)) != 1) {
      goto L200;
   }
// 						!MIRROR TO N OR S?
   if (findex.mloc == nrm) {
      dir = 695;
   }
   if (findex.mloc == srm) {
      dir = 699;
   }
// 						!DIR=N/S.
   if (findex.mdir % 180 != 0) {
      goto L100;
   }
// 						!MIRROR N-S?
   rspsub(847, dir);
// 						!YES, HE SEES PANEL
   rspsb2(848, dir, dir);
// 						!AND NARROW ROOMS.
   goto L200;

L100:
   m1 = mrhere(play.here);
// 						!WHICH MIRROR?
   mrbf = 0;
// 						!ASSUME INTACT.
   if (m1 == 1 && !findex.mr1f || m1 == 2 && !findex.mr2f) {
      mrbf = 1;
   }
   i__1 = mrbf + 849;
   rspsub(i__1, dir);
// 						!DESCRIBE.
   if (m1 == 1 && findex.mropnf) {
      i__1 = mrbf + 823;
      rspeak(i__1);
   }
   if (mrbf != 0) {
      rspeak(851);
   }

L200:
   i = 0;
// 						!ASSUME NO MORE TO DO.
   if (nt == 0 && (dir == 0 || dir == 699)) {
      i = 852;
   }
   if (st == 0 && (dir == 0 || dir == 695)) {
      i = 853;
   }
   if (nt + st + dir == 0) {
      i = 854;
   }
   if (ht != 0) {
      rspeak(i);
   }
// 						!DESCRIBE HALLS.
}

// Describe e/w narrow rooms
static void ewtell(int rm, int st) {
// System generated locals
   int i__1;

// Local variables
   int i;
   Bool m1;

// EWTELL, PAGE 2

// NOTE THAT WE ARE EAST OR WEST OF MIRROR, AND
// MIRROR MUST BE N-S.

   m1 = findex.mdir + (rm - MrAerX) % 2 * 180 == 180;
   i = (rm - MrAerX) % 2 + 819;
// 						!GET BASIC E/W STRING.
   if (m1 && !findex.mr1f || !m1 && !findex.mr2f) {
      i += 2;
   }
   rspeak(i);
   if (m1 && findex.mropnf) {
      i__1 = (i - 819) / 2 + 823;
      rspeak(i__1);
   }
   rspeak(825);
   rspeak(st);
}
