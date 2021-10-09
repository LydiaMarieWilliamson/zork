// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <string.h> // For strcmp().
#include "extern.h"
#include "common.h"

static void xendmv(bool);
static bool xvehic(int);

// Main command loop for dungeon
void game_(void) {
// Local variables
   bool f;
   int i;

// GAME, PAGE 2

// START UP, DESCRIBE CURRENT LOCATION.

   rspeak(1);
// 						!WELCOME ABOARD.
   f = rmdesc(3);
// 						!START GAME.

// NOW LOOP, READING AND EXECUTING COMMANDS.

L100:
   play.winner = PlayerAX;
// 						!PLAYER MOVING.
   play.telflg = false;
// 						!ASSUME NOTHING TOLD.
   if (prsvec.prscon <= 1) {
      rdline(input.inbuf, sizeof input.inbuf, 1);
   }

#ifdef ALLOW_GDT
   if (strcmp(&input.inbuf[prsvec.prscon - 1], "GDT") == 0) {
// 						!CALL ON GDT?
      gdt();
// 						!YES, INVOKE.
      goto L100;
// 						!ONWARD.
   }
#endif

   ++state.moves;
   prsvec.prswon = parse(input.inbuf, true);
   if (!prsvec.prswon) {
      goto L400;
   }
// 						!PARSE LOSES?
   if (xvehic(1)) {
      goto L400;
   }
// 						!VEHICLE HANDLE?

   if (prsvec.prsa == TellW) {
      goto L2000;
   }
// 						!TELL?
L300:
   if (prsvec.prso == ValuaOX || prsvec.prso == EveryOX) {
      goto L900;
   }
   if (!vappli(prsvec.prsa)) {
      goto L400;
   }
// 						!VERB OK?
L350:
   if (!findex_0.echof && play.here == EchoRRX) {
      goto L1000;
   }
   f = rappli(rooms.ractio[play.here - 1]);

L400:
   xendmv(play.telflg);
// 						!DO END OF MOVE.
   if (!lit(play.here)) {
      prsvec.prscon = 1;
   }
   goto L100;

L900:
   valuac(ValuaOX);
   goto L350;
// GAME, PAGE 3

// SPECIAL CASE-- ECHO ROOM.
// IF INPUT IS NOT 'ECHO' OR A DIRECTION, JUST ECHO.

L1000:
   rdline(input.inbuf, sizeof input.inbuf, 0);
   ++state.moves;
// 						!CHARGE FOR MOVES.
   if (strcmp(input.inbuf, "ECHO") != 0) goto L1300;
// 						!INPUT = ECHO?

#if 0
// Note:
// ∙	The upper for loop was bound changed from 78 to input.inlnt,
//	because rdline() no longer provides a 78 character buffer padded with blanks.
   for (i = 5; i <= input.inlnt; ++i) {
      if (input.inbuf[i - 1] != ' ') {
         goto L1300;
      }
// L1200:
   }
#endif

   rspeak(571);
// 						!KILL THE ECHO.
   findex_0.echof = true;
   objcts.oflag2[BarOX - 1] &= ~ScrDO;
   prsvec.prswon = true;
// 						!FAKE OUT PARSER.
   prsvec.prscon = 1;
// 						!FORCE NEW INPUT.
   goto L400;

L1300:
   prsvec.prswon = parse(input.inbuf, false);
   if (!prsvec.prswon || prsvec.prsa != WalkW) {
      goto L1400;
   }
   if (findxt(prsvec.prso, play.here)) {
      goto L300;
   }
// 						!VALID EXIT?

L1400:
#if 0
   more_output("%.*s\n", input.inlnt, input.inbuf);
#else
   more_output("%s\n", input.inbuf);
#endif
   play.telflg = true;
// 						!INDICATE OUTPUT.
   goto L1000;
// 						!MORE ECHO ROOM.
// GAME, PAGE 4

// SPECIAL CASE-- TELL <ACTOR>, NEW COMMAND
// NOTE THAT WE CANNOT BE IN THE ECHO ROOM.

L2000:
   if ((objcts.oflag2[prsvec.prso - 1] & ActrO) != 0) {
      goto L2100;
   }
   rspeak(602);
// 						!CANT DO IT.
   goto L350;
// 						!VAPPLI SUCCEEDS.

L2100:
   play.winner = oactor(prsvec.prso);
// 						!NEW PLAYER.
   play.here = advs.aroom[play.winner - 1];
// 						!NEW LOCATION.
   if (prsvec.prscon <= 1) {
      goto L2700;
   }
// 						!ANY INPUT?
   if (parse(input.inbuf, true)) {
      goto L2150;
   }
L2700:
   i = 341;
// 						!FAILS.
   if (play.telflg) {
      i = 604;
   }
// 						!GIVE RESPONSE.
   rspeak(i);
L2600:
   play.winner = PlayerAX;
// 						!RESTORE STATE.
   play.here = advs.aroom[play.winner - 1];
   goto L350;

L2150:
   if (aappli(advs.aactio[play.winner - 1])) {
      goto L2400;
   }
// 						!ACTOR HANDLE?
   if (xvehic(1)) {
      goto L2400;
   }
// 						!VEHICLE HANDLE?
   if (prsvec.prso == ValuaOX || prsvec.prso == EveryOX) {
      goto L2900;
   }
   if (!vappli(prsvec.prsa)) {
      goto L2400;
   }
// 						!VERB HANDLE?
//L2350:
   f = rappli(rooms.ractio[play.here - 1]);

L2400:
   xendmv(play.telflg);
// 						!DO END OF MOVE.
   goto L2600;
// 						!DONE.

L2900:
   valuac(ValuaOX);
// 						!ALL OR VALUABLES.
   goto L350;
}

// Execute end of move functions.
static void xendmv(bool flag) {
// Local variables
   bool f;

   if (!(flag)) {
      rspeak(341);
   }
// 						!DEFAULT REMARK.
   if (hack.thfact) {
      thiefd();
   }
// 						!THIEF DEMON.
   if (prsvec.prswon) {
      fightd();
   }
// 						!FIGHT DEMON.
   if (hack.swdact) {
      swordd();
   }
// 						!SWORD DEMON.
   if (prsvec.prswon) {
      f = clockd();
   }
// 						!CLOCK DEMON.
   if (prsvec.prswon) {
      f = xvehic(2);
   }
// 						!VEHICLE READOUT.
}

// Execute vehicle function
static bool xvehic(int n) {
// System generated locals
   bool ret_val;

// Local variables
   int av;

   ret_val = false;
// 						!ASSUME LOSES.
   av = advs.avehic[play.winner - 1];
// 						!GET VEHICLE.
   if (av != 0) {
      ret_val = oappli(objcts.oactio[av - 1], n);
   }
   return ret_val;
}
