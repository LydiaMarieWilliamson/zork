// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

static void litint(int, int *, int, const int *, int);

// Clock event applicables
void cevapp(int ri) {
// Initialized data
   static const int cndtck[10] = { 50, 20, 10, 5, 0, 156, 156, 156, 157, 0 };
   static const int lmptck[12] = { 50, 30, 20, 10, 4, 0, 154, 154, 154, 154, 155, 0 };

// System generated locals
   int i__1, i__2;

// Local variables
   bool f;
   int i, j, bc, br;

// CEVAPP, PAGE 2

   if (ri == 0) {
      return;
   }
// 						!IGNORE DISABLED.
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
   }
   bug(3, ri);

// CEV1--	CURE CLOCK.  LET PLAYER SLOWLY RECOVER.

L1000:
// Computing MIN
   i__1 = 0, i__2 = advs.astren[PlayerAX - 1] + 1;
   advs.astren[PlayerAX - 1] = min(i__1, i__2);
// 						!RECOVER.
   if (advs.astren[PlayerAX - 1] >= 0) {
      return;
   }
// 						!FULLY RECOVERED?
   cevent.ctick[CurCX - 1] = 30;
// 						!NO, WAIT SOME MORE.
   return;

// CEV2--	MAINT-ROOM WITH LEAK.  RAISE THE WATER LEVEL.

L2000:
   if (play.here == MaintRX) {
      i__1 = findex_1.rvmnt / 2 + 71;
      rspeak(i__1);
   }
// 						!DESCRIBE.
   ++findex_1.rvmnt;
// 						!RAISE WATER LEVEL.
   if (findex_1.rvmnt <= 16) {
      return;
   }
// 						!IF NOT FULL, EXIT.
   cevent.ctick[MntCX - 1] = 0;
// 						!FULL, DISABLE CLOCK.
   rooms.rflag[MaintRX - 1] |= MungR;
   rrand[MaintRX - 1] = 80;
// 						!SAY IT IS FULL OF WATER.
   if (play.here == MaintRX) {
      jigsup(81);
   }
// 						!DROWN HIM IF PRESENT.
   return;

// CEV3--	LANTERN.  DESCRIBE GROWING DIMNESS.

L3000:
   litint(LampOX, &findex_1.orlamp, LntCX, lmptck, 12);
// 						!DO LIGHT INTERRUPT.
   return;

// CEV4--	MATCH.  OUT IT GOES.

L4000:
   rspeak(153);
// 						!MATCH IS OUT.
   objcts.oflag1[MatchOX - 1] &= ~OnO;
   return;

// CEV5--	CANDLE.  DESCRIBE GROWING DIMNESS.

L5000:
   litint(CandlOX, &findex_1.orcand, CndCX, cndtck, 10);
// 						!DO CANDLE INTERRUPT.
   return;
// CEVAPP, PAGE 3

// CEV6--	BALLOON

L6000:
   cevent.ctick[BalCX - 1] = 3;
// 						!RESCHEDULE INTERRUPT.
   f = advs.avehic[play.winner - 1] == BalloOX;
// 						!SEE IF IN BALLOON.
   if (state.bloc == VlBotRX) {
      goto L6800;
   }
// 						!AT BOTTOM?
   if (state.bloc == Ledg2RX || state.bloc == Ledg3RX || state.bloc == Ledg4RX || state.bloc == VlBotRX) {
      goto L6700;
   }
// 						!ON LEDGE?
   if ((objcts.oflag2[RecepOX - 1] & OpenO) != 0 && findex_1.binff != 0) {
      goto L6500;
   }

// BALLOON IS IN MIDAIR AND IS DEFLATED (OR HAS RECEPTACLE CLOSED).
// FALL TO NEXT ROOM.

   if (state.bloc != Vair1RX) {
      goto L6300;
   }
// 						!IN VAIR1?
   state.bloc = VlBotRX;
// 						!YES, NOW AT VLBOT.
   newsta(BalloOX, 0, state.bloc, 0, 0);
   if (f) {
      goto L6200;
   }
// 						!IN BALLOON?
   if (play.here == Ledg2RX || play.here == Ledg3RX || play.here == Ledg4RX || play.here == VlBotRX) {
      rspeak(530);
   }
// 						!ON LEDGE, DESCRIBE.
   return;

L6200:
   f = moveto(state.bloc, play.winner);
// 						!MOVE HIM.
   if (findex_1.binff == 0) {
      goto L6250;
   }
// 						!IN BALLOON.  INFLATED?
   rspeak(531);
