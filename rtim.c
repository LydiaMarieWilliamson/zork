// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).

// Support routines for dungeon.
// C99 is now locked in and assumed.
#include <time.h> // For time() and localtime().
#include <stdlib.h> // For exit().
#include "extern.h"
#include "common.h"

// The time since 2001 in seconds.
long time2001(void) {
#if 1
// Portable programs, actually, should not rely on the return value of time().
   const long _2001 = 11323 * 24 * 60 * 60;
   time_t Now = time(NULL); return (long)(Now - _2001);
#else
// A fall-back version for implementations of C99 in which time() does not return the time-since-UNIX-epoch in seconds.
   const int Leap2000 = 2000 / 4 - 2000 / 100 + 2000 / 400;
   time_t Now; time(&Now); struct tm *DT = gmtime(&Now);
   int Y = 1900 + DT->tm_year, M = 1 + DT->tm_mon, D = DT->tm_mday, Hr = DT->tm_hour, Mn = DT->tm_min, Sc = DT->tm_sec;
   long T = 365 * (M - 1) / 12;
   if (M < 8) T--;
   if (M < 3) T += M;
   else {
      if (Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0)) T++;
   // if (Y % 4 == 0) T++;
   // if (Y % 100 == 0) T--;
   // if (Y % 400 == 0) T++;
   }
   T += D - 1;
   Y--;
   T += 365 * (Y - 2000) + Y / 4 - Y / 100 + Y / 400 - Leap2000;
   return 60 * (60 * (24 * T + Hr) + Mn) + Sc;
#endif
}

// common /random/ long Seed0; const long M0; const int A0, Q0, R0;
// common /random/ long Seed1; const long M1; const int A1, Q1, R1;
static const long M0 = 1 + 2 * 3 * 7 * 631 * 81031; // ≡ 2³¹ - 85
static const long M1 = 1 + 2 * 19 * 31 * 1019 * 1789; // ≡ 2³¹ - 249
static long Seed0, Seed1;

void _srand(long S0, long S1) {
   Seed0 = S0 % M0, Seed1 = S1 % M1;
}

// A random long integer in [1, M0 - 1].
// P.L'Ecuyer, ‟Efficient and portable combined random number generators”, CACM 31(6), June 1988, 742-751.
// The period of the generator is:
//	(M0 - 1)(M1 - 1)/2 ≡ 2 × 3 × 7 × 19 × 31 × 631 × 1019 × 1789 × 81031 ≡ 2⁶¹ - 360777242114
static long _rand(void) {
   const int A0 = 40014, Q0 = M0 / A0, R0 = M0 % A0;
   const int A1 = 40692, Q1 = M1 / A1, R1 = M1 % A1;
// This requires:
// ∙	(M0 - 1)/2 and (M1 - 1)/2 be relatively prime,
// ∙	A0² < M0 and A1² < M1,
// ∙	0 ≤ Seed0 < M0, 0 ≤ Seed1 < M1.
// Under these conditions, the following is equivalent to:
// ∙	Seed0 = A0 * Seed0 % M0, Seed1 = A1 * Seed1 % M1;
// and 0 ≤ Seed0 < M0, 0 ≤ Seed1 < M1 continues to hold.
   int K0 = Seed0 / Q0; Seed0 = A0 * (Seed0 - K0 * Q0) - K0 * R0; if (Seed0 < 0) Seed0 += M0;
   int K1 = Seed1 / Q1; Seed1 = A1 * (Seed1 - K1 * Q1) - K1 * R1; if (Seed1 < 0) Seed1 += M1;
// The result is in the range [0, M0 - 2].
   int Z = Seed0 - Seed1; if (Z < 1) Z += M0 - 1;
   return Z;
}

// The last remnant of the seed update routine from the Fortran original is used, here, to initialize the seed.
void inirnd(long seed) {
   _srand(seed, (seed*0x423 + 0x11)&0xffffffff);
}

// Random number generator.
// A random integer in [0, maxval - 1].
int rnd(int maxval) {
   return _rand() % maxval;
}

// Terminate the game.
void exit_(void) {
// NO "CALL EXIT" HERE
   fprintf(stderr, "Game Over.\n");
   exit(0);
}
