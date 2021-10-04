// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Special purpose room routines, part 1
bool rappl1(int ri) {
// System generated locals
   int i__1, i__2;
   bool ret_val;

// Local variables
   bool f;
   int i;
   int j;

// RAPPL1, PAGE 2

   ret_val = true;
// 						!USUALLY IGNORED.
   if (ri == 0) {
      return ret_val;
   }
// 						!RETURN IF NAUGHT.

// 						!SET TO FALSE FOR

// 						!NEW DESC NEEDED.
   switch (ri) {
      case 1:
         goto L1000;
      case 2:
         goto L2000;
      case 3:
         goto L3000;
      case 4:
         goto L4000;
      case 5:
         goto L5000;
      case 6:
         goto L6000;
      case 7:
         goto L7000;
      case 8:
         goto L8000;
      case 9:
         goto L9000;
      case 10:
         goto L10000;
      case 11:
         goto L11000;
      case 12:
         goto L12000;
      case 13:
         goto L13000;
      case 14:
         goto L14000;
      case 15:
         goto L15000;
      case 16:
         goto L16000;
      case 17:
         goto L17000;
      case 18:
         goto L18000;
      case 19:
         goto L19000;
      case 20:
         goto L20000;
      case 21:
         goto L21000;
      case 22:
         goto L22000;
      case 23:
         goto L23000;
      case 24:
         goto L24000;
      case 25:
         goto L25000;
      case 26:
         goto L26000;
      case 27:
         goto L27000;
      case 28:
         goto L28000;
      case 29:
         goto L29000;
      case 30:
         goto L30000;
      case 31:
         goto L31000;
      case 32:
         goto L32000;
      case 33:
         goto L33000;
      case 34:
         goto L34000;
      case 35:
         goto L35000;
      case 36:
         goto L36000;
      case 37:
         goto L37000;
   }
   bug(1, ri);

// R1--	EAST OF HOUSE.  DESCRIPTION DEPENDS ON STATE OF WINDOW

L1000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 13;
// 						!ASSUME CLOSED.
   if ((objcts.oflag2[WindoOX - 1] & OpenO) != 0) {
      i = 12;
   }
// 						!IF OPEN, AJAR.
   rspsub(11, i);
// 						!DESCRIBE.
   return ret_val;

// R2--	KITCHEN.  SAME VIEW FROM INSIDE.

L2000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 13;
// 						!ASSUME CLOSED.
   if ((objcts.oflag2[WindoOX - 1] & OpenO) != 0) {
      i = 12;
   }
// 						!IF OPEN, AJAR.
   rspsub(14, i);
// 						!DESCRIBE.
   return ret_val;

// R3--	LIVING ROOM.  DESCRIPTION DEPENDS ON MAGICF (STATE OF
// 	DOOR TO CYCLOPS ROOM), RUG (MOVED OR NOT), DOOR (OPEN OR CLOSED)

L3000:
   if (prsvec.prsa != LookW) {
      goto L3500;
   }
// 						!LOOK?
   i = 15;
// 						!ASSUME NO HOLE.
   if (findex_0.magicf) {
      i = 16;
   }
// 						!IF MAGICF, CYCLOPS HOLE.
   rspeak(i);
// 						!DESCRIBE.
   i = findex_1.orrug + 17;
// 						!ASSUME INITIAL STATE.
   if ((objcts.oflag2[DoorOX - 1] & OpenO) != 0) {
      i += 2;
   }
// 						!DOOR OPEN?
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

// 	NOT A LOOK WORD.  REEVALUATE TROPHY CASE.

L3500:
   if (prsvec.prsa != TakeW && (prsvec.prsa != PutW || prsvec.prsi != TCaseOX)) {
      return ret_val;
   }
   advs.ascore[play.winner - 1] = state.rwscor;
// 						!SCORE TROPHY CASE.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!RETAIN RAW SCORE AS WELL.
      j = i;
// 						!FIND OUT IF IN CASE.
   L3550:
      j = objcts.ocan[j - 1];
// 						!TRACE OWNERSHIP.
      if (j == 0) {
         goto L3600;
      }
      if (j != TCaseOX) {
         goto L3550;
      }
// 						!DO ALL LEVELS.
      advs.ascore[play.winner - 1] += objcts.otval[i - 1];
   L3600:
      ;
   }
   scrupd(0);
