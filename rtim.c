// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).

// Support routines for dungeon.
// C99 is now locked in and assumed.
#include <time.h> // For time() and localtime().
#include <stdlib.h> // For exit() and rand().
#include "extern.h"
#include "common.h"

// Get the time in hours, minutes and seconds.
void intime(int *HourP, int *MinuteP, int *SecondP) {
// gettim(*HourP, *MinuteP, *SecondP, Hundredths);
   time_t Now; time(&Now);
   struct tm *HereNow = localtime(&Now);
   *HourP = HereNow->tm_hour, *MinuteP = HereNow->tm_min, *SecondP = HereNow->tm_sec;
}

// common /random/
void inirnd(int seed) {
   srand((unsigned)seed);
}

// Random number generator.
int rnd(int maxval) {
   return rand() % maxval;
}

// Terminate the game.
void exit_(void) {
// NO "CALL EXIT" HERE
   fprintf(stderr, "Game Over.\n");
   exit(0);
}
