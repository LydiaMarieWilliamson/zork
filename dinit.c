// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <stdio.h>
#ifdef __AMOS__
#   include <amos.h>
#endif
#include "extern.h"
#include "common.h"
#include <stdlib.h> // For srand().

FILE *dbfile;

#ifndef TEXTFILE
#   if defined __AMOS__
#      define TEXTFILE "lib:dtextc.dat"
#   elif defined unix
#      define TEXTFILE "/usr/games/lib/dunlib/dtextc.dat"
#   else
#      error I need a definition for TEXTFILE
#   endif
#endif
#ifndef LOCALTEXTFILE
#   define LOCALTEXTFILE "dtextc.dat"
#endif
// Read a single two byte int from the index file
#define rdint(indxfile) (ch = getc(indxfile), 256*(ch > 127? ch - 256: (ch)) + getc(indxfile))

// Read a number of two byte integers from the index file
static void rdints(int c, int *pi, FILE *indxfile) {
   int ch; // Local variable for rdint

   while (c-- != 0)
      *pi++ = rdint(indxfile);
}

// Read a partial array of integers.
// These are stored as index,value pairs.
static void rdpartialints(int c, int *pi, FILE *indxfile) {
   int ch; // Local variable for rdint

   while (1) {
      int i;

      if (c < 255) {
         i = getc(indxfile);
         if (i == 255)
            return;
      } else {
         i = rdint(indxfile);
         if (i == -1)
            return;
      }

      pi[i] = rdint(indxfile);
   }
}

// Read a number of one byte flags from the index file
static void rdflags(int c, Bool *pf, FILE *indxfile) {
   while (c-- != 0)
      *pf++ = getc(indxfile);
}

// Dungeon initialization subroutine
Bool init(void/*int x*/) {
// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   int xmax, r2max, dirmax, recno;
   int i, j, k;
   register int ch;
   register FILE *indxfile;
   int mmax, omax, rmax, vmax, amax, cmax, fmax, smax;

   more_init();

// INIT, PAGE 2

// FIRST CHECK FOR PROTECTION VIOLATION

   if (protected_()) {
      goto L10000;
   }
// 						!PROTECTION VIOLATION?
// print( //F
//    " There appears before you a threatening figure clad ", //F
//    "all over%/ in heavy black armor.  His legs seem like the ", //F
//    "massive trunk%/ of the oak tree.  His broad shoulders and ", //F
//    "helmeted head loom%/ high over your own puny frame, and ", //F
//    "you realize that his powerful%/ arms could easily crush the ", //F
//    "very life from your body.  There%/ hangs from his belt a ", //F
//    "veritable arsenal of deadly weapons:%/ sword, mace, ball ", //F
//    "and chain, dagger, lance, and trident.%/ He speaks with a ", //F
//    "commanding voice:%/%/%20X\"You shall not pass.\"%/%/ As ", //F
//    "he grabs you by the neck all grows dim about you." //F
// ); //F
   more_output("There appears before you a threatening figure clad all over");
   more_output("in heavy black armor.  His legs seem like the massive trunk");
   more_output("of the oak tree.  His broad shoulders and helmeted head loom");
   more_output("high over your own puny frame, and you realize that his powerful");
   more_output("arms could easily crush the very life from your body.  There");
   more_output("hangs from his belt a veritable arsenal of deadly weapons:");
   more_output("sword, mace, ball and chain, dagger, lance, and trident.");
   more_output("He speaks with a commanding voice:");
   more_output("");
   more_output("                    \"You shall not pass.\"");
   more_output("");
   more_output("As he grabs you by the neck all grows dim about you.");
   exit_();

// NOW START INITIALIZATION PROPER

L10000:
   ret_val = false;
// 						!ASSUME INIT FAILS.
   mmax = 1050;
// 						!SET UP ARRAY LIMITS.
   omax = 220;
   rmax = 200;
   vmax = 4;
   amax = 4;
   cmax = 25;
   fmax = 46;
   smax = 22;
   xmax = 900;
   r2max = 20;
   dirmax = 15;

   rmsg.mlnt = 0;
// 						!INIT ARRAY COUNTERS.
   objcts.olnt = 0;
   rooms.rlnt = 0;
   vill.vlnt = 0;
   advs.alnt = 0;
   cevent.clnt = 0;
   exits.xlnt = 1;
   oroom2_.r2lnt = 0;

   state.ltshft = 10;
// 						!SET UP STATE VARIABLES.
   state.mxscor = state.ltshft;
   state.egscor = 0;
   state.egmxsc = 0;
   state.mxload = 100;
   state.rwscor = 0;
   state.deaths = 0;
   state.moves = 0;
   time_.pltime = 0;
   state.mungrm = 0;
   state.hs = 0;
   prsvec.prsa = 0;
// 						!CLEAR PARSE VECTOR.
   prsvec.prsi = 0;
   prsvec.prso = 0;
   prsvec.prscon = 1;
   orphs.oflag = 0;
// 						!CLEAR ORPHANS.
   orphs.oact = 0;
   orphs.oslot = 0;
   orphs.oprep = 0;
   orphs.oname = 0;
   hack.thfflg = false;
// 						!THIEF NOT INTRODUCED BUT
   hack.thfact = true;
// 						!IS ACTIVE.
   hack.swdact = false;
// 						!SWORD IS INACTIVE.
   hack.swdsta = 0;
// 						!SWORD IS OFF.

   recno = 1;
// 						!INIT DB FILE POINTER.
   star.mbase = 0;
// 						!INIT MELEE BASE.
// INIT, PAGE 3

// INIT ALL ARRAYS.

   i__1 = cmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR CLOCK EVENTS
      cevent.cflag[i - 1] = false;
      cevent.ctick[i - 1] = 0;
      cevent.cactio[i - 1] = 0;
// L5:
   }

   i__1 = fmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR FLAGS.
      flags[i - 1] = false;
