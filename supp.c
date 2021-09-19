// Support routines for dungeon: in place of the f2c library functions.
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

// C99 is now locked in and assumed.
#include <stdlib.h> // For exit() and rand().
#include <time.h> // For time() and localtime().

// Terminate the game.
void exit_(void) {
   fprintf(stderr, "The game is over.\n");
   exit(0);
}

// Get time in hours, minutes and seconds.
void itime(int *hrptr, int *minptr, int *secptr) {
   time_t timebuf; time(&timebuf);
   struct tm *tmptr = localtime(&timebuf);
   *hrptr = tmptr->tm_hour, *minptr = tmptr->tm_min, *secptr = tmptr->tm_sec;
}

// Random number generator.
int rnd(int maxval) {
   return rand() % maxval;
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

// Initialize the more waiting facility (determine how many rows the terminal has).
static int crows, coutput;

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
// If z is not NULL it is a simple string which is output here;
// otherwise it needs some sort of formatting, and is output after this function returns
// (if all computers had vprintf I would just use it, but they probably don't).
void more_output(const char *z) {
// Pager code remarked out to allow streamed input and output.
#if 0
   if (crows > 0 && coutput > crows - 2) {
      printf("Press return to continue: ");
      (void)fflush(stdout);
      while (getchar() != '\n');
      coutput = 0;
   }
#endif
   if (z != NULL) printf("%s\n", z);
   coutput++;
}

// The terminal is waiting for input (clear the number of output lines)
void more_input(void) {
   coutput = 0;
}
