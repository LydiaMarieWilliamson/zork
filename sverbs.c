// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Simple verbs processor
// All verbs in this routine must be independent of object actions
bool sverbs(int ri) {
// Initialized data
   const int mxnop = 39;
   const int mxjoke = 64;
   static const int jokes[25] = {
      4, 5, 3, 304, 305, 306, 307, 308, 309, 310, 311, 312,
      313, 5314, 5319, 324, 325, 883, 884, 120, 120, 0, 0, 0, 0
   };
   static const int answer[14] = {
      0, 1, 2, 3, 4, 4, 4, 4, 5, 5, 5, 6, 7, 7
   };
   static const char *const ansstr[14] = {
      "TEMPLE", "FOREST", "30003", "FLASK", "RUB", "FONDLE", "CARRES",
      "TOUCH", "BONES", "BODY", "SKELE", "RUSTYKNIFE", "NONE", "NOWHER"
   };

// System generated locals
   int i__1, i__2;
   bool ret_val;

// Local variables
   bool f;
   int i, j;
   int k;
   int l;
   char ch[1 * 6];
   int cp, wp;
   char pp1[1 * 6], pp2[1 * 6];
   int odi2 = 0, odo2 = 0;

// SVERBS, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (prsvec.prso != 0) {
      odo2 = objcts.odesc2[prsvec.prso - 1];
   }
// 						!SET UP DESCRIPTORS.
   if (prsvec.prsi != 0) {
      odi2 = objcts.odesc2[prsvec.prsi - 1];
   }

   if (ri == 0) {
      bug(7, ri);
   }
// 						!ZERO IS VERBOTEN.
   if (ri <= mxnop) {
      return ret_val;
   }
// 						!NOP?
   if (ri <= mxjoke) {
      goto L100;
   }
// 						!JOKE?
   switch (ri - mxjoke) {
      case 1:
         goto L65000;
      case 2:
         goto L66000;
      case 3:
         goto L67000;
      case 4:
         goto L68000;
      case 5:
         goto L69000;
      case 6:
         goto L1000;
      case 7:
         goto L2000;
      case 8:
         goto L3000;
      case 9:
         goto L4000;
      case 10:
         goto L5000;
      case 11:
         goto L6000;
      case 12:
         goto L7000;
      case 13:
         goto L8000;
      case 14:
         goto L9000;
      case 15:
         goto L10000;
      case 16:
         goto L11000;
      case 17:
         goto L12000;
      case 18:
         goto L13000;
      case 19:
         goto L14000;
      case 20:
         goto L15000;
      case 21:
         goto L16000;
      case 22:
         goto L17000;
      case 23:
         goto L18000;
      case 24:
         goto L19000;
      case 25:
         goto L20000;
      case 26:
         goto L21000;
      case 27:
         goto L22000;
      case 28:
         goto L23000;
      case 29:
         goto L24000;
      case 30:
         goto L25000;
      case 31:
         goto L26000;
      case 32:
         goto L27000;
   }
   bug(7, ri);

// ALL VERB PROCESSORS RETURN HERE TO DECLARE FAILURE.

//L10:
   ret_val = false;
// 						!LOSE.
   return ret_val;

// JOKE PROCESSOR.
// FIND PROPER ENTRY IN JOKES, USE IT TO SELECT STRING TO PRINT.

L100:
   i = jokes[ri - mxnop - 1];
// 						!GET TABLE ENTRY.
   j = i / 1000;
// 						!ISOLATE # STRINGS.
   if (j != 0) {
      i = i % 1000 + rnd(j);
   }
// 						!IF RANDOM, CHOOSE.
   rspeak(i);
// 						!PRINT JOKE.
   return ret_val;
// SVERBS, PAGE 2A

// V65--	ROOM

L65000:
   ret_val = rmdesc(2);
// 						!DESCRIBE ROOM ONLY.
   return ret_val;