// 						!SEE IF ENDGAME TRIG.
   return ret_val;
// RAPPL1, PAGE 3

// R4--	CELLAR.  SHUT DOOR AND BAR IT IF HE JUST WALKED IN.

L4000:
   if (prsvec.prsa != LookW) {
      goto L4500;
   }
// 						!LOOK?
   rspeak(21);
// 						!DESCRIBE CELLAR.
   return ret_val;

L4500:
   if (prsvec.prsa != WalkIW) {
      return ret_val;
   }
// 						!WALKIN?
   if ((objcts.oflag2[DoorOX - 1] & OpenO + TChO) != OpenO) {
      return ret_val;
   }
   objcts.oflag2[DoorOX - 1] = (objcts.oflag2[DoorOX - 1] | TChO) & ~OpenO;
   rspeak(22);
// 						!SLAM AND BOLT DOOR.
   return ret_val;

// R5--	MAZE11.  DESCRIBE STATE OF GRATING.

L5000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(23);
// 						!DESCRIBE.
   i = 24;
// 						!ASSUME LOCKED.
   if (findex_0.grunlf) {
      i = 26;
   }
// 						!UNLOCKED?
   if ((objcts.oflag2[GrateOX - 1] & OpenO) != 0) {
      i = 25;
   }
// 						!OPEN?
   rspeak(i);
// 						!DESCRIBE GRATE.
   return ret_val;

// R6--	CLEARING.  DESCRIBE CLEARING, MOVE LEAVES.

L6000:
   if (prsvec.prsa != LookW) {
      goto L6500;
   }
// 						!LOOK?
   rspeak(27);
// 						!DESCRIBE.
   if (findex_1.rvclr == 0) {
      return ret_val;
   }
// 						!LEAVES MOVED?
   i = 28;
// 						!YES, ASSUME GRATE CLOSED.
   if ((objcts.oflag2[GrateOX - 1] & OpenO) != 0) {
      i = 29;
   }
// 						!OPEN?
   rspeak(i);
// 						!DESCRIBE GRATE.
   return ret_val;

L6500:
   if (findex_1.rvclr != 0 || qhere(LeaveOX, ClearRX) && (prsvec.prsa != MoveW || prsvec.prso != LeaveOX)) {
      return ret_val;
   }
   rspeak(30);
// 						!MOVE LEAVES, REVEAL GRATE.
   findex_1.rvclr = 1;
// 						!INDICATE LEAVES MOVED.
   return ret_val;
// RAPPL1, PAGE 4

// R7--	RESERVOIR SOUTH.  DESCRIPTION DEPENDS ON LOW TIDE FLAG.

L7000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 31;
// 						!ASSUME FULL.
   if (findex_0.lwtidf) {
      i = 32;
   }
// 						!IF LOW TIDE, EMPTY.
   rspeak(i);
// 						!DESCRIBE.
   rspeak(33);
// 						!DESCRIBE EXITS.
   return ret_val;

// R8--	RESERVOIR.  STATE DEPENDS ON LOW TIDE FLAG.

L8000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 34;
// 						!ASSUME FULL.
   if (findex_0.lwtidf) {
      i = 35;
   }
// 						!IF LOW TIDE, EMTPY.
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

// R9--	RESERVOIR NORTH.  ALSO DEPENDS ON LOW TIDE FLAG.

L9000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 36;
// 						!YOU GET THE IDEA.
   if (findex_0.lwtidf) {
      i = 37;
   }
   rspeak(i);
   rspeak(38);
   return ret_val;

// R10--	GLACIER ROOM.  STATE DEPENDS ON MELTED, VANISHED FLAGS.

L10000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(39);
// 						!BASIC DESCRIPTION.
   i = 0;
// 						!ASSUME NO CHANGES.
   if (findex_0.glacmf) {
      i = 40;
   }
