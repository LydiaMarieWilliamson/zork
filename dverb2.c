// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <stdio.h>
#include "extern.h"
#include "common.h"

static int cxappl(int);

// Save game state
void savegm(void) {
   prsvec_1.prswon = false;
// 						!DISABLE GAME.
// Note: save file format is different for PDP versus non-PDP versions

// open(unit:1, file:"dsave.dat", access:"SEQUENTIAL", status:"UNKNOWN", form:"UNFORMATTED", err:L100); //F
   FILE *ExF = fopen("dsave.dat", BINWRITE); if (ExF == NULL) goto L100;

   int PlTime = gttime();
// 						!GET TIME.

#define PutVar(Var) (fwrite((const void *)&(Var), sizeof (Var), (1), (ExF)))
#define PutArr(N, Buf) (fwrite((const void *)(Buf), sizeof (Buf)[0], (N), (ExF)))

// write(1, vers_1.vmaj, vers_1.vmin, vers_1.vedit); //F
{  int Edit = vers_1.vedit; PutVar(vers_1.vmaj), PutVar(vers_1.vmin), PutVar(Edit); }
// write(1, //F
//    play_1.winner, play_1.here, hack_1.thfpos, play_1.telflg, hack_1.thfflg, hack_1.thfact, //F
//    hack_1.swdact, hack_1.swdsta, puzzle_1.cpvec //F
// ); //F
   PutVar(play_1.winner), PutVar(play_1.here), PutVar(hack_1.thfpos);
   PutVar(play_1.telflg), PutVar(hack_1.thfflg), PutVar(hack_1.thfact);
   PutVar(hack_1.swdact), PutVar(hack_1.swdsta), PutArr(64, puzzle_1.cpvec);
// write(1, //F
//    PlTime, state_1.moves, state_1.deaths, state_1.rwscor, state_1.egscor, state_1.mxload, //F
//    state_1.ltshft, state_1.bloc, state_1.mungrm, state_1.hs, screen_1.fromdr, screen_1.scolrm, screen_1.scolac //F
// ); //F
   PutVar(PlTime), PutVar(state_1.moves), PutVar(state_1.deaths), PutVar(state_1.rwscor);
   PutVar(state_1.egscor), PutVar(state_1.mxload);
   PutVar(state_1.ltshft), PutVar(state_1.bloc), PutVar(state_1.mungrm), PutVar(state_1.hs), PutVar(screen_1.fromdr);
   PutVar(screen_1.scolrm), PutVar(screen_1.scolac);
// write(1, //F
//   objcts_1.odesc1, objcts_1.odesc2, objcts_1.oflag1, objcts_1.oflag2, objcts_1.ofval, objcts_1.otval, //F
//   objcts_1.osize, objcts_1.ocapac, objcts_1.oroom, objcts_1.oadv, objcts_1.ocan //F
// ); //F
   PutArr(220, objcts_1.odesc1), PutArr(220, objcts_1.odesc2), PutArr(220, objcts_1.oflag1), PutArr(220, objcts_1.oflag2);
   PutArr(220, objcts_1.ofval), PutArr(220, objcts_1.otval);
   PutArr(220, objcts_1.osize), PutArr(220, objcts_1.ocapac);
   PutArr(220, objcts_1.oroom), PutArr(220, objcts_1.oadv), PutArr(220, objcts_1.ocan);
// write(1, rooms_1.rval, rooms_1.rflag); //F
   PutArr(200, rooms_1.rval), PutArr(200, rooms_1.rflag);
// write(1, advs_1.aroom, advs_1.ascore, advs_1.avehic, advs_1.astren, advs_1.aflag); //F
   PutArr(4, advs_1.aroom), PutArr(4, advs_1.ascore), PutArr(4, advs_1.avehic), PutArr(4, advs_1.astren), PutArr(4, advs_1.aflag);
// write(1, flags, switch_, vill_1.vprob, cevent_1.cflag, cevent_1.ctick); //F
   PutArr(46, flags), PutArr(22, switch_), PutArr(4, vill_1.vprob), PutArr(25, cevent_1.cflag), PutArr(25, cevent_1.ctick);

// close(unit:1); //F
   if (fclose(ExF) == EOF) goto L100;
   rspeak(597);
   return;

L100:
   rspeak(598);
// 						!CANT DO IT.
}