// L10:
   }
   findex.buoyf = true;
// 						!SOME START AS TRUE.
   findex.egyptf = true;
   findex.cagetf = true;
   findex.mr1f = true;
   findex.mr2f = true;
   findex.follwf = true;
   i__1 = smax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR SWITCHES.
      switch_[i - 1] = 0;
// L12:
   }
   findex.ormtch = 4;
// 						!NUMBER OF MATCHES.
   findex.lcell = 1;
   findex.pnumb = 1;
   findex.mdir = 270;
   findex.mloc = MrBrX;
   findex.cphere = 10;

   i__1 = r2max;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR ROOM 2 ARRAY.
      oroom2_.rroom2[i - 1] = 0;
      oroom2_.oroom2[i - 1] = 0;
// L15:
   }

   i__1 = xmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR TRAVEL ARRAY.
      exits.travel[i - 1] = 0;
// L20:
   }

   i__1 = vmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR VILLAINS ARRAYS.
      vill.vopps[i - 1] = 0;
      vill.vprob[i - 1] = 0;
      vill.villns[i - 1] = 0;
      vill.vbest[i - 1] = 0;
      vill.vmelee[i - 1] = 0;
// L30:
   }

   i__1 = omax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR OBJECT ARRAYS.
      objcts.odesc1[i - 1] = 0;
      objcts.odesc2[i - 1] = 0;
      objcts.odesco[i - 1] = 0;
      objcts.oread[i - 1] = 0;
      objcts.oactio[i - 1] = 0;
      objcts.oflag1[i - 1] = 0;
      objcts.oflag2[i - 1] = 0;
      objcts.ofval[i - 1] = 0;
      objcts.otval[i - 1] = 0;
      objcts.osize[i - 1] = 0;
      objcts.ocapac[i - 1] = 0;
      objcts.ocan[i - 1] = 0;
      objcts.oadv[i - 1] = 0;
      objcts.oroom[i - 1] = 0;
// L40:
   }

   i__1 = rmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR ROOM ARRAYS.
      rooms.rdesc1[i - 1] = 0;
      rooms.rdesc2[i - 1] = 0;
      rooms.ractio[i - 1] = 0;
      rooms.rflag[i - 1] = 0;
      rooms.rval[i - 1] = 0;
      rooms.rexit[i - 1] = 0;
// L50:
   }

   i__1 = mmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR MESSAGE DIRECTORY.
      rmsg.rtext[i - 1] = 0;
// L60:
   }

   i__1 = amax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR ADVENTURER'S ARRAYS.
      advs.aroom[i - 1] = 0;
      advs.ascore[i - 1] = 0;
      advs.avehic[i - 1] = 0;
      advs.aobj[i - 1] = 0;
      advs.aactio[i - 1] = 0;
      advs.astren[i - 1] = 0;
      advs.aflag[i - 1] = 0;
// L70:
   }

   debug.dbgflg = 0;
   debug.prsflg = 0;

// allow setting gdtflg true if user id matches wizard id
// this way, the wizard doesn't have to recompile to use gdt

#ifdef ALLOW_GDT
// 	Changed by TAA so that always in wizard ID
   debug.gdtflg = wizard();
#else
   debug.gdtflg = 0;
#endif

   screen.fromdr = 0;
// 						!INIT SCOL GOODIES.
   screen.scolrm = 0;
   screen.scolac = 0;
