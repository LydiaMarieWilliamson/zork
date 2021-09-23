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

   rmsg_1.mlnt = 0;
// 						!INIT ARRAY COUNTERS.
   objcts_1.olnt = 0;
   rooms_1.rlnt = 0;
   vill_1.vlnt = 0;
   advs_1.alnt = 0;
   cevent_1.clnt = 0;
   exits_1.xlnt = 1;
   oroom2_1.r2lnt = 0;

   state_1.ltshft = 10;
// 						!SET UP STATE VARIABLES.
   state_1.mxscor = state_1.ltshft;
   state_1.egscor = 0;
   state_1.egmxsc = 0;
   state_1.mxload = 100;
   state_1.rwscor = 0;
   state_1.deaths = 0;
   state_1.moves = 0;
   time_1.pltime = 0;
   state_1.mungrm = 0;
   state_1.hs = 0;
   prsvec_1.prsa = 0;
// 						!CLEAR PARSE VECTOR.
   prsvec_1.prsi = 0;
   prsvec_1.prso = 0;
   prsvec_1.prscon = 1;
   orphs_1.oflag = 0;
// 						!CLEAR ORPHANS.
   orphs_1.oact = 0;
   orphs_1.oslot = 0;
   orphs_1.oprep = 0;
   orphs_1.oname = 0;
   hack_1.thfflg = false;
// 						!THIEF NOT INTRODUCED BUT
   hack_1.thfact = true;
// 						!IS ACTIVE.
   hack_1.swdact = false;
// 						!SWORD IS INACTIVE.
   hack_1.swdsta = 0;
// 						!SWORD IS OFF.

   recno = 1;
// 						!INIT DB FILE POINTER.
   star_1.mbase = 0;
// 						!INIT MELEE BASE.
// INIT, PAGE 3

// INIT ALL ARRAYS.

   i__1 = cmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR CLOCK EVENTS
      cevent_1.cflag[i - 1] = false;
      cevent_1.ctick[i - 1] = 0;
      cevent_1.cactio[i - 1] = 0;
// L5:
   }

   i__1 = fmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR FLAGS.
      flags[i - 1] = false;
// L10:
   }
   findex_1.buoyf = true;
// 						!SOME START AS TRUE.
   findex_1.egyptf = true;
   findex_1.cagetf = true;
   findex_1.mr1f = true;
   findex_1.mr2f = true;
   findex_1.follwf = true;
   i__1 = smax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR SWITCHES.
      switch_[i - 1] = 0;
// L12:
   }
   findex_1.ormtch = 4;
// 						!NUMBER OF MATCHES.
   findex_1.lcell = 1;
   findex_1.pnumb = 1;
   findex_1.mdir = 270;
   findex_1.mloc = rindex_1.mrb;
   findex_1.cphere = 10;

   i__1 = r2max;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR ROOM 2 ARRAY.
      oroom2_1.rroom2[i - 1] = 0;
      oroom2_1.oroom2[i - 1] = 0;
// L15:
   }

   i__1 = xmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR TRAVEL ARRAY.
      exits_1.travel[i - 1] = 0;
// L20:
   }

   i__1 = vmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR VILLAINS ARRAYS.
      vill_1.vopps[i - 1] = 0;
      vill_1.vprob[i - 1] = 0;
      vill_1.villns[i - 1] = 0;
      vill_1.vbest[i - 1] = 0;
      vill_1.vmelee[i - 1] = 0;
// L30:
   }

   i__1 = omax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR OBJECT ARRAYS.
      objcts_1.odesc1[i - 1] = 0;
      objcts_1.odesc2[i - 1] = 0;
      objcts_1.odesco[i - 1] = 0;
      objcts_1.oread[i - 1] = 0;
      objcts_1.oactio[i - 1] = 0;
      objcts_1.oflag1[i - 1] = 0;
      objcts_1.oflag2[i - 1] = 0;
      objcts_1.ofval[i - 1] = 0;
      objcts_1.otval[i - 1] = 0;
      objcts_1.osize[i - 1] = 0;
      objcts_1.ocapac[i - 1] = 0;
      objcts_1.ocan[i - 1] = 0;
      objcts_1.oadv[i - 1] = 0;
      objcts_1.oroom[i - 1] = 0;
// L40:
   }

   i__1 = rmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR ROOM ARRAYS.
      rooms_1.rdesc1[i - 1] = 0;
      rooms_1.rdesc2[i - 1] = 0;
      rooms_1.ractio[i - 1] = 0;
      rooms_1.rflag[i - 1] = 0;
      rooms_1.rval[i - 1] = 0;
      rooms_1.rexit[i - 1] = 0;
