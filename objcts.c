// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Object special action routines
Bool oappli(int ri, int arg) {
// Initialized data
   const int mxsmp = 99;

// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   Bool f;
   int flobts, i;
   int j,/* x,*/ av, io, ir, iz;
   int odi2 = 0, odo2 = 0;
   int nloc;

// OAPPLI, PAGE 2

   if (ri == 0) {
      goto L10;
   }
// 						!ZERO IS FALSE APP.
   if (ri <= mxsmp) {
      goto L100;
   }
// 						!SIMPLE OBJECT?
   if (prsvec.prso > 220) {
      goto L5;
   }
   if (prsvec.prso != 0) {
      odo2 = objcts.odesc2[prsvec.prso - 1];
   }
L5:
   if (prsvec.prsi != 0) {
      odi2 = objcts.odesc2[prsvec.prsi - 1];
   }
   av = advs.avehic[play.winner - 1];
   flobts = FlamO + LiteO + OnO;
   ret_val = true;

   switch (ri - mxsmp) {
      case 1:
         goto L2000;
      case 2:
         goto L5000;
      case 3:
         goto L10000;
      case 4:
         goto L11000;
      case 5:
         goto L12000;
      case 6:
         goto L15000;
      case 7:
         goto L18000;
      case 8:
         goto L19000;
      case 9:
         goto L20000;
      case 10:
         goto L22000;
      case 11:
         goto L25000;
      case 12:
         goto L26000;
      case 13:
         goto L32000;
      case 14:
         goto L35000;
      case 15:
         goto L39000;
      case 16:
         goto L40000;
      case 17:
         goto L45000;
      case 18:
         goto L47000;
      case 19:
         goto L48000;
      case 20:
         goto L49000;
      case 21:
         goto L50000;
      case 22:
         goto L51000;
      case 23:
         goto L52000;
      case 24:
         goto L54000;
      case 25:
         goto L55000;
      case 26:
         goto L56000;
      case 27:
         goto L57000;
      case 28:
         goto L58000;
      case 29:
         goto L59000;
      case 30:
         goto L60000;
      case 31:
         goto L61000;
      case 32:
         goto L62000;
   }
   bug(6, ri);

// RETURN HERE TO DECLARE FALSE RESULT

L10:
   ret_val = false;
   return ret_val;

// SIMPLE OBJECTS, PROCESSED EXTERNALLY.

L100:
   if (ri < 32) {
      ret_val = sobjs(ri, arg);
   } else {
      ret_val = nobjs(ri/*, arg*/);
   }
   return ret_val;
// OAPPLI, PAGE 3

// O100--	MACHINE FUNCTION

L2000:
   if (play.here != MMachRX) {
      goto L10;
   }
// 						!NOT HERE? F
   ret_val = opncls(MachiOX, 123, 124);
// 						!HANDLE OPN/CLS.
   return ret_val;

// O101--	WATER FUNCTION

L5000:
   if (prsvec.prsa != FillW) {
      goto L5050;
   }
// 						!FILL X WITH Y IS
   prsvec.prsa = PutW;
// 						!MADE INTO
   i = prsvec.prsi;
   prsvec.prsi = prsvec.prso;
   prsvec.prso = i;
// 						!PUT Y IN X.
   i = odi2;
   odi2 = odo2;
   odo2 = i;
L5050:
   if (prsvec.prso == WaterOX || prsvec.prso == GWateOX) {
      goto L5100;
   }
   rspeak(561);
// 						!WATER IS IND OBJ,
   return ret_val;
// 						!PUNT.

L5100:
   if (prsvec.prsa != TakeW) {
      goto L5400;
   }
// 						!TAKE WATER?
   if (objcts.oadv[BottlOX - 1] == play.winner && objcts.ocan[prsvec.prso - 1] != BottlOX) {
      goto L5500;
   }
   if (objcts.ocan[prsvec.prso - 1] == 0) {
      goto L5200;
   }
// 						!INSIDE ANYTHING?
   if ((objcts.oflag2[objcts.ocan[prsvec.prso - 1] - 1] & OpenO) != 0) {
      goto L5200;
   }
// 						!YES, OPEN?
   rspsub(525, objcts.odesc2[objcts.ocan[prsvec.prso - 1] - 1]);
// 						!INSIDE, CLOSED, PUNT.
   return ret_val;

L5200:
   rspeak(615);
// 						!NOT INSIDE OR OPEN,
   return ret_val;
// 						!SLIPS THRU FINGERS.

L5400:
   if (prsvec.prsa != PutW) {
      goto L5700;
   }
// 						!PUT WATER IN X?
   if (av != 0 && prsvec.prsi == av) {
      goto L5800;
   }
// 						!IN VEH?
   if (prsvec.prsi == BottlOX) {
      goto L5500;
   }
// 						!IN BOTTLE?
   rspsub(297, odi2);
// 						!WONT GO ELSEWHERE.
   newsta(prsvec.prso, 0, 0, 0, 0);
// 						!VANISH WATER.
   return ret_val;

L5500:
   if ((objcts.oflag2[BottlOX - 1] & OpenO) != 0) {
      goto L5550;
   }
// 						!BOTTLE OPEN?
   rspeak(612);
// 						!NO, LOSE.
   return ret_val;

L5550:
   if (qempty(BottlOX)) {
      goto L5600;
   }
// 						!OPEN, EMPTY?
   rspeak(613);
// 						!NO, ALREADY FULL.
   return ret_val;

L5600:
   newsta(WaterOX, 614, 0, BottlOX, 0);
// 						!TAKE WATER TO BOTTLE.
   return ret_val;

L5700:
   if (prsvec.prsa != DropW && prsvec.prsa != PourW && prsvec.prsa != GiveW) {
      goto L5900;
   }
   if (av != 0) {
      goto L5800;
   }
// 						!INTO VEHICLE?
   newsta(prsvec.prso, 133, 0, 0, 0);
// 						!NO, VANISHES.
   return ret_val;

L5800:
   newsta(WaterOX, 0, 0, av, 0);
// 						!WATER INTO VEHICLE.
   rspsub(296, objcts.odesc2[av - 1]);
// 						!DESCRIBE.
   return ret_val;

L5900:
   if (prsvec.prsa != ThrowW) {
      goto L10;
   }
// 						!LAST CHANCE, THROW?
   newsta(prsvec.prso, 132, 0, 0, 0);
// 						!VANISHES.
   return ret_val;
// OAPPLI, PAGE 4

// O102--	LEAF PILE

L10000:
   if (prsvec.prsa != BurnW) {
      goto L10500;
   }
// 						!BURN?
   if (objcts.oroom[prsvec.prso - 1] == 0) {
      goto L10100;
   }
// 						!WAS HE CARRYING?
   newsta(prsvec.prso, 158, 0, 0, 0);
// 						!NO, BURN IT.
   return ret_val;

L10100:
   newsta(prsvec.prso, 0, play.here, 0, 0);
// 						!DROP LEAVES.
   jigsup(159);
// 						!BURN HIM.
   return ret_val;

L10500:
   if (prsvec.prsa != MoveW) {
      goto L10600;
   }
// 						!MOVE?
   rspeak(2);
// 						!DONE.
   return ret_val;

L10600:
   if (prsvec.prsa != LookUW || findex.rvclr != 0) {
      goto L10;
   }
   rspeak(344);
// 						!LOOK UNDER?
   return ret_val;

// O103--	TROLL, DONE EXTERNALLY.

L11000:
   ret_val = trollp(/*arg*/);
// 						!TROLL PROCESSOR.
   return ret_val;

// O104--	RUSTY KNIFE.

L12000:
   if (prsvec.prsa != TakeW) {
      goto L12100;
   }
// 						!TAKE?
   if (objcts.oadv[SwordOX - 1] == play.winner) {
      rspeak(160);
   }
// 						!PULSE SWORD.
   goto L10;

L12100:
   if ((prsvec.prsa != AttacW && prsvec.prsa != KillW || prsvec.prsi != RKnifOX) && (prsvec.prsa != SwingW && prsvec.prsa != ThrowW || prsvec.prso != RKnifOX)) {
      goto L10;
   }
   newsta(RKnifOX, 0, 0, 0, 0);
// 						!KILL KNIFE.
   jigsup(161);
// 						!KILL HIM.
   return ret_val;
// OAPPLI, PAGE 5

// O105--	GLACIER

L15000:
   if (prsvec.prsa != ThrowW) {
      goto L15500;
   }
// 						!THROW?
   if (prsvec.prso != TorchOX) {
      goto L15400;
   }
// 						!TORCH?
   newsta(IceOX, 169, 0, 0, 0);
// 						!MELT ICE.
   objcts.odesc1[TorchOX - 1] = 174;
// 						!MUNG TORCH.
   objcts.odesc2[TorchOX - 1] = 173;
   objcts.oflag1[TorchOX - 1] &= ~flobts;
   newsta(TorchOX, 0, StreaRX, 0, 0);
// 						!MOVE TORCH.
   findex.glacrf = true;
// 						!GLACIER GONE.
   if (!lit(play.here)) {
      rspeak(170);
   }
// 						!IN DARK?
   return ret_val;

L15400:
   rspeak(171);
// 						!JOKE IF NOT TORCH.
   return ret_val;

L15500:
   if (prsvec.prsa != ReadW || prsvec.prso != IceOX) {
      goto L10;
   }
   if ((objcts.oflag1[prsvec.prsi - 1] & flobts) == flobts) {
      goto L15600;
   }
   rspsub(298, odi2);
// 						!CANT MELT WITH THAT.
   return ret_val;

L15600:
   findex.glacmf = true;
// 						!PARTIAL MELT.
   if (prsvec.prsi != TorchOX) {
      goto L15700;
   }
// 						!MELT WITH TORCH?
   objcts.odesc1[TorchOX - 1] = 174;
// 						!MUNG TORCH.
   objcts.odesc2[TorchOX - 1] = 173;
   objcts.oflag1[TorchOX - 1] &= ~flobts;
L15700:
   jigsup(172);
// 						!DROWN.
   return ret_val;

// O106--	BLACK BOOK

L18000:
   if (prsvec.prsa != OpenW) {
      goto L18100;
   }
// 						!OPEN?
   rspeak(180);
// 						!JOKE.
   return ret_val;

L18100:
   if (prsvec.prsa != CloseW) {
      goto L18200;
   }
// 						!CLOSE?
   rspeak(181);
   return ret_val;

L18200:
   if (prsvec.prsa != BurnW) {
      goto L10;
   }
// 						!BURN?
   newsta(prsvec.prso, 0, 0, 0, 0);
// 						!FATAL JOKE.
   jigsup(182);
   return ret_val;
// OAPPLI, PAGE 6

// O107--	CANDLES, PROCESSED EXTERNALLY

L19000:
   ret_val = lightp(CandlOX);
   return ret_val;

// O108--	MATCHES, PROCESSED EXTERNALLY

L20000:
   ret_val = lightp(MatchOX);
   return ret_val;

// O109--	CYCLOPS, PROCESSED EXTERNALLY.

L22000:
   ret_val = cyclop(/*arg*/);
// 						!CYCLOPS
   return ret_val;

// O110--	THIEF, PROCESSED EXTERNALLY

L25000:
   ret_val = thiefp(/*arg*/);
   return ret_val;

// O111--	WINDOW

L26000:
   ret_val = opncls(WindoOX, 208, 209);
// 						!OPEN/CLS WINDOW.
   return ret_val;

// O112--	PILE OF BODIES

L32000:
   if (prsvec.prsa != TakeW) {
      goto L32500;
   }
// 						!TAKE?
   rspeak(228);
// 						!CANT.
   return ret_val;

L32500:
   if (prsvec.prsa != BurnW && prsvec.prsa != MungW) {
      goto L10;
   }
   if (findex.onpolf) {
      return ret_val;
   }
// 						!BURN OR MUNG?
   findex.onpolf = true;
// 						!SET HEAD ON POLE.
   newsta(HPoleOX, 0, Lld2RX, 0, 0);
   jigsup(229);
// 						!BEHEADED.
   return ret_val;

// O113--	VAMPIRE BAT

L35000:
   rspeak(50);
// 						!TIME TO FLY, JACK.
   f = moveto(batdrp[rnd(batdrpN)], play.winner);
// 						!SELECT RANDOM DEST.
   f = rmdesc(0);
   return ret_val;
// OAPPLI, PAGE 7

// O114--	STICK

L39000:
   if (prsvec.prsa != WaveW) {
      goto L10;
   }
// 						!WAVE?
   if (play.here == MRainRX) {
      goto L39500;
   }
// 						!ON RAINBOW?
   if (play.here == PogRX || play.here == FallsRX) {
      goto L39200;
   }
   rspeak(244);
// 						!NOTHING HAPPENS.
   return ret_val;

L39200:
   objcts.oflag1[PotOX - 1] |= VisiO;
   findex.rainbf = !findex.rainbf;
// 						!COMPLEMENT RAINBOW.
   i = 245;
// 						!ASSUME OFF.
   if (findex.rainbf) {
      i = 246;
   }
// 						!IF ON, SOLID.
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

L39500:
   findex.rainbf = false;
// 						!ON RAINBOW,
   jigsup(247);
// 						!TAKE A FALL.
   return ret_val;

// O115--	BALLOON, HANDLED EXTERNALLY

L40000:
   ret_val = ballop(arg);
   return ret_val;

// O116--	HEADS

L45000:
   if (prsvec.prsa != HelloW) {
      goto L45100;
   }
// 						!HELLO HEADS?
   rspeak(633);
// 						!TRULY BIZARRE.
   return ret_val;

L45100:
   if (prsvec.prsa == MeltW) {
      goto L10;
   }
// 						!READ IS OK.
   newsta(LCaseOX, 260, LRoomRX, 0, 0);
// 						!MAKE LARGE CASE.
   i = robadv(play.winner, 0, LCaseOX, 0) + robrm(play.here, 100, 0, LCaseOX, 0);
   jigsup(261);
// 						!KILL HIM.
   return ret_val;
// OAPPLI, PAGE 8

// O117--	SPHERE

L47000:
   if (findex.cagesf || prsvec.prsa != TakeW) {
      goto L10;
   }
// 						!TAKE?
   if (play.winner != PlayerAX) {
      goto L47500;
   }
// 						!ROBOT TAKE?
   rspeak(263);
// 						!NO, DROP CAGE.
   if (objcts.oroom[RobotOX - 1] != play.here) {
      goto L47200;
   }
// 						!ROBOT HERE?
   f = moveto(CageDRX, play.winner);
// 						!YES, MOVE INTO CAGE.
   newsta(RobotOX, 0, CageDRX, 0, 0);
// 						!MOVE ROBOT.
   advs.aroom[RobotAX - 1] = CageDRX;
   objcts.oflag1[RobotOX - 1] |= NDscO;
   cevent.ctick[SphCX - 1] = 10;
// 						!GET OUT IN 10 OR ELSE.
   return ret_val;

L47200:
   newsta(SpherOX, 0, 0, 0, 0);
// 						!YOURE DEAD.
   rooms.rflag[CageRRX - 1] |= MungR;
   rrand[CageRRX - 1] = 147;
   jigsup(148);
// 						!MUNG PLAYER.
   return ret_val;

L47500:
   newsta(SpherOX, 0, 0, 0, 0);
// 						!ROBOT TRIED,
   newsta(RobotOX, 264, 0, 0, 0);
// 						!KILL HIM.
   newsta(CageOX, 0, play.here, 0, 0);
// 						!INSERT MANGLED CAGE.
   return ret_val;

// O118--	GEOMETRICAL BUTTONS

L48000:
   if (prsvec.prsa != PushW) {
      goto L10;
   }
// 						!PUSH?
   i = prsvec.prso - SqButOX + 1;
// 						!GET BUTTON INDEX.
   if (i <= 0 || i >= 4) {
      goto L10;
   }
// 						!A BUTTON?
   if (play.winner != PlayerAX) {
      switch (i) {
         case 1:
            goto L48100;
         case 2:
            goto L48200;
         case 3:
            goto L48300;
      }
   }
   jigsup(265);
// 						!YOU PUSHED, YOU DIE.
   return ret_val;

L48100:
   i = 267;
   if (findex.carozf) {
      i = 266;
   }
// 						!SPEED UP?
   findex.carozf = true;
   rspeak(i);
   return ret_val;

L48200:
   i = 266;
// 						!ASSUME NO CHANGE.
   if (findex.carozf) {
      i = 268;
   }
   findex.carozf = false;
   rspeak(i);
   return ret_val;

L48300:
   findex.caroff = !findex.caroff;
// 						!FLIP CAROUSEL.
   if (!qhere(IrBoxOX, CarouRX)) {
      return ret_val;
   }
// 						!IRON BOX IN CAROUSEL?
   rspeak(269);
// 						!YES, THUMP.
   objcts.oflag1[IrBoxOX - 1] ^= VisiO;
   if (findex.caroff) {
      rooms.rflag[CarouRX - 1] &= ~SeenR;
   }
   return ret_val;

// O119--	FLASK FUNCTION

L49000:
   if (prsvec.prsa == OpenW) {
      goto L49100;
   }
// 						!OPEN?
   if (prsvec.prsa != MungW && prsvec.prsa != ThrowW) {
      goto L10;
   }
   newsta(FlaskOX, 270, 0, 0, 0);
// 						!KILL FLASK.
L49100:
   rooms.rflag[play.here - 1] |= MungR;
   rrand[play.here - 1] = 271;
   jigsup(272);
// 						!POISONED.
   return ret_val;

// O120--	BUCKET FUNCTION

L50000:
   if (arg != 2) {
      goto L10;
   }
// 						!READOUT?
   if (objcts.ocan[WaterOX - 1] != BuckeOX || findex.bucktf) {
      goto L50500;
   }
   findex.bucktf = true;
// 						!BUCKET AT TOP.
   cevent.ctick[BucCX - 1] = 100;
// 						!START COUNTDOWN.
   newsta(BuckeOX, 290, TWellRX, 0, 0);
// 						!REPOSITION BUCKET.
   goto L50900;
// 						!FINISH UP.

L50500:
   if (objcts.ocan[WaterOX - 1] == BuckeOX || !findex.bucktf) {
      goto L10;
   }
   findex.bucktf = false;
   newsta(BuckeOX, 291, BWellRX, 0, 0);
// 						!BUCKET AT BOTTOM.
L50900:
   if (av != BuckeOX) {
      return ret_val;
   }
// 						!IN BUCKET?
   f = moveto(objcts.oroom[BuckeOX - 1], play.winner);
// 						!MOVE ADVENTURER.
   f = rmdesc(0);
// 						!DESCRIBE ROOM.
   return ret_val;
// OAPPLI, PAGE 9

// O121--	EATME CAKE

L51000:
   if (prsvec.prsa != EatW || prsvec.prso != ECakeOX || play.here != AliCeRX) {
      goto L10;
   }
   newsta(ECakeOX, 273, 0, 0, 0);
// 						!VANISH CAKE.
   objcts.oflag1[RobotOX - 1] &= ~VisiO;
   ret_val = moveto(AliSmRX, play.winner);
// 						!MOVE TO ALICE SMALL.
   iz = 64;
   ir = AliSmRX;
   io = AliCeRX;
   goto L52405;

// O122--	ICINGS

L52000:
   if (prsvec.prsa != MeltW) {
      goto L52200;
   }
// 						!READ?
   i = 274;
// 						!CANT READ.
   if (prsvec.prsi != 0) {
      i = 275;
   }
// 						!THROUGH SOMETHING?
   if (prsvec.prsi == BottlOX) {
      i = 276;
   }
// 						!THROUGH BOTTLE?
   if (prsvec.prsi == FlaskOX) {
      i = prsvec.prso - OrIceOX + 277;
   }
// 						!THROUGH FLASK?
   rspeak(i);
// 						!READ FLASK.
   return ret_val;

L52200:
   if (prsvec.prsa != ThrowW || prsvec.prso != RdIceOX || prsvec.prsi != PoolOX) {
      goto L52300;
   }
   newsta(PoolOX, 280, 0, 0, 0);
// 						!VANISH POOL.
   objcts.oflag1[SaffrOX - 1] |= VisiO;
   return ret_val;

L52300:
   if (play.here != AliCeRX && play.here != AliSmRX && play.here != AliTrRX) {
      goto L10;
   }
   if (prsvec.prsa != EatW && prsvec.prsa != ThrowW || prsvec.prso != OrIceOX) {
      goto L52400;
   }
   newsta(OrIceOX, 0, 0, 0, 0);
// 						!VANISH ORANGE ICE.
   rooms.rflag[play.here - 1] |= MungR;
   rrand[play.here - 1] = 281;
   jigsup(282);
// 						!VANISH ADVENTURER.
   return ret_val;

L52400:
   if (prsvec.prsa != EatW || prsvec.prso != BlIceOX) {
      goto L10;
   }
   newsta(BlIceOX, 283, 0, 0, 0);
// 						!VANISH BLUE ICE.
   if (play.here != AliSmRX) {
      goto L52500;
   }
// 						!IN REDUCED ROOM?
   objcts.oflag1[RobotOX - 1] |= VisiO;
   io = play.here;
   ret_val = moveto(AliCeRX, play.winner);
   iz = 0;
   ir = AliCeRX;

//  Do a size change, common loop used also by code at 51000

L52405:
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!ENLARGE WORLD.
      if (objcts.oroom[i - 1] != io || objcts.osize[i - 1] == 10000) {
         goto L52450;
      }
      objcts.oroom[i - 1] = ir;
      objcts.osize[i - 1] *= iz;
   L52450:
      ;
   }
   return ret_val;

