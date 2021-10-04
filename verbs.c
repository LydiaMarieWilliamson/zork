// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Main verb processing routine
bool vappli(int ri) {
// Initialized data
   const int mxnop = 39;
   const int mxsmp = 99;

// System generated locals
   int i__1;
   bool ret_val;

// Local variables
   int melee;
   bool f;
   int i, j,/* x,*/ av;
   int rmk;
   int odi2 = 0, odo2 = 0;

// VAPPLI, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.

   if (prsvec.prso > 220) {
      goto L5;
   }

   if (prsvec.prso != 0) {
      odo2 = objcts.odesc2[prsvec.prso - 1];
   }
// 						!SET UP DESCRIPTORS.
L5:
   if (prsvec.prsi != 0) {
      odi2 = objcts.odesc2[prsvec.prsi - 1];
   }
   av = advs.avehic[play.winner - 1];
   rmk = rnd(6) + 372;
// 						!REMARK FOR HACK-HACKS.

   if (ri == 0) {
      goto L10;
   }
// 						!ZERO IS FALSE.
   if (ri <= mxnop) {
      return ret_val;
   }
// 						!NOP?
   if (ri <= mxsmp) {
      goto L100;
   }
// 						!SIMPLE VERB?
   switch (ri - mxsmp) {
      case 1:
         goto L18000;
      case 2:
         goto L20000;
      case 3:
         goto L22000;
      case 4:
         goto L23000;
      case 5:
         goto L24000;
      case 6:
         goto L25000;
      case 7:
         goto L26000;
      case 8:
         goto L27000;
      case 9:
         goto L28000;
      case 10:
         goto L29000;
      case 11:
         goto L30000;
      case 12:
         goto L31000;
      case 13:
         goto L32000;
      case 14:
         goto L33000;
      case 15:
         goto L34000;
      case 16:
         goto L35000;
      case 17:
         goto L36000;
      case 18:
         goto L38000;
      case 19:
         goto L39000;
      case 20:
         goto L40000;
      case 21:
         goto L41000;
      case 22:
         goto L42000;
      case 23:
         goto L43000;
      case 24:
         goto L44000;
      case 25:
         goto L45000;
      case 26:
         goto L46000;
      case 27:
         goto L47000;
      case 28:
         goto L48000;
      case 29:
         goto L49000;
      case 30:
         goto L50000;
      case 31:
         goto L51000;
      case 32:
         goto L52000;
      case 33:
         goto L53000;
      case 34:
         goto L55000;
      case 35:
         goto L56000;
      case 36:
         goto L58000;
      case 37:
         goto L59000;
      case 38:
         goto L60000;
      case 39:
         goto L63000;
      case 40:
         goto L64000;
      case 41:
         goto L65000;
      case 42:
         goto L66000;
      case 43:
         goto L68000;
      case 44:
         goto L69000;
      case 45:
         goto L70000;
      case 46:
         goto L71000;
      case 47:
         goto L72000;
      case 48:
         goto L73000;
      case 49:
         goto L74000;
      case 50:
         goto L77000;
      case 51:
         goto L78000;
      case 52:
         goto L80000;
      case 53:
         goto L81000;
      case 54:
         goto L82000;
      case 55:
         goto L83000;
      case 56:
         goto L84000;
      case 57:
         goto L85000;
      case 58:
         goto L86000;
      case 59:
         goto L87000;
      case 60:
         goto L88000;
   }
   bug(7, ri);

// ALL VERB PROCESSORS RETURN HERE TO DECLARE FAILURE.

L10:
   ret_val = false;
// 						!LOSE.
   return ret_val;

// SIMPLE VERBS ARE HANDLED EXTERNALLY.

L100:
   ret_val = sverbs(ri);
   return ret_val;
// VAPPLI, PAGE 3

// V100--	READ.  OUR FIRST REAL VERB.

L18000:
   if (lit(play.here)) {
      goto L18100;
   }
// 						!ROOM LIT?
   rspeak(356);
// 						!NO, CANT READ.
   return ret_val;

L18100:
   if (prsvec.prsi == 0) {
      goto L18200;
   }
// 						!READ THROUGH OBJ?
   if ((objcts.oflag1[prsvec.prsi - 1] & TranO) != 0) {
      goto L18200;
   }
   rspsub(357, odi2);
// 						!NOT TRANSPARENT.
   return ret_val;

L18200:
   if ((objcts.oflag1[prsvec.prso - 1] & ReadO) != 0) {
      goto L18300;
   }
   rspsub(358, odo2);
// 						!NOT READABLE.
   return ret_val;

L18300:
   if (!objact(/*x*/)) {
      rspeak(objcts.oread[prsvec.prso - 1]);
   }
   return ret_val;

// V101--	MELT.  UNLESS OBJECT HANDLES, JOKE.

L20000:
   if (!objact(/*x*/)) {
      rspsub(361, odo2);
   }
   return ret_val;

// V102--	INFLATE.  WORKS ONLY WITH BOATS.

L22000:
   if (!objact(/*x*/)) {
      rspeak(368);
   }
// 						!OBJ HANDLE?
   return ret_val;

// V103--	DEFLATE.

L23000:
   if (!objact(/*x*/)) {
      rspeak(369);
   }
// 						!OBJ HANDLE?
   return ret_val;
// VAPPLI, PAGE 4

// V104--	ALARM.  IF SLEEPING, WAKE HIM UP.

L24000:
   if ((objcts.oflag2[prsvec.prso - 1] & SlepO) == 0) {
      goto L24100;
   }
   ret_val = objact(/*x*/);
// 						!SLEEPING, LET OBJ DO.
   return ret_val;

L24100:
   rspsub(370, odo2);
// 						!JOKE.
   return ret_val;

// V105--	EXORCISE.  OBJECTS HANDLE.

L25000:
   f = objact(/*x*/);
// 						!OBJECTS HANDLE.
   return ret_val;

// V106--	PLUG.  LET OBJECTS HANDLE.

L26000:
   if (!objact(/*x*/)) {
      rspeak(371);
   }
   return ret_val;

// V107--	KICK.  IF OBJECT IGNORES, JOKE.

L27000:
   if (!objact(/*x*/)) {
      rspsb2(378, odo2, rmk);
   }
   return ret_val;

// V108--	WAVE.  SAME.

L28000:
   if (!objact(/*x*/)) {
      rspsb2(379, odo2, rmk);
   }
   return ret_val;

// V109,V110--	RAISE, LOWER.  SAME.

L29000:
L30000:
   if (!objact(/*x*/)) {
      rspsb2(380, odo2, rmk);
   }
   return ret_val;

// V111--	RUB.  SAME.

L31000:
   if (!objact(/*x*/)) {
      rspsb2(381, odo2, rmk);
   }
   return ret_val;

// V112--	PUSH.  SAME.

L32000:
   if (!objact(/*x*/)) {
      rspsb2(382, odo2, rmk);
   }
   return ret_val;
// VAPPLI, PAGE 5

// V113--	UNTIE.  IF OBJECT IGNORES, JOKE.

L33000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJECT HANDLE?
   i = 383;
// 						!NO, NOT TIED.
   if ((objcts.oflag2[prsvec.prso - 1] & TieO) == 0) {
      i = 384;
   }
   rspeak(i);
   return ret_val;

// V114--	TIE.  NEVER REALLY WORKS.

L34000:
   if ((objcts.oflag2[prsvec.prso - 1] & TieO) != 0) {
      goto L34100;
   }
   rspeak(385);
// 						!NOT TIEABLE.
   return ret_val;

L34100:
   if (!objact(/*x*/)) {
      rspsub(386, odo2);
   }
// 						!JOKE.
   return ret_val;

// V115--	TIE UP.  NEVER REALLY WORKS.

L35000:
   if ((objcts.oflag2[prsvec.prsi - 1] & TieO) != 0) {
      goto L35100;
   }
   rspsub(387, odo2);
// 						!NOT TIEABLE.
   return ret_val;

L35100:
   i = 388;
// 						!ASSUME VILLAIN.
   if ((objcts.oflag2[prsvec.prso - 1] & VillO) == 0) {
      i = 389;
   }
   rspsub(i, odo2);
// 						!JOKE.
   return ret_val;

// V116--	TURN.  OBJECT MUST HANDLE.

L36000:
   if ((objcts.oflag1[prsvec.prso - 1] & TurnO) != 0) {
      goto L36100;
   }
   rspeak(390);
// 						!NOT TURNABLE.
   return ret_val;

L36100:
   if ((objcts.oflag1[prsvec.prsi - 1] & ToolO) != 0) {
      goto L36200;
   }
   rspsub(391, odi2);
// 						!NOT A TOOL.
   return ret_val;

L36200:
   ret_val = objact(/*x*/);
// 						!LET OBJECT HANDLE.
   return ret_val;

// V117--	BREATHE.  BECOMES INFLATE WITH LUNGS.

L38000:
   prsvec.prsa = InflaW;
   prsvec.prsi = LungsOX;
   goto L22000;
// 						!HANDLE LIKE INFLATE.

// V118--	KNOCK.  MOSTLY JOKE.

L39000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   i = 394;
// 						!JOKE FOR DOOR.
   if ((objcts.oflag1[prsvec.prso - 1] & DoorO) == 0) {
      i = 395;
   }
   rspsub(i, odo2);
// 						!JOKE FOR NONDOORS TOO.
   return ret_val;

// V119--	LOOK.

L40000:
   if (prsvec.prso != 0) {
      goto L41500;
   }
// 						!SOMETHING TO LOOK AT?
   ret_val = rmdesc(3);
// 						!HANDLED BY RMDESC.
   return ret_val;

// V120--	EXAMINE.

L41000:
   if (prsvec.prso != 0) {
      goto L41500;
   }
// 						!SOMETHING TO EXAMINE?
   ret_val = rmdesc(0);
// 						!HANDLED BY RMDESC.
   return ret_val;

L41500:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   i = objcts.oread[prsvec.prso - 1];
// 						!GET READING MATERIAL.
   if (i != 0) {
      rspeak(i);
   }
// 						!OUTPUT IF THERE,
   if (i == 0) {
      rspsub(429, odo2);
   }
// 						!OTHERWISE DEFAULT.
   prsvec.prsa = FooW;
// 						!DEFUSE ROOM PROCESSORS.
   return ret_val;

// V121--	SHAKE.  IF HOLLOW OBJECT, SOME ACTION.

L42000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJECT HANDLE?
   if ((objcts.oflag2[prsvec.prso - 1] & VillO) == 0) {
      goto L42100;
   }
   rspeak(371);
// 						!JOKE FOR VILLAINS.
   return ret_val;

L42100:
   if (qempty(prsvec.prso) || (objcts.oflag1[prsvec.prso - 1] & TakeO) == 0) {
      goto L10;
   }
   if ((objcts.oflag2[prsvec.prso - 1] & OpenO) != 0) {
      goto L42300;
   }
// 						!OPEN?  SPILL.
   rspsub(396, odo2);
// 						!NO, DESCRIBE NOISE.
   return ret_val;

L42300:
   rspsub(397, odo2);
// 						!SPILL THE WORKS.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!SPILL CONTENTS.
      if (objcts.ocan[i - 1] != prsvec.prso) {
         goto L42500;
      }
// 						!INSIDE?
      objcts.oflag2[i - 1] |= TChO;
      if (av == 0) {
         goto L42400;
      }
// 						!IN VEHICLE?
      newsta(i, 0, 0, av, 0);
// 						!YES, SPILL IN THERE.
      goto L42500;

   L42400:
      newsta(i, 0, play.here, 0, 0);
// 						!NO, SPILL ON FLOOR,
      if (i == WaterOX) {
         newsta(i, 133, 0, 0, 0);
      }
// 						!BUT WATER DISAPPEARS.
   L42500:
      ;
   }
   return ret_val;

