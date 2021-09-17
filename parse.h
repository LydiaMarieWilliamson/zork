#ifndef OnceOnlyParse_h
#define OnceOnlyParse_h

// parse.h -- header file for parsing structures used by dungeon

// These structures are only used by the parsing routines.  They are in
// their own file since they are so large.

#ifndef EXTERN
#   define EXTERN extern
#endif

// parser.h:
// common /pv/
EXTERN struct {
   int act, o1, o2, p1, p2;
} pv_;
#define pv_1 pv_
// int objvec[2]; // equivalence (objvec[1], pv_1.o1);
#define objvec ((int *)&pv_1 + 1)
// int prpvec[2]; // equivalence (prpvec[1], pv_1.p1);
#define prpvec ((int *)&pv_1 + 3)
// int pvec[5]; // equivalence (pvec, pv_1.act);
#define pvec ((int *)&pv_1)

// common /syntax/
EXTERN struct {
   int vflag, dobj, dfl1, dfl2, dfw1, dfw2, iobj, ifl1, ifl2, ifw1, ifw2;
} syntax_;
#define syntax_1 syntax_
// int syn[11]; // equivalence (syntax_1.vflag, syn);
#define syn ((int *)&syntax_1)

// Syntax flags
// common /synflg/
#define SDIR (16384)
#define SIND (8192)
#define SSTD (4096)
#define SFLIP (2048)
#define SDRIV (1024)
#define SVMASK (511)

// Object flags
// common /objflg/
#define VABIT (16384)
#define VRBIT (8192)
#define VTBIT (4096)
#define VCBIT (2048)
#define VEBIT (1024)
#define VFBIT (512)
#define VPMASK (511)

// vocab.h:

// VOCABULARIES

// common /buzvoc/
extern const struct buzvoc_1_ {
   int bvoc[20];
} buzvoc_;
#define buzvoc_1 buzvoc_

// common /prpvoc/
extern const struct prpvoc_1_ {
   int pvoc[45];
} prpvoc_;
#define prpvoc_1 prpvoc_

// common /dirvoc/
extern const struct dirvoc_1_ {
   int dvoc[75];
} dirvoc_;
#define dirvoc_1 dirvoc_

// common /adjvoc/ int avoc1[184], avoc2[114], avoc3[106], avocnd;
// int avoc[450]; // equivalence (avoc[1], adjvoc_1.avoc1[1]);
extern const int avoc[];

// common /vrbvoc/ int vvoc1[92], vvoc1a[108], vvoc1b[38], vvoc2[104], vvoc3[136], vvoc4[116], vvoc5[134], vvoc6[117], vvoc7[89], vvocnd;
// int vvoc[950]; // equivalence (vvoc[1], vrbvoc_1.vvoc1[1]);
extern const int vvoc[];

// common /objvoc/ ovoc1[159], ovoc2[144], ovoc3[150], ovoc4[128], ovoc5[111], ovoc6[104], ovoc6a[97], ovoc7[127], ovocnd;
// int ovoc[1050]; // equivalence (ovoc[1], objvoc_1.ovoc1[1]);
extern const int ovoc[];

#endif // OnceOnly