// V66--	OBJECTS

L66000:
   ret_val = rmdesc(1);
// 						!DESCRIBE OBJ ONLY.
   if (!play.telflg) {
      rspeak(138);
   }
// 						!NO OBJECTS.
   return ret_val;

// V67--	RNAME

L67000:
   i__1 = rooms.rdesc2[play.here - 1];
   rspeak(i__1);
// 						!SHORT ROOM NAME.
   return ret_val;

// V68--	RESERVED

L68000:
   return ret_val;

// V69--	RESERVED

L69000:
   return ret_val;
// SVERBS, PAGE 3

// V70--	BRIEF.  SET FLAG.

L1000:
   findex_0.brieff = true;
// 						!BRIEF DESCRIPTIONS.
   findex_0.superf = false;
   rspeak(326);
   return ret_val;

// V71--	VERBOSE.  CLEAR FLAGS.

L2000:
   findex_0.brieff = false;
// 						!LONG DESCRIPTIONS.
   findex_0.superf = false;
   rspeak(327);
   return ret_val;

// V72--	SUPERBRIEF.  SET FLAG.

L3000:
   findex_0.superf = true;
   rspeak(328);
   return ret_val;

// V73-- STAY (USED IN ENDGAME).

L4000:
   if (play.winner != MastrAX) {
      goto L4100;
   }
// 						!TELL MASTER, STAY.
   rspeak(781);
// 						!HE DOES.
   cevent.ctick[FolCX - 1] = 0;
// 						!NOT FOLLOWING.
   return ret_val;

L4100:
   if (play.winner == PlayerAX) {
      rspeak(664);
   }
// 						!JOKE.
   return ret_val;

// V74--	VERSION.  PRINT INFO.

L5000:
   more_output("V%1d.%1d%c\n", vmaj, vmin, (int)vedit);
   play.telflg = true;
   return ret_val;

// V75--	SWIM.  ALWAYS A JOKE.

L6000:
   i = 330;
// 						!ASSUME WATER.
   if ((rooms.rflag[play.here - 1] & WaterR + FillR) == 0) {
      i = rnd(3) + 331;
   }
   rspeak(i);
   return ret_val;

// V76--	GERONIMO.  IF IN BARREL, FATAL, ELSE JOKE.

L7000:
   if (play.here == MBarrRX) {
      goto L7100;
   }
// 						!IN BARREL?
   rspeak(334);
// 						!NO, JOKE.
   return ret_val;

L7100:
   jigsup(335);
// 						!OVER FALLS.
   return ret_val;

// V77--	SINBAD ET AL.  CHASE CYCLOPS, ELSE JOKE.

L8000:
   if (play.here == MCyclRX && qhere(CycloOX, play.here)) {
      goto L8100;
   }
   rspeak(336);
// 						!NOT HERE, JOKE.
   return ret_val;

L8100:
   newsta(CycloOX, 337, 0, 0, 0);
// 						!CYCLOPS FLEES.
   findex_0.cyclof = true;
// 						!SET ALL FLAGS.
   findex_0.magicf = true;
   objcts.oflag2[CycloOX - 1] &= ~FiteO;
   return ret_val;

// V78--	WELL.  OPEN DOOR, ELSE JOKE.

L9000:
   if (findex_0.riddlf || play.here != RiddlRX) {
      goto L9100;
   }
// 						!IN RIDDLE ROOM?
   findex_0.riddlf = true;
// 						!YES, SOLVED IT.
   rspeak(338);
   return ret_val;

L9100:
   rspeak(339);
// 						!WELL, WHAT?
   return ret_val;

// V79--	PRAY.  IF IN TEMP2, POOF
// 						!

L10000:
   if (play.here != Temp2RX) {
      goto L10050;
   }
// 						!IN TEMPLE?
   if (moveto(Fore1RX, play.winner)) {
      goto L10100;
   }
