// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Simple objects processor
// Objects in this module cannot call rminfo(), jigsup(), major verbs, or other non-resident subroutines
Bool sobjs(int ri, int arg) {
// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   Bool f;
   int i;
   int mroom;
   int av;
   int odi2 = 0, odo2 = 0;

// SOBJS, PAGE 2

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
   ret_val = true;

   switch (ri) {
      case 1:
         goto L1000;
      case 2:
         goto L3000;
      case 3:
         goto L4000;
      case 4:
         goto L6000;
      case 5:
         goto L7000;
      case 6:
         goto L8000;
      case 7:
         goto L9000;
      case 8:
         goto L13000;
      case 9:
         goto L14000;
      case 10:
         goto L16000;
      case 11:
         goto L17000;
      case 12:
         goto L21000;
      case 13:
         goto L23000;
      case 14:
         goto L24000;
      case 15:
         goto L27000;
      case 16:
         goto L28000;
      case 17:
         goto L29000;
      case 18:
         goto L30000;
      case 19:
         goto L31000;
      case 20:
         goto L33000;
      case 21:
         goto L34000;
      case 22:
         goto L36000;
      case 23:
         goto L37000;
      case 24:
         goto L38000;
      case 25:
         goto L41000;
      case 26:
         goto L42000;
      case 27:
         goto L43000;
      case 28:
         goto L44000;
      case 29:
         goto L46000;
      case 30:
         goto L53000;
      case 31:
         goto L56000;
   }
   bug(6, ri);

// RETURN HERE TO DECLARE FALSE RESULT

L10:
   ret_val = false;
   return ret_val;
// SOBJS, PAGE 3

// O1--	GUNK FUNCTION

L1000:
   if (objcts.ocan[GunkOX - 1] == 0) {
      goto L10;
   }
// 						!NOT INSIDE? F
   newsta(GunkOX, 122, 0, 0, 0);
// 						!FALLS APART.
   return ret_val;

// O2--	TROPHY CASE

L3000:
   if (prsvec.prsa != TakeW) {
      goto L10;
   }
// 						!TAKE?
   rspeak(128);
// 						!CANT.
   return ret_val;

// O3--	BOTTLE FUNCTION

L4000:
   if (prsvec.prsa != ThrowW) {
      goto L4100;
   }
// 						!THROW?
   newsta(prsvec.prso, 129, 0, 0, 0);
// 						!BREAKS.
   return ret_val;

L4100:
   if (prsvec.prsa != MungW) {
      goto L10;
   }
// 						!MUNG?
   newsta(prsvec.prso, 131, 0, 0, 0);
// 						!BREAKS.
   return ret_val;
// SOBJS, PAGE 4

// O4--	ROPE FUNCTION

L6000:
   if (play.here == DomeRX) {
      goto L6100;
   }
// 						!IN DOME?
   findex.domef = false;
// 						!NO,
   if (prsvec.prsa != UnTieW) {
      goto L6050;
   }
// 						!UNTIE?
   rspeak(134);
// 						!CANT
   return ret_val;

L6050:
   if (prsvec.prsa != TieW) {
      goto L10;
   }
// 						!TIE?
   rspeak(135);
// 						!CANT TIE
   return ret_val;

L6100:
   if (prsvec.prsa != TieW || prsvec.prsi != RailiOX) {
      goto L6200;
   }
   if (findex.domef) {
      goto L6150;
   }
// 						!ALREADY TIED?
   findex.domef = true;
// 						!NO, TIE IT.
   objcts.oflag1[RopeOX - 1] |= NDscO;
   objcts.oflag2[RopeOX - 1] |= ClmbO;
   newsta(RopeOX, 137, DomeRX, 0, 0);
   return ret_val;

L6150:
   rspeak(136);
// 						!DUMMY.
   return ret_val;

L6200:
   if (prsvec.prsa != UnTieW) {
      goto L6300;
   }
// 						!UNTIE?
   if (findex.domef) {
      goto L6250;
   }
// 						!TIED?
   rspeak(134);
// 						!NO, DUMMY.
   return ret_val;

L6250:
   findex.domef = false;
// 						!YES, UNTIE IT.
   objcts.oflag1[RopeOX - 1] &= ~NDscO;
   objcts.oflag2[RopeOX - 1] &= ~ClmbO;
   rspeak(139);
   return ret_val;

L6300:
   if (findex.domef || prsvec.prsa != DropW) {
      goto L6400;
   }
// 						!DROP & UNTIED?
   newsta(RopeOX, 140, MTorcRX, 0, 0);
// 						!YES, DROP.
   return ret_val;

L6400:
   if (prsvec.prsa != TakeW || !findex.domef) {
      goto L10;
   }
   rspeak(141);
// 						!TAKE & TIED.
   return ret_val;

// O5--	SWORD FUNCTION

L7000:
   if (prsvec.prsa == TakeW && play.winner == PlayerAX) {
      hack.swdact = true;
   }
   goto L10;

// O6--	LANTERN

L8000:
   if (prsvec.prsa != ThrowW) {
      goto L8100;
   }
// 						!THROW?
   newsta(LampOX, 0, 0, 0, 0);
// 						!KILL LAMP,
   newsta(BLampOX, 142, play.here, 0, 0);
// 						!REPLACE WITH BROKEN.
   return ret_val;

L8100:
   if (prsvec.prsa == TrnOnW) {
      cevent.cflag[LntCX - 1] = true;
   }
   if (prsvec.prsa == TrnOfW) {
      cevent.cflag[LntCX - 1] = false;
   }
   goto L10;

// O7--	RUG FUNCTION

L9000:
   if (prsvec.prsa != RaiseW) {
      goto L9100;
   }
// 						!RAISE?
   rspeak(143);
// 						!CANT
   return ret_val;

L9100:
   if (prsvec.prsa != TakeW) {
      goto L9200;
   }
// 						!TAKE?
   rspeak(144);
// 						!CANT
   return ret_val;

L9200:
   if (prsvec.prsa != MoveW) {
      goto L9300;
   }
// 						!MOVE?
   i__1 = findex.orrug + 145;
   rspeak(i__1);
   findex.orrug = 1;
   objcts.oflag1[DoorOX - 1] |= VisiO;
   return ret_val;

L9300:
   if (prsvec.prsa != LookUW || findex.orrug != 0 || (objcts.oflag2[DoorOX - 1] & OpenO) != 0) {
      goto L10;
   }
   rspeak(345);
   return ret_val;
// SOBJS, PAGE 5

// O8--	SKELETON

L13000:
   i = robrm(play.here, 100, Lld2RX, 0, 0) + robadv(play.winner, Lld2RX, 0, 0);
   if (i != 0) {
      rspeak(162);
   }
// 						!IF ROBBED, SAY SO.
   return ret_val;

// O9--	MIRROR

L14000:
   if (findex.mirrmf || prsvec.prsa != RubW) {
      goto L14500;
   }
   mroom = play.here ^ 1;
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!INTERCHANGE OBJS.
      if (objcts.oroom[i - 1] == play.here) {
         objcts.oroom[i - 1] = -1;
      }
      if (objcts.oroom[i - 1] == mroom) {
         objcts.oroom[i - 1] = play.here;
      }
      if (objcts.oroom[i - 1] == -1) {
         objcts.oroom[i - 1] = mroom;
      }
// L14100:
   }
   f = moveto(mroom, play.winner);
   rspeak(163);