// V122--	MOVE.  MOSTLY JOKES.

L43000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   i = 398;
// 						!ASSUME NOT HERE.
   if (qhere(prsvec.prso, play.here)) {
      i = 399;
   }
   rspsub(i, odo2);
// 						!JOKE.
   return ret_val;
// VAPPLI, PAGE 6

// V123--	TURN ON.

L44000:
   f = lit(play.here);
// 						!RECORD IF LIT.
   if (objact(/*x*/)) {
      goto L44300;
   }
// 						!OBJ HANDLE?
   if ((objcts.oflag1[prsvec.prso - 1] & LiteO) != 0 && objcts.oadv[prsvec.prso - 1] == play.winner) {
      goto L44100;
   }
   rspeak(400);
// 						!CANT DO IT.
   return ret_val;

L44100:
   if ((objcts.oflag1[prsvec.prso - 1] & OnO) == 0) {
      goto L44200;
   }
   rspeak(401);
// 						!ALREADY ON.
   return ret_val;

L44200:
   objcts.oflag1[prsvec.prso - 1] |= OnO;
   rspsub(404, odo2);
L44300:
   if (!f && lit(play.here)) {
      f = rmdesc(0);
   }
// 						!ROOM NEWLY LIT.
   return ret_val;

// V124--	TURN OFF.