// 						!FORE1 STILL THERE?
L10050:
   rspeak(340);
// 						!JOKE.
   return ret_val;

L10100:
   f = rmdesc(3);
// 						!MOVED, DESCRIBE.
   return ret_val;

// V80--	TREASURE.  IF IN TEMP1, POOF
// 						!

L11000:
   if (play.here != Temp1RX) {
      goto L11050;
   }
// 						!IN TEMPLE?
   if (moveto(TreasRX, play.winner)) {
      goto L10100;
   }
// 						!TREASURE ROOM THERE?
L11050:
   rspeak(341);
// 						!NOTHING HAPPENS.
   return ret_val;

// V81--	TEMPLE.  IF IN TREAS, POOF
// 						!

L12000:
   if (play.here != TreasRX) {
      goto L12050;
   }
// 						!IN TREASURE?
   if (moveto(Temp1RX, play.winner)) {
      goto L10100;
   }
// 						!TEMP1 STILL THERE?
L12050:
   rspeak(341);
// 						!NOTHING HAPPENS.
   return ret_val;

// V82--	BLAST.  USUALLY A JOKE.

L13000:
   i = 342;
// 						!DONT UNDERSTAND.
   if (prsvec.prso == SafeOX) {
      i = 252;
   }
// 						!JOKE FOR SAFE.
   rspeak(i);
   return ret_val;

// V83--	SCORE.  PRINT SCORE.

L14000:
   score(false);
   return ret_val;

// V84--	QUIT.  FINISH OUT THE GAME.

L15000:
   score(true);
// 						!TELLL SCORE.
   if (!yesno(343, 0, 0)) {
      return ret_val;
   }
// 						!ASK FOR Y/N DECISION.
   fclose(StoryF);
   exit_();
// 						!BYE.
// SVERBS, PAGE 4

// V85--	FOLLOW (USED IN ENDGAME)

L16000:
   if (play.winner != MastrAX) {
      return ret_val;
   }
// 						!TELL MASTER, FOLLOW.
   rspeak(782);
   cevent.ctick[FolCX - 1] = -1;
// 						!STARTS FOLLOWING.
   return ret_val;

// V86--	WALK THROUGH

L17000:
   if (screen.scolrm == 0 || prsvec.prso != ScolOX && (prsvec.prso != WNortOX || play.here != BkBoxRX)) {
      goto L17100;
   }
   screen.scolac = screen.scolrm;
// 						!WALKED THRU SCOL.
   prsvec.prso = 0;
// 						!FAKE OUT FROMDR.
   cevent.ctick[SclCX - 1] = 6;
// 						!START ALARM.
   rspeak(668);
// 						!DISORIENT HIM.
   f = moveto(screen.scolrm, play.winner);
// 						!INTO ROOM.
   f = rmdesc(3);
// 						!DESCRIBE.
   return ret_val;

L17100:
   if (play.here != screen.scolac) {
      goto L17300;
   }
// 						!ON OTHER SIDE OF SCOL?
   for (i = 1; i <= 12; i += 3) {
// 						!WALK THRU PROPER WALL?
      if (screen.scolwl[i - 1] == play.here && screen.scolwl[i] == prsvec.prso) {
         goto L17500;
      }
// L17200:
   }

L17300:
   if ((objcts.oflag1[prsvec.prso - 1] & TakeO) != 0) {
      goto L17400;
   }
   i = 669;
// 						!NO, JOKE.
   if (prsvec.prso == ScolOX) {
      i = 670;
   }
// 						!SPECIAL JOKE FOR SCOL.
   rspsub(i, odo2);
   return ret_val;

L17400:
   i = 671;
// 						!JOKE.
   if (objcts.oroom[prsvec.prso - 1] != 0) {
      i = rnd(5) + 552;
   }
// 						!SPECIAL JOKES IF CARRY.
   rspeak(i);
   return ret_val;

L17500:
   prsvec.prso = screen.scolwl[i + 1];