// L50:
   }

   i__1 = mmax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR MESSAGE DIRECTORY.
      rmsg_1.rtext[i - 1] = 0;
// L60:
   }

   i__1 = amax;
   for (i = 1; i <= i__1; ++i) {
// 						!CLEAR ADVENTURER'S ARRAYS.
      advs_1.aroom[i - 1] = 0;
      advs_1.ascore[i - 1] = 0;
      advs_1.avehic[i - 1] = 0;
      advs_1.aobj[i - 1] = 0;
      advs_1.aactio[i - 1] = 0;
      advs_1.astren[i - 1] = 0;
      advs_1.aflag[i - 1] = 0;
// L70:
   }

   debug_1.dbgflg = 0;
   debug_1.prsflg = 0;

// allow setting gdtflg true if user id matches wizard id
// this way, the wizard doesn't have to recompile to use gdt

#ifdef ALLOW_GDT
// 	Changed by TAA so that always in wizard ID
   debug_1.gdtflg = wizard();
#else
   debug_1.gdtflg = 0;
#endif

   screen_1.fromdr = 0;
// 						!INIT SCOL GOODIES.
   screen_1.scolrm = 0;
   screen_1.scolac = 0;
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
   if (i != vers_1.vmaj || j != vers_1.vmin) {
      goto L1925;
   }
#if 0
// open(unit:chan_1.dbch, file:"/usr/share/games/dungeon/dtext.dat", //F
//    status:"old", form:"unformatted", access:"direct", //F
//    recl:76, err:L1950 //F
// ); //F
#else
// open(unit:chan_1.dbch, file:"dtext.dat", //F
//    status:"old", form:"unformatted", access:"direct", //F
//    recl:76, err:L1950 //F
// ); //F
#endif
#ifdef ALLOW_GDT
// print(" RESTORING FROM \"dindx.dat\""); //F
#endif
// // const char *Fmt = "%I8"; //F
// const char *Fmt = "%I6"; //F
// read(1, Fmt, &state_1.mxscor, &star_1.strbit, &state_1.egmxsc); //F
   state_1.mxscor = rdint(indxfile), star_1.strbit = rdint(indxfile), state_1.egmxsc = rdint(indxfile);
// read(1, Fmt, &rooms_1.rlnt, &rooms_1.rdesc2, rooms_1.rdesc1, rooms_1.rexit, rooms_1.ractio, rooms_1.rval, rooms_1.rflag); //F
   rooms_1.rlnt = rdint(indxfile);
   rdints(rooms_1.rlnt, rooms_1.rdesc1, indxfile), rdints(rooms_1.rlnt, rooms_1.rdesc2, indxfile);
   rdints(rooms_1.rlnt, rooms_1.rexit, indxfile), rdpartialints(rooms_1.rlnt, rooms_1.ractio, indxfile);
   rdpartialints(rooms_1.rlnt, rooms_1.rval, indxfile), rdints(rooms_1.rlnt, rooms_1.rflag, indxfile);
// read(1, Fmt, &exits_1.xlnt, exits_1.travel); //F
   exits_1.xlnt = rdint(indxfile), rdints(exits_1.xlnt, exits_1.travel, indxfile);
// read(1, Fmt, //F
//    objcts_1.olnt, objcts_1.odesc1, objcts_1.odesc2, objcts_1.odesco, objcts_1.oactio, objcts_1.oflag1, objcts_1.oflag2, //F
//    objcts_1.ofval, objcts_1.otval, objcts_1.osize, objcts_1.ocapac, objcts_1.oroom, objcts_1.oadv, objcts_1.ocan, objcts_1.oread //F
// ); //F
   objcts_1.olnt = rdint(indxfile);
   rdints(objcts_1.olnt, objcts_1.odesc1, indxfile), rdints(objcts_1.olnt, objcts_1.odesc2, indxfile);
   rdpartialints(objcts_1.olnt, objcts_1.odesco, indxfile), rdpartialints(objcts_1.olnt, objcts_1.oactio, indxfile);
   rdints(objcts_1.olnt, objcts_1.oflag1, indxfile), rdpartialints(objcts_1.olnt, objcts_1.oflag2, indxfile);
   rdpartialints(objcts_1.olnt, objcts_1.ofval, indxfile), rdpartialints(objcts_1.olnt, objcts_1.otval, indxfile);
   rdints(objcts_1.olnt, objcts_1.osize, indxfile), rdpartialints(objcts_1.olnt, objcts_1.ocapac, indxfile);
   rdints(objcts_1.olnt, objcts_1.oroom, indxfile), rdpartialints(objcts_1.olnt, objcts_1.oadv, indxfile);
   rdpartialints(objcts_1.olnt, objcts_1.ocan, indxfile), rdpartialints(objcts_1.olnt, objcts_1.oread, indxfile);
