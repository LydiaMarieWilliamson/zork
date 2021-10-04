// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Applicables for adventurers
bool aappli(int ri) {
// System generated locals
   bool ret_val;

// Local variables
   bool f;
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
   if (prsvec.prsa != RaiseW || prsvec.prso != RCageOX) {
      goto L1200;
   }
   cevent.cflag[SphCX - 1] = false;
// 						!ROBOT RAISED CAGE.
   play.winner = PlayerAX;
// 						!RESET FOR PLAYER.
   f = moveto(CageRRX, play.winner);
// 						!MOVE TO NEW ROOM.
   newsta(CageOX, 567, CageRRX, 0, 0);
// 						!INSTALL CAGE IN ROOM.
   newsta(RobotOX, 0, CageRRX, 0, 0);
// 						!INSTALL ROBOT IN ROOM.
   advs.aroom[RobotAX - 1] = CageRRX;
// 						!ALSO MOVE ROBOT/ADV.
   findex_0.cagesf = true;
// 						!CAGE SOLVED.
   objcts.oflag1[RobotOX - 1] &= ~NDscO;
   objcts.oflag1[SpherOX - 1] |= TakeO;
   return ret_val;

L1200:
   if (prsvec.prsa != DrinkW && prsvec.prsa != EatW) {
      goto L1300;
   }
   rspeak(568);
// 						!EAT OR DRINK, JOKE.
   return ret_val;

L1300:
   if (prsvec.prsa != MeltW) {
      goto L1400;
   }
// 						!READ,
   rspeak(569);
// 						!JOKE.
   return ret_val;

L1400:
   if (prsvec.prsa == WalkW || prsvec.prsa == TakeW || prsvec.prsa == DropW || prsvec.prsa == PutW || prsvec.prsa == PushW || prsvec.prsa == ThrowW || prsvec.prsa == TurnW || prsvec.prsa == LeapW) {
      goto L10;
   }
   rspeak(570);
// 						!JOKE.
   return ret_val;
// AAPPLI, PAGE 3

// A2--	MASTER.  PROCESS MOST COMMANDS GIVEN TO MASTER.

L2000:
   if ((objcts.oflag2[QDoorOX - 1] & OpenO) != 0) {
      goto L2100;
   }
   rspeak(783);
// 						!NO MASTER YET.
   return ret_val;

L2100:
   if (prsvec.prsa != WalkW) {
      goto L2200;
   }
// 						!WALK?
   i = 784;
// 						!ASSUME WONT.
   if (play.here == SCorrRX && (prsvec.prso == NorthDX || prsvec.prso == EnterDX) || play.here == NCorrRX && (prsvec.prso == SouthDX || prsvec.prso == EnterDX)) {
      i = 785;
   }
   rspeak(i);
   return ret_val;

L2200:
   if (prsvec.prsa == TakeW || prsvec.prsa == DropW || prsvec.prsa == PutW || prsvec.prsa == ThrowW || prsvec.prsa == PushW || prsvec.prsa == TurnW || prsvec.prsa == SpinW || prsvec.prsa == TrnToW || prsvec.prsa == FolloW || prsvec.prsa == StayW || prsvec.prsa == OpenW || prsvec.prsa == CloseW || prsvec.prsa == KillW) {
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
   bool once;
   int rhere;

// THIEFD, PAGE 2

#if defined ALLOW_GDT && 0
   dflag = (debug.prsflg & 0x8000) != 0;
#endif
// 						!SET UP DETAIL FLAG.
   once = false;
// 						!INIT FLAG.
L1025:
   rhere = objcts.oroom[ThiefOX - 1];
// 						!VISIBLE POS.
   if (rhere != 0) {
      hack.thfpos = rhere;
   }

   if (hack.thfpos == play.here) {
      goto L1100;
   }
// 						!THIEF IN WIN RM?
   if (hack.thfpos != TreasRX) {
      goto L1400;
   }
// 						!THIEF NOT IN TREAS?

// THIEF IS IN TREASURE ROOM, AND WINNER IS NOT.

#if defined ALLOW_GDT && 0
   if (dflag) more_output("THIEFD-- IN TREASURE ROOM\n");
#endif
   if (rhere == 0) {
      goto L1050;
   }
// 						!VISIBLE?
   newsta(ThiefOX, 0, 0, 0, 0);
// 						!YES, VANISH.
   rhere = 0;
   if (qhere(StillOX, TreasRX) || objcts.oadv[StillOX - 1] == -ThiefOX) {
      newsta(StillOX, 0, 0, ThiefOX, 0);
   }
L1050:
   i__1 = -ThiefOX;
   i = robadv(i__1, hack.thfpos, 0, 0);
// 						!DROP VALUABLES.
   if (qhere(EggOX, hack.thfpos)) {
      objcts.oflag2[EggOX - 1] |= OpenO;
   }
   goto L1700;

// THIEF AND WINNER IN SAME ROOM.

L1100:
   if (hack.thfpos == TreasRX) {
      goto L1700;
   }
// 						!IF TREAS ROOM, NOTHING.
   if ((rooms.rflag[hack.thfpos - 1] & LightR) != 0) {
      goto L1400;
   }
#if defined ALLOW_GDT && 0
   if (dflag) more_output("THIEFD-- IN ADV ROOM\n");
#endif
   if (hack.thfflg) {
      goto L1300;
   }
// 						!THIEF ANNOUNCED?
   if (rhere != 0 || prob(70, 70)) {
      goto L1150;
   }
// 						!IF INVIS AND 30%.
   if (objcts.ocan[StillOX - 1] != ThiefOX) {
      goto L1700;
   }
// 						!ABORT IF NO STILLETTO.
   newsta(ThiefOX, 583, hack.thfpos, 0, 0);
// 						!INSERT THIEF INTO ROOM.
   hack.thfflg = true;
// 						!THIEF IS ANNOUNCED.
   return;

L1150:
   if (rhere == 0 || (objcts.oflag2[ThiefOX - 1] & FiteO) == 0) {
      goto L1200;
   }
   if (winnin(ThiefOX, play.winner)) {
      goto L1175;
   }
// 						!WINNING?
   newsta(ThiefOX, 584, 0, 0, 0);
// 						!NO, VANISH THIEF.
   objcts.oflag2[ThiefOX - 1] &= ~FiteO;
   if (qhere(StillOX, hack.thfpos) || objcts.oadv[StillOX - 1] == -ThiefOX) {
      newsta(StillOX, 0, 0, ThiefOX, 0);
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
   newsta(ThiefOX, 585, 0, 0, 0);
// 						!VANISH THIEF.
   if (qhere(StillOX, hack.thfpos) || objcts.oadv[StillOX - 1] == -ThiefOX) {
      newsta(StillOX, 0, 0, ThiefOX, 0);
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
   i__1 = -ThiefOX;
   i__2 = -ThiefOX;
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
   newsta(ThiefOX, i, 0, 0, 0);
// 						!VANISH THIEF.
   if (qhere(StillOX, hack.thfpos) || objcts.oadv[StillOX - 1] == -ThiefOX) {
      newsta(StillOX, 0, 0, ThiefOX, 0);
   }
   if (nr != 0 && !lit(hack.thfpos)) {
      rspeak(406);
   }
   rhere = 0;
   goto L1700;
// 						!ONWARD.

// NOT IN ADVENTURERS ROOM.

L1400:
   newsta(ThiefOX, 0, 0, 0, 0);
// 						!VANISH.
   rhere = 0;
#if defined ALLOW_GDT && 0
   if (dflag) more_output("THIEFD-- IN ROOM %d\n", hack.thfpos);
#endif
   if (qhere(StillOX, hack.thfpos) || objcts.oadv[StillOX - 1] == -ThiefOX) {
      newsta(StillOX, 0, 0, ThiefOX, 0);
   }
   if ((rooms.rflag[hack.thfpos - 1] & SeenR) == 0) {
      goto L1700;
   }
   i__1 = -ThiefOX;
   i = robrm(hack.thfpos, 75, 0, 0, i__1);
// 						!ROB ROOM 75%.
   if (hack.thfpos < Maze1RX || hack.thfpos > Maz15RX || play.here < Maze1RX || play.here > Maz15RX) {
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
      i__2 = -ThiefOX;
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
      i__2 = -ThiefOX;
      newsta(i, 0, 0, 0, i__2);
      objcts.oflag2[i - 1] |= TChO;
      goto L1700;
   L1550:
      ;
   }

// NOW MOVE TO NEW ROOM.

L1700:
   if (objcts.oadv[RopeOX - 1] == -ThiefOX) {
      findex_0.domef = false;
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
   if (hack.thfpos == TreasRX) {
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
      if (objcts.oadv[i - 1] != -ThiefOX || prob(70, 70) || objcts.otval[i - 1] > 0) {
         goto L1850;
      }
      newsta(i, j, hack.thfpos, 0, 0);
      j = 0;
   L1850:
      ;
   }
}