L52500:
   jigsup(284);
// 						!ENLARGED IN WRONG ROOM.
   return ret_val;

// O123--	BRICK

L54000:
   if (prsvec.prsa != BurnW) {
      goto L10;
   }
// 						!BURN?
   jigsup(150);
// 						!BOOM
// 						!
   return ret_val;

// O124--	MYSELF

L55000:
   if (prsvec.prsa != GiveW) {
      goto L55100;
   }
// 						!GIVE?
   newsta(prsvec.prso, 2, 0, 0, PlayerAX);
// 						!DONE.
   return ret_val;

L55100:
   if (prsvec.prsa != TakeW) {
      goto L55200;
   }
// 						!TAKE?
   rspeak(286);
// 						!JOKE.
   return ret_val;

L55200:
   if (prsvec.prsa != KillW && prsvec.prsa != MungW) {
      goto L10;
   }
   jigsup(287);
// 						!KILL, NO JOKE.
   return ret_val;
// OAPPLI, PAGE 10

// O125--	PANELS INSIDE MIRROR

L56000:
   if (prsvec.prsa != PushW) {
      goto L10;
   }
// 						!PUSH?
   if (findex.poleuf != 0) {
      goto L56100;
   }
// 						!SHORT POLE UP?
   i = 731;
// 						!NO, WONT BUDGE.
   if (findex.mdir % 180 == 0) {
      i = 732;
   }