L45000:
   if (objact(/*x*/)) {
      goto L45300;
   }
// 						!OBJ HANDLE?
   if ((objcts.oflag1[prsvec.prso - 1] & LiteO) != 0 && objcts.oadv[prsvec.prso - 1] == play.winner) {
      goto L45100;
   }
   rspeak(402);
// 						!CANT DO IT.
   return ret_val;

L45100:
   if ((objcts.oflag1[prsvec.prso - 1] & OnO) != 0) {
      goto L45200;
   }
   rspeak(403);
// 						!ALREADY OFF.
   return ret_val;

L45200:
   objcts.oflag1[prsvec.prso - 1] &= ~OnO;
   rspsub(405, odo2);
L45300:
   if (!lit(play.here)) {
      rspeak(406);
   }
// 						!MAY BE DARK.
   return ret_val;

// V125--	OPEN.  A FINE MESS.

L46000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if ((objcts.oflag1[prsvec.prso - 1] & ContO) != 0) {
      goto L46100;
   }
L46050:
   rspsub(407, odo2);
// 						!NOT OPENABLE.
   return ret_val;

L46100:
   if (objcts.ocapac[prsvec.prso - 1] != 0) {
      goto L46200;
   }
   rspsub(408, odo2);
// 						!NOT OPENABLE.
   return ret_val;

