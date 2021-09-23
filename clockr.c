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
   Bool f;
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
   i__1 = 0, i__2 = advs.astren[aindex.player - 1] + 1;
   advs.astren[aindex.player - 1] = min(i__1, i__2);
// 						!RECOVER.
   if (advs.astren[aindex.player - 1] >= 0) {
      return;
   }
// 						!FULLY RECOVERED?
   cevent.ctick[cindex.cevcur - 1] = 30;
// 						!NO, WAIT SOME MORE.
   return;

// CEV2--	MAINT-ROOM WITH LEAK.  RAISE THE WATER LEVEL.

L2000:
   if (play.here == rindex_.maint) {
      i__1 = findex.rvmnt / 2 + 71;
      rspeak(i__1);
   }
// 						!DESCRIBE.
   ++findex.rvmnt;
// 						!RAISE WATER LEVEL.
   if (findex.rvmnt <= 16) {
      return;
   }
// 						!IF NOT FULL, EXIT.
   cevent.ctick[cindex.cevmnt - 1] = 0;
// 						!FULL, DISABLE CLOCK.
   rooms.rflag[rindex_.maint - 1] |= MungR;
   rrand[rindex_.maint - 1] = 80;
// 						!SAY IT IS FULL OF WATER.
   if (play.here == rindex_.maint) {
      jigsup(81);
   }
// 						!DROWN HIM IF PRESENT.
   return;

// CEV3--	LANTERN.  DESCRIBE GROWING DIMNESS.

L3000:
   litint(oindex.lamp, &findex.orlamp, cindex.cevlnt, lmptck, 12);
// 						!DO LIGHT INTERRUPT.
   return;

// CEV4--	MATCH.  OUT IT GOES.

L4000:
   rspeak(153);
// 						!MATCH IS OUT.
   objcts.oflag1[oindex.match - 1] &= ~OnO;
   return;

// CEV5--	CANDLE.  DESCRIBE GROWING DIMNESS.

L5000:
   litint(oindex.candl, &findex.orcand, cindex.cevcnd, cndtck, 10);
// 						!DO CANDLE INTERRUPT.
   return;
// CEVAPP, PAGE 3

// CEV6--	BALLOON

L6000:
   cevent.ctick[cindex.cevbal - 1] = 3;
// 						!RESCHEDULE INTERRUPT.
   f = advs.avehic[play.winner - 1] == oindex.ballo;
// 						!SEE IF IN BALLOON.
   if (state.bloc == rindex_.vlbot) {
      goto L6800;
   }
// 						!AT BOTTOM?
   if (state.bloc == rindex_.ledg2 || state.bloc == rindex_.ledg3 || state.bloc == rindex_.ledg4 || state.bloc == rindex_.vlbot) {
      goto L6700;
   }
// 						!ON LEDGE?
   if ((objcts.oflag2[oindex.recep - 1] & OpenO) != 0 && findex.binff != 0) {
      goto L6500;
   }

// BALLOON IS IN MIDAIR AND IS DEFLATED (OR HAS RECEPTACLE CLOSED).
// FALL TO NEXT ROOM.

   if (state.bloc != rindex_.vair1) {
      goto L6300;
   }
// 						!IN VAIR1?
   state.bloc = rindex_.vlbot;
// 						!YES, NOW AT VLBOT.
   newsta(oindex.ballo, 0, state.bloc, 0, 0);
   if (f) {
      goto L6200;
   }
// 						!IN BALLOON?
   if (play.here == rindex_.ledg2 || play.here == rindex_.ledg3 || play.here == rindex_.ledg4 || play.here == rindex_.vlbot) {
      rspeak(530);
   }
// 						!ON LEDGE, DESCRIBE.
   return;

L6200:
   f = moveto(state.bloc, play.winner);
// 						!MOVE HIM.
   if (findex.binff == 0) {
      goto L6250;
   }
// 						!IN BALLOON.  INFLATED?
   rspeak(531);
// 						!YES, LANDED.
   f = rmdesc(0);
// 						!DESCRIBE.
   return;

L6250:
   newsta(oindex.ballo, 532, 0, 0, 0);
// 						!NO, BALLOON & CONTENTS DIE.
   newsta(oindex.dball, 0, state.bloc, 0, 0);
// 						!INSERT DEAD BALLOON.
   advs.avehic[play.winner - 1] = 0;
// 						!NOT IN VEHICLE.
   cevent.cflag[cindex.cevbal - 1] = false;