// read(1, Fmt, &oroom2_1.r2lnt, oroom2_1.oroom2, oroom2_1.rroom2); //F
   oroom2_1.r2lnt = rdint(indxfile);
   rdints(oroom2_1.r2lnt, oroom2_1.oroom2, indxfile), rdints(oroom2_1.r2lnt, oroom2_1.rroom2, indxfile);
// read(1, Fmt, &cevent_1.clnt, cevent_1.ctick, cevent_1.cactio); //F
   cevent_1.clnt = rdint(indxfile);
   rdints(cevent_1.clnt, cevent_1.ctick, indxfile), rdints(cevent_1.clnt, cevent_1.cactio, indxfile);
// read(1, "%L4", cevent_1.cflag); //F
   rdflags(cevent_1.clnt, cevent_1.cflag, indxfile);
// read(1, Fmt, &vill_1.vlnt, vill_1.villns, vill_1.vprob, vill_1.vopps, vill_1.vbest, vill_1.vmelee); //F
   vill_1.vlnt = rdint(indxfile), rdints(vill_1.vlnt, vill_1.villns, indxfile);
   rdpartialints(vill_1.vlnt, vill_1.vprob, indxfile), rdpartialints(vill_1.vlnt, vill_1.vopps, indxfile);
   rdints(vill_1.vlnt, vill_1.vbest, indxfile), rdints(vill_1.vlnt, vill_1.vmelee, indxfile);
// read(1, Fmt, &advs_1.alnt, advs_1.aroom, advs_1.ascore, advs_1.avehic, advs_1.aobj, advs_1.aactio, advs_1.astren, advs_1.aflag); //F
   advs_1.alnt = rdint(indxfile), rdints(advs_1.alnt, advs_1.aroom, indxfile);
   rdpartialints(advs_1.alnt, advs_1.ascore, indxfile), rdpartialints(advs_1.alnt, advs_1.avehic, indxfile);
   rdints(advs_1.alnt, advs_1.aobj, indxfile), rdints(advs_1.alnt, advs_1.aactio, indxfile);
   rdints(advs_1.alnt, advs_1.astren, indxfile), rdpartialints(advs_1.alnt, advs_1.aflag, indxfile);
// read(1, Fmt, &star_1.mbase, &rmsg_1.mlnt, rmsg_1.rtext); //F
   star_1.mbase = rdint(indxfile);
   rmsg_1.mlnt = rdint(indxfile), rdints(rmsg_1.mlnt, rmsg_1.rtext, indxfile);

// Save location of start of message text
// close(1); //F
   rmsg_1.mrloc = ftell(indxfile);
// 						!INIT DONE.

// INIT, PAGE 5

// THE INTERNAL DATA BASE IS NOW ESTABLISHED.
// SET UP TO PLAY THE GAME.

   itime(&time_1.shour, &time_1.smin, &time_1.ssec);
//    srand(time_1.shour ^ (time_1.smin ^ time_1.ssec));

   play_1.winner = aindex_1.player;
   last_1.lastit = advs_1.aobj[aindex_1.player - 1];
   play_1.here = advs_1.aroom[play_1.winner - 1];
   hack_1.thfpos = objcts_1.oroom[oindex_1.thief - 1];
   state_1.bloc = objcts_1.oroom[oindex_1.ballo - 1];
   ret_val = true;

   return ret_val;
// INIT, PAGE 6

// ERRORS-- INIT FAILS.

L1925:
// print(
//    " \"dindx.dat\" is version %I1.%I1%A1.%/" //F
//    "  I require version %I1.%I1%A1.", //F
//    i, j, k, vers_1.vmaj, vers_1.vmin, vers_1.vedit //F
// ); //F
   more_output(NULL), printf("%s is version %1d.%1d%c.\n", TEXTFILE, i, j, k);
   more_output(NULL), printf("I require version %1d.%1d%c.\n", vers_1.vmaj, vers_1.vmin, vers_1.vedit);
   goto L1975;
L1950:
// print(" I can't open ","dindx.dat","."); //F
   more_output(NULL), printf("I can't open %s.\n", TEXTFILE);
L1975:
// print( //F
//    " Suddenly a sinister, wraithlike figure appears before ", //F
//    "you,%/ seeming to float in the air.  In a low, sorrowful voice", //F
//    " he says,%/ \"Alas, the very nature of the world has changed, ", //F
//    "and the dungeon%/ cannot be found.  All must now pass away.\"", //F
//    "  Raising his oaken staff%/ in farewell, he fades into the " //F
//    "spreading darkness.  In his place%/ appears a tastefully " //F
//    "lettered sign reading:%/%/%23XINITIALIZATION FAILURE%/%/", //F
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
