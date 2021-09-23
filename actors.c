// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Applicables for adventurers
Bool aappli(int ri) {
// System generated locals
   Bool ret_val;

// Local variables
   Bool f;
   int i;

// AAPPLI, PAGE 2

   if (ri == 0) {
      goto L10;
   }
// 						!IF ZERO, NO APP.
   ret_val = true;
// 						!ASSUME WINS.
   switch (ri) {
      case 1:
         goto L1000;
      case 2:
         goto L2000;
   }
// 						!BRANCH ON ADV.
   bug(11, ri);

// COMMON FALSE RETURN.

L10:
   ret_val = false;
   return ret_val;

// A1--	ROBOT.  PROCESS MOST COMMANDS GIVEN TO ROBOT.

L1000:
   if (prsvec.prsa != vindex.raisew || prsvec.prso != oindex.rcage) {
      goto L1200;
   }
   cevent.cflag[cindex.cevsph - 1] = false;
// 						!ROBOT RAISED CAGE.
   play.winner = aindex.player;
// 						!RESET FOR PLAYER.
   f = moveto(rindex_.cager, play.winner);
// 						!MOVE TO NEW ROOM.
   newsta(oindex.cage, 567, rindex_.cager, 0, 0);
// 						!INSTALL CAGE IN ROOM.
   newsta(oindex.robot, 0, rindex_.cager, 0, 0);
// 						!INSTALL ROBOT IN ROOM.
   advs.aroom[aindex.arobot - 1] = rindex_.cager;
// 						!ALSO MOVE ROBOT/ADV.
   findex.cagesf = true;
// 						!CAGE SOLVED.
   objcts.oflag1[oindex.robot - 1] &= ~NDscO;
   objcts.oflag1[oindex.spher - 1] |= TakeO;
   return ret_val;

L1200:
   if (prsvec.prsa != vindex.drinkw && prsvec.prsa != vindex.eatw) {
      goto L1300;
   }
   rspeak(568);
// 						!EAT OR DRINK, JOKE.
   return ret_val;

L1300:
   if (prsvec.prsa != vindex.readw) {
      goto L1400;
   }
// 						!READ,
   rspeak(569);
// 						!JOKE.
   return ret_val;

L1400:
   if (prsvec.prsa == vindex.walkw || prsvec.prsa == vindex.takew || prsvec.prsa == vindex.dropw || prsvec.prsa == vindex.putw || prsvec.prsa == vindex.pushw || prsvec.prsa == vindex.throww || prsvec.prsa == vindex.turnw || prsvec.prsa == vindex.leapw) {
      goto L10;
   }
   rspeak(570);
// 						!JOKE.
   return ret_val;
// AAPPLI, PAGE 3

// A2--	MASTER.  PROCESS MOST COMMANDS GIVEN TO MASTER.

L2000:
   if ((objcts.oflag2[oindex.qdoor - 1] & OpenO) != 0) {
      goto L2100;
   }
   rspeak(783);
// 						!NO MASTER YET.
   return ret_val;

L2100:
   if (prsvec.prsa != vindex.walkw) {
      goto L2200;
   }
// 						!WALK?
   i = 784;
// 						!ASSUME WONT.
   if (play.here == rindex_.scorr && (prsvec.prso == xsrch.xnorth || prsvec.prso == xsrch.xenter) || play.here == rindex_.ncorr && (prsvec.prso == xsrch.xsouth || prsvec.prso == xsrch.xenter)) {
      i = 785;
   }
   rspeak(i);
   return ret_val;

L2200:
   if (prsvec.prsa == vindex.takew || prsvec.prsa == vindex.dropw || prsvec.prsa == vindex.putw || prsvec.prsa == vindex.throww || prsvec.prsa == vindex.pushw || prsvec.prsa == vindex.turnw || prsvec.prsa == vindex.spinw || prsvec.prsa == vindex.trntow || prsvec.prsa == vindex.follow || prsvec.prsa == vindex.stayw || prsvec.prsa == vindex.openw || prsvec.prsa == vindex.closew || prsvec.prsa == vindex.killw) {
      goto L10;
   }
   rspeak(786);
// 						!MASTER CANT DO IT.
   return ret_val;
}

