// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <stdio.h>
#include <string.h> // For strcmp().
#include "extern.h"
#include "common.h"

static void xendmv(Bool);
static Bool xvehic(int);

// Main command loop for dungeon
void game_(void) {
// Local variables
   Bool f;
   int i;

// START UP, DESCRIBE CURRENT LOCATION.

   rspeak(1);
// 						!WELCOME ABOARD.
   f = rmdesc(3);
// 						!START GAME.

// NOW LOOP, READING AND EXECUTING COMMANDS.

L100:
   play_1.winner = aindex_1.player;
// 						!PLAYER MOVING.
   play_1.telflg = false;
// 						!ASSUME NOTHING TOLD.
   if (prsvec_1.prscon <= 1) {
      rdline(input_1.inbuf, 1);
   }
#ifdef ALLOW_GDT

   if (strcmp(input_1.inbuf + prsvec_1.prscon - 1, "GDT") == 0) {
// 						!CALL ON GDT?
      gdt();
// 						!YES, INVOKE.
      goto L100;
// 						!ONWARD.
   }
#endif // ALLOW_GDT

   ++state_1.moves;
   prsvec_1.prswon = parse(input_1.inbuf, true);
   if (!prsvec_1.prswon) {
      goto L400;
   }
// 						!PARSE LOSES?
   if (xvehic(1)) {
      goto L400;
   }
// 						!VEHICLE HANDLE?

   if (prsvec_1.prsa == vindex_1.tellw) {
      goto L2000;
   }
// 						!TELL?
L300:
   if (prsvec_1.prso == oindex_1.valua || prsvec_1.prso == oindex_1.every) {
      goto L900;
   }
   if (!vappli(prsvec_1.prsa)) {
      goto L400;
   }
// 						!VERB OK?
L350:
   if (!findex_1.echof && play_1.here == rindex_1.echor) {
      goto L1000;
   }
   f = rappli(rooms_1.ractio[play_1.here - 1]);

L400:
   xendmv(play_1.telflg);
// 						!DO END OF MOVE.
   if (!lit(play_1.here)) {
      prsvec_1.prscon = 1;
   }
   goto L100;

L900:
   valuac(oindex_1.valua);
   goto L350;
// GAME, PAGE 3

// SPECIAL CASE-- ECHO ROOM.
// IF INPUT IS NOT 'ECHO' OR A DIRECTION, JUST ECHO.

L1000:
   rdline(input_1.inbuf, 0);
   ++state_1.moves;
// 						!CHARGE FOR MOVES.
   if (strcmp(input_1.inbuf, "ECHO") != 0)
      goto L1300;

   rspeak(571);
// 						!KILL THE ECHO.
   findex_1.echof = true;
   objcts_1.oflag2[oindex_1.bar - 1] &= ~ScrDO;
   prsvec_1.prswon = true;
// 						!FAKE OUT PARSER.
   prsvec_1.prscon = 1;
// 						!FORCE NEW INPUT.
   goto L400;

L1300:
   prsvec_1.prswon = parse(input_1.inbuf, false);
   if (!prsvec_1.prswon || prsvec_1.prsa != vindex_1.walkw) {
      goto L1400;
   }
   if (findxt(prsvec_1.prso, play_1.here)) {
      goto L300;
   }
// 						!VALID EXIT?

L1400:
   more_output(input_1.inbuf);
   play_1.telflg = true;
// 						!INDICATE OUTPUT.
   goto L1000;
// 						!MORE ECHO ROOM.
// GAME, PAGE 4

// SPECIAL CASE-- TELL <ACTOR>, NEW COMMAND
// NOTE THAT WE CANNOT BE IN THE ECHO ROOM.

L2000:
   if ((objcts_1.oflag2[prsvec_1.prso - 1] & ActrO) != 0) {
      goto L2100;
   }
   rspeak(602);
// 						!CANT DO IT.
   goto L350;
// 						!VAPPLI SUCCEEDS.

L2100:
   play_1.winner = oactor(prsvec_1.prso);
// 						!NEW PLAYER.
   play_1.here = advs_1.aroom[play_1.winner - 1];
// 						!NEW LOCATION.
   if (prsvec_1.prscon <= 1) {
      goto L2700;
   }
// 						!ANY INPUT?
   if (parse(input_1.inbuf, true)) {
      goto L2150;
   }
L2700:
   i = 341;
// 						!FAILS.
   if (play_1.telflg) {
      i = 604;
   }
// 						!GIVE RESPONSE.
   rspeak(i);
L2600:
   play_1.winner = aindex_1.player;
// 						!RESTORE STATE.
   play_1.here = advs_1.aroom[play_1.winner - 1];
   goto L350;

L2150:
   if (aappli(advs_1.aactio[play_1.winner - 1])) {
      goto L2400;
   }
// 						!ACTOR HANDLE?
   if (xvehic(1)) {
      goto L2400;
   }
// 						!VEHICLE HANDLE?
   if (prsvec_1.prso == oindex_1.valua || prsvec_1.prso == oindex_1.every) {
      goto L2900;
   }
   if (!vappli(prsvec_1.prsa)) {
      goto L2400;
   }
// 						!VERB HANDLE?
//L2350:
   f = rappli(rooms_1.ractio[play_1.here - 1]);

L2400:
   xendmv(play_1.telflg);
// 						!DO END OF MOVE.
   goto L2600;
// 						!DONE.

L2900:
   valuac(oindex_1.valua);
// 						!ALL OR VALUABLES.
   goto L350;
}

// Execute end of move functions.
static void xendmv(Bool flag) {
// Local variables
   Bool f;
#if 0
   int x; //(@) Not actually used.
#endif
   if (!(flag)) {
      rspeak(341);
   }
// 						!DEFAULT REMARK.
   if (hack_1.thfact) {
      thiefd();
   }
// 						!THIEF DEMON.
   if (prsvec_1.prswon) {
      fightd();
   }
// 						!FIGHT DEMON.
   if (hack_1.swdact) {
      swordd();
   }
// 						!SWORD DEMON.
   if (prsvec_1.prswon) {
      f = clockd(/*x*/);
   }
// 						!CLOCK DEMON.
   if (prsvec_1.prswon) {
      f = xvehic(2);
   }
// 						!VEHICLE READOUT.
}

// Execute vehicle function
static Bool xvehic(int n) {
// System generated locals
   Bool ret_val;

// Local variables
   int av;

   ret_val = false;
// 						!ASSUME LOSES.
   av = advs_1.avehic[play_1.winner - 1];
// 						!GET VEHICLE.
   if (av != 0) {
      ret_val = oappli(objcts_1.oactio[av - 1], n);
   }
   return ret_val;
}