// 						!DIFF MSG IF N-S.
   rspeak(i);
// 						!TELL WONT MOVE.
   return ret_val;

L56100:
   if (findex.mloc != MrGrX) {
      goto L56200;
   }
// 						!IN GDN ROOM?
   rspeak(733);
// 						!YOU LOSE.
   jigsup(685);
   return ret_val;

L56200:
   i = 831;
// 						!ROTATE L OR R.
   if (prsvec.prso == RdWalOX || prsvec.prso == YlWalOX) {
      i = 830;
   }
   rspeak(i);
// 						!TELL DIRECTION.
   findex.mdir = (findex.mdir + 45 + (i - 830) * 270) % 360;
// 						!CALCULATE NEW DIR.
   i__1 = findex.mdir / 45 + 695;
   rspsub(734, i__1);
// 						!TELL NEW DIR.
   if (findex.wdopnf) {
      rspeak(730);
   }
// 						!IF PANEL OPEN, CLOSE.
   findex.wdopnf = false;
   return ret_val;
// 						!DONE.

// O126--	ENDS INSIDE MIRROR

L57000:
   if (prsvec.prsa != PushW) {
      goto L10;
   }
// 						!PUSH?
   if (findex.mdir % 180 == 0) {
      goto L57100;
   }
// 						!MIRROR N-S?
   rspeak(735);