// 						!SHAKE WORLD.
   return ret_val;

L14500:
   if (prsvec.prsa != LookW && prsvec.prsa != LookIW && prsvec.prsa != ExamiW) {
      goto L14600;
   }
   i = 164;
// 						!MIRROR OK.
   if (findex.mirrmf) {
      i = 165;
   }
// 						!MIRROR DEAD.
   rspeak(i);
   return ret_val;

L14600:
   if (prsvec.prsa != TakeW) {
      goto L14700;
   }
// 						!TAKE?
   rspeak(166);
// 						!JOKE.
   return ret_val;

L14700:
   if (prsvec.prsa != MungW && prsvec.prsa != ThrowW) {
      goto L10;
   }
   i = 167;
// 						!MIRROR BREAKS.
   if (findex.mirrmf) {
      i = 168;
   }
// 						!MIRROR ALREADY BROKEN.
   findex.mirrmf = true;
   findex.badlkf = true;
   rspeak(i);
   return ret_val;
// SOBJS, PAGE 6

// O10--	DUMBWAITER

L16000:
   if (prsvec.prsa != RaiseW) {
      goto L16100;
   }
// 						!RAISE?
   if (findex.cagetf) {
      goto L16400;
   }
// 						!ALREADY AT TOP?
   newsta(TBaskOX, 175, TShafRX, 0, 0);