L46200:
   if (!((objcts.oflag2[prsvec.prso - 1] & OpenO) != 0)) {
      goto L46225;
   }
   rspeak(412);
// 						!ALREADY OPEN.
   return ret_val;

L46225:
   objcts.oflag2[prsvec.prso - 1] |= OpenO;
   if ((objcts.oflag1[prsvec.prso - 1] & TranO) != 0 || qempty(prsvec.prso)) {
      goto L46300;
   }
   princo(prsvec.prso, 410);
// 						!PRINT CONTENTS.
   return ret_val;

L46300:
   rspeak(409);
// 						!DONE
   return ret_val;

// V126--	CLOSE.

L47000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if ((objcts.oflag1[prsvec.prso - 1] & ContO) == 0) {
      goto L46050;
   }
   if (objcts.ocapac[prsvec.prso - 1] != 0) {
      goto L47100;
   }
   rspsub(411, odo2);
// 						!NOT CLOSABLE.
   return ret_val;

L47100:
   if ((objcts.oflag2[prsvec.prso - 1] & OpenO) != 0) {
      goto L47200;
   }
// 						!OPEN?
   rspeak(413);
// 						!NO, JOKE.
   return ret_val;

L47200:
   objcts.oflag2[prsvec.prso - 1] &= ~OpenO;
   rspeak(414);
// 						!DONE.
   return ret_val;
// VAPPLI, PAGE 7

// V127--	FIND.  BIG MEGILLA.

L48000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   i = 415;
// 						!DEFAULT CASE.
   if (qhere(prsvec.prso, play.here)) {
      goto L48300;
   }
// 						!IN ROOM?
   if (objcts.oadv[prsvec.prso - 1] == play.winner) {
      goto L48200;
   }
// 						!ON WINNER?
   j = objcts.ocan[prsvec.prso - 1];
// 						!DOWN ONE LEVEL.
   if (j == 0) {
      goto L10;
   }
   if ((objcts.oflag1[j - 1] & TranO) == 0 && (!((objcts.oflag2[j - 1] & OpenO) != 0) || (objcts.oflag1[j - 1] & DoorO + ContO) == 0)) {
      goto L10;
   }
   i = 417;
