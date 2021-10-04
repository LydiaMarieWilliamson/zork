// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Encrypt password
void encryp(const char *inw, char *outw) {
// Initialized data
   const char keyw[1 * 6] = "E" "C" "O" "R" "M" "S";

   int i, j, uinw[6], usum;
   char ukeyw[1 * 6];
   int uinws, ukeyws;

// Parameter adjustments
   --outw;
   --inw;

// Function Body

   uinws = 0;
// 						!UNBIASED INW SUM.
   ukeyws = 0;
// 						!UNBIASED KEYW SUM.
   j = 1;
// 						!POINTER IN KEYWORD.
   for (i = 1; i <= 6; ++i) {
// 						!UNBIAS, COMPUTE SUMS.
      ukeyw[i - 1] = keyw[i - 1] - 64;
      if (inw[j] <= '@') {
         j = 1;
      }
      uinw[i - 1] = inw[j] - 64;
      ukeyws += ukeyw[i - 1];
      uinws += uinw[i - 1];
      ++j;
// L100:
   }

   usum = uinws % 8 + (ukeyws % 8 << 3);
// 						!COMPUTE MASK.
   for (i = 1; i <= 6; ++i) {
      j = (uinw[i - 1] ^ ukeyw[i - 1] ^ usum) & 31;
      usum = (usum + 1) % 32;
      if (j > 26) {
         j %= 26;
      }
      outw[i] = max(1, j) + 64;
// L200:
   }
}

// Move to next state in puzzle room
void cpgoto(int st) {
// System generated locals
   int i__1, i__2;

// Local variables
   int i;

// CPGOTO, PAGE 2

   rooms.rflag[CPuzzRX - 1] &= ~SeenR;
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!RELOCATE OBJECTS.
      if (objcts.oroom[i - 1] == CPuzzRX && (objcts.oflag2[i - 1] & ActrO + VillO) == 0) {
         i__2 = findex_1.cphere * hfactr;
         newsta(i, 0, i__2, 0, 0);
      }
      if (objcts.oroom[i - 1] == st * hfactr) {
         newsta(i, 0, CPuzzRX, 0, 0);
      }
// L100:
   }
   findex_1.cphere = st;
}

// Describe puzzle room
void cpinfo(int rmk, int st) {
// Local variables
   int i, j, k, l;
   char dgm[1 * 8];

// Initialized data
   const int dgmoft[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
   const char pict[1 * 5] = "S" "S" "S" " " "M";

// CPINFO, PAGE 2

   rspeak(rmk);
   for (i = 1; i <= 8; ++i) {
      j = dgmoft[i - 1];
      dgm[i - 1] = pict[puzzle.cpvec[st + j - 1] + 3];
// 						!GET PICTURE ELEMENT.
      if (abs(j) == 1 || abs(j) == 8) {
         goto L100;
      }
      k = 8;
      if (j < 0) {
         k = -8;
      }
// 						!GET ORTHO DIR.
      l = j - k;
      if (puzzle.cpvec[st + k - 1] != 0 && puzzle.cpvec[st + l - 1] != 0) {
         dgm[i - 1] = '?';
      }
   L100:
      ;
   }
   more_output("       |%c%c %c%c %c%c|\n", dgm[0], dgm[0], dgm[1], dgm[1], dgm[2], dgm[2]);
   more_output(" West  |%c%c .. %c%c|  East\n", dgm[3], dgm[3], dgm[4], dgm[4]);
   more_output("       |%c%c %c%c %c%c|\n", dgm[5], dgm[5], dgm[6], dgm[6], dgm[7], dgm[7]);

   if (st == 10) {
      rspeak(870);
   }
// 						!AT HOLE?
   if (st == 37) {
      rspeak(871);
   }
// 						!AT NICHE?
   i = 872;
// 						!DOOR OPEN?
   if (findex_0.cpoutf) {
      i = 873;
   }
   if (st == 52) {
      rspeak(i);
   }
// 						!AT DOOR?
   if (puzzle.cpvec[st] == -2) {
      rspeak(874);
   }
// 						!EAST LADDER?
   if (puzzle.cpvec[st - 2] == -3) {
      rspeak(875);
   }
// 						!WEST LADDER?
}