// 						!NO, RAISE BASKET.
   newsta(FBaskOX, 0, BShafRX, 0, 0);
   findex.cagetf = true;
// 						!AT TOP.
   return ret_val;

L16100:
   if (prsvec.prsa != LowerW) {
      goto L16200;
   }
// 						!LOWER?
   if (!findex.cagetf) {
      goto L16400;
   }
// 						!ALREADY AT BOTTOM?
   newsta(TBaskOX, 176, BShafRX, 0, 0);
// 						!NO, LOWER BASKET.
   newsta(FBaskOX, 0, TShafRX, 0, 0);
   findex.cagetf = false;
   if (!lit(play.here)) {
      rspeak(406);
   }
// 						!IF DARK, DIE.
   return ret_val;

L16200:
   if (prsvec.prso != FBaskOX && prsvec.prsi != FBaskOX) {
      goto L16300;
   }
   rspeak(130);
// 						!WRONG BASKET.
   return ret_val;

L16300:
   if (prsvec.prsa != TakeW) {
      goto L10;
   }
// 						!TAKE?
   rspeak(177);
// 						!JOKE.
   return ret_val;

L16400:
   i__1 = rnd(3) + 125;
   rspeak(i__1);
// 						!DUMMY.
   return ret_val;

// O11--	GHOST FUNCTION

L17000:
   i = 178;
// 						!ASSUME DIRECT.
   if (prsvec.prso != GhostOX) {
      i = 179;
   }
// 						!IF NOT, INDIRECT.
   rspeak(i);
   return ret_val;
// 						!SPEAK AND EXIT.
// SOBJS, PAGE 7

// O12--	TUBE

L21000:
   if (prsvec.prsa != PutW || prsvec.prsi != TubeOX) {
      goto L10;
   }
   rspeak(186);
// 						!CANT PUT BACK IN.
   return ret_val;

// O13--	CHALICE

L23000:
   if (prsvec.prsa != TakeW || objcts.ocan[prsvec.prso - 1] != 0 || objcts.oroom[prsvec.prso - 1] != TreasRX || objcts.oroom[ThiefOX - 1] != TreasRX || (objcts.oflag2[ThiefOX - 1] & FiteO) == 0 || !hack.thfact) {
      goto L10;
   }
   rspeak(204);
// 						!CANT TAKE.
   return ret_val;

// O14--	PAINTING

L24000:
   if (prsvec.prsa != MungW) {
      goto L10;
   }
// 						!MUNG?
   rspeak(205);
// 						!DESTROY PAINTING.
   objcts.ofval[prsvec.prso - 1] = 0;
   objcts.otval[prsvec.prso - 1] = 0;
   objcts.odesc1[prsvec.prso - 1] = 207;
   objcts.odesc2[prsvec.prso - 1] = 206;
   return ret_val;
// SOBJS, PAGE 8

// O15--	BOLT

L27000:
   if (prsvec.prsa != TurnW) {
      goto L10;
   }
// 						!TURN BOLT?
   if (prsvec.prsi != WrencOX) {
      goto L27500;
   }
// 						!WITH WRENCH?
   if (findex.gatef) {
      goto L27100;
   }
// 						!PROPER BUTTON PUSHED?
   rspeak(210);
// 						!NO, LOSE.
   return ret_val;

L27100:
   if (findex.lwtidf) {
      goto L27200;
   }
// 						!LOW TIDE NOW?
   findex.lwtidf = true;
// 						!NO, EMPTY DAM.
   rspeak(211);
   objcts.oflag2[CoffiOX - 1] &= ~ScrDO;
   objcts.oflag1[TrunkOX - 1] |= VisiO;
   rooms.rflag[ReserRX - 1] = (rooms.rflag[ReserRX - 1] | LandR) & ~(WaterR + SeenR);
   return ret_val;

L27200:
   findex.lwtidf = false;
// 						!YES, FILL DAM.
   rspeak(212);
   if (qhere(TrunkOX, ReserRX)) {
      objcts.oflag1[TrunkOX - 1] &= ~VisiO;
   }
   rooms.rflag[ReserRX - 1] = (rooms.rflag[ReserRX - 1] | WaterR) & ~LandR;
   return ret_val;

L27500:
   rspsub(299, odi2);
// 						!NOT WITH THAT.
   return ret_val;

