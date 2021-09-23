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
   if (prsvec_1.prso > 220) {
      goto L5;
   }
   if (prsvec_1.prso != 0) {
      odo2 = objcts_1.odesc2[prsvec_1.prso - 1];
   }
L5:
   if (prsvec_1.prsi != 0) {
      odi2 = objcts_1.odesc2[prsvec_1.prsi - 1];
   }
   av = advs_1.avehic[play_1.winner - 1];
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
   if (play_1.here != rindex_1.mmach) {
      goto L10;
   }
// 						!NOT HERE? F
   ret_val = opncls(oindex_1.machi, 123, 124);
// 						!HANDLE OPN/CLS.
   return ret_val;

// O101--	WATER FUNCTION

L5000:
   if (prsvec_1.prsa != vindex_1.fillw) {
      goto L5050;
   }
// 						!FILL X WITH Y IS
   prsvec_1.prsa = vindex_1.putw;
// 						!MADE INTO
   i = prsvec_1.prsi;
   prsvec_1.prsi = prsvec_1.prso;
   prsvec_1.prso = i;
// 						!PUT Y IN X.
   i = odi2;
   odi2 = odo2;
   odo2 = i;
L5050:
   if (prsvec_1.prso == oindex_1.water || prsvec_1.prso == oindex_1.gwate) {
      goto L5100;
   }
   rspeak(561);
// 						!WATER IS IND OBJ,
   return ret_val;
// 						!PUNT.

L5100:
   if (prsvec_1.prsa != vindex_1.takew) {
      goto L5400;
   }
// 						!TAKE WATER?
   if (objcts_1.oadv[oindex_1.bottl - 1] == play_1.winner && objcts_1.ocan[prsvec_1.prso - 1] != oindex_1.bottl) {
      goto L5500;
   }
   if (objcts_1.ocan[prsvec_1.prso - 1] == 0) {
      goto L5200;
   }
// 						!INSIDE ANYTHING?
   if ((objcts_1.oflag2[objcts_1.ocan[prsvec_1.prso - 1] - 1] & OpenO) != 0) {
      goto L5200;
   }
// 						!YES, OPEN?
   rspsub(525, objcts_1.odesc2[objcts_1.ocan[prsvec_1.prso - 1] - 1]);
// 						!INSIDE, CLOSED, PUNT.
   return ret_val;

L5200:
   rspeak(615);
// 						!NOT INSIDE OR OPEN,
   return ret_val;
// 						!SLIPS THRU FINGERS.

L5400:
   if (prsvec_1.prsa != vindex_1.putw) {
      goto L5700;
   }
// 						!PUT WATER IN X?
   if (av != 0 && prsvec_1.prsi == av) {
      goto L5800;
   }
// 						!IN VEH?
   if (prsvec_1.prsi == oindex_1.bottl) {
      goto L5500;
   }
// 						!IN BOTTLE?
   rspsub(297, odi2);
// 						!WONT GO ELSEWHERE.
   newsta(prsvec_1.prso, 0, 0, 0, 0);
// 						!VANISH WATER.
   return ret_val;

L5500:
   if ((objcts_1.oflag2[oindex_1.bottl - 1] & OpenO) != 0) {
      goto L5550;
   }
// 						!BOTTLE OPEN?
   rspeak(612);
// 						!NO, LOSE.
   return ret_val;

L5550:
   if (qempty(oindex_1.bottl)) {
      goto L5600;
   }
// 						!OPEN, EMPTY?
   rspeak(613);
// 						!NO, ALREADY FULL.
   return ret_val;

L5600:
   newsta(oindex_1.water, 614, 0, oindex_1.bottl, 0);
// 						!TAKE WATER TO BOTTLE.
   return ret_val;

L5700:
   if (prsvec_1.prsa != vindex_1.dropw && prsvec_1.prsa != vindex_1.pourw && prsvec_1.prsa != vindex_1.givew) {
      goto L5900;
   }
   if (av != 0) {
      goto L5800;
   }
// 						!INTO VEHICLE?
   newsta(prsvec_1.prso, 133, 0, 0, 0);
// 						!NO, VANISHES.
   return ret_val;