// Intermove thief demon
void thiefd(void) {
// System generated locals
   int i__1, i__2;

// Local variables
   int i, j, nr;
   Bool once;
   int rhere;

// THIEFD, PAGE 2

#ifdef ALLOW_GDT
// dflag = (debug.prsflg & 32768) != 0; //F
#endif
// 						!SET UP DETAIL FLAG.
   once = false;
// 						!INIT FLAG.
L1025:
   rhere = objcts.oroom[oindex.thief - 1];
// 						!VISIBLE POS.
   if (rhere != 0) {
      hack.thfpos = rhere;
   }

   if (hack.thfpos == play.here) {
      goto L1100;
   }
// 						!THIEF IN WIN RM?
   if (hack.thfpos != rindex_.treas) {
      goto L1400;
   }
// 						!THIEF NOT IN TREAS?

// THIEF IS IN TREASURE ROOM, AND WINNER IS NOT.

#ifdef ALLOW_GDT
// if (dflag) print(" THIEFD-- IN TREASURE ROOM"); //F
#endif
   if (rhere == 0) {
      goto L1050;
   }
// 						!VISIBLE?
   newsta(oindex.thief, 0, 0, 0, 0);
// 						!YES, VANISH.
   rhere = 0;
   if (qhere(oindex.still, rindex_.treas) || objcts.oadv[oindex.still - 1] == -oindex.thief) {
      newsta(oindex.still, 0, 0, oindex.thief, 0);
   }
L1050:
   i__1 = -oindex.thief;
   i = robadv(i__1, hack.thfpos, 0, 0);
// 						!DROP VALUABLES.
   if (qhere(oindex.egg, hack.thfpos)) {
      objcts.oflag2[oindex.egg - 1] |= OpenO;
   }
   goto L1700;

// THIEF AND WINNER IN SAME ROOM.

L1100:
   if (hack.thfpos == rindex_.treas) {
      goto L1700;
   }
// 						!IF TREAS ROOM, NOTHING.
   if ((rooms.rflag[hack.thfpos - 1] & LightR) != 0) {
      goto L1400;
   }
#ifdef ALLOW_GDT
// if (dflag) print(" THIEFD-- IN ADV ROOM"); //F
#endif
   if (hack.thfflg) {
      goto L1300;
   }
// 						!THIEF ANNOUNCED?
   if (rhere != 0 || prob(70, 70)) {
      goto L1150;
   }
// 						!IF INVIS AND 30%.
   if (objcts.ocan[oindex.still - 1] != oindex.thief) {
      goto L1700;
   }
// 						!ABORT IF NO STILLETTO.
   newsta(oindex.thief, 583, hack.thfpos, 0, 0);
// 						!INSERT THIEF INTO ROOM.
   hack.thfflg = true;
// 						!THIEF IS ANNOUNCED.
   return;

L1150:
   if (rhere == 0 || (objcts.oflag2[oindex.thief - 1] & FiteO) == 0) {
      goto L1200;
   }
   if (winnin(oindex.thief, play.winner)) {
      goto L1175;
   }
// 						!WINNING?
   newsta(oindex.thief, 584, 0, 0, 0);
// 						!NO, VANISH THIEF.
   objcts.oflag2[oindex.thief - 1] &= ~FiteO;
   if (qhere(oindex.still, hack.thfpos) || objcts.oadv[oindex.still - 1] == -oindex.thief) {
      newsta(oindex.still, 0, 0, oindex.thief, 0);
   }
   return;

L1175:
   if (prob(90, 90)) {
      goto L1700;
   }
// 						!90% CHANCE TO STAY.

L1200:
   if (rhere == 0 || prob(70, 70)) {
      goto L1250;
   }
// 						!IF VISIBLE AND 30%
   newsta(oindex.thief, 585, 0, 0, 0);
// 						!VANISH THIEF.
   if (qhere(oindex.still, hack.thfpos) || objcts.oadv[oindex.still - 1] == -oindex.thief) {
      newsta(oindex.still, 0, 0, oindex.thief, 0);
   }
   return;

L1300:
   if (rhere == 0) {
      goto L1700;
   }
// 						!ANNOUNCED.  VISIBLE?
L1250:
   if (prob(70, 70)) {
      return;
   }
// 						!70% CHANCE TO DO NOTHING.
   hack.thfflg = true;
   i__1 = -oindex.thief;
   i__2 = -oindex.thief;
   nr = robrm(hack.thfpos, 100, 0, 0, i__1) + robadv(play.winner, 0, 0, i__2);
   i = 586;
// 						!ROBBED EM.
   if (rhere != 0) {
      i = 588;
   }
// 						!WAS HE VISIBLE?
   if (nr != 0) {
      ++i;
   }
// 						!DID HE GET ANYTHING?
   newsta(oindex.thief, i, 0, 0, 0);
// 						!VANISH THIEF.
   if (qhere(oindex.still, hack.thfpos) || objcts.oadv[oindex.still - 1] == -oindex.thief) {
      newsta(oindex.still, 0, 0, oindex.thief, 0);
   }
   if (nr != 0 && !lit(hack.thfpos)) {
      rspeak(406);
   }
   rhere = 0;
   goto L1700;
// 						!ONWARD.

// NOT IN ADVENTURERS ROOM.

L1400:
   newsta(oindex.thief, 0, 0, 0, 0);
// 						!VANISH.
   rhere = 0;
#ifdef ALLOW_GDT
// if (dflag) print(" THIEFD-- IN ROOM %I4", hack.thfpos); //F
#endif
   if (qhere(oindex.still, hack.thfpos) || objcts.oadv[oindex.still - 1] == -oindex.thief) {
      newsta(oindex.still, 0, 0, oindex.thief, 0);
   }
   if ((rooms.rflag[hack.thfpos - 1] & SeenR) == 0) {
      goto L1700;
   }
   i__1 = -oindex.thief;
   i = robrm(hack.thfpos, 75, 0, 0, i__1);
// 						!ROB ROOM 75%.
   if (hack.thfpos < rindex_.maze1 || hack.thfpos > rindex_.maz15 || play.here < rindex_.maze1 || play.here > rindex_.maz15) {
      goto L1500;
   }
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!BOTH IN MAZE.
      if (!qhere(i, hack.thfpos) || prob(60, 60) || (objcts.oflag1[i - 1] & VisiO + TakeO) != VisiO + TakeO) {
         goto L1450;
      }
      rspsub(590, objcts.odesc2[i - 1]);
// 						!TAKE OBJECT.
      if (prob(40, 20)) {
         goto L1700;
      }
      i__2 = -oindex.thief;
      newsta(i, 0, 0, 0, i__2);
// 						!MOST OF THE TIME.
      objcts.oflag2[i - 1] |= TChO;
      goto L1700;
   L1450:
      ;
   }
   goto L1700;