// 						!ASSUME IN ROOM.
   if (qhere(j, play.here)) {
      goto L48100;
   }
   if (objcts.oadv[j - 1] != play.winner) {
      goto L10;
   }
// 						!NOT HERE OR ON PERSON.
   i = 418;
L48100:
   rspsub(i, objcts.odesc2[j - 1]);
// 						!DESCRIBE FINDINGS.
   return ret_val;

L48200:
   i = 416;
L48300:
   rspsub(i, odo2);
// 						!DESCRIBE FINDINGS.
   return ret_val;

// V128--	WAIT.  RUN CLOCK DEMON.

L49000:
   rspeak(419);
// 						!TIME PASSES.
   for (i = 1; i <= 3; ++i) {
      if (clockd(/*x*/)) {
         return ret_val;
      }
// L49100:
   }
   return ret_val;

// V129--	SPIN.
// V159--	TURN TO.

L50000:
L88000:
   if (!objact(/*x*/)) {
      rspeak(663);
   }
// 						!IF NOT OBJ, JOKE.
   return ret_val;

// V130--	BOARD.  WORKS WITH VEHICLES.

L51000:
   if ((objcts.oflag2[prsvec.prso - 1] & VehO) != 0) {
      goto L51100;
   }
   rspsub(421, odo2);
// 						!NOT VEHICLE, JOKE.
   return ret_val;

L51100:
   if (qhere(prsvec.prso, play.here)) {
      goto L51200;
   }
// 						!HERE?
   rspsub(420, odo2);
// 						!NO, JOKE.
   return ret_val;

L51200:
   if (av == 0) {
      goto L51300;
   }
// 						!ALREADY GOT ONE?
   rspsub(422, odo2);
// 						!YES, JOKE.
   return ret_val;

L51300:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   rspsub(423, odo2);
// 						!DESCRIBE.
   advs.avehic[play.winner - 1] = prsvec.prso;
   if (play.winner != PlayerAX) {
      objcts.ocan[advs.aobj[play.winner - 1] - 1] = prsvec.prso;
   }
   return ret_val;

// V131--	DISEMBARK.

L52000:
   if (av == prsvec.prso) {
      goto L52100;
   }
// 						!FROM VEHICLE?
   rspeak(424);
// 						!NO, JOKE.
   return ret_val;

L52100:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if ((rooms.rflag[play.here - 1] & LandR) != 0) {
      goto L52200;
   }
   rspeak(425);
// 						!NOT ON LAND.
   return ret_val;

L52200:
   advs.avehic[play.winner - 1] = 0;
   rspeak(426);
   if (play.winner != PlayerAX) {
      newsta(advs.aobj[play.winner - 1], 0, play.here, 0, 0);
   }
   return ret_val;

// V132--	TAKE.  HANDLED EXTERNALLY.

L53000:
   ret_val = take(true);
   return ret_val;

// V133--	INVENTORY.  PROCESSED EXTERNALLY.

L55000:
   invent(play.winner);
   return ret_val;
// VAPPLI, PAGE 8

// V134--	FILL.  STRANGE DOINGS WITH WATER.

L56000:
   if (prsvec.prsi != 0) {
      goto L56050;
   }
// 						!ANY OBJ SPECIFIED?
   if ((rooms.rflag[play.here - 1] & WaterR + FillR) != 0) {
      goto L56025;
   }
   rspeak(516);
// 						!NOTHING TO FILL WITH.
   prsvec.prswon = false;
// 						!YOU LOSE.
   return ret_val;

L56025:
   prsvec.prsi = GWateOX;
// 						!USE GLOBAL WATER.
L56050:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if (prsvec.prsi != GWateOX && prsvec.prsi != WaterOX) {
      rspsb2(444, odi2, odo2);
   }
   return ret_val;

// V135,V136--	EAT/DRINK

L58000:
L59000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if (prsvec.prso == GWateOX) {
      goto L59500;
   }
// 						!DRINK GLOBAL WATER?
   if (!((objcts.oflag1[prsvec.prso - 1] & FoodO) != 0)) {
      goto L59400;
   }