L5800:
   newsta(oindex_1.water, 0, 0, av, 0);
// 						!WATER INTO VEHICLE.
   rspsub(296, objcts_1.odesc2[av - 1]);
// 						!DESCRIBE.
   return ret_val;

L5900:
   if (prsvec_1.prsa != vindex_1.throww) {
      goto L10;
   }
// 						!LAST CHANCE, THROW?
   newsta(prsvec_1.prso, 132, 0, 0, 0);
// 						!VANISHES.
   return ret_val;
// OAPPLI, PAGE 4

// O102--	LEAF PILE

L10000:
   if (prsvec_1.prsa != vindex_1.burnw) {
      goto L10500;
   }
// 						!BURN?
   if (objcts_1.oroom[prsvec_1.prso - 1] == 0) {
      goto L10100;
   }
// 						!WAS HE CARRYING?
   newsta(prsvec_1.prso, 158, 0, 0, 0);
// 						!NO, BURN IT.
   return ret_val;

L10100:
   newsta(prsvec_1.prso, 0, play_1.here, 0, 0);
// 						!DROP LEAVES.
   jigsup(159);
// 						!BURN HIM.
   return ret_val;

L10500:
   if (prsvec_1.prsa != vindex_1.movew) {
      goto L10600;
   }
// 						!MOVE?
   rspeak(2);
// 						!DONE.
   return ret_val;