// O16--	GRATING

L28000:
   if (prsvec.prsa != OpenW && prsvec.prsa != CloseW) {
      goto L10;
   }
   if (findex.grunlf) {
      goto L28200;
   }
// 						!UNLOCKED?
   rspeak(214);
// 						!NO, LOCKED.
   return ret_val;

L28200:
   i = 215;
// 						!UNLOCKED, VIEW FRM CLR.
   if (play.here != ClearRX) {
      i = 216;
   }
// 						!VIEW FROM BELOW.
   ret_val = opncls(GrateOX, i, 885);
// 						!OPEN/CLOSE.
   rooms.rflag[MGratRX - 1] &= ~LightR;
   if ((objcts.oflag2[GrateOX - 1] & OpenO) != 0) {
      rooms.rflag[MGratRX - 1] |= LightR;
   }
   if (!lit(play.here)) {
      rspeak(406);
   }
// 						!IF DARK, DIE.
   return ret_val;

// O17--	TRAP DOOR

L29000:
   if (play.here != LRoomRX) {
      goto L29100;
   }
// 						!FROM LIVING ROOM?
   ret_val = opncls(DoorOX, 218, 219);
// 						!OPEN/CLOSE.
   return ret_val;

L29100:
   if (play.here != CellaRX) {
      goto L10;
   }
// 						!FROM CELLAR?
   if (prsvec.prsa != OpenW || (objcts.oflag2[DoorOX - 1] & OpenO) != 0) {
      goto L29200;
   }
   rspeak(220);
// 						!CANT OPEN CLOSED DOOR.
   return ret_val;

L29200:
   ret_val = opncls(DoorOX, 0, 22);
// 						!NORMAL OPEN/CLOSE.
   return ret_val;

// O18--	DURABLE DOOR

L30000:
   i = 0;
// 						!ASSUME NO APPL.
   if (prsvec.prsa == OpenW) {
      i = 221;
   }
// 						!OPEN?
   if (prsvec.prsa == BurnW) {
      i = 222;
   }
// 						!BURN?
   if (prsvec.prsa == MungW) {
      i = rnd(3) + 223;
   }
// 						!MUNG?
   if (i == 0) {
      goto L10;
   }
   rspeak(i);
   return ret_val;

// O19--	MASTER SWITCH

L31000:
   if (prsvec.prsa != TurnW) {
      goto L10;
   }
// 						!TURN?
   if (prsvec.prsi != ScrewOX) {
      goto L31500;
   }
// 						!WITH SCREWDRIVER?
   if ((objcts.oflag2[MachiOX - 1] & OpenO) != 0) {
      goto L31600;
   }
// 						!LID UP?
   rspeak(226);
// 						!NO, ACTIVATE.
   if (objcts.ocan[CoalOX - 1] != MachiOX) {
      goto L31400;
   }
// 						!COAL INSIDE?
   newsta(CoalOX, 0, 0, 0, 0);
// 						!KILL COAL,
   newsta(DiamoOX, 0, 0, MachiOX, 0);
// 						!REPLACE WITH DIAMOND.
   return ret_val;

L31400:
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!KILL NONCOAL OBJECTS.
      if (objcts.ocan[i - 1] != MachiOX) {
         goto L31450;
      }
// 						!INSIDE MACHINE?
      newsta(i, 0, 0, 0, 0);
// 						!KILL OBJECT AND CONTENTS.
      newsta(GunkOX, 0, 0, MachiOX, 0);
// 						!REDUCE TO GUNK.
   L31450:
      ;
   }
   return ret_val;

L31500:
   rspsub(300, odi2);
// 						!CANT TURN WITH THAT.
   return ret_val;

L31600:
   rspeak(227);
// 						!LID IS UP.
   return ret_val;
// SOBJS, PAGE 9

// O20--	LEAK

L33000:
   if (prsvec.prso != LeakOX || prsvec.prsa != PlugW || findex.rvmnt <= 0) {
      goto L10;
   }
   if (prsvec.prsi != PuttyOX) {
      goto L33100;
   }
// 						!WITH PUTTY?
   findex.rvmnt = -1;
// 						!DISABLE LEAK.
   cevent.ctick[MntCX - 1] = 0;
   rspeak(577);
   return ret_val;

L33100:
   rspsub(301, odi2);
// 						!CANT WITH THAT.
   return ret_val;

// O21--	DROWNING BUTTONS