// 						!EDIBLE?
   if (objcts.oadv[prsvec.prso - 1] == play.winner) {
      goto L59200;
   }
// 						!YES, ON WINNER?
L59100:
   rspsub(454, odo2);
// 						!NOT ACCESSIBLE.
   return ret_val;

L59200:
   if (prsvec.prsa == DrinkW) {
      goto L59300;
   }
// 						!DRINK FOOD?
   newsta(prsvec.prso, 455, 0, 0, 0);
// 						!NO, IT DISAPPEARS.
   return ret_val;

L59300:
   rspeak(456);
// 						!YES, JOKE.
   return ret_val;

L59400:
   if (!((objcts.oflag1[prsvec.prso - 1] & DrnkO) != 0)) {
      goto L59600;
   }
// 						!DRINKABLE?
   if (objcts.ocan[prsvec.prso - 1] == 0) {
      goto L59100;
   }
// 						!YES, IN SOMETHING?
   if (objcts.oadv[objcts.ocan[prsvec.prso - 1] - 1] != play.winner) {
      goto L59100;
   }
   if ((objcts.oflag2[objcts.ocan[prsvec.prso - 1] - 1] & OpenO) != 0) {
      goto L59500;
   }
// 						!CONT OPEN?
   rspeak(457);
// 						!NO, JOKE.
   return ret_val;

L59500:
   newsta(prsvec.prso, 458, 0, 0, 0);
// 						!GONE.
   return ret_val;

L59600:
   rspsub(453, odo2);
// 						!NOT FOOD OR DRINK.
   return ret_val;

// V137--	BURN.  COMPLICATED.

L60000:
   if ((objcts.oflag1[prsvec.prsi - 1] & FlamO + LiteO + OnO) != FlamO + LiteO + OnO) {
      goto L60400;
   }
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if (objcts.ocan[prsvec.prso - 1] != RecepOX) {
      goto L60050;
   }
// 						!BALLOON?
   if (oappli(objcts.oactio[BalloOX - 1], 0)) {
      return ret_val;
   }
// 						!DID IT HANDLE?
L60050:
   if ((objcts.oflag1[prsvec.prso - 1] & BurnO) == 0) {
      goto L60300;
   }
   if (objcts.oadv[prsvec.prso - 1] != play.winner) {
      goto L60100;
   }
// 						!CARRYING IT?
   rspsub(459, odo2);
   jigsup(460);
   return ret_val;

L60100:
   j = objcts.ocan[prsvec.prso - 1];
// 						!GET CONTAINER.
   if (qhere(prsvec.prso, play.here) || av != 0 && j == av) {
      goto L60200;
   }
   if (j == 0) {
      goto L60150;
   }
// 						!INSIDE?
   if (!((objcts.oflag2[j - 1] & OpenO) != 0)) {
      goto L60150;
   }
// 						!OPEN?
   if (qhere(j, play.here) || av != 0 && objcts.ocan[j - 1] == av) {
      goto L60200;
   }
L60150:
   rspeak(461);
// 						!CANT REACH IT.
   return ret_val;

L60200:
   rspsub(462, odo2);
// 						!BURN IT.
   newsta(prsvec.prso, 0, 0, 0, 0);
   return ret_val;

L60300:
   rspsub(463, odo2);
// 						!CANT BURN IT.
   return ret_val;

L60400:
   rspsub(301, odi2);
// 						!CANT BURN IT WITH THAT.
   return ret_val;
// VAPPLI, PAGE 9

// V138--	MUNG.  GO TO COMMON ATTACK CODE.

L63000:
   i = 466;
// 						!CHOOSE PHRASE.
   if ((objcts.oflag2[prsvec.prso - 1] & VillO) != 0) {
      goto L66100;
   }
   if (!objact(/*x*/)) {
      rspsb2(466, odo2, rmk);
   }
   return ret_val;

// V139--	KILL.  GO TO COMMON ATTACK CODE.

L64000:
   i = 467;
// 						!CHOOSE PHRASE.
   goto L66100;

// V140--	SWING.  INVERT OBJECTS, FALL THRU TO ATTACK.

L65000:
   j = prsvec.prso;