// 						!THRU SCOL WALL...
   for (i = 1; i <= 8; i += 2) {
// 						!FIND MATCHING ROOM.
      if (prsvec.prso == screen.scoldr[i - 1]) {
         screen.scolrm = screen.scoldr[i];
      }
// L17600:
   }
// 						!DECLARE NEW SCOLRM.
   cevent.ctick[SclCX - 1] = 0;
// 						!CANCEL ALARM.
   rspeak(668);
// 						!DISORIENT HIM.
   f = moveto(BkBoxRX, play.winner);
// 						!BACK IN BOX ROOM.
   f = rmdesc(3);
   return ret_val;

// V87--	RING.  A JOKE.

L18000:
   i = 359;
// 						!CANT RING.
   if (prsvec.prso == BellOX) {
      i = 360;
   }
// 						!DING, DONG.
   rspeak(i);
// 						!JOKE.
   return ret_val;

// V88--	BRUSH.  JOKE WITH OBSCURE TRAP.

L19000:
   if (prsvec.prso == TeethOX) {
      goto L19100;
   }
// 						!BRUSH TEETH?
   rspeak(362);
// 						!NO, JOKE.
   return ret_val;

L19100:
   if (prsvec.prsi != 0) {
      goto L19200;
   }
// 						!WITH SOMETHING?
   rspeak(363);
// 						!NO, JOKE.
   return ret_val;

L19200:
   if (prsvec.prsi == PuttyOX && objcts.oadv[PuttyOX - 1] == play.winner) {
      goto L19300;
   }
   rspsub(364, odi2);
// 						!NO, JOKE.
   return ret_val;

L19300:
   jigsup(365);
// 						!YES, DEAD
// 						!
// 						!
// 						!
// 						!
// 						!
   return ret_val;
// SVERBS, PAGE 5

// V89--	DIG.  UNLESS SHOVEL, A JOKE.

L20000:
   if (prsvec.prso == ShoveOX) {
      return ret_val;
   }
// 						!SHOVEL?
   i = 392;
// 						!ASSUME TOOL.
   if ((objcts.oflag1[prsvec.prso - 1] & ToolO) == 0) {
      i = 393;
   }
   rspsub(i, odo2);
   return ret_val;

// V90--	TIME.  PRINT OUT DURATION OF GAME.

L21000:
   k = gttime();
// 						!GET PLAY TIME.
   i = k / 60;
   j = k % 60;

   printf("You have been playing Dungeon for ");
   if (i >= 1) printf("%d %s and ", i, i != 1 ? "hours" : "hour");
   more_output("%d %s.\n", j, j != 1 ? "minutes" : "minute");
   play.telflg = true;
   return ret_val;

// V91--	LEAP.  USUALLY A JOKE, WITH A CATCH.

L22000:
   if (prsvec.prso == 0) {
      goto L22200;
   }
// 						!OVER SOMETHING?
   if (qhere(prsvec.prso, play.here)) {
      goto L22100;
   }
// 						!HERE?
   rspeak(447);
// 						!NO, JOKE.
   return ret_val;

L22100:
   if ((objcts.oflag2[prsvec.prso - 1] & VillO) == 0) {
      goto L22300;
   }
   rspsub(448, odo2);
// 						!CANT JUMP VILLAIN.
   return ret_val;

L22200:
   if (!findxt(DownDX, play.here)) {
      goto L22300;
   }
// 						!DOWN EXIT?
   if (curxt.xtype == xpars.xno || curxt.xtype == xpars.xcond && !flags[xflag - 1]) {
      goto L22400;
   }
L22300:
   i__1 = rnd(5) + 314;
   rspeak(i__1);
// 						!WHEEEE
// 						!
   return ret_val;

L22400:
   i__1 = rnd(4) + 449;
   jigsup(i__1);
// 						!FATAL LEAP.
   return ret_val;