// Restore game state
void rstrgm(void) {
   prsvec_1.prswon = false;
// 						!DISABLE GAME.
// Note: save file format is different for PDP versus non-PDP versions

// open(unit:1, file:"dsave.dat", access:"SEQUENTIAL", status:"OLD", form:"UNFORMATTED", err:L100); //F
   FILE *InF = fopen("dsave.dat", BINREAD); if (InF == NULL) goto L100;

#define GetVar(Var) (fread((void *)&(Var), sizeof (Var), (1), (InF)))
#define GetArr(N, Buf) (fread((void *)(Buf), sizeof (Buf)[0], (N), (InF)))

// read(1, &Maj, &Min, &Edit); //F
   int Maj, Min, Edit; GetVar(Maj), GetVar(Min), GetVar(Edit);
   if (Maj != vers_1.vmaj || Min != vers_1.vmin) goto L200;

// read(1, //F
//    &play_1.winner, &play_1.here, &hack_1.thfpos, &play_1.telflg, &play_1.thfflg, &hack_1.thfflg, //F
//    &hack_1.swdact, &hack_1.swdsta, &puzzle_1.cpvec //F
// ); //F
   GetVar(play_1.winner), GetVar(play_1.here), GetVar(hack_1.thfpos);
   GetVar(play_1.telflg), GetVar(hack_1.thfflg), GetVar(hack_1.thfact);
   GetVar(hack_1.swdact), GetVar(hack_1.swdsta), GetArr(64, puzzle_1.cpvec);
// read(1, //F
//    &time_1.pltime, &state_1.moves, &state_1.deaths, &state_1.rwscor, &state_1.egscor, &state_1.mxload, //F
//    &state_1.ltshft, &state_1.bloc, &state_1.mungrm, &state_1.hs, &state_1.fromdr, &state_1.scolrm, &state_1.scolac //F
// ); //F
   GetVar(time_1.pltime), GetVar(state_1.moves), GetVar(state_1.deaths), GetVar(state_1.rwscor);
   GetVar(state_1.egscor), GetVar(state_1.mxload);
   GetVar(state_1.ltshft), GetVar(state_1.bloc), GetVar(state_1.mungrm), GetVar(state_1.hs), GetVar(screen_1.fromdr);
   GetVar(screen_1.scolrm), GetVar(screen_1.scolac);
// read(1, //F
//    &objcts_1.odesc1, &objcts_1.odesc2, &objcts_1.oflag1, &objcts_1.oflag2, &objcts_1.ofval, &objcts_1.otval, //F
//    &objcts_1.osize, &objcts_1.ocapac, &objcts_1.oroom, &objcts_1.oadv, &objcts_1.ocan //F
// ); //F
   GetArr(220, objcts_1.odesc1), GetArr(220, objcts_1.odesc2), GetArr(220, objcts_1.oflag1), GetArr(220, objcts_1.oflag2);
   GetArr(220, objcts_1.ofval), GetArr(220, objcts_1.otval);
   GetArr(220, objcts_1.osize), GetArr(220, objcts_1.ocapac);
   GetArr(220, objcts_1.oroom), GetArr(220, objcts_1.oadv), GetArr(220, objcts_1.ocan);
// read(1, rooms_1.rval, rooms_1.rflag); //F
   GetArr(200, rooms_1.rval), GetArr(200, rooms_1.rflag);
// read(1, &advs_1.aroom, &advs_1.ascore, &advs_1.avehic, &advs_1.astren, &advs_1.aflag); //F
   GetArr(4, advs_1.aroom), GetArr(4, advs_1.ascore), GetArr(4, advs_1.avehic), GetArr(4, advs_1.astren), GetArr(4, advs_1.aflag);
// read(1, flags, switch_, &vill_1.vprob, cevent_1.cflag, cevent_1.ctick); //F
   GetArr(46, flags), GetArr(22, switch_), GetArr(4, vill_1.vprob), GetArr(25, cevent_1.cflag), GetArr(25, cevent_1.ctick);

// close(unit:1); //F
   (void)fclose(InF);
   rspeak(599);
   return;

L100:
   rspeak(598);
// 						!CANT DO IT.
   return;

L200:
   rspeak(600);
// 						!OBSOLETE VERSION
// close(unit:1); //F
   (void)fclose(InF);
}

