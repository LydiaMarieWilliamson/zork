// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"

// Dungeon functions which need local definition.
#ifdef __AMOS__
#   include <moncal.h>
#endif

// This function should return true if it's OK for people to play the game, false otherwise.
// If you have a working <time.h> library, you can define NONBUSINESS to disallow play Monday to Friday, 9-5
// (this is only checked at the start of the game, though).
// For more complex control you will have to write your own version of this function.
#ifdef NONBUSINESS
#   ifdef BSD4_2
#      include <sys/timeb.h>
#   else
#      include <time.h>
#   endif
#endif
Bool protected_(void) {
#ifndef NONBUSINESS
   return true;
#else
// True if it's Sunday or Saturday or before 09:00 or after 17:00.
   time_t t; (void)time(&t);
   struct tm *q = localtime(&t);
   return q->tm_wday == 0 || q->tm_wday == 6 || q->tm_hour < 9 || q->tm_hour >= 17;
#endif
}

#ifdef ALLOW_GDT
// This function should return true if the user is allowed to invoke the game debugging tool by typing "gdt".
// This isn't very useful without the source code, and it's mainly for people trying to debug the game.
// You can define WIZARDID to specify a user id on a UNIX system.
// On a non AMOS, non unix system this function will have to be changed if you want to use gdt.
#   ifndef WIZARDID
#      define WIZARDID (0)
#   endif
Bool wizard(void) {
#   if 1
   return true;
#   elif defined __AMOS__
   return jobidx()->jobusr == 0x102;
#   elif defined unix
   return getuid() == 0 || getuid() == WIZARDID;
#   else
   return true;
#   endif
}
#endif