L34000:
   if (prsvec.prsa != PushW) {
      goto L10;
   }
// 						!PUSH?
   switch (prsvec.prso - RButtOX + 1) {
      case 1:
         goto L34100;
      case 2:
         goto L34200;
      case 3:
         goto L34300;
      case 4:
         goto L34400;
   }
   goto L10;
// 						!NOT A BUTTON.

L34100:
   rooms.rflag[play.here - 1] ^= LightR;
   i = 230;
   if ((rooms.rflag[play.here - 1] & LightR) != 0) {
      i = 231;
   }
   rspeak(i);
   return ret_val;

L34200:
   findex.gatef = true;
// 						!RELEASE GATE.
   rspeak(232);
   return ret_val;

L34300:
   findex.gatef = false;
// 						!INTERLOCK GATE.
   rspeak(232);
   return ret_val;

L34400:
   if (findex.rvmnt != 0) {
      goto L34500;
   }
// 						!LEAK ALREADY STARTED?
   rspeak(233);
// 						!NO, START LEAK.
   findex.rvmnt = 1;
   cevent.ctick[MntCX - 1] = -1;
   return ret_val;

L34500:
   rspeak(234);
// 						!BUTTON JAMMED.
   return ret_val;

// O22--	INFLATABLE BOAT

L36000:
   if (prsvec.prsa != InflaW) {
      goto L10;
   }
// 						!INFLATE?
   if (objcts.oroom[IBoatOX - 1] != 0) {
      goto L36100;
   }
// 						!IN ROOM?
   rspeak(235);
// 						!NO, JOKE.
   return ret_val;

L36100:
   if (prsvec.prsi != PumpOX) {
      goto L36200;
   }
// 						!WITH PUMP?
   newsta(IBoatOX, 0, 0, 0, 0);
// 						!KILL DEFL BOAT,
   newsta(RBoatOX, 236, play.here, 0, 0);
// 						!REPL WITH INF.
   findex.deflaf = false;
   return ret_val;

L36200:
   i = 237;
// 						!JOKES.
   if (prsvec.prsi != LungsOX) {
      i = 303;
   }
   rspsub(i, odi2);
   return ret_val;

// O23--	DEFLATED BOAT

L37000:
   if (prsvec.prsa != InflaW) {
      goto L37100;
   }
// 						!INFLATE?
   rspeak(238);
// 						!JOKE.
   return ret_val;

L37100:
   if (prsvec.prsa != PlugW) {
      goto L10;
   }
// 						!PLUG?
   if (prsvec.prsi != PuttyOX) {
      goto L33100;
   }
// 						!WITH PUTTY?
   newsta(IBoatOX, 239, objcts.oroom[DBoatOX - 1], objcts.ocan[DBoatOX - 1], objcts.oadv[DBoatOX - 1]);
   newsta(DBoatOX, 0, 0, 0, 0);
// 						!KILL DEFL BOAT, REPL.
   return ret_val;
// SOBJS, PAGE 10

// O24--	RUBBER BOAT

L38000:
   if (arg != 0) {
      goto L10;
   }
// 						!DISMISS READIN, OUT.
   if (prsvec.prsa != BoardW || objcts.oadv[StickOX - 1] != play.winner) {
      goto L38100;
   }
   newsta(RBoatOX, 0, 0, 0, 0);
// 						!KILL INFL BOAT,
   newsta(DBoatOX, 240, play.here, 0, 0);
// 						!REPL WITH DEAD.
   findex.deflaf = true;
   return ret_val;

L38100:
   if (prsvec.prsa != InflaW) {
      goto L38200;
   }
// 						!INFLATE?
   rspeak(367);
// 						!YES, JOKE.
   return ret_val;

L38200:
   if (prsvec.prsa != DeflaW) {
      goto L10;
   }
// 						!DEFLATE?
   if (av == RBoatOX) {
      goto L38300;
   }
// 						!IN BOAT?
   if (objcts.oroom[RBoatOX - 1] == 0) {
      goto L38400;
   }
// 						!ON GROUND?
   newsta(RBoatOX, 0, 0, 0, 0);
// 						!KILL INFL BOAT,
   newsta(IBoatOX, 241, play.here, 0, 0);
// 						!REPL WITH DEFL.
   findex.deflaf = true;
   return ret_val;

L38300:
   rspeak(242);
// 						!IN BOAT.
   return ret_val;

