// supp.c -- support routines for dungeon

#include <stdio.h>

#ifdef unix
#   include <sys/types.h>
#endif

#ifdef BSD4_2
#   include <sys/time.h>
#else
#   include <time.h>
#endif

#include "extern.h"

// Define these here to avoid using <stdlib.h>

extern void exit(int);
extern int rand(void);

// C99 is now locked in and assumed.
#include <time.h> // For time() and localtime();

// Terminate the game

void exit_(void) {
   fprintf(stderr, "The game is over.\n");
   exit(0);
}

// Get time in hours, minutes and seconds

void itime_(int *hrptr, int *minptr, int *secptr) {
   time_t timebuf;
   struct tm *tmptr;

   time(&timebuf);
   tmptr = localtime(&timebuf);

   *hrptr = tmptr->tm_hour;
   *minptr = tmptr->tm_min;
   *secptr = tmptr->tm_sec;
}

// Random number generator

int rnd_(int maxval) {
   return rand() % maxval;
}

// Terminal support routines for dungeon
// By Ian Lance Taylor ian@airs.com or uunet!airs!ian

// The dungeon game can often output long strings, more than enough
// to overwhelm a typical 24 row terminal (I assume that back when
// dungeon was written people generally used paper terminals (I know
// I did) so this was not a problem).  The functions in this file
// provide a very simplistic ``more'' facility.  They are necessarily
// somewhat operating system dependent, although I have tried to
// minimize it as much as I could.

// The following macro definitions may be used to control how these
// functions work:
//
//	MORE_NONE	Don't use the more facility at all
//	MORE_24		Always assume a 24 row terminal
//	MORE_TERMCAP	Use termcap routines to get rows of terminal
//	MORE_TERMINFO	Use terminfo routines to get rows of terminal
//	MORE_AMOS	Use AMOS monitor calls to get rows of terminal
//
// If none of these are defined then this will use termcap routines on
// unix and AMOS routines on AMOS.

#ifndef MORE_NONE
#   ifndef MORE_24
#      ifndef MORE_TERMCAP
#         ifndef MORE_TERMINFO
#            ifndef MORE_AMOS
#               ifdef __AMOS__
#                  define MORE_AMOS
#               else
#                  ifdef unix
#                     define MORE_TERMCAP
#                  else
#                     define MORE_NONE
#                  endif
#               endif
#            endif
#         endif
#      endif
#   endif
#endif

#ifdef MORE_TERMCAP
extern char *getenv(const char *);
extern void tgetent(char *, const char *);
extern int tgetnum(const char *);
#else
#   ifdef MORE_TERMINFO
#      include <cursesX.h>
#      include <term.h>
extern void setupterm(const char *, int, int);
#   else
#      ifdef MORE_AMOS
#         include <moncal.h>
#         include <unistd.h>
#      endif
#   endif
#endif

// Initialize the more waiting facility (determine how many rows the terminal has).

static int crows;
static int coutput;

void more_init(void) {
#ifdef MORE_NONE
   crows = 0;
#else
#   ifdef MORE_24
   crows = 24;
#   else
#      ifdef MORE_TERMCAP
   char buf[2048];
   char *term;

   term = getenv("TERM");
   if (term == NULL)
      crows = 0;
   else {
      tgetent(buf, term);
      crows = tgetnum("li");
   }
#      else
#         ifdef MORE_TERMINFO
   int i;

   setupterm(NULL, 1, &i);
   if (i != 1)
      crows = 0;
   else
      crows = lines;
#         else
#            ifdef MORE_AMOS
   trm_char st;

   if (isatty(fileno(stdin)) == 0)
      crows = 0;
   else {
      trmchr(&st, 0);
      crows = st.row;
   }
#            else
#               error This should be impossible
#            endif
#         endif
#      endif
#   endif
#endif
}

// The program wants to output a line to the terminal.  If z is not
// NULL it is a simple string which is output here; otherwise it
// needs some sort of formatting, and is output after this function
// returns (if all computers had vprintf I would just it, but they
// probably don't).
void more_output(const char *z) {
// pager code remarked out to allow streamed input and output
#if 0
   if (crows > 0 && coutput > crows - 2) {
      printf("Press return to continue: ");
      (void)fflush(stdout);
      while (getchar() != '\n');
      coutput = 0;
   }
#endif
   if (z != NULL)
      printf("%s\n", z);

   coutput++;
}

// The terminal is waiting for input (clear the number of output lines)

void more_input(void) {
   coutput = 0;
}