// 						!NO, WONT BUDGE.
   return ret_val;

L57100:
   if (prsvec.prso != PinDrOX) {
      goto L57300;
   }
// 						!PUSH PINE WALL?
   if (findex.mloc == MrCrX && findex.mdir == 180 || findex.mloc == MrDrX && findex.mdir == 0 || findex.mloc == MrGrX) {
      goto L57200;
   }
   rspeak(736);
// 						!NO, OPENS.
   findex.wdopnf = true;
// 						!INDICATE OPEN.
   cevent.cflag[PinCX - 1] = true;
// 						!TIME OPENING.
   cevent.ctick[PinCX - 1] = 5;
   return ret_val;

L57200:
   rspeak(737);
// 						!GDN SEES YOU, DIE.
   jigsup(685);
   return ret_val;

L57300:
   nloc = findex.mloc - 1;
// 						!NEW LOC IF SOUTH.
   if (findex.mdir == 0) {
      nloc = findex.mloc + 1;
   }
// 						!NEW LOC IF NORTH.
   if (nloc >= MrArX && nloc <= MrDrX) {
      goto L57400;
   }
   rspeak(738);
// 						!HAVE REACHED END.
   return ret_val;

L57400:
   i = 699;
// 						!ASSUME SOUTH.
   if (findex.mdir == 0) {
      i = 695;
   }