// 						!PARTIAL MELT?
   if (findex_0.glacrf) {
      i = 41;
   }
// 						!COMPLETE MELT?
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

// R11--	FOREST ROOM

L11000:
   if (prsvec.prsa == WalkIW) {
      cevent.cflag[ForCX - 1] = true;
   }
// 						!IF WALK IN, BIRDIE.
   return ret_val;

// R12--	MIRROR ROOM.  STATE DEPENDS ON MIRROR INTACT.

L12000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(42);
// 						!DESCRIBE.
   if (findex_0.mirrmf) {
      rspeak(43);
   }
// 						!IF BROKEN, NASTY REMARK.
   return ret_val;
// RAPPL1, PAGE 5

// R13--	CAVE2 ROOM.  BLOW OUT CANDLES WITH 50% PROBABILITY.

L13000:
   if (prsvec.prsa != WalkIW) {
      return ret_val;
   }
// 						!WALKIN?
   if (prob(50, 50) || objcts.oadv[CandlOX - 1] != play.winner || !((objcts.oflag1[CandlOX - 1] & OnO) != 0)) {
      return ret_val;
   }
   objcts.oflag1[CandlOX - 1] &= ~OnO;
   rspeak(47);
// 						!TELL OF WINDS.
   cevent.cflag[CndCX - 1] = false;
// 						!HALT CANDLE COUNTDOWN.
   return ret_val;

// R14--	BOOM ROOM.  BLOW HIM UP IF CARRYING FLAMING OBJECT.

L14000:
   j = objcts.odesc2[CandlOX - 1];
// 						!ASSUME CANDLE.
   if (objcts.oadv[CandlOX - 1] == play.winner && (objcts.oflag1[CandlOX - 1] & OnO) != 0) {
      goto L14100;
   }
   j = objcts.odesc2[TorchOX - 1];
// 						!ASSUME TORCH.
   if (objcts.oadv[TorchOX - 1] == play.winner && (objcts.oflag1[TorchOX - 1] & OnO) != 0) {
      goto L14100;
   }
   j = objcts.odesc2[MatchOX - 1];
   if (objcts.oadv[MatchOX - 1] == play.winner && (objcts.oflag1[MatchOX - 1] & OnO) != 0) {
      goto L14100;
   }
   return ret_val;
// 						!SAFE

L14100:
   if (prsvec.prsa != TrnOnW) {
      goto L14200;
   }
// 						!TURN ON?
   rspsub(294, j);
// 						!BOOM
// 						!
   jigsup(44);
   return ret_val;

L14200:
   if (prsvec.prsa != WalkIW) {
      return ret_val;
   }
// 						!WALKIN?
   rspsub(295, j);
// 						!BOOM
// 						!
   jigsup(44);
   return ret_val;

// R15--	NO-OBJS.  SEE IF EMPTY HANDED, SCORE LIGHT SHAFT.

L15000:
   findex_0.empthf = true;
// 						!ASSUME TRUE.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!SEE IF CARRYING.
      if (objcts.oadv[i - 1] == play.winner) {
         findex_0.empthf = false;
      }
// L15100:
   }

   if (play.here != BShafRX || !lit(play.here)) {
      return ret_val;
   }
   scrupd(state.ltshft);
// 						!SCORE LIGHT SHAFT.
   state.ltshft = 0;
// 						!NEVER AGAIN.
   return ret_val;
// RAPPL1, PAGE 6

// R16--	MACHINE ROOM.  DESCRIBE MACHINE.

L16000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   i = 46;
// 						!ASSUME LID CLOSED.
   if ((objcts.oflag2[MachiOX - 1] & OpenO) != 0) {
      i = 12;
   }
// 						!IF OPEN, OPEN.
   rspsub(45, i);
// 						!DESCRIBE.
   return ret_val;

// R17--	BAT ROOM.  UNLESS CARRYING GARLIC, FLY AWAY WITH ME...

L17000:
   if (prsvec.prsa != LookW) {
      goto L17500;
   }
// 						!LOOK?
   rspeak(48);
