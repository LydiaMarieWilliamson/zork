// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).

// Support routines for dungeon.
#include <stdio.h>
#include <time.h> // For time() and localtime().
#include <stdlib.h> // For exit() and rand().
#include "extern.h"

// Terminate the game.
void exit_(void) {
   fprintf(stderr, "The game is over.\n");
   exit(0);
}

// Get time in hours, minutes and seconds.
void intime(int *hrptr, int *minptr, int *secptr) {
   time_t timebuf; time(&timebuf);
   struct tm *tmptr = localtime(&timebuf);
   *hrptr = tmptr->tm_hour, *minptr = tmptr->tm_min, *secptr = tmptr->tm_sec;
}

// common /random/
static int seedy;

void inirnd(int seed) {
#if 1
   seedy = seed;
#else
   srand((unsigned)(seedy = seed));
#endif
}

// Random number generator.
int rnd(int maxval) {
#if 0
   seedy = seedy * 1059 + 17 & 2147483647;
   return seedy / 100 % maxval;
#else
   return rand() % maxval;
#endif
}