// 						!NORTH.
   j = 739;
// 						!ASSUME SMOOTH.
   if (findex.poleuf != 0) {
      j = 740;
   }
// 						!POLE UP, WOBBLES.
   rspsub(j, i);
// 						!DESCRIBE.
   findex.mloc = nloc;
   if (findex.mloc != MrGrX) {
      return ret_val;
   }
// 						!NOW IN GDN ROOM?

   if (findex.poleuf != 0) {
      goto L57500;
   }
// 						!POLE UP, GDN SEES.
   if (findex.mropnf || findex.wdopnf) {
      goto L57600;
   }
// 						!DOOR OPEN, GDN SEES.
   if (findex.mr1f && findex.mr2f) {
      return ret_val;
   }
// 						!MIRRORS INTACT, OK.
   rspeak(742);
// 						!MIRRORS BROKEN, DIE.
   jigsup(743);
   return ret_val;

L57500:
   rspeak(741);
// 						!POLE UP, DIE.
   jigsup(743);
   return ret_val;

L57600:
   rspeak(744);
// 						!DOOR OPEN, DIE.
   jigsup(743);
   return ret_val;
// OAPPLI, PAGE 11

// O127--	GLOBAL GUARDIANS

L58000:
   if (prsvec.prsa != AttacW && prsvec.prsa != KillW && prsvec.prsa != MungW) {
      goto L58100;
   }
   jigsup(745);