// 						!YES, LANDED.
   f = rmdesc(0);
// 						!DESCRIBE.
   return;

L6250:
   newsta(BalloOX, 532, 0, 0, 0);
// 						!NO, BALLOON & CONTENTS DIE.
   newsta(DBallOX, 0, state.bloc, 0, 0);
// 						!INSERT DEAD BALLOON.
   advs.avehic[play.winner - 1] = 0;
// 						!NOT IN VEHICLE.
   cevent.cflag[BalCX - 1] = false;
// 						!DISABLE INTERRUPTS.
   cevent.cflag[BrnCX - 1] = false;
   findex_1.binff = 0;
   findex_1.btief = 0;
   return;

L6300:
   --state.bloc;
// 						!NOT IN VAIR1, DESCEND.
   newsta(BalloOX, 0, state.bloc, 0, 0);
   if (f) {
      goto L6400;
   }
// 						!IS HE IN BALLOON?
   if (play.here == Ledg2RX || play.here == Ledg3RX || play.here == Ledg4RX || play.here == VlBotRX) {
      rspeak(533);
   }
// 						!IF ON LEDGE, DESCRIBE.
   return;

L6400:
   f = moveto(state.bloc, play.winner);
// 						!IN BALLOON, MOVE HIM.
   rspeak(534);
// 						!DESCRIBE.
   f = rmdesc(0);
   return;

// BALLOON IS IN MIDAIR AND IS INFLATED, UP-UP-AND-AWAY
// 						!

L6500:
   if (state.bloc != Vair4RX) {
      goto L6600;
   }
// 						!AT VAIR4?
   cevent.ctick[BrnCX - 1] = 0;
   cevent.ctick[BalCX - 1] = 0;
   findex_1.binff = 0;
   findex_1.btief = 0;
   state.bloc = VlBotRX;
// 						!FALL TO BOTTOM.
   newsta(BalloOX, 0, 0, 0, 0);
// 						!BALLOON & CONTENTS DIE.
   newsta(DBallOX, 0, state.bloc, 0, 0);
// 						!SUBSTITUTE DEAD BALLOON.
   if (f) {
      goto L6550;
   }
// 						!WAS HE IN IT?
   if (play.here == Ledg2RX || play.here == Ledg3RX || play.here == Ledg4RX || play.here == VlBotRX) {
      rspeak(535);
   }
// 						!IF HE CAN SEE, DESCRIBE.
   return;

L6550:
   jigsup(536);
// 						!IN BALLOON AT CRASH, DIE.
   return;

L6600:
   ++state.bloc;
// 						!NOT AT VAIR4, GO UP.
   newsta(BalloOX, 0, state.bloc, 0, 0);
   if (f) {
      goto L6650;
   }
// 						!IN BALLOON?
   if (play.here == Ledg2RX || play.here == Ledg3RX || play.here == Ledg4RX || play.here == VlBotRX) {
      rspeak(537);
   }
// 						!CAN HE SEE IT?
   return;

L6650:
   f = moveto(state.bloc, play.winner);
// 						!MOVE PLAYER.
   rspeak(538);
// 						!DESCRIBE.
   f = rmdesc(0);
   return;

// ON LEDGE, GOES TO MIDAIR ROOM WHETHER INFLATED OR NOT.

L6700:
   state.bloc += Vair2RX - Ledg2RX;
// 						!MOVE TO MIDAIR.
   newsta(BalloOX, 0, state.bloc, 0, 0);
   if (f) {
      goto L6750;
   }
// 						!IN BALLOON?
   if (play.here == Ledg2RX || play.here == Ledg3RX || play.here == Ledg4RX || play.here == VlBotRX) {
      rspeak(539);
   }
// 						!NO, STRANDED.
   cevent.ctick[VlgCX - 1] = 10;
// 						!MATERIALIZE GNOME.
   return;

L6750:
   f = moveto(state.bloc, play.winner);
// 						!MOVE TO NEW ROOM.
   rspeak(540);
// 						!DESCRIBE.
   f = rmdesc(0);
   return;

// AT BOTTOM, GO UP IF INFLATED, DO NOTHING IF DEFLATED.

L6800:
   if (findex_1.binff == 0 || !((objcts.oflag2[RecepOX - 1] & OpenO) != 0)) {
      return;
   }
   state.bloc = Vair1RX;
// 						!INFLATED AND OPEN,
   newsta(BalloOX, 0, state.bloc, 0, 0);
// 						!GO UP TO VAIR1.
   if (f) {
      goto L6850;
   }