// 						!DESCRIBE ROOM.
   if (objcts.oadv[GarliOX - 1] == play.winner) {
      rspeak(49);
   }
// 						!BAT HOLDS NOSE.
   return ret_val;

L17500:
   if (prsvec.prsa != WalkIW || objcts.oadv[GarliOX - 1] == play.winner) {
      return ret_val;
   }
   rspeak(50);
// 						!TIME TO FLY, JACK.
   f = moveto(batdrp[rnd(batdrpN)], play.winner);
// 						!SELECT RANDOM DEST.
   ret_val = false;
// 						!INDICATE NEW DESC NEEDED.
   return ret_val;

// R18--	DOME ROOM.  STATE DEPENDS ON WHETHER ROPE TIED TO RAILING.

L18000:
   if (prsvec.prsa != LookW) {
      goto L18500;
   }
// 						!LOOK?
   rspeak(51);
// 						!DESCRIBE.
   if (findex_0.domef) {
      rspeak(52);
   }
// 						!IF ROPE, DESCRIBE.
   return ret_val;

L18500:
   if (prsvec.prsa == LeapW) {
      jigsup(53);
   }
// 						!DID HE JUMP???
   return ret_val;

// R19--	TORCH ROOM.  ALSO DEPENDS ON WHETHER ROPE TIED TO RAILING.

L19000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(54);
// 						!DESCRIBE.
   if (findex_0.domef) {
      rspeak(55);
   }
// 						!IF ROPE, DESCRIBE.
   return ret_val;

// R20--	CAROUSEL ROOM.  SPIN HIM OR KILL HIM.

L20000:
   if (prsvec.prsa != LookW) {
      goto L20500;
   }
// 						!LOOK?
   rspeak(56);
// 						!DESCRIBE.
   if (!findex_0.caroff) {
      rspeak(57);
   }
// 						!IF NOT FLIPPED, SPIN.
   return ret_val;

L20500:
   if (prsvec.prsa == WalkIW && findex_0.carozf) {
      jigsup(58);
   }
// 						!WALKED IN.
   return ret_val;
// RAPPL1, PAGE 7

// R21--	LLD ROOM.  HANDLE EXORCISE, DESCRIPTIONS.

L21000:
   if (prsvec.prsa != LookW) {
      goto L21500;
   }
// 						!LOOK?
   rspeak(59);
// 						!DESCRIBE.
   if (!findex_0.lldf) {
      rspeak(60);
   }
// 						!IF NOT VANISHED, GHOSTS.
   return ret_val;

L21500:
   if (prsvec.prsa != ExorcW) {
      return ret_val;
   }
// 						!EXORCISE?
   if (objcts.oadv[BellOX - 1] == play.winner && objcts.oadv[BookOX - 1] == play.winner && objcts.oadv[CandlOX - 1] == play.winner && (objcts.oflag1[CandlOX - 1] & OnO) != 0) {
      goto L21600;
   }
   rspeak(62);
// 						!NOT EQUIPPED.
   return ret_val;

L21600:
   if (qhere(GhostOX, play.here)) {
      goto L21700;
   }
// 						!GHOST HERE?
   jigsup(61);
// 						!NOPE, EXORCISE YOU.
   return ret_val;

L21700:
   newsta(GhostOX, 63, 0, 0, 0);
// 						!VANISH GHOST.
   findex_0.lldf = true;
// 						!OPEN GATE.
   return ret_val;

// R22--	LLD2-ROOM.  IS HIS HEAD ON A POLE?

L22000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(64);
// 						!DESCRIBE.
   if (findex_0.onpolf) {
      rspeak(65);
   }
// 						!ON POLE?
   return ret_val;

// R23--	DAM ROOM.  DESCRIBE RESERVOIR, PANEL.

L23000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(66);
// 						!DESCRIBE.
   i = 67;
   if (findex_0.lwtidf) {
      i = 68;
   }
   rspeak(i);
// 						!DESCRIBE RESERVOIR.
   rspeak(69);
// 						!DESCRIBE PANEL.
   if (findex_0.gatef) {
      rspeak(70);
   }
