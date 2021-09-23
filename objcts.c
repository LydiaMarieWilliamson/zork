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
   if (play.here != rindex_.mmach) {
      goto L10;
   }
// 						!NOT HERE? F
   ret_val = opncls(oindex.machi, 123, 124);
// 						!HANDLE OPN/CLS.
   return ret_val;

// O101--	WATER FUNCTION

L5000:
   if (prsvec.prsa != vindex.fillw) {
      goto L5050;
   }
// 						!FILL X WITH Y IS
   prsvec.prsa = vindex.putw;
// 						!MADE INTO
   i = prsvec.prsi;
   prsvec.prsi = prsvec.prso;
   prsvec.prso = i;
// 						!PUT Y IN X.
   i = odi2;
   odi2 = odo2;
   odo2 = i;
L5050:
   if (prsvec.prso == oindex.water || prsvec.prso == oindex.gwate) {
      goto L5100;
   }
   rspeak(561);
// 						!WATER IS IND OBJ,
   return ret_val;
// 						!PUNT.

L5100:
   if (prsvec.prsa != vindex.takew) {
      goto L5400;
   }
// 						!TAKE WATER?
   if (objcts.oadv[oindex.bottl - 1] == play.winner && objcts.ocan[prsvec.prso - 1] != oindex.bottl) {
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
   if (prsvec.prsa != vindex.putw) {
      goto L5700;
   }
// 						!PUT WATER IN X?
   if (av != 0 && prsvec.prsi == av) {
      goto L5800;
   }
// 						!IN VEH?
   if (prsvec.prsi == oindex.bottl) {
      goto L5500;
   }
// 						!IN BOTTLE?
   rspsub(297, odi2);
// 						!WONT GO ELSEWHERE.
   newsta(prsvec.prso, 0, 0, 0, 0);
// 						!VANISH WATER.
   return ret_val;

L5500:
   if ((objcts.oflag2[oindex.bottl - 1] & OpenO) != 0) {
      goto L5550;
   }
// 						!BOTTLE OPEN?
   rspeak(612);
// 						!NO, LOSE.
   return ret_val;

L5550:
   if (qempty(oindex.bottl)) {
      goto L5600;
   }
// 						!OPEN, EMPTY?
   rspeak(613);
// 						!NO, ALREADY FULL.
   return ret_val;

L5600:
   newsta(oindex.water, 614, 0, oindex.bottl, 0);
// 						!TAKE WATER TO BOTTLE.
   return ret_val;

L5700:
   if (prsvec.prsa != vindex.dropw && prsvec.prsa != vindex.pourw && prsvec.prsa != vindex.givew) {
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
   newsta(oindex.water, 0, 0, av, 0);
// 						!WATER INTO VEHICLE.
   rspsub(296, objcts.odesc2[av - 1]);
// 						!DESCRIBE.
   return ret_val;

L5900:
   if (prsvec.prsa != vindex.throww) {
      goto L10;
   }
// 						!LAST CHANCE, THROW?
   newsta(prsvec.prso, 132, 0, 0, 0);
// 						!VANISHES.
   return ret_val;
// OAPPLI, PAGE 4

// O102--	LEAF PILE

L10000:
   if (prsvec.prsa != vindex.burnw) {
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
   if (prsvec.prsa != vindex.movew) {
      goto L10600;
   }
// 						!MOVE?
   rspeak(2);
// 						!DONE.
   return ret_val;

L10600:
   if (prsvec.prsa != vindex.lookuw || findex.rvclr != 0) {
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
   if (prsvec.prsa != vindex.takew) {
      goto L12100;
   }
// 						!TAKE?
   if (objcts.oadv[oindex.sword - 1] == play.winner) {
      rspeak(160);
   }
// 						!PULSE SWORD.
   goto L10;

L12100:
   if ((prsvec.prsa != vindex.attacw && prsvec.prsa != vindex.killw || prsvec.prsi != oindex.rknif) && (prsvec.prsa != vindex.swingw && prsvec.prsa != vindex.throww || prsvec.prso != oindex.rknif)) {
      goto L10;
   }
   newsta(oindex.rknif, 0, 0, 0, 0);
// 						!KILL KNIFE.
   jigsup(161);
// 						!KILL HIM.
   return ret_val;
// OAPPLI, PAGE 5

// O105--	GLACIER

L15000:
   if (prsvec.prsa != vindex.throww) {
      goto L15500;
   }
// 						!THROW?
   if (prsvec.prso != oindex.torch) {
      goto L15400;
   }
// 						!TORCH?
   newsta(oindex.ice, 169, 0, 0, 0);
// 						!MELT ICE.
   objcts.odesc1[oindex.torch - 1] = 174;
// 						!MUNG TORCH.
   objcts.odesc2[oindex.torch - 1] = 173;
   objcts.oflag1[oindex.torch - 1] &= ~flobts;
   newsta(oindex.torch, 0, rindex_.strea, 0, 0);
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
   if (prsvec.prsa != vindex.meltw || prsvec.prso != oindex.ice) {
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
   if (prsvec.prsi != oindex.torch) {
      goto L15700;
   }
// 						!MELT WITH TORCH?
   objcts.odesc1[oindex.torch - 1] = 174;
// 						!MUNG TORCH.
   objcts.odesc2[oindex.torch - 1] = 173;
   objcts.oflag1[oindex.torch - 1] &= ~flobts;
L15700:
   jigsup(172);
// 						!DROWN.
   return ret_val;

// O106--	BLACK BOOK

L18000:
   if (prsvec.prsa != vindex.openw) {
      goto L18100;
   }
// 						!OPEN?
   rspeak(180);
// 						!JOKE.
   return ret_val;

L18100:
   if (prsvec.prsa != vindex.closew) {
      goto L18200;
   }
// 						!CLOSE?
   rspeak(181);
   return ret_val;

L18200:
   if (prsvec.prsa != vindex.burnw) {
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
   ret_val = lightp(oindex.candl);
   return ret_val;

// O108--	MATCHES, PROCESSED EXTERNALLY

L20000:
   ret_val = lightp(oindex.match);
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
   ret_val = opncls(oindex.windo, 208, 209);
// 						!OPEN/CLS WINDOW.
   return ret_val;

// O112--	PILE OF BODIES

L32000:
   if (prsvec.prsa != vindex.takew) {
      goto L32500;
   }
// 						!TAKE?
   rspeak(228);
// 						!CANT.
   return ret_val;

L32500:
   if (prsvec.prsa != vindex.burnw && prsvec.prsa != vindex.mungw) {
      goto L10;
   }
   if (findex.onpolf) {
      return ret_val;
   }
// 						!BURN OR MUNG?
   findex.onpolf = true;
// 						!SET HEAD ON POLE.
   newsta(oindex.hpole, 0, rindex_.lld2, 0, 0);
   jigsup(229);
// 						!BEHEADED.
   return ret_val;

// O113--	VAMPIRE BAT

L35000:
   rspeak(50);
// 						!TIME TO FLY, JACK.
   f = moveto(bats.batdrp[rnd(9)], play.winner);
// 						!SELECT RANDOM DEST.
   f = rmdesc(0);
   return ret_val;
// OAPPLI, PAGE 7

// O114--	STICK

L39000:
   if (prsvec.prsa != vindex.wavew) {
      goto L10;
   }
// 						!WAVE?
   if (play.here == rindex_.mrain) {
      goto L39500;
   }
// 						!ON RAINBOW?
   if (play.here == rindex_.pog || play.here == rindex_.falls) {
      goto L39200;
   }
   rspeak(244);
// 						!NOTHING HAPPENS.
   return ret_val;

L39200:
   objcts.oflag1[oindex.pot - 1] |= VisiO;
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
   if (prsvec.prsa != vindex.hellow) {
      goto L45100;
   }
// 						!HELLO HEADS?
   rspeak(633);
// 						!TRULY BIZARRE.
   return ret_val;

L45100:
   if (prsvec.prsa == vindex.readw) {
      goto L10;
   }
// 						!READ IS OK.
   newsta(oindex.lcase, 260, rindex_.lroom, 0, 0);
// 						!MAKE LARGE CASE.
   i = robadv(play.winner, 0, oindex.lcase, 0) + robrm(play.here, 100, 0, oindex.lcase, 0);
   jigsup(261);
// 						!KILL HIM.
   return ret_val;
// OAPPLI, PAGE 8

// O117--	SPHERE

L47000:
   if (findex.cagesf || prsvec.prsa != vindex.takew) {
      goto L10;
   }
// 						!TAKE?
   if (play.winner != aindex.player) {
      goto L47500;
   }
// 						!ROBOT TAKE?
   rspeak(263);
// 						!NO, DROP CAGE.
   if (objcts.oroom[oindex.robot - 1] != play.here) {
      goto L47200;
   }
// 						!ROBOT HERE?
   f = moveto(rindex_.caged, play.winner);
// 						!YES, MOVE INTO CAGE.
   newsta(oindex.robot, 0, rindex_.caged, 0, 0);
// 						!MOVE ROBOT.
   advs.aroom[aindex.arobot - 1] = rindex_.caged;
   objcts.oflag1[oindex.robot - 1] |= NDscO;
   cevent.ctick[cindex.cevsph - 1] = 10;
// 						!GET OUT IN 10 OR ELSE.
   return ret_val;

L47200:
   newsta(oindex.spher, 0, 0, 0, 0);
// 						!YOURE DEAD.
   rooms.rflag[rindex_.cager - 1] |= MungR;
   rrand[rindex_.cager - 1] = 147;
   jigsup(148);
// 						!MUNG PLAYER.
   return ret_val;

L47500:
   newsta(oindex.spher, 0, 0, 0, 0);
// 						!ROBOT TRIED,
   newsta(oindex.robot, 264, 0, 0, 0);
// 						!KILL HIM.
   newsta(oindex.cage, 0, play.here, 0, 0);
// 						!INSERT MANGLED CAGE.
   return ret_val;

// O118--	GEOMETRICAL BUTTONS

L48000:
   if (prsvec.prsa != vindex.pushw) {
      goto L10;
   }
// 						!PUSH?
   i = prsvec.prso - oindex.sqbut + 1;
// 						!GET BUTTON INDEX.
   if (i <= 0 || i >= 4) {
      goto L10;
   }
// 						!A BUTTON?
   if (play.winner != aindex.player) {
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
   if (!qhere(oindex.irbox, rindex_.carou)) {
      return ret_val;
   }
// 						!IRON BOX IN CAROUSEL?
   rspeak(269);
// 						!YES, THUMP.
   objcts.oflag1[oindex.irbox - 1] ^= VisiO;
   if (findex.caroff) {
      rooms.rflag[rindex_.carou - 1] &= ~SeenR;
   }
   return ret_val;

// O119--	FLASK FUNCTION

L49000:
   if (prsvec.prsa == vindex.openw) {
      goto L49100;
   }
// 						!OPEN?
   if (prsvec.prsa != vindex.mungw && prsvec.prsa != vindex.throww) {
      goto L10;
   }
   newsta(oindex.flask, 270, 0, 0, 0);
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
   if (objcts.ocan[oindex.water - 1] != oindex.bucke || findex.bucktf) {
      goto L50500;
   }
   findex.bucktf = true;
// 						!BUCKET AT TOP.
   cevent.ctick[cindex.cevbuc - 1] = 100;
// 						!START COUNTDOWN.
   newsta(oindex.bucke, 290, rindex_.twell, 0, 0);
// 						!REPOSITION BUCKET.
   goto L50900;
// 						!FINISH UP.

L50500:
   if (objcts.ocan[oindex.water - 1] == oindex.bucke || !findex.bucktf) {
      goto L10;
   }
   findex.bucktf = false;
   newsta(oindex.bucke, 291, rindex_.bwell, 0, 0);
// 						!BUCKET AT BOTTOM.
L50900:
   if (av != oindex.bucke) {
      return ret_val;
   }
// 						!IN BUCKET?
   f = moveto(objcts.oroom[oindex.bucke - 1], play.winner);
// 						!MOVE ADVENTURER.
   f = rmdesc(0);
// 						!DESCRIBE ROOM.
   return ret_val;
// OAPPLI, PAGE 9

// O121--	EATME CAKE

L51000:
   if (prsvec.prsa != vindex.eatw || prsvec.prso != oindex.ecake || play.here != rindex_.alice) {
      goto L10;
   }
   newsta(oindex.ecake, 273, 0, 0, 0);
// 						!VANISH CAKE.
   objcts.oflag1[oindex.robot - 1] &= ~VisiO;
   ret_val = moveto(rindex_.alism, play.winner);
// 						!MOVE TO ALICE SMALL.
   iz = 64;
   ir = rindex_.alism;
   io = rindex_.alice;
   goto L52405;

// O122--	ICINGS

L52000:
   if (prsvec.prsa != vindex.readw) {
      goto L52200;
   }
// 						!READ?
   i = 274;
// 						!CANT READ.
   if (prsvec.prsi != 0) {
      i = 275;
   }
// 						!THROUGH SOMETHING?
   if (prsvec.prsi == oindex.bottl) {
      i = 276;
   }
// 						!THROUGH BOTTLE?
   if (prsvec.prsi == oindex.flask) {
      i = prsvec.prso - oindex.orice + 277;
   }
// 						!THROUGH FLASK?
   rspeak(i);
// 						!READ FLASK.
   return ret_val;

L52200:
   if (prsvec.prsa != vindex.throww || prsvec.prso != oindex.rdice || prsvec.prsi != oindex.pool) {
      goto L52300;
   }
   newsta(oindex.pool, 280, 0, 0, 0);
// 						!VANISH POOL.
   objcts.oflag1[oindex.saffr - 1] |= VisiO;
   return ret_val;

L52300:
   if (play.here != rindex_.alice && play.here != rindex_.alism && play.here != rindex_.alitr) {
      goto L10;
   }
   if (prsvec.prsa != vindex.eatw && prsvec.prsa != vindex.throww || prsvec.prso != oindex.orice) {
      goto L52400;
   }
   newsta(oindex.orice, 0, 0, 0, 0);
// 						!VANISH ORANGE ICE.
   rooms.rflag[play.here - 1] |= MungR;
   rrand[play.here - 1] = 281;
   jigsup(282);
// 						!VANISH ADVENTURER.
   return ret_val;

L52400:
   if (prsvec.prsa != vindex.eatw || prsvec.prso != oindex.blice) {
      goto L10;
   }
   newsta(oindex.blice, 283, 0, 0, 0);
// 						!VANISH BLUE ICE.
   if (play.here != rindex_.alism) {
      goto L52500;
   }
// 						!IN REDUCED ROOM?
   objcts.oflag1[oindex.robot - 1] |= VisiO;
   io = play.here;
   ret_val = moveto(rindex_.alice, play.winner);
   iz = 0;
   ir = rindex_.alice;

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
   if (prsvec.prsa != vindex.burnw) {
      goto L10;
   }
// 						!BURN?
   jigsup(150);
// 						!BOOM
// 						!
   return ret_val;

// O124--	MYSELF

L55000:
   if (prsvec.prsa != vindex.givew) {
      goto L55100;
   }
// 						!GIVE?
   newsta(prsvec.prso, 2, 0, 0, aindex.player);
// 						!DONE.
   return ret_val;

L55100:
   if (prsvec.prsa != vindex.takew) {
      goto L55200;
   }
// 						!TAKE?
   rspeak(286);
// 						!JOKE.
   return ret_val;

L55200:
   if (prsvec.prsa != vindex.killw && prsvec.prsa != vindex.mungw) {
      goto L10;
   }
   jigsup(287);
// 						!KILL, NO JOKE.
   return ret_val;
// OAPPLI, PAGE 10

// O125--	PANELS INSIDE MIRROR

L56000:
   if (prsvec.prsa != vindex.pushw) {
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
   if (findex.mloc != rindex_.mrg) {
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
   if (prsvec.prso == oindex.rdwal || prsvec.prso == oindex.ylwal) {
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
   if (prsvec.prsa != vindex.pushw) {
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
   if (prsvec.prso != oindex.pindr) {
      goto L57300;
   }
// 						!PUSH PINE WALL?
   if (findex.mloc == rindex_.mrc && findex.mdir == 180 || findex.mloc == rindex_.mrd && findex.mdir == 0 || findex.mloc == rindex_.mrg) {
      goto L57200;
   }
   rspeak(736);
// 						!NO, OPENS.
   findex.wdopnf = true;
// 						!INDICATE OPEN.
   cevent.cflag[cindex.cevpin - 1] = true;
// 						!TIME OPENING.
   cevent.ctick[cindex.cevpin - 1] = 5;
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
   if (nloc >= rindex_.mra && nloc <= rindex_.mrd) {
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
   if (findex.mloc != rindex_.mrg) {
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
   if (prsvec.prsa != vindex.attacw && prsvec.prsa != vindex.killw && prsvec.prsa != vindex.mungw) {
      goto L58100;
   }
   jigsup(745);
// 						!LOSE.
   return ret_val;

L58100:
   if (prsvec.prsa != vindex.hellow) {
      goto L10;
   }
// 						!HELLO?
   rspeak(746);
// 						!NO REPLY.
   return ret_val;

// O128--	GLOBAL MASTER

L59000:
   if (prsvec.prsa != vindex.attacw && prsvec.prsa != vindex.killw && prsvec.prsa != vindex.mungw) {
      goto L59100;
   }
   jigsup(747);
// 						!BAD IDEA.
   return ret_val;

L59100:
   if (prsvec.prsa != vindex.takew) {
      goto L10;
   }
// 						!TAKE?
   rspeak(748);
// 						!JOKE.
   return ret_val;

// O129--	NUMERAL FIVE (FOR JOKE)

L60000:
   if (prsvec.prsa != vindex.takew) {
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
   if (prsvec.prsa != vindex.openw) {
      goto L61100;
   }
// 						!OPEN?
   i = 793;
   if ((objcts.oflag2[oindex.tomb - 1] & OpenO) != 0) {
      i = 794;
   }
   rspeak(i);
   objcts.oflag2[oindex.tomb - 1] |= OpenO;
   return ret_val;

L61100:
   if (prsvec.prsa != vindex.closew) {
      goto L45000;
   }
// 						!CLOSE?
   i = 795;
   if ((objcts.oflag2[oindex.tomb - 1] & OpenO) != 0) {
      i = 796;
   }
   rspeak(i);
   objcts.oflag2[oindex.tomb - 1] &= ~OpenO;
   if (play.here == rindex_.crypt) {
      cevent.ctick[cindex.cevste - 1] = 3;
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
   if (prsvec.prsa == vindex.clmbw || prsvec.prsa == vindex.clmbuw) {
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
   f = moveto(rindex_.cpant, play.winner);
// 						!TO ANTEROOM.
   f = rmdesc(3);
// 						!DESCRIBE.
   return ret_val;
}