// SVERBS, PAGE 6

// V92--	LOCK.

L23000:
   if (prsvec.prso == GrateOX && play.here == MGratRX) {
      goto L23200;
   }
L23100:
   rspeak(464);
// 						!NOT LOCK GRATE.
   return ret_val;

L23200:
   findex_0.grunlf = false;
// 						!GRATE NOW LOCKED.
   rspeak(214);
   exits.travel[rooms.rexit[play.here - 1]] = 214;
// 						!CHANGE EXIT STATUS.
   return ret_val;

// V93--	UNLOCK

L24000:
   if (prsvec.prso != GrateOX || play.here != MGratRX) {
      goto L23100;
   }
   if (prsvec.prsi == KeysOX) {
      goto L24200;
   }
// 						!GOT KEYS?
   rspsub(465, odi2);
// 						!NO, JOKE.
   return ret_val;

L24200:
   findex_0.grunlf = true;
// 						!UNLOCK GRATE.
   rspeak(217);
   exits.travel[rooms.rexit[play.here - 1]] = 217;
// 						!CHANGE EXIT STATUS.
   return ret_val;

// V94--	DIAGNOSE.

L25000:
   i = fights(play.winner, false);
// 						!GET FIGHTS STRENGTH.
   j = advs.astren[play.winner - 1];
// 						!GET HEALTH.
// Computing MIN
   i__1 = i + j;
   k = min(i__1, 4);
// 						!GET STATE.
   if (!cevent.cflag[CurCX - 1]) {
      j = 0;
   }
// 						!IF NO WOUNDS.
// Computing MIN
   i__1 = 4, i__2 = abs(j);
   l = min(i__1, i__2);
// 						!SCALE.
   i__1 = l + 473;
   rspeak(i__1);
// 						!DESCRIBE HEALTH.
   i = (-j - 1) * 30 + cevent.ctick[CurCX - 1];
// 						!COMPUTE WAIT.

   if (j != 0) {
      more_output("You will be cured after %d moves.\n", i);
   }

   i__1 = k + 478;
   rspeak(i__1);
// 						!HOW MUCH MORE?
   if (state.deaths != 0) {
      i__1 = state.deaths + 482;
      rspeak(i__1);
   }
// 						!HOW MANY DEATHS?
   return ret_val;
// SVERBS, PAGE 7

// V95--	INCANT

L26000:
   for (i = 1; i <= 6; ++i) {
// 						!SET UP PARSE.
      pp1[i - 1] = ' ';
      pp2[i - 1] = ' ';
// L26100:
   }
   wp = 1;
// 						!WORD POINTER.
   cp = 1;
// 						!CHAR POINTER.
   if (prsvec.prscon <= 1) {
      goto L26300;
   }
   for (const char *z = input.inbuf + prsvec.prscon - 1; *z != '\0'; z++) {
// 						!PARSE INPUT
      if (*z == ',') {
         goto L26300;
      }
// 						!END OF PHRASE?
      if (*z != ' ') {
         goto L26150;
      }
// 						!SPACE?
      if (cp != 1) {
         ++wp;
      }
      cp = 1;
      goto L26200;
   L26150:
      if (wp == 1) {
         pp1[cp - 1] = *z;
      }
// 						!STUFF INTO HOLDER.
      if (wp == 2) {
         pp2[cp - 1] = *z;
      }
// Computing MIN
      i__2 = cp + 1;
      cp = min(i__2, 6);
   L26200:
      ;
   }

L26300:
   prsvec.prscon = 1;
// 						!KILL REST OF LINE.
   if (pp1[0] != ' ') {
      goto L26400;
   }
// 						!ANY INPUT?
   rspeak(856);
// 						!NO, HO HUM.
   return ret_val;

L26400:
   encryp(pp1, ch);
// 						!COMPUTE RESPONSE.
   if (pp2[0] != ' ') {
      goto L26600;
   }