// 						!IN BALLOON?
   if (play.here == Ledg2RX || play.here == Ledg3RX || play.here == Ledg4RX || play.here == VlBotRX) {
      rspeak(541);
   }
// 						!IF CAN SEE, DESCRIBE.
   return;

L6850:
   f = moveto(state.bloc, play.winner);
// 						!MOVE PLAYER.
   rspeak(542);
   f = rmdesc(0);
   return;
// CEVAPP, PAGE 4

// CEV7--	BALLOON BURNUP

L7000:
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!FIND BURNING OBJECT
      if (RecepOX == objcts.ocan[i - 1] && (objcts.oflag1[i - 1] & FlamO) != 0) {
         goto L7200;
      }
// L7100:
   }
   bug(4, 0);

L7200:
   newsta(i, 0, 0, 0, 0);
// 						!VANISH OBJECT.
   findex_1.binff = 0;
// 						!UNINFLATED.
   if (play.here == state.bloc) {
      rspsub(292, objcts.odesc2[i - 1]);
   }
// 						!DESCRIBE.
   return;

// CEV8--	FUSE FUNCTION

L8000:
   if (objcts.ocan[FuseOX - 1] != BrickOX) {
      goto L8500;
   }
// 						!IGNITED BRICK?
   br = objcts.oroom[BrickOX - 1];
// 						!GET BRICK ROOM.
   bc = objcts.ocan[BrickOX - 1];
// 						!GET CONTAINER.
   if (br == 0 && bc != 0) {
      br = objcts.oroom[bc - 1];
   }
   newsta(FuseOX, 0, 0, 0, 0);
// 						!KILL FUSE.
   newsta(BrickOX, 0, 0, 0, 0);
// 						!KILL BRICK.
   if (br != 0 && br != play.here) {
      goto L8100;
   }
// 						!BRICK ELSEWHERE?

   rooms.rflag[play.here - 1] |= MungR;
   rrand[play.here - 1] = 114;
// 						!MUNG ROOM.
   jigsup(150);
// 						!DEAD.
   return;

L8100:
   rspeak(151);
// 						!BOOM.
   state.mungrm = br;
// 						!SAVE ROOM THAT BLEW.
   cevent.ctick[SafCX - 1] = 5;
// 						!SET SAFE INTERRUPT.
   if (br != MSafeRX) {
      goto L8200;
   }
// 						!BLEW SAFE ROOM?
   if (bc != SSlotOX) {
      return;
   }
// 						!WAS BRICK IN SAFE?
   newsta(SSlotOX, 0, 0, 0, 0);
// 						!KILL SLOT.
   objcts.oflag2[SafeOX - 1] |= OpenO;
   findex_0.safef = true;
// 						!INDICATE SAFE BLOWN.
   return;

L8200:
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!BLEW WRONG ROOM.
      if (qhere(i, br) && (objcts.oflag1[i - 1] & TakeO) != 0) {
         newsta(i, 0, 0, 0, 0);
      }
// L8250:
   }
   if (br != LRoomRX) {
      return;
   }
// 						!BLEW LIVING ROOM?
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts.ocan[i - 1] == TCaseOX) {
         newsta(i, 0, 0, 0, 0);
      }
// 						!KILL TROPHY CASE.
// L8300:
   }
   return;

L8500:
   if (qhere(FuseOX, play.here) || objcts.oadv[FuseOX - 1] == play.winner) {
      rspeak(152);
   }
   newsta(FuseOX, 0, 0, 0, 0);
// 						!KILL FUSE.
   return;
// CEVAPP, PAGE 5

// CEV9--	LEDGE MUNGE.

L9000:
   rooms.rflag[Ledg4RX - 1] |= MungR;
   rrand[Ledg4RX - 1] = 109;
   if (play.here == Ledg4RX) {
      goto L9100;
   }
// 						!WAS HE THERE?
   rspeak(110);
// 						!NO, NARROW ESCAPE.
   return;

L9100:
   if (advs.avehic[play.winner - 1] != 0) {
      goto L9200;
   }
// 						!IN VEHICLE?
   jigsup(111);
// 						!NO, DEAD.
   return;

L9200:
   if (findex_1.btief != 0) {
      goto L9300;
   }
// 						!TIED TO LEDGE?
   rspeak(112);
// 						!NO, NO PLACE TO LAND.
   return;

L9300:
   state.bloc = VlBotRX;
// 						!YES, CRASH BALLOON.
   newsta(BalloOX, 0, 0, 0, 0);
// 						!BALLOON & CONTENTS DIE.
   newsta(DBallOX, 0, state.bloc, 0, 0);