// 						!BUBBLE IS GLOWING.
   return ret_val;

// R24--	TREE ROOM

L24000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(660);
// 						!DESCRIBE.
   i = 661;
// 						!SET FLAG FOR BELOW.
   i__1 = objcts.olnt;
   for (j = 1; j <= i__1; ++j) {
// 						!DESCRIBE OBJ IN FORE3.
      if (!qhere(j, Fore3RX) || j == FTreeOX) {
         goto L24200;
      }
      rspeak(i);
// 						!SET STAGE,
      i = 0;
      rspsub(502, objcts.odesc2[j - 1]);
// 						!DESCRIBE.
   L24200:
      ;
   }
   return ret_val;
// RAPPL1, PAGE 8

// R25--	CYCLOPS-ROOM.  DEPENDS ON CYCLOPS STATE, ASLEEP FLAG, MAGIC FLAG.

L25000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(606);
// 						!DESCRIBE.
   i = 607;
// 						!ASSUME BASIC STATE.
   if (findex_1.rvcyc > 0) {
      i = 608;
   }
// 						!>0?  HUNGRY.
   if (findex_1.rvcyc < 0) {
      i = 609;
   }
// 						!<0?  THIRSTY.
   if (findex_0.cyclof) {
      i = 610;
   }
// 						!ASLEEP?
   if (findex_0.magicf) {
      i = 611;
   }
// 						!GONE?
   rspeak(i);
// 						!DESCRIBE.
   if (!findex_0.cyclof && findex_1.rvcyc != 0) {
      i__1 = abs(findex_1.rvcyc) + 193;
      rspeak(i__1);
   }
   return ret_val;

// R26--	BANK BOX ROOM.

L26000:
   if (prsvec.prsa != WalkIW) {
      return ret_val;
   }
// 						!SURPRISE HIM.
   for (i = 1; i <= 8; i += 2) {
// 						!SCOLRM DEPENDS ON
      if (screen.fromdr == screen.scoldr[i - 1]) {
         screen.scolrm = screen.scoldr[i];
      }
// L26100:
   }
// 						!ENTRY DIRECTION.
   return ret_val;

// R27--	TREASURE ROOM.

L27000:
   if (prsvec.prsa != WalkIW || !hack.thfact) {
      return ret_val;
   }
   if (objcts.oroom[ThiefOX - 1] != play.here) {
      newsta(ThiefOX, 82, play.here, 0, 0);
   }
   hack.thfpos = play.here;
// 						!RESET SEARCH PATTERN.
   objcts.oflag2[ThiefOX - 1] |= FiteO;
   if (objcts.oroom[ChaliOX - 1] == play.here) {
      objcts.oflag1[ChaliOX - 1] &= ~TakeO;
   }

// 	VANISH EVERYTHING IN ROOM

   j = 0;
// 						!ASSUME NOTHING TO VANISH.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (i == ChaliOX || i == ThiefOX || !qhere(i, play.here)) {
         goto L27200;
      }
      j = 83;
// 						!FLAG BYEBYE.
      objcts.oflag1[i - 1] &= ~VisiO;
   L27200:
      ;
   }
   rspeak(j);
// 						!DESCRIBE.
   return ret_val;

// R28--	CLIFF FUNCTION.  SEE IF CARRYING INFLATED BOAT.

L28000:
   findex_0.deflaf = objcts.oadv[RBoatOX - 1] != play.winner;
// 						!TRUE IF NOT CARRYING.
   return ret_val;
// RAPPL1, PAGE 9

// R29--	RIVR4 ROOM.  PLAY WITH BUOY.

L29000:
   if (!findex_0.buoyf || objcts.oadv[BuoyOX - 1] != play.winner) {
      return ret_val;
   }
   rspeak(84);
// 						!GIVE HINT,
   findex_0.buoyf = false;
// 						!THEN DISABLE.
   return ret_val;

// R30--	OVERFALLS.  DOOM.

L30000:
   if (prsvec.prsa != LookW) {
      jigsup(85);
   }
// 						!OVER YOU GO.
   return ret_val;

// R31--	BEACH ROOM.  DIG A HOLE.