// INIT, PAGE 4

// NOW RESTORE FROM EXISTING INDEX FILE.

#if 0
// open(unit:1,file:"/usr/share/games/dungeon/dindx.dat", //F
//    status:"OLD", form:"FORMATTED", access:"SEQUENTIAL", err:L1900 //F
// ); //F
#else
// open(unit:1,file:"dindx.dat", //F
//    status:"OLD", form:"FORMATTED", access:"SEQUENTIAL", err:L1900 //F
// ); //F
#endif
#ifdef __AMOS__
   if ((dbfile = fdopen(ropen(LOCALTEXTFILE, 0), BINREAD)) == NULL && (dbfile = fdopen(ropen(TEXTFILE, 0), BINREAD)) == NULL)
      goto L1950;
#else
   if ((dbfile = fopen(LOCALTEXTFILE, BINREAD)) == NULL && (dbfile = fopen(TEXTFILE, BINREAD)) == NULL)
      goto L1950;
#endif

   indxfile = dbfile;

// read(1, "%I6", &i, &j, &k); //F
   i = rdint(indxfile), j = rdint(indxfile), k = rdint(indxfile);
// 						!GET VERSION.
   if (i != vmaj || j != vmin) {
      goto L1925;
   }
#if 0
// open(unit:chan.dbch, file:"/usr/share/games/dungeon/dtext.dat", //F
//    status:"old", form:"unformatted", access:"direct", //F
//    recl:76, err:L1950 //F
// ); //F
#else
// open(unit:chan.dbch, file:"dtext.dat", //F
//    status:"old", form:"unformatted", access:"direct", //F
//    recl:76, err:L1950 //F
// ); //F
#endif
#ifdef ALLOW_GDT
// print(" RESTORING FROM \"dindx.dat\""); //F
#endif
// // const char *Fmt = "%I8"; //F
// const char *Fmt = "%I6"; //F
// read(1, Fmt, &state.mxscor, &star.strbit, &state.egmxsc); //F
   state.mxscor = rdint(indxfile), star.strbit = rdint(indxfile), state.egmxsc = rdint(indxfile);
// read(1, Fmt, &rooms.rlnt, &rooms.rdesc2, rooms.rdesc1, rooms.rexit, rooms.ractio, rooms.rval, rooms.rflag); //F
   rooms.rlnt = rdint(indxfile);
   rdints(rooms.rlnt, rooms.rdesc1, indxfile), rdints(rooms.rlnt, rooms.rdesc2, indxfile);
   rdints(rooms.rlnt, rooms.rexit, indxfile), rdpartialints(rooms.rlnt, rooms.ractio, indxfile);
   rdpartialints(rooms.rlnt, rooms.rval, indxfile), rdints(rooms.rlnt, rooms.rflag, indxfile);
// read(1, Fmt, &exits.xlnt, exits.travel); //F
   exits.xlnt = rdint(indxfile), rdints(exits.xlnt, exits.travel, indxfile);
// read(1, Fmt, //F
//    objcts.olnt, objcts.odesc1, objcts.odesc2, objcts.odesco, objcts.oactio, objcts.oflag1, objcts.oflag2, //F
//    objcts.ofval, objcts.otval, objcts.osize, objcts.ocapac, objcts.oroom, objcts.oadv, objcts.ocan, objcts.oread //F
// ); //F
   objcts.olnt = rdint(indxfile);
   rdints(objcts.olnt, objcts.odesc1, indxfile), rdints(objcts.olnt, objcts.odesc2, indxfile);
   rdpartialints(objcts.olnt, objcts.odesco, indxfile), rdpartialints(objcts.olnt, objcts.oactio, indxfile);
   rdints(objcts.olnt, objcts.oflag1, indxfile), rdpartialints(objcts.olnt, objcts.oflag2, indxfile);
   rdpartialints(objcts.olnt, objcts.ofval, indxfile), rdpartialints(objcts.olnt, objcts.otval, indxfile);
   rdints(objcts.olnt, objcts.osize, indxfile), rdpartialints(objcts.olnt, objcts.ocapac, indxfile);
   rdints(objcts.olnt, objcts.oroom, indxfile), rdpartialints(objcts.olnt, objcts.oadv, indxfile);
   rdpartialints(objcts.olnt, objcts.ocan, indxfile), rdpartialints(objcts.olnt, objcts.oread, indxfile);
// read(1, Fmt, &oroom2_.r2lnt, oroom2_.oroom2, oroom2_.rroom2); //F
   oroom2_.r2lnt = rdint(indxfile);
   rdints(oroom2_.r2lnt, oroom2_.oroom2, indxfile), rdints(oroom2_.r2lnt, oroom2_.rroom2, indxfile);