L10600:
   if (prsvec_1.prsa != vindex_1.lookuw || findex_1.rvclr != 0) {
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
   if (prsvec_1.prsa != vindex_1.takew) {
      goto L12100;
   }
// 						!TAKE?
   if (objcts_1.oadv[oindex_1.sword - 1] == play_1.winner) {
      rspeak(160);
   }
// 						!PULSE SWORD.
   goto L10;

L12100:
   if ((prsvec_1.prsa != vindex_1.attacw && prsvec_1.prsa != vindex_1.killw || prsvec_1.prsi != oindex_1.rknif) && (prsvec_1.prsa != vindex_1.swingw && prsvec_1.prsa != vindex_1.throww || prsvec_1.prso != oindex_1.rknif)) {
      goto L10;
   }
   newsta(oindex_1.rknif, 0, 0, 0, 0);
// 						!KILL KNIFE.
   jigsup(161);
// 						!KILL HIM.
   return ret_val;
// OAPPLI, PAGE 5

// O105--	GLACIER

L15000:
   if (prsvec_1.prsa != vindex_1.throww) {
      goto L15500;
   }
// 						!THROW?
   if (prsvec_1.prso != oindex_1.torch) {
      goto L15400;
   }
// 						!TORCH?
   newsta(oindex_1.ice, 169, 0, 0, 0);
// 						!MELT ICE.
   objcts_1.odesc1[oindex_1.torch - 1] = 174;
// 						!MUNG TORCH.
   objcts_1.odesc2[oindex_1.torch - 1] = 173;
   objcts_1.oflag1[oindex_1.torch - 1] &= ~flobts;
   newsta(oindex_1.torch, 0, rindex_1.strea, 0, 0);
// 						!MOVE TORCH.
   findex_1.glacrf = true;
// 						!GLACIER GONE.
   if (!lit(play_1.here)) {
      rspeak(170);
   }
// 						!IN DARK?
   return ret_val;

L15400:
   rspeak(171);
// 						!JOKE IF NOT TORCH.
   return ret_val;

L15500:
   if (prsvec_1.prsa != vindex_1.meltw || prsvec_1.prso != oindex_1.ice) {
      goto L10;
   }
   if ((objcts_1.oflag1[prsvec_1.prsi - 1] & flobts) == flobts) {
      goto L15600;
   }
   rspsub(298, odi2);
// 						!CANT MELT WITH THAT.
   return ret_val;

L15600:
   findex_1.glacmf = true;
// 						!PARTIAL MELT.
   if (prsvec_1.prsi != oindex_1.torch) {
      goto L15700;
   }
// 						!MELT WITH TORCH?
   objcts_1.odesc1[oindex_1.torch - 1] = 174;
// 						!MUNG TORCH.
   objcts_1.odesc2[oindex_1.torch - 1] = 173;
   objcts_1.oflag1[oindex_1.torch - 1] &= ~flobts;
L15700:
   jigsup(172);
// 						!DROWN.
   return ret_val;

// O106--	BLACK BOOK

L18000:
   if (prsvec_1.prsa != vindex_1.openw) {
      goto L18100;
   }
// 						!OPEN?
   rspeak(180);
// 						!JOKE.
   return ret_val;

L18100:
   if (prsvec_1.prsa != vindex_1.closew) {
      goto L18200;
   }
// 						!CLOSE?
   rspeak(181);
   return ret_val;

L18200:
   if (prsvec_1.prsa != vindex_1.burnw) {
      goto L10;
   }
// 						!BURN?
   newsta(prsvec_1.prso, 0, 0, 0, 0);
// 						!FATAL JOKE.
   jigsup(182);
   return ret_val;
// OAPPLI, PAGE 6

// O107--	CANDLES, PROCESSED EXTERNALLY

L19000:
   ret_val = lightp(oindex_1.candl);
   return ret_val;

// O108--	MATCHES, PROCESSED EXTERNALLY

L20000:
   ret_val = lightp(oindex_1.match);
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
   ret_val = opncls(oindex_1.windo, 208, 209);
// 						!OPEN/CLS WINDOW.
   return ret_val;

// O112--	PILE OF BODIES

L32000:
   if (prsvec_1.prsa != vindex_1.takew) {
      goto L32500;
   }
// 						!TAKE?
   rspeak(228);
// 						!CANT.
   return ret_val;

L32500:
   if (prsvec_1.prsa != vindex_1.burnw && prsvec_1.prsa != vindex_1.mungw) {
      goto L10;
   }
   if (findex_1.onpolf) {
      return ret_val;
   }
// 						!BURN OR MUNG?
   findex_1.onpolf = true;
// 						!SET HEAD ON POLE.
   newsta(oindex_1.hpole, 0, rindex_1.lld2, 0, 0);
   jigsup(229);
// 						!BEHEADED.
   return ret_val;

// O113--	VAMPIRE BAT

L35000:
   rspeak(50);
// 						!TIME TO FLY, JACK.
   f = moveto(bats_1.batdrp[rnd(9)], play_1.winner);
// 						!SELECT RANDOM DEST.
   f = rmdesc(0);
   return ret_val;
// OAPPLI, PAGE 7

// O114--	STICK

L39000:
   if (prsvec_1.prsa != vindex_1.wavew) {
      goto L10;
   }
// 						!WAVE?
   if (play_1.here == rindex_1.mrain) {
      goto L39500;
   }
// 						!ON RAINBOW?
   if (play_1.here == rindex_1.pog || play_1.here == rindex_1.falls) {
      goto L39200;
   }
   rspeak(244);
// 						!NOTHING HAPPENS.
   return ret_val;

L39200:
   objcts_1.oflag1[oindex_1.pot - 1] |= VisiO;
   findex_1.rainbf = !findex_1.rainbf;
// 						!COMPLEMENT RAINBOW.
   i = 245;
// 						!ASSUME OFF.
   if (findex_1.rainbf) {
      i = 246;
   }
// 						!IF ON, SOLID.
   rspeak(i);
// 						!DESCRIBE.
   return ret_val;

L39500:
   findex_1.rainbf = false;
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
   if (prsvec_1.prsa != vindex_1.hellow) {
      goto L45100;
   }
// 						!HELLO HEADS?
   rspeak(633);
// 						!TRULY BIZARRE.
   return ret_val;

L45100:
   if (prsvec_1.prsa == vindex_1.readw) {
      goto L10;
   }
// 						!READ IS OK.
   newsta(oindex_1.lcase, 260, rindex_1.lroom, 0, 0);
// 						!MAKE LARGE CASE.
   i = robadv(play_1.winner, 0, oindex_1.lcase, 0) + robrm(play_1.here, 100, 0, oindex_1.lcase, 0);
   jigsup(261);
// 						!KILL HIM.
   return ret_val;
// OAPPLI, PAGE 8

// O117--	SPHERE

L47000:
   if (findex_1.cagesf || prsvec_1.prsa != vindex_1.takew) {
      goto L10;
   }
// 						!TAKE?
   if (play_1.winner != aindex_1.player) {
      goto L47500;
   }
// 						!ROBOT TAKE?
   rspeak(263);
// 						!NO, DROP CAGE.
   if (objcts_1.oroom[oindex_1.robot - 1] != play_1.here) {
      goto L47200;
   }
// 						!ROBOT HERE?
   f = moveto(rindex_1.caged, play_1.winner);
// 						!YES, MOVE INTO CAGE.
   newsta(oindex_1.robot, 0, rindex_1.caged, 0, 0);
// 						!MOVE ROBOT.
   advs_1.aroom[aindex_1.arobot - 1] = rindex_1.caged;
   objcts_1.oflag1[oindex_1.robot - 1] |= NDscO;
   cevent_1.ctick[cindex_1.cevsph - 1] = 10;
// 						!GET OUT IN 10 OR ELSE.
   return ret_val;

L47200:
   newsta(oindex_1.spher, 0, 0, 0, 0);
// 						!YOURE DEAD.
   rooms_1.rflag[rindex_1.cager - 1] |= MungR;
   rrand[rindex_1.cager - 1] = 147;
   jigsup(148);
// 						!MUNG PLAYER.
   return ret_val;

L47500:
   newsta(oindex_1.spher, 0, 0, 0, 0);
// 						!ROBOT TRIED,
   newsta(oindex_1.robot, 264, 0, 0, 0);
// 						!KILL HIM.
   newsta(oindex_1.cage, 0, play_1.here, 0, 0);
// 						!INSERT MANGLED CAGE.
   return ret_val;

// O118--	GEOMETRICAL BUTTONS

L48000:
   if (prsvec_1.prsa != vindex_1.pushw) {
      goto L10;
   }
// 						!PUSH?
   i = prsvec_1.prso - oindex_1.sqbut + 1;
// 						!GET BUTTON INDEX.
   if (i <= 0 || i >= 4) {
      goto L10;
   }
// 						!A BUTTON?
   if (play_1.winner != aindex_1.player) {
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
   if (findex_1.carozf) {
      i = 266;
   }
// 						!SPEED UP?
   findex_1.carozf = true;
   rspeak(i);
   return ret_val;

L48200:
   i = 266;
// 						!ASSUME NO CHANGE.
   if (findex_1.carozf) {
      i = 268;
   }
   findex_1.carozf = false;
   rspeak(i);
   return ret_val;

L48300:
   findex_1.caroff = !findex_1.caroff;
// 						!FLIP CAROUSEL.
   if (!qhere(oindex_1.irbox, rindex_1.carou)) {
      return ret_val;
   }
// 						!IRON BOX IN CAROUSEL?
   rspeak(269);
// 						!YES, THUMP.
   objcts_1.oflag1[oindex_1.irbox - 1] ^= VisiO;
   if (findex_1.caroff) {
      rooms_1.rflag[rindex_1.carou - 1] &= ~SeenR;
   }
   return ret_val;

// O119--	FLASK FUNCTION

L49000:
   if (prsvec_1.prsa == vindex_1.openw) {
      goto L49100;
   }
// 						!OPEN?
   if (prsvec_1.prsa != vindex_1.mungw && prsvec_1.prsa != vindex_1.throww) {
      goto L10;
   }
   newsta(oindex_1.flask, 270, 0, 0, 0);
// 						!KILL FLASK.
L49100:
   rooms_1.rflag[play_1.here - 1] |= MungR;
   rrand[play_1.here - 1] = 271;
   jigsup(272);
// 						!POISONED.
   return ret_val;

// O120--	BUCKET FUNCTION

L50000:
   if (arg != 2) {
      goto L10;
   }
// 						!READOUT?
   if (objcts_1.ocan[oindex_1.water - 1] != oindex_1.bucke || findex_1.bucktf) {
      goto L50500;
   }
   findex_1.bucktf = true;
// 						!BUCKET AT TOP.
   cevent_1.ctick[cindex_1.cevbuc - 1] = 100;
// 						!START COUNTDOWN.
   newsta(oindex_1.bucke, 290, rindex_1.twell, 0, 0);
// 						!REPOSITION BUCKET.
   goto L50900;
// 						!FINISH UP.

L50500:
   if (objcts_1.ocan[oindex_1.water - 1] == oindex_1.bucke || !findex_1.bucktf) {
      goto L10;
   }
   findex_1.bucktf = false;
   newsta(oindex_1.bucke, 291, rindex_1.bwell, 0, 0);
// 						!BUCKET AT BOTTOM.
L50900:
   if (av != oindex_1.bucke) {
      return ret_val;
   }
// 						!IN BUCKET?
   f = moveto(objcts_1.oroom[oindex_1.bucke - 1], play_1.winner);
// 						!MOVE ADVENTURER.
   f = rmdesc(0);
// 						!DESCRIBE ROOM.
   return ret_val;
// OAPPLI, PAGE 9

// O121--	EATME CAKE

L51000:
   if (prsvec_1.prsa != vindex_1.eatw || prsvec_1.prso != oindex_1.ecake || play_1.here != rindex_1.alice) {
      goto L10;
   }
   newsta(oindex_1.ecake, 273, 0, 0, 0);
// 						!VANISH CAKE.
   objcts_1.oflag1[oindex_1.robot - 1] &= ~VisiO;
   ret_val = moveto(rindex_1.alism, play_1.winner);
// 						!MOVE TO ALICE SMALL.
   iz = 64;
   ir = rindex_1.alism;
   io = rindex_1.alice;
   goto L52405;

// O122--	ICINGS

L52000:
   if (prsvec_1.prsa != vindex_1.readw) {
      goto L52200;
   }
// 						!READ?
   i = 274;
// 						!CANT READ.
   if (prsvec_1.prsi != 0) {
      i = 275;
   }
// 						!THROUGH SOMETHING?
   if (prsvec_1.prsi == oindex_1.bottl) {
      i = 276;
   }
// 						!THROUGH BOTTLE?
   if (prsvec_1.prsi == oindex_1.flask) {
      i = prsvec_1.prso - oindex_1.orice + 277;
   }
// 						!THROUGH FLASK?
   rspeak(i);
// 						!READ FLASK.
   return ret_val;

L52200:
   if (prsvec_1.prsa != vindex_1.throww || prsvec_1.prso != oindex_1.rdice || prsvec_1.prsi != oindex_1.pool) {
      goto L52300;
   }
   newsta(oindex_1.pool, 280, 0, 0, 0);
// 						!VANISH POOL.
   objcts_1.oflag1[oindex_1.saffr - 1] |= VisiO;
   return ret_val;

L52300:
   if (play_1.here != rindex_1.alice && play_1.here != rindex_1.alism && play_1.here != rindex_1.alitr) {
      goto L10;
   }
   if (prsvec_1.prsa != vindex_1.eatw && prsvec_1.prsa != vindex_1.throww || prsvec_1.prso != oindex_1.orice) {
      goto L52400;
   }
   newsta(oindex_1.orice, 0, 0, 0, 0);
// 						!VANISH ORANGE ICE.
   rooms_1.rflag[play_1.here - 1] |= MungR;
   rrand[play_1.here - 1] = 281;
   jigsup(282);
// 						!VANISH ADVENTURER.
   return ret_val;

L52400:
   if (prsvec_1.prsa != vindex_1.eatw || prsvec_1.prso != oindex_1.blice) {
      goto L10;
   }
   newsta(oindex_1.blice, 283, 0, 0, 0);
// 						!VANISH BLUE ICE.
   if (play_1.here != rindex_1.alism) {
      goto L52500;
   }
// 						!IN REDUCED ROOM?
   objcts_1.oflag1[oindex_1.robot - 1] |= VisiO;
   io = play_1.here;
   ret_val = moveto(rindex_1.alice, play_1.winner);
   iz = 0;
   ir = rindex_1.alice;

//  Do a size change, common loop used also by code at 51000

L52405:
   i__1 = objcts_1.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!ENLARGE WORLD.
      if (objcts_1.oroom[i - 1] != io || objcts_1.osize[i - 1] == 10000) {
         goto L52450;
      }
      objcts_1.oroom[i - 1] = ir;
      objcts_1.osize[i - 1] *= iz;
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
   if (prsvec_1.prsa != vindex_1.burnw) {
      goto L10;
   }
// 						!BURN?
   jigsup(150);
// 						!BOOM
// 						!
   return ret_val;

// O124--	MYSELF

L55000:
   if (prsvec_1.prsa != vindex_1.givew) {
      goto L55100;
   }
// 						!GIVE?
   newsta(prsvec_1.prso, 2, 0, 0, aindex_1.player);
// 						!DONE.
   return ret_val;

L55100:
   if (prsvec_1.prsa != vindex_1.takew) {
      goto L55200;
   }
// 						!TAKE?
   rspeak(286);
// 						!JOKE.
   return ret_val;

L55200:
   if (prsvec_1.prsa != vindex_1.killw && prsvec_1.prsa != vindex_1.mungw) {
      goto L10;
   }
   jigsup(287);
// 						!KILL, NO JOKE.
   return ret_val;
// OAPPLI, PAGE 10

// O125--	PANELS INSIDE MIRROR

L56000:
   if (prsvec_1.prsa != vindex_1.pushw) {
      goto L10;
   }
// 						!PUSH?
   if (findex_1.poleuf != 0) {
      goto L56100;
   }
// 						!SHORT POLE UP?
   i = 731;
// 						!NO, WONT BUDGE.
   if (findex_1.mdir % 180 == 0) {
      i = 732;
   }
// 						!DIFF MSG IF N-S.
   rspeak(i);
// 						!TELL WONT MOVE.
   return ret_val;

L56100:
   if (findex_1.mloc != rindex_1.mrg) {
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
   if (prsvec_1.prso == oindex_1.rdwal || prsvec_1.prso == oindex_1.ylwal) {
      i = 830;
   }
   rspeak(i);
// 						!TELL DIRECTION.
   findex_1.mdir = (findex_1.mdir + 45 + (i - 830) * 270) % 360;
// 						!CALCULATE NEW DIR.
   i__1 = findex_1.mdir / 45 + 695;
   rspsub(734, i__1);
// 						!TELL NEW DIR.
   if (findex_1.wdopnf) {
      rspeak(730);
   }
// 						!IF PANEL OPEN, CLOSE.
   findex_1.wdopnf = false;
   return ret_val;
// 						!DONE.

// O126--	ENDS INSIDE MIRROR

L57000:
   if (prsvec_1.prsa != vindex_1.pushw) {
      goto L10;
   }
// 						!PUSH?
   if (findex_1.mdir % 180 == 0) {
      goto L57100;
   }
// 						!MIRROR N-S?
   rspeak(735);
// 						!NO, WONT BUDGE.
   return ret_val;

L57100:
   if (prsvec_1.prso != oindex_1.pindr) {
      goto L57300;
   }
// 						!PUSH PINE WALL?
   if (findex_1.mloc == rindex_1.mrc && findex_1.mdir == 180 || findex_1.mloc == rindex_1.mrd && findex_1.mdir == 0 || findex_1.mloc == rindex_1.mrg) {
      goto L57200;
   }
   rspeak(736);
// 						!NO, OPENS.
   findex_1.wdopnf = true;
// 						!INDICATE OPEN.
   cevent_1.cflag[cindex_1.cevpin - 1] = true;
// 						!TIME OPENING.
   cevent_1.ctick[cindex_1.cevpin - 1] = 5;
   return ret_val;

L57200:
   rspeak(737);
// 						!GDN SEES YOU, DIE.
   jigsup(685);
   return ret_val;

L57300:
   nloc = findex_1.mloc - 1;
// 						!NEW LOC IF SOUTH.
   if (findex_1.mdir == 0) {
      nloc = findex_1.mloc + 1;
   }
// 						!NEW LOC IF NORTH.
   if (nloc >= rindex_1.mra && nloc <= rindex_1.mrd) {
      goto L57400;
   }
   rspeak(738);
// 						!HAVE REACHED END.
   return ret_val;

L57400:
   i = 699;
// 						!ASSUME SOUTH.
   if (findex_1.mdir == 0) {
      i = 695;
   }
// 						!NORTH.
   j = 739;
// 						!ASSUME SMOOTH.
   if (findex_1.poleuf != 0) {
      j = 740;
   }
// 						!POLE UP, WOBBLES.
   rspsub(j, i);
// 						!DESCRIBE.
   findex_1.mloc = nloc;
   if (findex_1.mloc != rindex_1.mrg) {
      return ret_val;
   }
// 						!NOW IN GDN ROOM?

   if (findex_1.poleuf != 0) {
      goto L57500;
   }
// 						!POLE UP, GDN SEES.
   if (findex_1.mropnf || findex_1.wdopnf) {
      goto L57600;
   }
// 						!DOOR OPEN, GDN SEES.
   if (findex_1.mr1f && findex_1.mr2f) {
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
   if (prsvec_1.prsa != vindex_1.attacw && prsvec_1.prsa != vindex_1.killw && prsvec_1.prsa != vindex_1.mungw) {
      goto L58100;
   }
   jigsup(745);
// 						!LOSE.
   return ret_val;

L58100:
   if (prsvec_1.prsa != vindex_1.hellow) {
      goto L10;
   }
// 						!HELLO?
   rspeak(746);
// 						!NO REPLY.
   return ret_val;

// O128--	GLOBAL MASTER

L59000:
   if (prsvec_1.prsa != vindex_1.attacw && prsvec_1.prsa != vindex_1.killw && prsvec_1.prsa != vindex_1.mungw) {
      goto L59100;
   }
   jigsup(747);
// 						!BAD IDEA.
   return ret_val;

L59100:
   if (prsvec_1.prsa != vindex_1.takew) {
      goto L10;
   }
// 						!TAKE?
   rspeak(748);
// 						!JOKE.
   return ret_val;

// O129--	NUMERAL FIVE (FOR JOKE)

L60000:
   if (prsvec_1.prsa != vindex_1.takew) {
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
   if (!findex_1.endgmf) {
      goto L45000;
   }
// 						!IF NOT EG, DIE.
   if (prsvec_1.prsa != vindex_1.openw) {
      goto L61100;
   }
// 						!OPEN?
   i = 793;
   if ((objcts_1.oflag2[oindex_1.tomb - 1] & OpenO) != 0) {
      i = 794;
   }
   rspeak(i);
   objcts_1.oflag2[oindex_1.tomb - 1] |= OpenO;
   return ret_val;

L61100:
   if (prsvec_1.prsa != vindex_1.closew) {
      goto L45000;
   }
// 						!CLOSE?
   i = 795;
   if ((objcts_1.oflag2[oindex_1.tomb - 1] & OpenO) != 0) {
      i = 796;
   }
   rspeak(i);
   objcts_1.oflag2[oindex_1.tomb - 1] &= ~OpenO;
   if (play_1.here == rindex_1.crypt) {
      cevent_1.ctick[cindex_1.cevste - 1] = 3;
   }
// 						!IF IN CRYPT, START EG.
   return ret_val;
// OAPPLI, PAGE 12

// O131--	GLOBAL LADDER

L62000:
   if (puzzle_1.cpvec[findex_1.cphere] == -2 || puzzle_1.cpvec[findex_1.cphere - 2] == -3) {
      goto L62100;
   }
   rspeak(865);
// 						!NO, LOSE.
   return ret_val;

L62100:
   if (prsvec_1.prsa == vindex_1.clmbw || prsvec_1.prsa == vindex_1.clmbuw) {
      goto L62200;
   }
   rspeak(866);
// 						!CLIMB IT?
   return ret_val;

L62200:
   if (findex_1.cphere == 10 && puzzle_1.cpvec[findex_1.cphere] == -2) {
      goto L62300;
   }
   rspeak(867);
// 						!NO, HIT YOUR HEAD.
   return ret_val;

L62300:
   f = moveto(rindex_1.cpant, play_1.winner);
// 						!TO ANTEROOM.
   f = rmdesc(3);
// 						!DESCRIBE.
   return ret_val;
}