// 						!INSERT DEAD BALLOON.
   findex_1.btief = 0;
   findex_1.binff = 0;
   cevent.cflag[BalCX - 1] = false;
   cevent.cflag[BrnCX - 1] = false;
   jigsup(113);
// 						!DEAD
   return;

// CEV10--	SAFE MUNG.

L10000:
   rooms.rflag[state.mungrm - 1] |= MungR;
   rrand[state.mungrm - 1] = 114;
   if (play.here == state.mungrm) {
      goto L10100;
   }
// 						!IS HE PRESENT?
   rspeak(115);
// 						!LET HIM KNOW.
   if (state.mungrm == MSafeRX) {
      cevent.ctick[LedCX - 1] = 8;
   }
// 						!START LEDGE CLOCK.
   return;

L10100:
   i = 116;
// 						!HE'S DEAD,
   if ((rooms.rflag[play.here - 1] & HouseR) != 0) {
      i = 117;
   }
   jigsup(i);
// 						!LET HIM KNOW.
   return;
// CEVAPP, PAGE 6

// CEV11--	VOLCANO GNOME

L11000:
   if (play.here == Ledg2RX || play.here == Ledg3RX || play.here == Ledg4RX || play.here == VlBotRX) {
      goto L11100;
   }
// 						!IS HE ON LEDGE?
   cevent.ctick[VlgCX - 1] = 1;
// 						!NO, WAIT A WHILE.
   return;

L11100:
   newsta(GnomeOX, 118, play.here, 0, 0);
// 						!YES, MATERIALIZE GNOME.
   return;

// CEV12--	VOLCANO GNOME DISAPPEARS

L12000:
   newsta(GnomeOX, 149, 0, 0, 0);
// 						!DISAPPEAR THE GNOME.
   return;

// CEV13--	BUCKET.

L13000:
   if (objcts.ocan[WaterOX - 1] == BuckeOX) {
      newsta(WaterOX, 0, 0, 0, 0);
   }
   return;

// CEV14--	SPHERE.  IF EXPIRES, HE'S TRAPPED.

L14000:
   rooms.rflag[CageRRX - 1] |= MungR;
   rrand[CageRRX - 1] = 147;
   jigsup(148);
// 						!MUNG PLAYER.
   return;

// CEV15--	END GAME HERALD.

L15000:
   findex_0.endgmf = true;
// 						!WE'RE IN ENDGAME.
   rspeak(119);
// 						!INFORM OF ENDGAME.
   return;
// CEVAPP, PAGE 7

// CEV16--	FOREST MURMURS

L16000:
   cevent.cflag[ForCX - 1] = play.here == MTreeRX || play.here >= Fore1RX && play.here < ClearRX;
   if (cevent.cflag[ForCX - 1] && prob(10, 10)) {
      rspeak(635);
   }
   return;

// CEV17--	SCOL ALARM

L17000:
   if (play.here == BkTwiRX) {
      cevent.cflag[ZgICX - 1] = true;
   }
// 						!IF IN TWI, GNOME.
   if (play.here == BkVauRX) {
      jigsup(636);
   }
// 						!IF IN VAU, DEAD.
   return;

// CEV18--	ENTER GNOME OF ZURICH

L18000:
   cevent.cflag[ZgOCX - 1] = true;
// 						!EXITS, TOO.
   newsta(ZGnomOX, 0, BkTwiRX, 0, 0);
// 						!PLACE IN TWI.
   if (play.here == BkTwiRX) {
      rspeak(637);
   }
// 						!ANNOUNCE.
   return;

// CEV19--	EXIT GNOME

L19000:
   newsta(ZGnomOX, 0, 0, 0, 0);
// 						!VANISH.
   if (play.here == BkTwiRX) {
      rspeak(638);
   }
// 						!ANNOUNCE.
   return;
// CEVAPP, PAGE 8

// CEV20--	START OF ENDGAME

L20000:
   if (findex_0.spellf) {
      goto L20200;
   }
// 						!SPELL HIS WAY IN?
   if (play.here != CryptRX) {
      return;
   }
// 						!NO, STILL IN TOMB?
   if (!lit(play.here)) {
      goto L20100;
   }
// 						!LIGHTS OFF?
   cevent.ctick[SteCX - 1] = 3;
// 						!RESCHEDULE.
   return;

L20100:
   rspeak(727);
// 						!ANNOUNCE.
L20200:
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!STRIP HIM OF OBJS.
      newsta(i, 0, objcts.oroom[i - 1], objcts.ocan[i - 1], 0);