// Move in specified direction
Bool walk(/*int x*/) {
// System generated locals
   Bool ret_val;

// WALK, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (play_1.winner != aindex_1.player || lit(play_1.here) || prob(25, 25)) {
      goto L500;
   }
   if (!findxt(prsvec_1.prso, play_1.here)) {
      goto L450;
   }
// 						!INVALID EXIT? GRUE
// 						!
   switch (curxt_1.xtype) {
      case 1:
         goto L400;
      case 2:
         goto L200;
      case 3:
         goto L100;
      case 4:
         goto L300;
   }
// 						!DECODE EXIT TYPE.
   bug(9, curxt_1.xtype);

L100:
   if (cxappl(curxt_1.xactio) != 0) {
      goto L400;
   }
// 						!CEXIT... RETURNED ROOM?
   if (flags[*xflag - 1]) {
      goto L400;
   }
// 						!NO, FLAG ON?
L200:
   jigsup(523);
// 						!BAD EXIT, GRUE
// 						!
   return ret_val;

L300:
   if (cxappl(curxt_1.xactio) != 0) {
      goto L400;
   }
// 						!DOOR... RETURNED ROOM?
   if ((objcts_1.oflag2[curxt_1.xobj - 1] & OpenO) != 0) {
      goto L400;
   }
// 						!NO, DOOR OPEN?
   jigsup(523);
// 						!BAD EXIT, GRUE
// 						!
   return ret_val;

L400:
   if (lit(curxt_1.xroom1)) {
      goto L900;
   }
// 						!VALID ROOM, IS IT LIT?
L450:
   jigsup(522);
// 						!NO, GRUE
// 						!
   return ret_val;

// ROOM IS LIT, OR WINNER IS NOT PLAYER (NO GRUE).

L500:
   if (findxt(prsvec_1.prso, play_1.here)) {
      goto L550;
   }
// 						!EXIT EXIST?
L525:
   curxt_1.xstrng = 678;
// 						!ASSUME WALL.
   if (prsvec_1.prso == xsrch_1.xup) {
      curxt_1.xstrng = 679;
   }
// 						!IF UP, CANT.
   if (prsvec_1.prso == xsrch_1.xdown) {
      curxt_1.xstrng = 680;
   }
// 						!IF DOWN, CANT.
   if ((rooms_1.rflag[play_1.here - 1] & NWallR) != 0) {
      curxt_1.xstrng = 524;
   }
   rspeak(curxt_1.xstrng);
   prsvec_1.prscon = 1;
// 						!STOP CMD STREAM.
   return ret_val;

L550:
   switch (curxt_1.xtype) {
      case 1:
         goto L900;
      case 2:
         goto L600;
      case 3:
         goto L700;
      case 4:
         goto L800;
   }
// 						!BRANCH ON EXIT TYPE.
   bug(9, curxt_1.xtype);

L700:
   if (cxappl(curxt_1.xactio) != 0) {
      goto L900;
   }
// 						!CEXIT... RETURNED ROOM?
   if (flags[*xflag - 1]) {
      goto L900;
   }
