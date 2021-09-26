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
Bool protct(void/*int x*/) {
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

// Support routines for dungeon: in place of the f2c library functions.
#include <stdio.h>
#include <stdarg.h>

#ifdef __AMOS__
#   include <amos.h>
FILE *OpenInF(const char *File, const char *Mode) { return fdopen(ropen(File, 0), Mode); }
#else
FILE *OpenInF(const char *File, const char *Mode) { return fopen(File, Mode); }
#endif

// Read a single two byte int from the index file
int GetWord(FILE *InF) {
   int Ch = getc(InF); if (Ch > 0x7f) Ch -= 0x100;
   return 0x100*Ch + getc(InF);
}

// Read a number of two byte integers from the index file
void GetWords(int Lim, int *WordP, FILE *InF) {
   while (Lim-- > 0) *WordP++ = GetWord(InF);
}

// Read a partial array of integers.
// These are stored as index,value pairs.
void GetPairs(int Lim, int *PairTab, FILE *InF) {
   while (true) {
      int p;
      if (Lim < 0xff) {
         p = getc(InF); if (p == 0xff) return;
      } else {
         p = GetWord(InF); if (p == -1) return;
      }
      PairTab[p] = GetWord(InF);
   }
}

// Read a number of one byte flags from the index file
void GetFlags(int Lim, Bool *FlagP, FILE *InF) {
   while (Lim-- > 0) *FlagP++ = getc(InF);
}

// Terminal support routines for dungeon
// By Ian Lance Taylor ian@airs.com or uunet!airs!ian

// The dungeon game can often output long strings, more than enough to overwhelm a typical 24 row terminal
// (I assume that back when dungeon was written people generally used paper terminals (I know I did) so this was not a problem).
// The functions in this file provide a very simplistic ‟more” facility.
// They are necessarily somewhat operating system dependent, although I have tried to minimize it as much as I could.

// The following macro definitions may be used to control how these functions work:
//	MORE_NONE	Don't use the more facility at all
//	MORE_24		Always assume a 24 row terminal
//	MORE_TERMCAP	Use termcap routines to get rows of terminal
//	MORE_TERMINFO	Use terminfo routines to get rows of terminal
//	MORE_AMOS	Use AMOS monitor calls to get rows of terminal
// If none of these are defined then this will use termcap routines on unix and AMOS routines on AMOS.

#if defined MORE_NONE || defined MORE_24 || defined MORE_TERMCAP || defined MORE_TERMINFO || defined MORE_AMOS
#elif defined __AMOS__
#   define MORE_AMOS
#elif defined unix
#   define MORE_TERMCAP
#else
#   define MORE_NONE
#endif

#if defined MORE_TERMCAP
extern char *getenv(const char *);
extern void tgetent(char *, const char *);
extern int tgetnum(const char *);
#elif defined MORE_TERMINFO
#   include <cursesX.h>
#   include <term.h>
extern void setupterm(const char *, int, int);
#elif defined MORE_AMOS
#   include <moncal.h>
#   include <unistd.h>
#endif

static int crows, coutput;

// Initialize the more waiting facility (determine how many rows the terminal has).
void more_init(void) {
#if defined MORE_NONE
   crows = 0;
#elif defined MORE_24
   crows = 24;
#elif defined MORE_TERMCAP
   char buf[0x800];
   char *term = getenv("TERM");
   if (term == NULL) crows = 0;
   else
      tgetent(buf, term), crows = tgetnum("li");
#elif defined MORE_TERMINFO
   int i; setupterm(NULL, 1, &i);
   crows = i != 1? 0: lines;
#elif defined MORE_AMOS
   if (isatty(fileno(stdin)) == 0) crows = 0;
   else {
      trm_char st; trmchr(&st, 0), crows = st.row;
   }
#else
#   error This should be impossible
#endif
}

// The program wants to output a line to the terminal.
// If Format is not NULL it is a format string which controls the output here;
// along with additional arguments, like printf();
// making use of vprintf(), which is part of the C99 library declared in <stdio.h>, and is therefore assumed.
void more_output(const char *Format, ...) {
// Pager code remarked out to allow streamed input and output.
#if 0
   if (crows > 0 && coutput > crows - 2) {
      printf("Press return to continue: "), fflush(stdout);
      while (getchar() != '\n');
      coutput = 0;
   }
#endif
   if (Format != NULL) {
      va_list AP; va_start(AP, Format), vfprintf(stdout, Format, AP), va_end(AP);
   }
   coutput++;
}

// The terminal is waiting for input (clear the number of output lines)
char *more_input(char *Buf, size_t N) {
   coutput = 0;
   return fgets(Buf, N, stdin);
}