// 						!INVERT.
   prsvec.prso = prsvec.prsi;
   prsvec.prsi = j;
   j = odo2;
   odo2 = odi2;
   odi2 = j;
   prsvec.prsa = AttacW;
// 						!FOR OBJACT.

// V141--	ATTACK.  FALL THRU TO ATTACK CODE.

L66000:
   i = 468;

// COMMON MUNG/ATTACK/SWING/KILL CODE.

L66100:
   if (prsvec.prso != 0) {
      goto L66200;
   }
// 						!ANYTHING?
   rspeak(469);
// 						!NO, JOKE.
   return ret_val;

L66200:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if ((objcts.oflag2[prsvec.prso - 1] & VillO) != 0) {
      goto L66300;
   }
   if ((objcts.oflag1[prsvec.prso - 1] & VictO) == 0) {
      rspsub(470, odo2);
   }
   return ret_val;

L66300:
   j = 471;
// 						!ASSUME NO WEAPON.
   if (prsvec.prsi == 0) {
      goto L66500;
   }
   if ((objcts.oflag2[prsvec.prsi - 1] & WeapO) == 0) {
      goto L66400;
   }
   melee = 1;
// 						!ASSUME SWORD.
   if (prsvec.prsi != SwordOX) {
      melee = 2;
   }
// 						!MUST BE KNIFE.
   i = blow(PlayerAX, prsvec.prso, melee, true, 0);
// 						!STRIKE BLOW.
   return ret_val;

L66400:
   j = 472;
// 						!NOT A WEAPON.
L66500:
   rspsb2(i, odo2, j);
// 						!JOKE.
   return ret_val;
// VAPPLI, PAGE 10

// V142--	WALK.  PROCESSED EXTERNALLY.

L68000:
   ret_val = walk(/*x*/);
   return ret_val;

// V143--	TELL.  PROCESSED IN GAME.

L69000:
   rspeak(603);
   return ret_val;

// V144--	PUT.  PROCESSED EXTERNALLY.

L70000:
   ret_val = put(/*true*/);
   return ret_val;

// V145,V146,V147,V148--	DROP/GIVE/POUR/THROW

L71000:
L72000:
L73000:
L74000:
   ret_val = drop(/*false*/);
   return ret_val;

// V149--	SAVE

L77000:
   if ((rooms.rflag[TStrsRX - 1] & SeenR) == 0) {
      goto L77100;
   }
   rspeak(828);
// 						!NO SAVES IN ENDGAME.
   return ret_val;

L77100:
   savegm();
   return ret_val;

// V150--	RESTORE

L78000:
   if ((rooms.rflag[TStrsRX - 1] & SeenR) == 0) {
      goto L78100;
   }
   rspeak(829);
// 						!NO RESTORES IN ENDGAME.
   return ret_val;

L78100:
   rstrgm();
   return ret_val;
// VAPPLI, PAGE 11

// V151--	HELLO

L80000:
   if (prsvec.prso != 0) {
      goto L80100;
   }
// 						!ANY OBJ?
   i__1 = rnd(4) + 346;
   rspeak(i__1);
// 						!NO, VANILLA HELLO.
   return ret_val;

L80100:
   if (prsvec.prso != AviatOX) {
      goto L80200;
   }
// 						!HELLO AVIATOR?
   rspeak(350);
// 						!NOTHING HAPPENS.
   return ret_val;

L80200:
   if (prsvec.prso != SailoOX) {
      goto L80300;
   }
// 						!HELLO SAILOR?
   ++state.hs;
// 						!COUNT.
   i = 351;
// 						!GIVE NORMAL OR
   if (state.hs % 10 == 0) {
      i = 352;
   }
// 						!RANDOM MESSAGE.
   if (state.hs % 20 == 0) {
      i = 353;
   }
   rspeak(i);
// 						!SPEAK UP.
   return ret_val;

L80300:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   i = 354;
// 						!ASSUME VILLAIN.
   if ((objcts.oflag2[prsvec.prso - 1] & VillO + ActrO) == 0) {
      i = 355;
   }
   rspsub(i, odo2);
// 						!HELLO THERE
// 						!
   return ret_val;

// V152--	LOOK INTO