// 						!NO, FLAG ON?
L600:
   if (curxt_1.xstrng == 0) {
      goto L525;
   }
// 						!IF NO REASON, USE STD.
   rspeak(curxt_1.xstrng);
// 						!DENY EXIT.
   prsvec_1.prscon = 1;
// 						!STOP CMD STREAM.
   return ret_val;

L800:
   if (cxappl(curxt_1.xactio) != 0) {
      goto L900;
   }
// 						!DOOR... RETURNED ROOM?
   if ((objcts_1.oflag2[curxt_1.xobj - 1] & OpenO) != 0) {
      goto L900;
   }
// 						!NO, DOOR OPEN?
   if (curxt_1.xstrng == 0) {
      curxt_1.xstrng = 525;
   }
// 						!IF NO REASON, USE STD.
   rspsub(curxt_1.xstrng, objcts_1.odesc2[curxt_1.xobj - 1]);
   prsvec_1.prscon = 1;
// 						!STOP CMD STREAM.
   return ret_val;

L900:
   ret_val = moveto(curxt_1.xroom1, play_1.winner);
// 						!MOVE TO ROOM.
   if (ret_val) {
      ret_val = rmdesc(0);
   }
// 						!DESCRIBE ROOM.
   return ret_val;
}

// Conditional exit processors
static int cxappl(int ri) {
// System generated locals
   int ret_val, i__1;

// Local variables
   int i, j, k;
   int nxt;
   int ldir;

// CXAPPL, PAGE 2

   ret_val = 0;
// 						!NO RETURN.
   if (ri == 0) {
      return ret_val;
   }
// 						!IF NO ACTION, DONE.
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
   }
   bug(5, ri);

// C1- COFFIN-CURE

L1000:
   findex_1.egyptf = objcts_1.oadv[oindex_1.coffi - 1] != play_1.winner;
// 						!T IF NO COFFIN.
   return ret_val;

// C2- CAROUSEL EXIT
// C5- CAROUSEL OUT

L2000:
   if (findex_1.caroff) {
      return ret_val;
   }
// 						!IF FLIPPED, NOTHING.
L2500:
   rspeak(121);
// 						!SPIN THE COMPASS.
L5000:
   i = xpars_1.xelnt[xpars_1.xcond - 1] * rnd(8);
// 						!CHOOSE RANDOM EXIT.
   curxt_1.xroom1 = exits_1.travel[rooms_1.rexit[play_1.here - 1] + i - 1] & xpars_1.xrmask;
   ret_val = curxt_1.xroom1;
// 						!RETURN EXIT.
   return ret_val;

// C3- CHIMNEY FUNCTION

L3000:
   findex_1.litldf = false;
// 						!ASSUME HEAVY LOAD.
   j = 0;
   i__1 = objcts_1.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!COUNT OBJECTS.
      if (objcts_1.oadv[i - 1] == play_1.winner) {
         ++j;
      }
// L3100:
   }

   if (j > 2) {
      return ret_val;
   }
// 						!CARRYING TOO MUCH?
   curxt_1.xstrng = 446;
// 						!ASSUME NO LAMP.
   if (objcts_1.oadv[oindex_1.lamp - 1] != play_1.winner) {
      return ret_val;
   }
// 						!NO LAMP?
   findex_1.litldf = true;
// 						!HE CAN DO IT.
   if ((objcts_1.oflag2[oindex_1.door - 1] & OpenO) == 0) {
      objcts_1.oflag2[oindex_1.door - 1] &= ~TChO;
   }
   return ret_val;

// C4-	FROBOZZ FLAG (MAGNET ROOM, FAKE EXIT)
// C6-	FROBOZZ FLAG (MAGNET ROOM, REAL EXIT)

L4000:
   if (findex_1.caroff) {
      goto L2500;
   }
