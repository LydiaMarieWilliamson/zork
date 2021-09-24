// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

#if 1
//(@) Cheat, cheat! We make a ‟fallback” using a hack from the other repository.
#include <time.h>
void ITime(int HMS[3]) {
   time_t Now; time(&Now);
   struct tm *HereNow = localtime(&Now);
   HMS[0] = HereNow->tm_hour, HMS[1] = HereNow->tm_min, HMS[2] = HereNow->tm_sec;
}
#else
extern int /* Subroutine */ itime(int *);
#   define ITime(HMS) ((void)itime(HMS))
#endif

void intime(int * hours, int * minutes, int * seconds) {
   int tarray[3];

// 	CALL GETTIM(HOURS, MINUTES, SECONDS, HUNDREDTHS)
   ITime(tarray);
   *hours = tarray[0];
   *minutes = tarray[1];
   *seconds = tarray[2];
}

void inirnd(int seed) {
   random_.seedy = seed;
}

int rnd(int maxval) {
// System generated locals
   int ret_val;

   random_.seedy = random_.seedy * 1059 + 17 & 2147483647;
   ret_val = random_.seedy / 100 % maxval;
   return ret_val;
}

void exit_(void) {
// NO "CALL EXIT" HERE
   char *Msg = "";
   StopS(Msg, sizeof Msg);
}