L38400:
   rspeak(243);
// 						!NOT ON GROUND.
   return ret_val;

// O25--	BRAIDED ROPE

L41000:
   if (prsvec.prsa != TieW || prsvec.prso != BRopeOX || prsvec.prsi != Hook1OX && prsvec.prsi != Hook2OX) {
      goto L41500;
   }
   findex.btief = prsvec.prsi;
// 						!RECORD LOCATION.
   cevent.cflag[BalCX - 1] = false;
// 						!STALL ASCENT.
   rspeak(248);
   return ret_val;

L41500:
   if (prsvec.prsa != UnTieW || prsvec.prso != BRopeOX) {
      goto L10;
   }
   if (findex.btief != 0) {
      goto L41600;
   }
// 						!TIED UP?
   rspeak(249);
// 						!NO, JOKE.
   return ret_val;

L41600:
   rspeak(250);
   findex.btief = 0;
// 						!UNTIE.
   cevent.ctick[BalCX - 1] = 3;
// 						!RESTART CLOCK.
   cevent.cflag[BalCX - 1] = true;
   return ret_val;

// O26--	SAFE

L42000:
   i = 0;
// 						!ASSUME UNPROCESSED.
   if (prsvec.prsa == TakeW) {
      i = 251;
   }
// 						!TAKE?
   if (prsvec.prsa == OpenW && findex.safef) {
      i = 253;
   }
// 						!OPEN AFTER BLAST?
   if (prsvec.prsa == OpenW && !findex.safef) {
      i = 254;
   }
// 						!OPEN BEFORE BLAST?
   if (prsvec.prsa == CloseW && findex.safef) {
      i = 253;
   }
// 						!CLOSE AFTER?
   if (prsvec.prsa == CloseW && !findex.safef) {
      i = 255;
   }
   if (i == 0) {
      goto L10;
   }
   rspeak(i);
   return ret_val;

// O27--	FUSE

L43000:
   if (prsvec.prsa != BurnW) {
      goto L10;
   }
// 						!BURN?
   rspeak(256);
   cevent.ctick[FusCX - 1] = 2;
// 						!START COUNTDOWN.
   return ret_val;

// O28--	GNOME

L44000:
   if (prsvec.prsa != GiveW && prsvec.prsa != ThrowW) {
      goto L44500;
   }
   if (objcts.otval[prsvec.prso - 1] == 0) {
      goto L44100;
   }
// 						!TREASURE?
   rspsub(257, odo2);
// 						!YES, GET DOOR.
   newsta(prsvec.prso, 0, 0, 0, 0);
   newsta(GnomeOX, 0, 0, 0, 0);
// 						!VANISH GNOME.
   findex.gnodrf = true;
   return ret_val;

L44100:
   rspsub(258, odo2);
// 						!NO, LOSE OBJECT.
   newsta(prsvec.prso, 0, 0, 0, 0);
   return ret_val;

L44500:
   rspeak(259);
// 						!NERVOUS GNOME.
   if (!findex.gnomef) {
      cevent.ctick[GnoCX - 1] = 5;
   }
// 						!SCHEDULE BYEBYE.
   findex.gnomef = true;
   return ret_val;

// O29--	COKE BOTTLES

L46000:
   if (prsvec.prsa != ThrowW && prsvec.prsa != MungW) {
      goto L10;
   }
   newsta(prsvec.prso, 262, 0, 0, 0);
// 						!MUNG BOTTLES.
   return ret_val;
// SOBJS, PAGE 11

// O30--	ROBOT

L53000:
   if (prsvec.prsa != GiveW) {
      goto L53200;
   }
// 						!GIVE?
   newsta(prsvec.prso, 0, 0, 0, RobotAX);
// 						!PUT ON ROBOT.
   rspsub(302, odo2);
   return ret_val;

L53200:
   if (prsvec.prsa != MungW && prsvec.prsa != ThrowW) {
      goto L10;
   }
   newsta(RobotOX, 285, 0, 0, 0);
// 						!KILL ROBOT.
   return ret_val;

// O31--	GRUE

L56000:
   if (prsvec.prsa != ExamiW) {
      goto L56100;
   }
// 						!EXAMINE?
   rspeak(288);
   return ret_val;

L56100:
   if (prsvec.prsa != FindW) {
      goto L10;
   }
// 						!FIND?
   rspeak(289);
   return ret_val;
}