// 						!IF FLIPPED, GO SPIN.
   findex_1.frobzf = false;
// 						!OTHERWISE, NOT AN EXIT.
   return ret_val;

L6000:
   if (findex_1.caroff) {
      goto L2500;
   }
// 						!IF FLIPPED, GO SPIN.
   findex_1.frobzf = true;
// 						!OTHERWISE, AN EXIT.
   return ret_val;

// C7-	FROBOZZ FLAG (BANK ALARM)

L7000:
   findex_1.frobzf = objcts_1.oroom[oindex_1.bills - 1] != 0 && objcts_1.oroom[oindex_1.portr - 1] != 0;
   return ret_val;
// CXAPPL, PAGE 3

// C8-	FROBOZZ FLAG (MRGO)

L8000:
   findex_1.frobzf = false;
// 						!ASSUME CANT MOVE.
   if (findex_1.mloc != curxt_1.xroom1) {
      goto L8100;
   }
// 						!MIRROR IN WAY?
   if (prsvec_1.prso == xsrch_1.xnorth || prsvec_1.prso == xsrch_1.xsouth) {
      goto L8200;
   }
   if (findex_1.mdir % 180 != 0) {
      goto L8300;
   }
// 						!MIRROR MUST BE N-S.
   curxt_1.xroom1 = (curxt_1.xroom1 - rindex_1.mra << 1) + rindex_1.mrae;
// 						!CALC EAST ROOM.
   if (prsvec_1.prso > xsrch_1.xsouth) {
      ++curxt_1.xroom1;
   }
// 						!IF SW/NW, CALC WEST.
L8100:
   ret_val = curxt_1.xroom1;
   return ret_val;

L8200:
   curxt_1.xstrng = 814;
// 						!ASSUME STRUC BLOCKS.
   if (findex_1.mdir % 180 == 0) {
      return ret_val;
   }
// 						!IF MIRROR N-S, DONE.
L8300:
   ldir = findex_1.mdir;
// 						!SEE WHICH MIRROR.
   if (prsvec_1.prso == xsrch_1.xsouth) {
      ldir = 180;
   }
   curxt_1.xstrng = 815;
// 						!MIRROR BLOCKS.
   if (ldir > 180 && !findex_1.mr1f || ldir < 180 && !findex_1.mr2f) {
      curxt_1.xstrng = 816;
   }
   return ret_val;

// C9-	FROBOZZ FLAG (MIRIN)

L9000:
   if (mrhere(play_1.here) != 1) {
      goto L9100;
   }
// 						!MIRROR 1 HERE?
   if (findex_1.mr1f) {
      curxt_1.xstrng = 805;
   }
// 						!SEE IF BROKEN.
   findex_1.frobzf = findex_1.mropnf;
// 						!ENTER IF OPEN.
   return ret_val;

L9100:
   findex_1.frobzf = false;
// 						!NOT HERE,
   curxt_1.xstrng = 817;
// 						!LOSE.
   return ret_val;
// CXAPPL, PAGE 4

// C10-	FROBOZZ FLAG (MIRROR EXIT)

L10000:
   findex_1.frobzf = false;
// 						!ASSUME CANT.
   ldir = (prsvec_1.prso - xsrch_1.xnorth) / xsrch_1.xnorth * 45;
// 						!XLATE DIR TO DEGREES.
   if (!findex_1.mropnf || (findex_1.mdir + 270) % 360 != ldir && prsvec_1.prso != xsrch_1.xexit) {
      goto L10200;
   }
   curxt_1.xroom1 = (findex_1.mloc - rindex_1.mra << 1) + rindex_1.mrae + 1 - findex_1.mdir / 180;
// 						!ASSUME E-W EXIT.
   if (findex_1.mdir % 180 == 0) {
      goto L10100;
   }
// 						!IF N-S, OK.
   curxt_1.xroom1 = findex_1.mloc + 1;