L81000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   if ((objcts.oflag1[prsvec.prso - 1] & DoorO) == 0) {
      goto L81300;
   }
   if (!((objcts.oflag2[prsvec.prso - 1] & OpenO) != 0)) {
      goto L81200;
   }
// 						!OPEN?
   rspsub(628, odo2);
// 						!OPEN DOOR- UNINTERESTING.
   return ret_val;

L81200:
   rspsub(525, odo2);
// 						!CLOSED DOOR- CANT SEE.
   return ret_val;

L81300:
   if ((objcts.oflag2[prsvec.prso - 1] & VehO) != 0) {
      goto L81400;
   }
   if ((objcts.oflag2[prsvec.prso - 1] & OpenO) != 0 || (objcts.oflag1[prsvec.prso - 1] & TranO) != 0) {
      goto L81400;
   }
   if ((objcts.oflag1[prsvec.prso - 1] & ContO) != 0) {
      goto L81200;
   }
   rspsub(630, odo2);
// 						!CANT LOOK INSIDE.
   return ret_val;

L81400:
   if (qempty(prsvec.prso)) {
      goto L81500;
   }
// 						!VEH OR SEE IN.  EMPTY?
   princo(prsvec.prso, 573);
// 						!NO, LIST CONTENTS.
   return ret_val;

L81500:
   rspsub(629, odo2);
// 						!EMPTY.
   return ret_val;

// V153--	LOOK UNDER

L82000:
   if (!objact(/*x*/)) {
      rspeak(631);
   }
// 						!OBJECT HANDLE?
   return ret_val;
// VAPPLI, PAGE 12

// V154--	PUMP

L83000:
   if (objcts.oroom[PumpOX - 1] == play.here || objcts.oadv[PumpOX - 1] == play.winner) {
      goto L83100;
   }
   rspeak(632);
// 						!NO.
   return ret_val;

L83100:
   prsvec.prsi = PumpOX;
// 						!BECOMES INFLATE
   prsvec.prsa = InflaW;
// 						!X WITH PUMP.
   goto L22000;
// 						!DONE.

// V155--	WIND

L84000:
   if (!objact(/*x*/)) {
      rspsub(634, odo2);
   }
// 						!OBJ HANDLE?
   return ret_val;

// V156--	CLIMB
// V157--	CLIMB UP
// V158--	CLIMB DOWN

L85000:
L86000:
L87000:
   i = UpDX;
// 						!ASSUME UP.
   if (prsvec.prsa == ClmbDW) {
      i = DownDX;
   }
// 						!UNLESS CLIMB DN.
   f = (objcts.oflag2[prsvec.prso - 1] & ClmbO) != 0;
   if (f && findxt(i, play.here)) {
      goto L87500;
   }
// 						!ANYTHING TO CLIMB?
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!OBJ HANDLE?
   i = 657;
   if (f) {
      i = 524;
   }
// 						!VARIETY OF JOKES.
   if (!f && (prsvec.prso == WallOX || prsvec.prso >= WNortOX && prsvec.prso <= WNortOX + 3)) {
      i = 656;
   }
   rspeak(i);
// 						!JOKE.
   return ret_val;

L87500:
   prsvec.prsa = WalkW;
// 						!WALK
   prsvec.prso = i;
// 						!IN SPECIFIED DIR.
   ret_val = walk(/*x*/);
   return ret_val;
}

// Clock demon for intermove clock events
bool clockd(/*int x*/) {
// System generated locals
   int i__1;
   bool ret_val;

// Local variables
   int i;

   ret_val = false;
// 						!ASSUME NO ACTION.
   i__1 = cevent.clnt;
   for (i = 1; i <= i__1; ++i) {
      if (!cevent.cflag[i - 1] || cevent.ctick[i - 1] == 0) {
         goto L100;
      }
      if (cevent.ctick[i - 1] < 0) {
         goto L50;
      }
// 						!PERMANENT ENTRY?
      --cevent.ctick[i - 1];
      if (cevent.ctick[i - 1] != 0) {
         goto L100;
      }
// 						!TIMER EXPIRED?
   L50:
      ret_val = true;
      cevapp(cevent.cactio[i - 1]);
// 						!DO ACTION.
   L100:
      ;
   }
   return ret_val;
}