// L20300:
   }
   newsta(LampOX, 0, 0, 0, PlayerAX);
// 						!GIVE HIM LAMP.
   newsta(SwordOX, 0, 0, 0, PlayerAX);
// 						!GIVE HIM SWORD.

   objcts.oflag1[LampOX - 1] = (objcts.oflag1[LampOX - 1] | LiteO) & ~OnO;
   objcts.oflag2[LampOX - 1] |= TChO;
   cevent.cflag[LntCX - 1] = false;
// 						!LAMP IS GOOD AS NEW.
   cevent.ctick[LntCX - 1] = 350;
   findex_1.orlamp = 0;
   objcts.oflag2[SwordOX - 1] |= TChO;
   hack.swdact = true;
   hack.swdsta = 0;

   hack.thfact = false;
// 						!THIEF GONE.
   findex_0.endgmf = true;
// 						!ENDGAME RUNNING.
   cevent.cflag[MatCX - 1] = false;
// 						!MATCHES GONE,
   cevent.cflag[CndCX - 1] = false;
// 						!CANDLES GONE.

   scrupd(rooms.rval[CryptRX - 1]);
// 						!SCORE CRYPT,
   rooms.rval[CryptRX - 1] = 0;
// 						!BUT ONLY ONCE.
   f = moveto(TStrsRX, play.winner);
// 						!TO TOP OF STAIRS,
   f = rmdesc(3);
// 						!AND DESCRIBE.
   return;
// 						!BAM
// 						!

// CEV21--	MIRROR CLOSES.

L21000:
   findex_0.mrpshf = false;
// 						!BUTTON IS OUT.
   findex_0.mropnf = false;
// 						!MIRROR IS CLOSED.
   if (play.here == MrAntRX) {
      rspeak(728);
   }
// 						!DESCRIBE BUTTON.
   if (play.here == InMirRX || mrhere(play.here) == 1) {
      rspeak(729);
   }
   return;
// CEVAPP, PAGE 9

// CEV22--	DOOR CLOSES.

L22000:
   if (findex_0.wdopnf) {
      rspeak(730);
   }
// 						!DESCRIBE.
   findex_0.wdopnf = false;
// 						!CLOSED.
   return;

// CEV23--	INQUISITOR'S QUESTION

L23000:
   if (advs.aroom[PlayerAX - 1] != FDoorRX) {
      return;
   }
// 						!IF PLAYER LEFT, DIE.
   rspeak(769);
   i__1 = findex_1.quesno + 770;
   rspeak(i__1);
   cevent.ctick[InqCX - 1] = 2;
   return;

// CEV24--	MASTER FOLLOWS

L24000:
   if (advs.aroom[MastrAX - 1] == play.here) {
      return;
   }
// 						!NO MOVEMENT, DONE.
   if (play.here != CellRX && play.here != PCellRX) {
      goto L24100;
   }
   if (findex_0.follwf) {
      rspeak(811);
   }
// 						!WONT GO TO CELLS.
   findex_0.follwf = false;
   return;

L24100:
   findex_0.follwf = true;
// 						!FOLLOWING.
   i = 812;
// 						!ASSUME CATCHES UP.
   i__1 = MaxDX;
   i__2 = MinDX;
   for (j = MinDX; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
      if (findxt(j, advs.aroom[MastrAX - 1]) && curxt.xroom1 == play.here) {
         i = 813;
      }
// L24200:
   }
   rspeak(i);
   newsta(MasterOX, 0, play.here, 0, 0);
// 						!MOVE MASTER OBJECT.
   advs.aroom[MastrAX - 1] = play.here;
// 						!MOVE MASTER PLAYER.
}

// Light interrupt processor
static void litint(int obj, int *ctr, int cev, const int *ticks, int tickln) {
// Parameter adjustments
   --ticks;

// Function Body
   ++(*ctr);
// 						!ADVANCE STATE CNTR.
   cevent.ctick[cev - 1] = ticks[*ctr];
// 						!RESET INTERRUPT.
   if (cevent.ctick[cev - 1] != 0) {
      goto L100;
   }
// 						!EXPIRED?
   objcts.oflag1[obj - 1] &= ~(LiteO + FlamO + OnO);
   if (objcts.oroom[obj - 1] == play.here || objcts.oadv[obj - 1] == play.winner) {
      rspsub(293, objcts.odesc2[obj - 1]);
   }
   return;

L100:
   if (objcts.oroom[obj - 1] == play.here || objcts.oadv[obj - 1] == play.winner) {
      rspeak(ticks[*ctr + tickln / 2]);
   }
}