// 						!ASSUME N EXIT.
   if (findex_1.mdir > 180) {
      curxt_1.xroom1 = findex_1.mloc - 1;
   }
// 						!IF SOUTH.
L10100:
   ret_val = curxt_1.xroom1;
   return ret_val;

L10200:
   if (!findex_1.wdopnf || (findex_1.mdir + 180) % 360 != ldir && prsvec_1.prso != xsrch_1.xexit) {
      return ret_val;
   }
   curxt_1.xroom1 = findex_1.mloc + 1;
// 						!ASSUME N.
   if (findex_1.mdir == 0) {
      curxt_1.xroom1 = findex_1.mloc - 1;
   }
// 						!IF S.
   rspeak(818);
// 						!CLOSE DOOR.
   findex_1.wdopnf = false;
   ret_val = curxt_1.xroom1;
   return ret_val;

// C11-	MAYBE DOOR.  NORMAL MESSAGE IS THAT DOOR IS CLOSED.
// 	BUT IF LCELL.NE.4, DOOR ISNT THERE.

L11000:
   if (findex_1.lcell != 4) {
      curxt_1.xstrng = 678;
   }
// 						!SET UP MSG.
   return ret_val;

// C12-	FROBZF (PUZZLE ROOM MAIN ENTRANCE)

L12000:
   findex_1.frobzf = true;
// 						!ALWAYS ENTER.
   findex_1.cphere = 10;
// 						!SET SUBSTATE.
   return ret_val;

// C13-	CPOUTF (PUZZLE ROOM SIZE ENTRANCE)

L13000:
   findex_1.cphere = 52;
// 						!SET SUBSTATE.
   return ret_val;
// CXAPPL, PAGE 5

// C14-	FROBZF (PUZZLE ROOM TRANSITIONS)

L14000:
   findex_1.frobzf = false;
// 						!ASSSUME LOSE.
   if (prsvec_1.prso != xsrch_1.xup) {
      goto L14100;
   }
// 						!UP?
   if (findex_1.cphere != 10) {
      return ret_val;
   }
// 						!AT EXIT?
   curxt_1.xstrng = 881;
// 						!ASSUME NO LADDER.
   if (puzzle_1.cpvec[findex_1.cphere] != -2) {
      return ret_val;
   }
// 						!LADDER HERE?
   rspeak(882);
// 						!YOU WIN.
   findex_1.frobzf = true;
// 						!LET HIM OUT.
   return ret_val;

L14100:
   if (findex_1.cphere != 52 || prsvec_1.prso != xsrch_1.xwest || !findex_1.cpoutf) {
      goto L14200;
   }
   findex_1.frobzf = true;
// 						!YES, LET HIM OUT.
   return ret_val;

L14200:
   for (i = 1; i <= 16; i += 2) {
// 						!LOCATE EXIT.
      if (prsvec_1.prso == puzzle_1.cpdr[i - 1]) {
         goto L14400;
      }
// L14300:
   }
   return ret_val;
// 						!NO SUCH EXIT.

L14400:
   j = puzzle_1.cpdr[i];
// 						!GET DIRECTIONAL OFFSET.
   nxt = findex_1.cphere + j;
// 						!GET NEXT STATE.
   k = 8;
// 						!GET ORTHOGONAL DIR.
   if (j < 0) {
      k = -8;
   }
   if ((abs(j) == 1 || abs(j) == 8 || (puzzle_1.cpvec[findex_1.cphere + k - 1] == 0 || puzzle_1.cpvec[nxt - k - 1] == 0)) && puzzle_1.cpvec[nxt - 1] == 0) {
      goto L14500;
   }
   return ret_val;

L14500:
   cpgoto(nxt);
// 						!MOVE TO STATE.
   curxt_1.xroom1 = rindex_1.cpuzz;
// 						!STAY IN ROOM.
   ret_val = curxt_1.xroom1;
   return ret_val;
}