L1500:
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!NOT IN MAZE.
      if (!qhere(i, hack.thfpos) || objcts.otval[i - 1] != 0 || prob(80, 60) || (objcts.oflag1[i - 1] & VisiO + TakeO) != VisiO + TakeO) {
         goto L1550;
      }
      i__2 = -oindex.thief;
      newsta(i, 0, 0, 0, i__2);
      objcts.oflag2[i - 1] |= TChO;
      goto L1700;
   L1550:
      ;
   }

// NOW MOVE TO NEW ROOM.

L1700:
   if (objcts.oadv[oindex.rope - 1] == -oindex.thief) {
      findex.domef = false;
   }
   if (once) {
      goto L1800;
   }
   once = !once;
L1750:
   --hack.thfpos;
// 						!NEXT ROOM.
   if (hack.thfpos <= 0) {
      hack.thfpos = rooms.rlnt;
   }
   if ((rooms.rflag[hack.thfpos - 1] & LandR + SacrdR + EndR) != LandR) {
      goto L1750;
   }
   hack.thfflg = false;
// 						!NOT ANNOUNCED.
   goto L1025;
// 						!ONCE MORE.

// ALL DONE.

L1800:
   if (hack.thfpos == rindex_.treas) {
      return;
   }
// 						!IN TREASURE ROOM?
   j = 591;
// 						!NO, DROP STUFF.
   if (hack.thfpos != play.here) {
      j = 0;
   }
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts.oadv[i - 1] != -oindex.thief || prob(70, 70) || objcts.otval[i - 1] > 0) {
         goto L1850;
      }
      newsta(i, j, hack.thfpos, 0, 0);
      j = 0;
   L1850:
      ;
   }
}