// 						!TWO PHRASES?

   if (findex_0.spellf) {
      goto L26550;
   }
// 						!HE'S TRYING TO LEARN.
// The following line fixes a nice bug in the UNIX version! /+ TAA +/
   if ((rooms.rflag[TStrsRX - 1] & SeenR) == 0) {
      goto L26575;
   }
   findex_0.spellf = true;
// 						!TELL HIM.
   play.telflg = true;
   more_output("A hollow voice replies:  \"%.6s %.6s\".\n", pp1, ch);

   return ret_val;

L26550:
   rspeak(857);
// 						!HE'S GOT ONE ALREADY.
   return ret_val;

L26575:
   rspeak(858);
// 						!HE'S NOT IN ENDGAME.
   return ret_val;

L26600:
   if ((rooms.rflag[TStrsRX - 1] & SeenR) != 0) {
      goto L26800;
   }
   for (i = 1; i <= 6; ++i) {
      if (pp2[i - 1] != ch[i - 1]) {
         goto L26575;
      }
// 						!WRONG.
// L26700:
   }
   findex_0.spellf = true;
// 						!IT WORKS.
   rspeak(859);
   cevent.ctick[SteCX - 1] = 1;
// 						!FORCE START.
   return ret_val;

L26800:
   rspeak(855);
// 						!TOO LATE.
   return ret_val;
// SVERBS, PAGE 8

// V96--	ANSWER

L27000:
   if (prsvec.prscon > 1 && play.here == FDoorRX && findex_0.inqstf) {
      goto L27100;
   }
   rspeak(799);
// 						!NO ONE LISTENS.
   prsvec.prscon = 1;
   return ret_val;

L27100:
   for (j = 1; j <= 14; j++) {
// 						!CHECK ANSWERS.
      if (findex_1.quesno != answer[j - 1]) goto L27300;
// 						!ONLY CHECK PROPER ANS.
      for (const char *z = ansstr[j - 1], *z2 = input.inbuf + prsvec.prscon - 1; *z != '\0'; z++, z2++) {
         for (; *z2 == ' '; z2++);
// 						!SKIP INPUT BLANKS.
         if (*z2 == '\0') goto L27300;
// 						!END OF INPUT? LOSE.
	 else if (*z2 != *z) goto L27300;
   // L27200:
      }
      goto L27500;
// 						!RIGHT ANSWER.
   L27300:
      ;
   }

   prsvec.prscon = 1;
// 						!KILL REST OF LINE.
   ++findex_1.nqatt;
// 						!WRONG, CRETIN.
   if (findex_1.nqatt >= 5) {
      goto L27400;
   }
// 						!TOO MANY WRONG?
   i__1 = findex_1.nqatt + 800;
   rspeak(i__1);
// 						!NO, TRY AGAIN.
   return ret_val;

L27400:
   rspeak(826);
// 						!ALL OVER.
   cevent.cflag[InqCX - 1] = false;
// 						!LOSE.
   return ret_val;

L27500:
   prsvec.prscon = 1;
// 						!KILL REST OF LINE.
   ++findex_1.corrct;
// 						!GOT IT RIGHT.
   rspeak(800);
// 						!HOORAY.
   if (findex_1.corrct >= 3) {
      goto L27600;
   }
// 						!WON TOTALLY?
   cevent.ctick[InqCX - 1] = 2;
// 						!NO, START AGAIN.
   findex_1.quesno = (findex_1.quesno + 3) % 8;
   findex_1.nqatt = 0;
   rspeak(769);
// 						!ASK NEXT QUESTION.
   i__1 = findex_1.quesno + 770;
   rspeak(i__1);
   return ret_val;

L27600:
   rspeak(827);
// 						!QUIZ OVER,
   cevent.cflag[InqCX - 1] = false;
   objcts.oflag2[QDoorOX - 1] |= OpenO;
   return ret_val;
}
