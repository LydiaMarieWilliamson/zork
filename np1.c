// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Start of parse
// This routine details on bit 2 of prsflg
int sparse(const int *lbuf, int llnt, Bool vbflag) {
// Initialized data
//   The following data statement originally was:
// 	DATA R50MIN/1RA/,R50WAL/3RWAL/
   const int r50min = 1600;
   const int r50wal = 36852;

// System generated locals
   int ret_val;

// Local variables
   int i, j, adj;
   int obj;
   int prep, pptr, lbuf1, lbuf2;
   int buzlnt, prplnt, dirlnt;

// SPARSE, PAGE 2

// Parameter adjustments
   --lbuf;

// Function Body
// SPARSE, PAGE 7

// SET UP FOR PARSING

   ret_val = -1;
// 						!ASSUME PARSE FAILS.
   adj = 0;
// 						!CLEAR PARTS HOLDERS.
   pv.act = 0;
   prep = 0;
   pptr = 0;
   pv.o1 = 0;
   pv.o2 = 0;
   pv.p1 = 0;
   pv.p2 = 0;
#if defined ALLOW_GDT && 0
   dflag = (debug.prsflg & 4) != 0;
#endif

   buzlnt = 20;
   prplnt = 48;
   dirlnt = 75;
// SPARSE, PAGE 8

// NOW LOOP OVER INPUT BUFFER OF LEXICAL TOKENS.

   for (i = 1; i <= llnt; i += 2) {
// 						!TWO WORDS/TOKEN.
      lbuf1 = lbuf[i];
// 						!GET CURRENT TOKEN.
      lbuf2 = lbuf[i + 1];
#if defined ALLOW_GDT && 0
      if (dflag) more_output("lbuf1=%d lbuf2=%d\n", lbuf1, lbuf2);
#endif
      if (lbuf1 == 0) {
         goto L1500;
      }
// 						!END OF BUFFER?

// CHECK FOR BUZZ WORD

      for (j = 1; j <= buzlnt; j += 2) {
         if (lbuf1 == bvoc[j - 1] && lbuf2 == bvoc[j]) {
            goto L1000;
         }
   // L50:
      }

// CHECK FOR ACTION OR DIRECTION

      if (pv.act != 0) {
         goto L75;
      }
// 						!GOT ACTION ALREADY?
      j = 1;
// 						!CHECK FOR ACTION.
   L125:
      if (lbuf1 == vvoc[j - 1] && lbuf2 == vvoc[j]) {
         goto L3000;
      }
// L150:
      j += 2;
// 						!ADV TO NEXT SYNONYM.
      if (!(vvoc[j - 1] > 0 && vvoc[j - 1] < r50min)) {
         goto L125;
      }
// 						!ANOTHER VERB?
      j = j + vvoc[j - 1] + 1;
// 						!NO, ADVANCE OVER SYNTAX.
      if (vvoc[j - 1] != -1) {
         goto L125;
      }
// 						!TABLE DONE?

   L75:
      if (pv.act != 0 && (vvoc[pv.act - 1] != r50wal || prep != 0)) {
         goto L200;
      }
      for (j = 1; j <= dirlnt; j += 3) {
// 						!THEN CHK FOR DIR.
         if (lbuf1 == dvoc[j - 1] && lbuf2 == dvoc[j]) {
            goto L2000;
         }
   // L100:
      }

// NOT AN ACTION, CHECK FOR PREPOSITION, ADJECTIVE, OR OBJECT.

   L200:
      for (j = 1; j <= prplnt; j += 3) {
// 						!LOOK FOR PREPOSITION.
         if (lbuf1 == pvoc[j - 1] && lbuf2 == pvoc[j]) {
            goto L4000;
         }
   // L250:
      }

      j = 1;
// 						!LOOK FOR ADJECTIVE.
   L300:
      if (lbuf1 == avoc[j - 1] && lbuf2 == avoc[j]) {
         goto L5000;
      }
      ++j;
   L325:
      ++j;
// 						!ADVANCE TO NEXT ENTRY.
      if (avoc[j - 1] > 0 && avoc[j - 1] < r50min) {
         goto L325;
      }
// 						!A RADIX 50 CONSTANT?
      if (avoc[j - 1] != -1) {
         goto L300;
      }
// 						!POSSIBLY, END TABLE?

      j = 1;
// 						!LOOK FOR OBJECT.
   L450:
      if (lbuf1 == ovoc[j - 1] && lbuf2 == ovoc[j]) {
         goto L600;
      }
      ++j;
   L500:
      ++j;
      if (ovoc[j - 1] > 0 && ovoc[j - 1] < r50min) {
         goto L500;
      }
      if (ovoc[j - 1] != -1) {
         goto L450;
      }

// NOT RECOGNIZABLE

      if (vbflag) {
         rspeak(601);
      }
      return ret_val;
// SPARSE, PAGE 9

// OBJECT PROCESSING (CONTINUATION OF DO LOOP ON PREV PAGE)

   L600:
      obj = getobj(j, adj, 0);
// 						!IDENTIFY OBJECT.
#if defined ALLOW_GDT && 0
      if (dflag) more_output("SPARSE- OBJ AT %d  OBJ= %d", j, obj);
#endif
      if (obj <= 0) {
         goto L6000;
      }
// 						!IF LE, COULDNT.
      if (obj != ItObjOX) {
         goto L650;
      }
// 						!"IT"?
      obj = getobj(0, 0, last.lastit);
// 						!FIND LAST.
      if (obj <= 0) {
         goto L6000;
      }
// 						!IF LE, COULDNT.

   L650:
      if (prep == 9) {
         goto L8000;
      }
// 						!"OF" OBJ?
      if (pptr == 2) {
         goto L7000;
      }
// 						!TOO MANY OBJS?
      ++pptr;
      objvec[pptr - 1] = obj;
// 						!STUFF INTO VECTOR.
      prpvec[pptr - 1] = prep;
   L700:
      prep = 0;
      adj = 0;
// Go to end of do loop (moved "1000 CONTINUE" to end of module, to avoid
// complaints about people jumping back into the doloop.)
      goto L1000;
// SPARSE, PAGE 10

// SPECIAL PARSE PROCESSORS

// 2000--	DIRECTION

   L2000:
      prsvec.prsa = WalkW;
      prsvec.prso = dvoc[j + 1];
      ret_val = 1;
#if defined ALLOW_GDT && 0
      if (dflag) more_output("SPARSE- DIR AT %d\n", j);
#endif
      return ret_val;

// 3000--	ACTION

   L3000:
      pv.act = j;
      orphs.oact = 0;
#if defined ALLOW_GDT && 0
      if (dflag) more_output("SPARSE- ACT AT %d\n", j);
      if (dflag) more_output("count=%d vnr=%d\n", vvoc[j + 1], vvoc[j + 2]);
#endif
      goto L1000;

// 4000--	PREPOSITION

   L4000:
      if (prep != 0) {
         goto L4500;
      }
      prep = pvoc[j + 1];
      adj = 0;
#if defined ALLOW_GDT && 0
      if (dflag) more_output("SPARSE- PREP AT %d\n", j);
#endif
      goto L1000;

   L4500:
      if (vbflag) {
         rspeak(616);
      }
      return ret_val;

// 5000--	ADJECTIVE

   L5000:
      adj = j;
      j = orphs.oname & orphs.oflag;
#if defined ALLOW_GDT && 0
      if (dflag) more_output("SPARSE- ADJ AT %d ORPHAN= %d\n", adj, j);
#endif
      if (j != 0 && i >= llnt) {
         goto L600;
      }
      goto L1000;

// 6000--	UNIDENTIFIABLE OBJECT (INDEX INTO OVOC IS J)

   L6000:
      if (obj < 0) {
         goto L6100;
      }
      j = 579;
      if (lit(play.here)) {
         j = 618;
      }
      if (vbflag) {
         rspeak(j);
      }
      return ret_val;

   L6100:
      if (obj != -10000) {
         goto L6200;
      }
      if (vbflag) {
         rspsub(620, objcts.odesc2[advs.avehic[play.winner - 1] - 1]);
      }
      return ret_val;

   L6200:
      if (vbflag) {
         rspeak(619);
      }
      if (pv.act == 0) {
         pv.act = orphs.oflag & orphs.oact;
      }
      orphan(-1, pv.act, pv.o1, prep, j);
      return ret_val;

// 7000--	TOO MANY OBJECTS.

   L7000:
      if (vbflag) {
         rspeak(617);
      }
      return ret_val;

// 8000--	RANDOMNESS FOR "OF" WORDS

   L8000:
      if (objvec[pptr - 1] == obj) {
         goto L700;
      }
      if (vbflag) {
         rspeak(601);
      }
      return ret_val;

// End of do-loop.

   L1000:
      ;
   }
// 						!AT LAST.

// NOW SOME MISC CLEANUP -- We fell out of the do-loop

L1500:
   if (pv.act == 0) {
      pv.act = orphs.oflag & orphs.oact;
   }
   if (pv.act == 0) {
      goto L9000;
   }
// 						!IF STILL NONE, PUNT.
   if (adj != 0) {
      goto L10000;
   }
// 						!IF DANGLING ADJ, PUNT.

   if (orphs.oflag != 0 && orphs.oprep != 0 && prep == 0 && pv.o1 != 0 && pv.o2 == 0 && pv.act == orphs.oact) {
      goto L11000;
   }

   ret_val = 0;
// 						!PARSE SUCCEEDS.
   if (prep == 0) {
      goto L1750;
   }
// 						!IF DANGLING PREP,
   if (pptr == 0 || prpvec[pptr - 1] != 0) {
      goto L12000;
   }
   prpvec[pptr - 1] = prep;
// 						!CVT TO 'PICK UP FROB'.

// 1750--	RETURN A RESULT

L1750:
// 						!WIN.
#if defined ALLOW_GDT && 0
   if (dflag) more_output("SPARSE RESULTS- %d %d %d %d %d\n", pv.act, pv.o1, pv.o2, pv.p1, pv.p2);
   if (dflag) more_output("sparse=%d\n", sparse);
#endif
   return ret_val;
// 						!LOSE.

// 9000--	NO ACTION, PUNT

L9000:
   if (pv.o1 == 0) {
      goto L10000;
   }
// 						!ANY DIRECT OBJECT?
   if (vbflag) {
      rspsub(621, objcts.odesc2[pv.o1 - 1]);
   }
// 						!WHAT TO DO?
   orphan(-1, 0, pv.o1, 0, 0);
   return ret_val;

// 10000--	TOTAL CHOMP

L10000:
   if (vbflag) {
      rspeak(622);
   }
// 						!HUH?
   return ret_val;

// 11000--	ORPHAN PREPOSITION.  CONDITIONS ARE
// 		O1.NE.0, O2=0, PREP=0, ACT=OACT

L11000:
   if (orphs.oslot != 0) {
      goto L11500;
   }
// 						!ORPHAN OBJECT?
   pv.p1 = orphs.oprep;
// 						!NO, JUST USE PREP.
   goto L1750;

L11500:
   pv.o2 = pv.o1;
// 						!YES, USE AS DIRECT OBJ.
   pv.p2 = orphs.oprep;
   pv.o1 = orphs.oslot;
   pv.p1 = 0;
   goto L1750;

// 12000--	TRUE HANGING PREPOSITION.
// 		ORPHAN FOR LATER.

L12000:
   orphan(-1, pv.act, 0, prep, 0);
// 						!ORPHAN PREP.
   goto L1750;
}