// read(1, Fmt, &cevent.clnt, cevent.ctick, cevent.cactio); //F
   cevent.clnt = rdint(indxfile);
   rdints(cevent.clnt, cevent.ctick, indxfile), rdints(cevent.clnt, cevent.cactio, indxfile);
// read(1, "%L4", cevent.cflag); //F
   rdflags(cevent.clnt, cevent.cflag, indxfile);
// read(1, Fmt, &vill.vlnt, vill.villns, vill.vprob, vill.vopps, vill.vbest, vill.vmelee); //F
   vill.vlnt = rdint(indxfile), rdints(vill.vlnt, vill.villns, indxfile);
   rdpartialints(vill.vlnt, vill.vprob, indxfile), rdpartialints(vill.vlnt, vill.vopps, indxfile);
   rdints(vill.vlnt, vill.vbest, indxfile), rdints(vill.vlnt, vill.vmelee, indxfile);
// read(1, Fmt, &advs.alnt, advs.aroom, advs.ascore, advs.avehic, advs.aobj, advs.aactio, advs.astren, advs.aflag); //F
   advs.alnt = rdint(indxfile), rdints(advs.alnt, advs.aroom, indxfile);
   rdpartialints(advs.alnt, advs.ascore, indxfile), rdpartialints(advs.alnt, advs.avehic, indxfile);
   rdints(advs.alnt, advs.aobj, indxfile), rdints(advs.alnt, advs.aactio, indxfile);
   rdints(advs.alnt, advs.astren, indxfile), rdpartialints(advs.alnt, advs.aflag, indxfile);
// read(1, Fmt, &star.mbase, &rmsg.mlnt, rmsg.rtext); //F
   star.mbase = rdint(indxfile);
   rmsg.mlnt = rdint(indxfile), rdints(rmsg.mlnt, rmsg.rtext, indxfile);

// Save location of start of message text
// close(1); //F
   rmsg.mrloc = ftell(indxfile);
// 						!INIT DONE.

// INIT, PAGE 5

// THE INTERNAL DATA BASE IS NOW ESTABLISHED.
// SET UP TO PLAY THE GAME.

   itime(&time_.shour, &time_.smin, &time_.ssec);
//    srand(time_.shour ^ (time_.smin ^ time_.ssec));

   play.winner = PlayerAX;
   last.lastit = advs.aobj[PlayerAX - 1];
   play.here = advs.aroom[play.winner - 1];
   hack.thfpos = objcts.oroom[ThiefOX - 1];
   state.bloc = objcts.oroom[BalloOX - 1];
   ret_val = true;

   return ret_val;
// INIT, PAGE 6

// ERRORS-- INIT FAILS.

L1925:
// print(
//    " \"dindx.dat\" is version %I1.%I1%A1.%/" //F
//    "  I require version %I1.%I1%A1.", //F
//    i, j, k, vmaj, vmin, vedit //F
// ); //F
   more_output(NULL), printf("%s is version %1d.%1d%c.\n", TEXTFILE, i, j, k);
   more_output(NULL), printf("I require version %1d.%1d%c.\n", vmaj, vmin, (int)vedit);
   goto L1975;
L1950:
// print(" I can't open ","dtext.dat","."); //F
   more_output(NULL), printf("I can't open %s.\n", TEXTFILE);
L1975:
// print( //F
//    " Suddenly a sinister, wraithlike figure appears before ", //F
//    "you,%/ seeming to float in the air.  In a low, sorrowful voice", //F
//    " he says,%/ \"Alas, the very nature of the world has changed, ", //F
//    "and the dungeon%/ cannot be found.  All must now pass away.\"", //F
//    "  Raising his oaken staff%/ in farewell, he fades into the ", //F
//    "spreading darkness.  In his place%/ appears a tastefully ", //F
//    "lettered sign reading:%/%/%23XINITIALIZATION FAILURE%/%/" //F
//    " The darkness becomes all encompassing, and your vision fails." //F
// ); //F
   more_output("Suddenly a sinister, wraithlike figure appears before you,");
   more_output("seeming to float in the air.  In a low, sorrowful voice he says,");
   more_output("\"Alas, the very nature of the world has changed, and the dungeon");
   more_output("cannot be found.  All must now pass away.\"  Raising his oaken staff");
   more_output("in farewell, he fades into the spreading darkness.  In his place");
   more_output("appears a tastefully lettered sign reading:");
   more_output("");
   more_output("                       INITIALIZATION FAILURE");
   more_output("");
   more_output("The darkness becomes all encompassing, and your vision fails.");
   return ret_val;
}