// 						!LOSE.
   return ret_val;

L58100:
   if (prsvec.prsa != HelloW) {
      goto L10;
   }
// 						!HELLO?
   rspeak(746);
// 						!NO REPLY.
   return ret_val;

// O128--	GLOBAL MASTER

L59000:
   if (prsvec.prsa != AttacW && prsvec.prsa != KillW && prsvec.prsa != MungW) {
      goto L59100;
   }
   jigsup(747);
// 						!BAD IDEA.
   return ret_val;

L59100:
   if (prsvec.prsa != TakeW) {
      goto L10;
   }
// 						!TAKE?
   rspeak(748);
// 						!JOKE.
   return ret_val;

// O129--	NUMERAL FIVE (FOR JOKE)

L60000:
   if (prsvec.prsa != TakeW) {
      goto L10;
   }
// 						!TAKE FIVE?
   rspeak(419);
// 						!TIME PASSES.
   for (i = 1; i <= 3; ++i) {
// 						!WAIT A WHILE.
      if (clockd(/*x*/)) {
         return ret_val;
      }
// L60100:
   }
   return ret_val;

// O130--	CRYPT FUNCTION

L61000:
   if (!findex.endgmf) {
      goto L45000;
   }
// 						!IF NOT EG, DIE.
   if (prsvec.prsa != OpenW) {
      goto L61100;
   }
