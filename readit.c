#include <stdio.h>
#include <stdbool.h>

#define BalloOX 98

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

// Read a number of boolean values from the index file
void GetFlags(int Lim, bool *FlagP, FILE *InF) {
   while (Lim-- > 0) *FlagP++ = getc(InF);
}

void PutMsg(int X) {
   if (X < 0) printf("#%05d", -X);
   else if (X > 0) printf("?%05d", +X);
   else printf("------");
}

// Dungeon initialization subroutine
int main(void) {
   const char *MyIndexFile = "dtextc.dat";
// Now, restore from the existing index file.
   FILE *IndexF = fopen(MyIndexFile, "r"); if (IndexF == NULL) { printf("I can't open %s.\n", MyIndexFile); return 1; }
// /edit/:
   int Maj = GetWord(IndexF), Min = GetWord(IndexF), Edit = GetWord(IndexF);
   printf("/edit/: %1d.%1d.%1d\n", Maj, Min, Edit);
// /state/: (bloc will be set later, and strbit is from /star/
   int mxscor = GetWord(IndexF), strbit = GetWord(IndexF), egmxsc = GetWord(IndexF), bloc = 0;
   printf("/state/: Max Score = %d, Eg Score = %d\n", mxscor, egmxsc);
// /rooms/: (eqr)
   printf("\n");
   printf("Room Table\n");
   printf("──────────\n");
   const int rmax = 200;
   int rlnt = GetWord(IndexF);
   int rdesc1[200], rdesc2[200], rexit[200], ractio[200], rval[200], rflag[200];
   for (int r = 0; r < rmax; r++) rdesc1[r] = 0, rdesc2[r] = 0, rexit[r] = 0, ractio[r] = 0, rval[r] = 0, rflag[r] = 0;
   GetWords(rlnt, rdesc1, IndexF), GetWords(rlnt, rdesc2, IndexF), GetWords(rlnt, rexit, IndexF), GetPairs(rlnt, ractio, IndexF), GetPairs(rlnt, rval, IndexF), GetWords(rlnt, rflag, IndexF);
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
   printf("/exits/: %d of %d exits { travel; }\n", xlnt, xmax);
   for (int x = 0; x < xlnt; x++) printf("%3u<<8|%3u,\n", ((unsigned)travel[x]&0xffff)>>8, (unsigned)travel[x]&0xff);
// /objcts/: (eqo)
   printf("\n");
   printf("Object Table\n");
   printf("────────────\n");
   const int omax = 220;
   int olnt = GetWord(IndexF);
   int odesc1[220], odesc2[220], odesco[220], oactio[220], oflag1[220], oflag2[220], ofval[220], otval[220], osize[220], ocapac[220], oroom[220], oadv[220], ocan[220], oread[220];
   for (int o = 0; o < omax; o++) odesc1[o] = 0, odesc2[o] = 0, odesco[o] = 0, oactio[o] = 0, oflag1[o] = 0, oflag2[o] = 0, ofval[o] = 0, otval[o] = 0, osize[o] = 0, ocapac[o] = 0, oroom[o] = 0, oadv[o] = 0, ocan[o] = 0, oread[o] = 0;
   GetWords(olnt, odesc1, IndexF), GetWords(olnt, odesc2, IndexF), GetPairs(olnt, odesco, IndexF), GetPairs(olnt, oactio, IndexF), GetWords(olnt, oflag1, IndexF), GetPairs(olnt, oflag2, IndexF), GetPairs(olnt, ofval, IndexF), GetPairs(olnt, otval, IndexF), GetWords(olnt, osize, IndexF), GetPairs(olnt, ocapac, IndexF), GetWords(olnt, oroom, IndexF), GetPairs(olnt, oadv, IndexF), GetPairs(olnt, ocan, IndexF), GetPairs(olnt, oread, IndexF);
   printf("/objcts/: %d of %d objects { desc1, desc2, desco, actio, flag1, flag2, fval, tval, size, capac, room, adv, can, read; }\n", olnt, omax);
   for (int o = 0; o < olnt; o++)
      printf("{ "), PutMsg(odesc1[o]), printf(", "), PutMsg(odesc2[o]), printf(", "), PutMsg(odesco[o]), printf(", %3d, 0x%04x, 0x%04x, %2d, %2d, %5d, %5d, %5d, %d, %3d, ", oactio[o], (unsigned)oflag1[o]&0xffff, (unsigned)oflag2[o]&0xffff, ofval[o], otval[o], osize[o], ocapac[o], oroom[o], oadv[o], ocan[o]), PutMsg(oread[o]), printf(" },\n");
   bloc = oroom[BalloOX - 1];
   printf("/state/ bloc: %d = oroom[%d]\n", bloc, BalloOX);
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
   GetWords(vlnt, villns, IndexF), GetPairs(vlnt, vprob, IndexF), GetPairs(vlnt, vopps, IndexF), GetWords(vlnt, vbest, IndexF), GetWords(vlnt, vmelee, IndexF);
   printf("/vill/: %d of %d villains { villns, prob, opps, best, melee; }\n", vlnt, vmax);
   for (int v = 0; v < vlnt; v++) printf("{ %2d, %d, %d, %2d, %d },\n", villns[v], vprob[v], vopps[v], vbest[v], vmelee[v]);
// /advs/:
   printf("\n");
   printf("Adventurer Table\n");
   printf("────────────────\n");
   const int amax = 4;
   int alnt = GetWord(IndexF);
   int aroom[4], ascore[4], avehic[4], aobj[4], aactio[4], astren[4], aflag[4];
   for (int a = 0; a < amax; a++) aroom[a] = 0, ascore[a] = 0, avehic[a] = 0, aobj[a] = 0, aactio[a] = 0, astren[a] = 0, aflag[a] = 0;
   GetWords(alnt, aroom, IndexF), GetPairs(alnt, ascore, IndexF), GetPairs(alnt, avehic, IndexF), GetWords(alnt, aobj, IndexF), GetWords(alnt, aactio, IndexF), GetWords(alnt, astren, IndexF), GetPairs(alnt, aflag, IndexF);
   printf("/advs/: %d of %d adventurers { room, score, vehic, obj, actio, stren, flag; }\n", alnt, amax);
   for (int a = 0; a < alnt; a++) printf("{ %3d, %d, %d, %3d, %d, %d, 0x%02x },\n", aroom[a], ascore[a], avehic[a], aobj[a], aactio[a], astren[a], (unsigned)aflag[a]);
// /star/: strbit was set, up above.
   int mbase = GetWord(IndexF);
   printf("/star/: Star Mask = %d, Melee Start = %d\n", strbit, mbase);
// /rmsg/:
   printf("\n");
   printf("Message Table\n");
   printf("─────────────\n");
   const int mmax = 1050;
   int mlnt = GetWord(IndexF);
   int rtext[1050]; for (int m = 0; m < mmax; m++) rtext[m] = 0;
   GetWords(mlnt, rtext, IndexF);
   int mrloc = ftell(IndexF);
   printf("/rmsg/: mrloc: %d\n", mrloc);
   printf("%d of %d messages { text; }\n", mlnt, mmax);
   for (int m = 0; m < mlnt; m++) PutMsg(rtext[m]), printf(",\n");
// Initialization done.
   printf("Message Table:\n");
   long X = 0L;
   const char *ZKey = "IanLanceTaylorJr";
   if (fseek(IndexF, X + (long)mrloc, SEEK_SET) == EOF) { fprintf(stderr, "Error seeking database loc %d\n", X); return 1; }
   bool New = true;
   while (true) {
      int Ch = getc(IndexF); if (Ch == EOF) break;
      Ch ^= ZKey[X&0xf]^(X&0xff);
      X++;
      if (Ch == '\0') {
         long X1 = (X + 7)/8*8;
         if (X1 > X) {
            if (fseek(IndexF, X1 + (long)mrloc, SEEK_SET) == EOF) { fprintf(stderr, "Error seeking database loc %d\n", X1); return 1; }
            X = X1;
         }
         putchar('\n'), New = true;
      } else {
         if (New) printf("#%05ld:", 1 + X/8), New = false;
         putchar(Ch);
         if (Ch == '\n') printf("      :");
      }
   }
   fclose(IndexF);
   return 0;
}
