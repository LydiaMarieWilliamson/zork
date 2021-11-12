#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// From local.c: IOErrs, GetWord(), GetLong(), GetWords(), GetLongs().
unsigned IOErrs = 0U;

// Read an integer from a line in the index file
int GetWord(FILE *InF) {
   int A = 0, n = fscanf(InF, "%d", &A);
   if (n < 1) IOErrs++;
   return A;
}

// Read a long integer from a line in the index file
long GetLong(FILE *InF) {
   int A = 0; long n = fscanf(InF, "%ld", &A);
   if (n < 1) IOErrs++;
   return A;
}

// Read a number of integers from separate lines in the index file
void GetWords(int Lim, int *WordP, FILE *InF) {
   while (Lim-- > 0) *WordP++ = GetWord(InF);
}

// Read a number of long integers from separate lines in the index file
void GetLongs(int Lim, long *LongP, FILE *InF) {
   while (Lim-- > 0) *LongP++ = GetLong(InF);
}

// Read a number of boolean values from separate lines in the index file
void GetFlags(int Lim, bool *FlagP, FILE *InF) {
   while (Lim-- > 0) {
      int Ch = '\0'; int n = fscanf(InF, " %c", &Ch);
      if (n < 1 || (Ch != 'F' && Ch != 'T')) IOErrs++;
      *FlagP++ = Ch != 'F';
   }
}

void PutMsg(long X) {
   if (X < 0) printf("#%06ld", -X);
   else if (X > 0) printf("?%04ld", +X);
   else printf("-----");
}

bool GetRec(FILE *InF, long *locp, size_t *np, char buf[]) {
// inirnd(0xe1e26d38); // Seed: (3789712696) 0xe1e26d38: 1984-12-28 03:30 UTC
// for (int x = 0; x < 0x100; x++) key[x] = rnd(0x100);
   static unsigned char key[0x100] = {
      0x31, 0x5f, 0x58, 0xd7, 0x99, 0x0e, 0xc2, 0x79, 0xf5, 0xa1, 0xcf, 0x23, 0xb6, 0x7e, 0xe4, 0x86,
      0xdb, 0x3e, 0x65, 0x09, 0xa0, 0xc3, 0xdd, 0xd5, 0xee, 0x3c, 0xb5, 0xe6, 0x1c, 0x5c, 0x04, 0x3a,
      0x62, 0xcf, 0x19, 0x5e, 0x34, 0x61, 0x18, 0x8f, 0xa7, 0x08, 0xbc, 0x57, 0x8c, 0x64, 0xd8, 0x12,
      0x7d, 0xa0, 0xfa, 0xf7, 0x3e, 0xd5, 0x84, 0x91, 0xa0, 0x88, 0xbd, 0x48, 0xd4, 0xef, 0x6b, 0xf8,
      0xf8, 0x2f, 0xe4, 0x82, 0x2a, 0x08, 0xd3, 0xdd, 0xa1, 0x8a, 0xc8, 0xd8, 0xfd, 0x78, 0x76, 0x73,
      0xf5, 0x98, 0x12, 0x7f, 0xc6, 0x69, 0x36, 0x28, 0xc7, 0xb9, 0x0f, 0xe0, 0xbd, 0x26, 0xdb, 0x5e,
      0xd2, 0x4b, 0x4e, 0x2e, 0x8a, 0xfa, 0x03, 0x82, 0x07, 0x6c, 0x25, 0x7d, 0x70, 0xda, 0x5c, 0x52,
      0xb0, 0x6d, 0x82, 0x2a, 0x0a, 0x2f, 0x2d, 0x5c, 0x5d, 0xd3, 0xc9, 0x4d, 0xe5, 0x9e, 0xef, 0x4d,
      0x6b, 0xd6, 0x41, 0xe3, 0xe6, 0x95, 0xe9, 0xe8, 0x4d, 0x49, 0xaf, 0xfc, 0x81, 0x25, 0x17, 0xec,
      0x77, 0x60, 0xe0, 0xc3, 0x40, 0xb7, 0xe7, 0xb9, 0xba, 0x6c, 0xad, 0xd1, 0x15, 0x8b, 0x29, 0xa5,
      0x70, 0x18, 0xf6, 0x29, 0x3c, 0xd3, 0x5c, 0x1c, 0xe3, 0x46, 0x53, 0xc6, 0xc8, 0xd3, 0x5b, 0xa1,
      0xe2, 0x0c, 0x8d, 0x0a, 0x2c, 0x2d, 0x39, 0xcf, 0xcd, 0x26, 0xec, 0x88, 0x0d, 0xab, 0xb7, 0xcd,
      0x67, 0x8e, 0xf5, 0x7c, 0x7b, 0x17, 0x12, 0xff, 0xcc, 0x81, 0x63, 0xf7, 0xc9, 0xec, 0x3d, 0x3a,
      0xac, 0x31, 0x44, 0x8b, 0x32, 0xad, 0xac, 0x59, 0x5d, 0x52, 0x96, 0xa9, 0x6d, 0x80, 0xb5, 0x1f,
      0x07, 0x5f, 0x00, 0x6a, 0x51, 0x6c, 0xfb, 0xc7, 0xda, 0xc5, 0x88, 0xa9, 0x0b, 0x2d, 0xe2, 0x96,
      0xba, 0x6e, 0xec, 0xef, 0x41, 0x56, 0x92, 0xc4, 0x0d, 0x1a, 0x0d, 0x9c, 0xca, 0x0b, 0x95, 0xaa
   };
   long loc = *locp - 1;
   if (fseek(InF, loc, SEEK_SET) == EOF) fprintf(stderr, "Error seeking database at #%ld\n", loc), exit(EXIT_FAILURE);
   unsigned char ix;
   if (fread(&ix, sizeof ix, 1, InF) != 1) fprintf(stderr, "Error reading string size at #%ld\n", loc), exit(EXIT_FAILURE);
   else loc++;
   size_t n = ix & ~0x80; bool last = ix & 0x80;
   if (fread(buf, 1, n, InF) != n) fprintf(stderr, "Error reading string line at #%ld\n", loc), exit(EXIT_FAILURE);
   for (int i = 0; i < n; i++, loc++) buf[i] ^= key[loc & 0xff];
   buf[n] = '\0';
   *locp = loc;
   *np = n;
   return last;
}