// 						!DISABLE INTERRUPTS.
   cevent.cflag[cindex.cevbrn - 1] = false;
   findex.binff = 0;
   findex.btief = 0;
   return;

L6300:
   --state.bloc;
// 						!NOT IN VAIR1, DESCEND.
   newsta(oindex.ballo, 0, state.bloc, 0, 0);
   if (f) {
      goto L6400;
   }
// 						!IS HE IN BALLOON?
   if (play.here == rindex_.ledg2 || play.here == rindex_.ledg3 || play.here == rindex_.ledg4 || play.here == rindex_.vlbot) {
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
   if (state.bloc != rindex_.vair4) {
      goto L6600;
   }
// 						!AT VAIR4?
   cevent.ctick[cindex.cevbrn - 1] = 0;
   cevent.ctick[cindex.cevbal - 1] = 0;
   findex.binff = 0;
   findex.btief = 0;
   state.bloc = rindex_.vlbot;
// 						!FALL TO BOTTOM.
   newsta(oindex.ballo, 0, 0, 0, 0);
// 						!BALLOON & CONTENTS DIE.
   newsta(oindex.dball, 0, state.bloc, 0, 0);
// 						!SUBSTITUTE DEAD BALLOON.
   if (f) {
      goto L6550;
   }
// 						!WAS HE IN IT?
   if (play.here == rindex_.ledg2 || play.here == rindex_.ledg3 || play.here == rindex_.ledg4 || play.here == rindex_.vlbot) {
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
   newsta(oindex.ballo, 0, state.bloc, 0, 0);
   if (f) {
      goto L6650;
   }
// 						!IN BALLOON?
   if (play.here == rindex_.ledg2 || play.here == rindex_.ledg3 || play.here == rindex_.ledg4 || play.here == rindex_.vlbot) {
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
   state.bloc += rindex_.vair2 - rindex_.ledg2;
// 						!MOVE TO MIDAIR.
   newsta(oindex.ballo, 0, state.bloc, 0, 0);
   if (f) {
      goto L6750;
   }
// 						!IN BALLOON?
   if (play.here == rindex_.ledg2 || play.here == rindex_.ledg3 || play.here == rindex_.ledg4 || play.here == rindex_.vlbot) {
      rspeak(539);
   }
// 						!NO, STRANDED.
   cevent.ctick[cindex.cevvlg - 1] = 10;
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
   if (findex.binff == 0 || !((objcts.oflag2[oindex.recep - 1] & OpenO) != 0)) {
      return;
   }
   state.bloc = rindex_.vair1;
// 						!INFLATED AND OPEN,
   newsta(oindex.ballo, 0, state.bloc, 0, 0);
// 						!GO UP TO VAIR1.
   if (f) {
      goto L6850;
   }
// 						!IN BALLOON?
   if (play.here == rindex_.ledg2 || play.here == rindex_.ledg3 || play.here == rindex_.ledg4 || play.here == rindex_.vlbot) {
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
      if (oindex.recep == objcts.ocan[i - 1] && (objcts.oflag1[i - 1] & FlamO) != 0) {
         goto L7200;
      }
// L7100:
   }
   bug(4, 0);

L7200:
   newsta(i, 0, 0, 0, 0);
// 						!VANISH OBJECT.
   findex.binff = 0;
// 						!UNINFLATED.
   if (play.here == state.bloc) {
      rspsub(292, objcts.odesc2[i - 1]);
   }
// 						!DESCRIBE.
   return;

// CEV8--	FUSE FUNCTION

L8000:
   if (objcts.ocan[oindex.fuse - 1] != oindex.brick) {
      goto L8500;
   }
// 						!IGNITED BRICK?
   br = objcts.oroom[oindex.brick - 1];
// 						!GET BRICK ROOM.
   bc = objcts.ocan[oindex.brick - 1];
// 						!GET CONTAINER.
   if (br == 0 && bc != 0) {
      br = objcts.oroom[bc - 1];
   }
   newsta(oindex.fuse, 0, 0, 0, 0);
// 						!KILL FUSE.
   newsta(oindex.brick, 0, 0, 0, 0);
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
   cevent.ctick[cindex.cevsaf - 1] = 5;
// 						!SET SAFE INTERRUPT.
   if (br != rindex_.msafe) {
      goto L8200;
   }
// 						!BLEW SAFE ROOM?
   if (bc != oindex.sslot) {
      return;
   }
// 						!WAS BRICK IN SAFE?
   newsta(oindex.sslot, 0, 0, 0, 0);
// 						!KILL SLOT.
   objcts.oflag2[oindex.safe - 1] |= OpenO;
   findex.safef = true;
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
   if (br != rindex_.lroom) {
      return;
   }
// 						!BLEW LIVING ROOM?
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts.ocan[i - 1] == oindex.tcase) {
         newsta(i, 0, 0, 0, 0);
      }
// 						!KILL TROPHY CASE.
// L8300:
   }
   return;

L8500:
   if (qhere(oindex.fuse, play.here) || objcts.oadv[oindex.fuse - 1] == play.winner) {
      rspeak(152);
   }
   newsta(oindex.fuse, 0, 0, 0, 0);
// 						!KILL FUSE.
   return;
// CEVAPP, PAGE 5

// CEV9--	LEDGE MUNGE.

L9000:
   rooms.rflag[rindex_.ledg4 - 1] |= MungR;
   rrand[rindex_.ledg4 - 1] = 109;
   if (play.here == rindex_.ledg4) {
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
   if (findex.btief != 0) {
      goto L9300;
   }
// 						!TIED TO LEDGE?
   rspeak(112);
// 						!NO, NO PLACE TO LAND.
   return;

L9300:
   state.bloc = rindex_.vlbot;
// 						!YES, CRASH BALLOON.
   newsta(oindex.ballo, 0, 0, 0, 0);
// 						!BALLOON & CONTENTS DIE.
   newsta(oindex.dball, 0, state.bloc, 0, 0);
// 						!INSERT DEAD BALLOON.
   findex.btief = 0;
   findex.binff = 0;
   cevent.cflag[cindex.cevbal - 1] = false;
   cevent.cflag[cindex.cevbrn - 1] = false;
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
   if (state.mungrm == rindex_.msafe) {
      cevent.ctick[cindex.cevled - 1] = 8;
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
   if (play.here == rindex_.ledg2 || play.here == rindex_.ledg3 || play.here == rindex_.ledg4 || play.here == rindex_.vlbot) {
      goto L11100;
   }
// 						!IS HE ON LEDGE?
   cevent.ctick[cindex.cevvlg - 1] = 1;
// 						!NO, WAIT A WHILE.
   return;

L11100:
   newsta(oindex.gnome, 118, play.here, 0, 0);
// 						!YES, MATERIALIZE GNOME.
   return;

// CEV12--	VOLCANO GNOME DISAPPEARS

L12000:
   newsta(oindex.gnome, 149, 0, 0, 0);
// 						!DISAPPEAR THE GNOME.
   return;

// CEV13--	BUCKET.

L13000:
   if (objcts.ocan[oindex.water - 1] == oindex.bucke) {
      newsta(oindex.water, 0, 0, 0, 0);
   }
   return;

// CEV14--	SPHERE.  IF EXPIRES, HE'S TRAPPED.

L14000:
   rooms.rflag[rindex_.cager - 1] |= MungR;
   rrand[rindex_.cager - 1] = 147;
   jigsup(148);
// 						!MUNG PLAYER.
   return;

// CEV15--	END GAME HERALD.

L15000:
   findex.endgmf = true;
// 						!WE'RE IN ENDGAME.
   rspeak(119);
// 						!INFORM OF ENDGAME.
   return;
// CEVAPP, PAGE 7

// CEV16--	FOREST MURMURS

L16000:
   cevent.cflag[cindex.cevfor - 1] = play.here == rindex_.mtree || play.here >= rindex_.fore1 && play.here < rindex_.clear;
   if (cevent.cflag[cindex.cevfor - 1] && prob(10, 10)) {
      rspeak(635);
   }
   return;

// CEV17--	SCOL ALARM

L17000:
   if (play.here == rindex_.bktwi) {
      cevent.cflag[cindex.cevzgi - 1] = true;
   }
// 						!IF IN TWI, GNOME.
   if (play.here == rindex_.bkvau) {
      jigsup(636);
   }
// 						!IF IN VAU, DEAD.
   return;

// CEV18--	ENTER GNOME OF ZURICH

L18000:
   cevent.cflag[cindex.cevzgo - 1] = true;
// 						!EXITS, TOO.
   newsta(oindex.zgnom, 0, rindex_.bktwi, 0, 0);
// 						!PLACE IN TWI.
   if (play.here == rindex_.bktwi) {
      rspeak(637);
   }
// 						!ANNOUNCE.
   return;

// CEV19--	EXIT GNOME

L19000:
   newsta(oindex.zgnom, 0, 0, 0, 0);
// 						!VANISH.
   if (play.here == rindex_.bktwi) {
      rspeak(638);
   }
// 						!ANNOUNCE.
   return;
// CEVAPP, PAGE 8

// CEV20--	START OF ENDGAME

L20000:
   if (findex.spellf) {
      goto L20200;
   }
// 						!SPELL HIS WAY IN?
   if (play.here != rindex_.crypt) {
      return;
   }
// 						!NO, STILL IN TOMB?
   if (!lit(play.here)) {
      goto L20100;
   }
// 						!LIGHTS OFF?
   cevent.ctick[cindex.cevste - 1] = 3;
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
   newsta(oindex.lamp, 0, 0, 0, aindex.player);
// 						!GIVE HIM LAMP.
   newsta(oindex.sword, 0, 0, 0, aindex.player);
// 						!GIVE HIM SWORD.

   objcts.oflag1[oindex.lamp - 1] = (objcts.oflag1[oindex.lamp - 1] | LiteO) & ~OnO;
   objcts.oflag2[oindex.lamp - 1] |= TChO;
   cevent.cflag[cindex.cevlnt - 1] = false;
// 						!LAMP IS GOOD AS NEW.
   cevent.ctick[cindex.cevlnt - 1] = 350;
   findex.orlamp = 0;
   objcts.oflag2[oindex.sword - 1] |= TChO;
   hack.swdact = true;
   hack.swdsta = 0;

   hack.thfact = false;
// 						!THIEF GONE.
   findex.endgmf = true;
// 						!ENDGAME RUNNING.
   cevent.cflag[cindex.cevmat - 1] = false;
// 						!MATCHES GONE,
   cevent.cflag[cindex.cevcnd - 1] = false;
// 						!CANDLES GONE.

   scrupd(rooms.rval[rindex_.crypt - 1]);
// 						!SCORE CRYPT,
   rooms.rval[rindex_.crypt - 1] = 0;
// 						!BUT ONLY ONCE.
   f = moveto(rindex_.tstrs, play.winner);
// 						!TO TOP OF STAIRS,
   f = rmdesc(3);
// 						!AND DESCRIBE.
   return;
// 						!BAM
// 						!

// CEV21--	MIRROR CLOSES.

L21000:
   findex.mrpshf = false;
// 						!BUTTON IS OUT.
   findex.mropnf = false;
// 						!MIRROR IS CLOSED.
   if (play.here == rindex_.mrant) {
      rspeak(728);
   }
// 						!DESCRIBE BUTTON.
   if (play.here == rindex_.inmir || mrhere(play.here) == 1) {
      rspeak(729);
   }
   return;
// CEVAPP, PAGE 9

// CEV22--	DOOR CLOSES.

L22000:
   if (findex.wdopnf) {
      rspeak(730);
   }
// 						!DESCRIBE.
   findex.wdopnf = false;
// 						!CLOSED.
   return;

// CEV23--	INQUISITOR'S QUESTION

L23000:
   if (advs.aroom[aindex.player - 1] != rindex_.fdoor) {
      return;
   }
// 						!IF PLAYER LEFT, DIE.
   rspeak(769);
   i__1 = findex.quesno + 770;
   rspeak(i__1);
   cevent.ctick[cindex.cevinq - 1] = 2;
   return;

// CEV24--	MASTER FOLLOWS

L24000:
   if (advs.aroom[aindex.amastr - 1] == play.here) {
      return;
   }
// 						!NO MOVEMENT, DONE.
   if (play.here != rindex_.cell && play.here != rindex_.pcell) {
      goto L24100;
   }
   if (findex.follwf) {
      rspeak(811);
   }
// 						!WONT GO TO CELLS.
   findex.follwf = false;
   return;

L24100:
   findex.follwf = true;
// 						!FOLLOWING.
   i = 812;
// 						!ASSUME CATCHES UP.
   i__1 = xsrch.xmax;
   i__2 = xsrch.xmin;
   for (j = xsrch.xmin; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
      if (findxt(j, advs.aroom[aindex.amastr - 1]) && curxt.xroom1 == play.here) {
         i = 813;
      }
// L24200:
   }
   rspeak(i);
   newsta(oindex.master, 0, play.here, 0, 0);
// 						!MOVE MASTER OBJECT.
   advs.aroom[aindex.amastr - 1] = play.here;
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