L31000:
   if (prsvec.prsa != DigW || prsvec.prso != ShoveOX) {
      return ret_val;
   }
   ++findex_1.rvsnd;
// 						!INCREMENT DIG STATE.
   switch (findex_1.rvsnd) {
      case 1:
         goto L31100;
      case 2:
         goto L31100;
      case 3:
         goto L31100;
      case 4:
         goto L31400;
      case 5:
         goto L31500;
   }
// 						!PROCESS STATE.
   bug(2, findex_1.rvsnd);

L31100:
   i__1 = findex_1.rvsnd + 85;
   rspeak(i__1);
// 						!1-3... DISCOURAGE HIM.
   return ret_val;

L31400:
   i = 89;
// 						!ASSUME DISCOVERY.
   if ((objcts.oflag1[StatuOX - 1] & VisiO) != 0) {
      i = 88;
   }
   rspeak(i);
   objcts.oflag1[StatuOX - 1] |= VisiO;
   return ret_val;

L31500:
   findex_1.rvsnd = 0;
// 						!5... SAND COLLAPSES
   jigsup(90);
// 						!AND SO DOES HE.
   return ret_val;

// R32--	TCAVE ROOM.  DIG A HOLE IN GUANO.

L32000:
   if (prsvec.prsa != DigW || prsvec.prso != ShoveOX) {
      return ret_val;
   }
   i = 91;
// 						!ASSUME NO GUANO.
   if (!qhere(GuanoOX, play.here)) {
      goto L32100;
   }
// 						!IS IT HERE?
// Computing MIN
   i__1 = 4, i__2 = findex_1.rvgua + 1;
   findex_1.rvgua = min(i__1, i__2);
// 						!YES, SET NEW STATE.
   i = findex_1.rvgua + 91;
// 						!GET NASTY REMARK.
L32100:
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

// R33--	FALLS ROOM

L33000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(96);
// 						!DESCRIBE.
   i = 97;
// 						!ASSUME NO RAINBOW.
   if (findex_0.rainbf) {
      i = 98;
   }
// 						!GOT ONE?
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;
// RAPPL1, PAGE 10

// R34--	LEDGE FUNCTION.  LEDGE CAN COLLAPSE.

L34000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(100);
// 						!DESCRIBE.
   i = 102;
// 						!ASSUME SAFE ROOM OK.
   if ((rooms.rflag[MSafeRX - 1] & MungR) != 0) {
      i = 101;
   }
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

// R35--	SAFE ROOM.  STATE DEPENDS ON WHETHER SAFE BLOWN.

L35000:
   if (prsvec.prsa != LookW) {
      return ret_val;
   }
// 						!LOOK?
   rspeak(104);
// 						!DESCRIBE.
   i = 105;
// 						!ASSUME OK.
   if (findex_0.safef) {
      i = 106;
   }
// 						!BLOWN?
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

// R36--	MAGNET ROOM.  DESCRIBE, CHECK FOR SPINDIZZY DOOM.

L36000:
   if (prsvec.prsa != LookW) {
      goto L36500;
   }
// 						!LOOK?
   rspeak(107);
// 						!DESCRIBE.
   return ret_val;

L36500:
   if (prsvec.prsa != WalkIW || !findex_0.caroff) {
      return ret_val;
   }
// 						!WALKIN ON FLIPPED?
   if (findex_0.carozf) {
      goto L36600;
   }
// 						!ZOOM?
   rspeak(108);
// 						!NO, SPIN HIS COMPASS.
   return ret_val;

L36600:
   i = 58;
// 						!SPIN HIS INSIDES.
   if (play.winner != PlayerAX) {
      i = 99;
   }
// 						!SPIN ROBOT.
   jigsup(i);
// 						!DEAD.
   return ret_val;

// R37--	CAGE ROOM.  IF SOLVED CAGE, MOVE TO OTHER CAGE ROOM.

L37000:
   if (findex_0.cagesf) {
      f = moveto(CageRRX, play.winner);
   }
// 						!IF SOLVED, MOVE.
   return ret_val;
}