// 						!OPEN?
   i = 793;
   if ((objcts.oflag2[TombOX - 1] & OpenO) != 0) {
      i = 794;
   }
   rspeak(i);
   objcts.oflag2[TombOX - 1] |= OpenO;
   return ret_val;

L61100:
   if (prsvec.prsa != CloseW) {
      goto L45000;
   }
// 						!CLOSE?
   i = 795;
   if ((objcts.oflag2[TombOX - 1] & OpenO) != 0) {
      i = 796;
   }
   rspeak(i);
   objcts.oflag2[TombOX - 1] &= ~OpenO;
   if (play.here == CryptRX) {
      cevent.ctick[SteCX - 1] = 3;
   }
// 						!IF IN CRYPT, START EG.
   return ret_val;
// OAPPLI, PAGE 12

// O131--	GLOBAL LADDER

L62000:
   if (puzzle.cpvec[findex.cphere] == -2 || puzzle.cpvec[findex.cphere - 2] == -3) {
      goto L62100;
   }
   rspeak(865);
// 						!NO, LOSE.
   return ret_val;

L62100:
   if (prsvec.prsa == ClmbW || prsvec.prsa == ClmbUW) {
      goto L62200;
   }
   rspeak(866);
// 						!CLIMB IT?
   return ret_val;

L62200:
   if (findex.cphere == 10 && puzzle.cpvec[findex.cphere] == -2) {
      goto L62300;
   }
   rspeak(867);
// 						!NO, HIT YOUR HEAD.
   return ret_val;

L62300:
   f = moveto(CpAntRX, play.winner);
// 						!TO ANTEROOM.
   f = rmdesc(3);
// 						!DESCRIBE.
   return ret_val;
}