// parser, gamestat, state, screen, mindex, /star/, /vers/, io, debug, /hyper/, rooms, rflag, exits, curxt, xpars, objects, oindex, clock, villians, advers, flags
int main(void) {
   const char *MyIndexFile = "dindx.dat";
// Now, restore from the existing index file.
   FILE *IndexF = fopen(MyIndexFile, "r"); if (IndexF == NULL) { printf("I can't open %s.\n", MyIndexFile); return EXIT_FAILURE; }
// /vers/:
   int Maj = GetWord(IndexF), Min = GetWord(IndexF), Edit = GetWord(IndexF);
   printf("/vers/: %1d.%1d%c\n", Maj, Min, Edit);
// /state/: (bloc will be set later).
   int mxscor = GetWord(IndexF), egmxsc = GetWord(IndexF), bloc = 0;
   printf("/state/: Max Score = %d, Eg Score = %d\n", mxscor, egmxsc);
// /rooms/: (eqr)
   printf("\n");
   printf("Room Table\n");
   printf("──────────\n");
   const int rmax = 200;
   int rlnt = GetWord(IndexF);
   int rdesc1[200], rdesc2[200], rexit[200], ractio[200], rval[200], rflag[200];
   for (int r = 0; r < rmax; r++) rdesc1[r] = 0, rdesc2[r] = 0, rexit[r] = 0, ractio[r] = 0, rval[r] = 0, rflag[r] = 0;
   GetWords(rlnt, rdesc1, IndexF), GetWords(rlnt, rdesc2, IndexF), GetWords(rlnt, rexit, IndexF), GetWords(rlnt, ractio, IndexF), GetWords(rlnt, rval, IndexF), GetWords(rlnt, rflag, IndexF);
   printf("/rooms/: %d of %d rooms { desc1, desc2, exit, actio, val, flag; }\n", rlnt, rmax);
   for (int r = 0; r < rlnt; r++) printf("{ "), PutMsg(rdesc1[r]), printf(", "), PutMsg(rdesc2[r]), printf(", %3d, %2d, %2d, 0x%04x },\n", rexit[r], ractio[r], rval[r], rflag[r]);
// /exits/:
   printf("\n");
   printf("Exit Table\n");
   printf("──────────\n");
   const int xmax = 900;
   int xlnt = GetWord(IndexF);
   int travel[900];
   for (int x = 0; x < xmax; x++) travel[x] = 0;
   GetWords(xlnt, travel, IndexF);
   printf("/exits/: %d of %d exits (travel) { lastx:1, direction:5, type-1:2, room:8, message, action:8, object:8; }\n", xlnt, xmax);
// travel[x+0]: lastx:1, direction:5, type-1:2, room:8 (type ∈ {1,2,3,4})
// travel[x+1]: message (type ∈ {2,3,4})
// travel[x+2]: action:8, object:8 (type ∈ {3,4})
   for (int x = 0; x < xlnt; x++) {
      unsigned T = (unsigned)travel[x], lastx = (T>>15)&1, direction = (T>>10)&0x1f, type = 1 + ((T>>8)&3), room = (T&0xff);
      if (type > 2 && x > xlnt - 3 || type > 1 && x > xlnt - 2) { printf("Format error.\n"); return EXIT_FAILURE; }
      printf("{ %u, %2u, %u, %3u", lastx, direction, type, room);
      if (type > 1) printf(", "), PutMsg(travel[++x]);
      if (type > 2) {
         unsigned T = (unsigned)travel[++x];
         printf(", %2u, %3u", (T>>8)&0xff, T&0xff);
      }
      printf(" },\n");
   }
// /objcts/: (eqo)
   printf("\n");
   printf("Object Table\n");
   printf("────────────\n");
   const int omax = 220;
   int olnt = GetWord(IndexF);
   int odesc1[220], odesc2[220], odesco[220];
   int oactio[220], oflag1[220], oflag2[220];
   int ofval[220], otval[220], osize[220], ocapac[220];
   int oroom[220], oadv[220], ocan[220], oread[220];
   for (int o = 0; o < omax; o++)
      odesc1[o] = 0, odesc2[o] = 0, odesco[o] = 0,
      oactio[o] = 0, oflag1[o] = 0, oflag2[o] = 0,
      ofval[o] = 0, otval[o] = 0, osize[o] = 0, ocapac[o] = 0,
      oroom[o] = 0, oadv[o] = 0, ocan[o] = 0, oread[o] = 0;
   GetWords(olnt, odesc1, IndexF), GetWords(olnt, odesc2, IndexF), GetWords(olnt, odesco, IndexF),
   GetWords(olnt, oactio, IndexF), GetWords(olnt, oflag1, IndexF), GetWords(olnt, oflag2, IndexF),
   GetWords(olnt, ofval, IndexF), GetWords(olnt, otval, IndexF), GetWords(olnt, osize, IndexF), GetWords(olnt, ocapac, IndexF),
   GetWords(olnt, oroom, IndexF), GetWords(olnt, oadv, IndexF), GetWords(olnt, ocan, IndexF), GetWords(olnt, oread, IndexF);
   printf("/objcts/: %d of %d objects { desc1, desc2, desco, actio, flag1, flag2, fval, tval, size, capac, room, adv, can, read; }\n", olnt, omax);
   for (int o = 0; o < olnt; o++)
      printf("{ "), PutMsg(odesc1[o]), printf(", "), PutMsg(odesc2[o]), printf(", "), PutMsg(odesco[o]),
      printf(", %3d, 0x%04x, 0x%04x, %2d, %2d, %5d, %5d, %5d, %d, %3d, ",
         oactio[o], (unsigned)oflag1[o] & 0xffff, (unsigned)oflag2[o] & 0xffff,
         ofval[o], otval[o], osize[o], ocapac[o],
         oroom[o], oadv[o], ocan[o]
      ), PutMsg(oread[o]), printf(" },\n");
// /oindex/:
   const int BalloOX = 98;
// /state/ (continued):
   bloc = oroom[BalloOX - 1];
   printf("/state/ bloc: %d = oroom[%d-1]\n", bloc, BalloOX);
// /oroom2/:
   printf("\n");
   printf("Room 2 Table\n");
   printf("────────────\n");
   const int r2max = 20;
   int r2lnt = GetWord(IndexF);
   int oroom2[20], rroom2[20];
   for (int r2 = 0; r2 < r2max; r2++) oroom2[r2] = 0, rroom2[r2] = 0;
   GetWords(r2lnt, oroom2, IndexF), GetWords(r2lnt, rroom2, IndexF);
   printf("/oroom2/: %d of %d room2 slots { o, r; }\n", r2lnt, r2max);
   for (int r2 = 0; r2 < r2lnt; r2++) printf("{ %3d, %3d },\n", oroom2[r2], rroom2[r2]);
// /cevent/:
   printf("\n");
   printf("Clock Table\n");
   printf("───────────\n");
   const int cmax = 25;
   int clnt = GetWord(IndexF);
   int ctick[25], cactio[25]; bool cflag[25];
   for (int c = 0; c < cmax; c++) ctick[c] = 0, cactio[c] = 0, cflag[c] = false;
   GetWords(clnt, ctick, IndexF), GetWords(clnt, cactio, IndexF), GetFlags(clnt, cflag, IndexF);
   printf("/cevent/: %d of %d clock events { tick, actio, flag; }\n", clnt, cmax);
   for (int c = 0; c < clnt; c++) printf("{ %3d, %2d, %5s },\n", ctick[c], cactio[c], cflag[c]? "true": "false");
// /vill/:
   printf("\n");
   printf("Villain Table\n");
   printf("─────────────\n");
   const int vmax = 4;
   int vlnt = GetWord(IndexF);
   int villns[4], vprob[4], vopps[4], vbest[4], vmelee[4];
   for (int v = 0; v < vmax; v++) villns[v] = 0, vprob[v] = 0, vopps[v] = 0, vbest[v] = 0, vmelee[v] = 0;
   GetWords(vlnt, villns, IndexF), GetWords(vlnt, vprob, IndexF), GetWords(vlnt, vopps, IndexF), GetWords(vlnt, vbest, IndexF), GetWords(vlnt, vmelee, IndexF);
   printf("/vill/: %d of %d villains { villns, prob, opps, best, melee; }\n", vlnt, vmax);
   for (int v = 0; v < vlnt; v++) printf("{ %2d, %d, %d, %2d, %d },\n", villns[v], vprob[v], vopps[v], vbest[v], vmelee[v]);
// /advs/:
   printf("\n");
   printf("Adventurer Table\n");
   printf("────────────────\n");
   const int amax = 4;
   int alnt = GetWord(IndexF);
   int aroom[4], ascore[4], avehic[4], aobj[4], aactio[4], astren[4], aflag[4];
   for (int a = 0; a < amax; a++)
      aroom[a] = 0, ascore[a] = 0, avehic[a] = 0, aobj[a] = 0, aactio[a] = 0, astren[a] = 0, aflag[a] = 0;
   GetWords(alnt, aroom, IndexF), GetWords(alnt, ascore, IndexF), GetWords(alnt, avehic, IndexF),
   GetWords(alnt, aobj, IndexF), GetWords(alnt, aactio, IndexF), GetWords(alnt, astren, IndexF), GetWords(alnt, aflag, IndexF);
   printf("/advs/: %d of %d adventurers { room, score, vehic, obj, actio, stren, flag; }\n", alnt, amax);
   for (int a = 0; a < alnt; a++) printf("{ %3d, %d, %d, %3d, %d, %d, 0x%02x },\n", aroom[a], ascore[a], avehic[a], aobj[a], aactio[a], astren[a], (unsigned)aflag[a]);
// /star/:
   int strbit = GetWord(IndexF), mbase = GetWord(IndexF);
   printf("/star/: Star Mask = %d, Melee Start = %d\n", strbit, mbase);
// /rmsg/:
   printf("\n");
   printf("Message Table\n");
   printf("─────────────\n");
   const int mmax = 1700;
   int mlnt = GetWord(IndexF);
   long rtext[1700]; for (int m = 0; m < mmax; m++) rtext[m] = 0L;
   GetLongs(mlnt, rtext, IndexF);
   printf("/rmsg/: %d of %d messages { text; }\n", mlnt, mmax);
   for (int m = 0; m < mlnt; m++) PutMsg(rtext[m]), printf(",\n");
// Initialization done.
   fclose(IndexF);
   if (IOErrs > 0) { printf("I can't read %s: %d error(s) found.", MyIndexFile, IOErrs); return EXIT_FAILURE; }
   const char *MyStoryFile = "dtext.dat";
   FILE *StoryF = fopen(MyStoryFile, "rb"); if (StoryF == NULL) { printf("I can't open %s.\n", MyStoryFile); return EXIT_FAILURE; }
   putchar('\n');
   printf("String Table\n");
   printf("────────────\n");
   long exx = 0L;
   char buf[0x80];
   const size_t bufn = sizeof buf;
   buf[bufn - 1] = '\0';
   for (int m = 0; m < mlnt; m++) {
      long x = rtext[m];
      if (x >= exx) continue; else exx = x, x = -x;
      size_t n; bool first = true, last = false;
      while (!last) {
         if (first) printf("#%06ld", x), first = false; else printf("       ");
         last = GetRec(StoryF, &x, &n, buf);
         printf(":%s\n", buf);
         x++;
      }
   }
   fclose(StoryF);
   return EXIT_SUCCESS;
}
