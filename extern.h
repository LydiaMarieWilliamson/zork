#ifndef OnceOnlyExtern_h
#define OnceOnlyExtern_h

// The functions for dungeon.
// Assumes C99, which is now (well into the 21st century) POSIX.
// That means: boolean types, function prototypes, "rb" and "wb" for fopen, "const", "void", etc.
#include <stdbool.h>

#define BINREAD "rb"
#define BINWRITE "wb"

typedef int Bool;

#define abs(X)		((X) >= 0? (X): -(X))
#define min(A, B)	((A) <= (B)? (A): (B))
#define max(A, B)	((A) >= (B)? (A): (B))

// local.c:
Bool protected(void);
Bool wizard(void);

// supp.c:
void more_init(void);
void more_output(const char *);
void more_input(void);

// actors.c:
Bool aappli_(int);
void thiefd_(void);

// ballop.c:
Bool ballop_(int);

// clockr.c:
void cevapp_(int);

// demons.c:
void fightd_(void);
int blow_(int, int, int, Bool, int);
void swordd_(void);

// dgame.c:
void game_(void);

// dinit.c:
Bool init_(void);

// dso1.c:
void princr_(Bool, int);
void invent_(int);
void princo_(int, int);

// dso2.c:
Bool moveto_(int, int);
void score_(Bool);
void scrupd_(int);

// dso3.c:
Bool findxt_(int, int);
int fwim_(int, int, int, int, int, Bool);
Bool yesno_(int, int, int);

// dso4.c:
int robadv_(int, int, int, int);
int robrm_(int, int, int, int, int);
Bool winnin_(int, int);
int fights_(int, Bool);
int vilstr_(int);

// dso5.c:
int gttime_(void);
Bool opncls_(int, int, int);
Bool lit_(int);
int weight_(int, int, int);

// dso6.c:
Bool ghere_(int, int);
int mrhere_(int);

// dso7.c:
void encryp_(const char *, char *);
void cpgoto_(int);
void cpinfo_(int, int);

// dsub.c
void rspeak_(int);
void rspsub_(int, int);
void rspsb2_(int, int, int);
Bool objact_(void/*int*/);
void bug_(int, int);
void newsta_(int, int, int, int, int);
Bool qhere_(int, int);
Bool qempty_(int);
void jigsup_(int);
int oactor_(int);
Bool prob_(int, int);
Bool rmdesc_(int);
Bool rappli_(int);

// dverb1.c:
Bool take_(Bool);
Bool drop_(void/*Bool*/);
Bool put_(void/*Bool*/);
void valuac_(int);

// dverb2.c:
void savegm_(void);
void rstrgm_(void);
Bool walk_(void/*int*/);

// gdt.c:
void gdt_(void);

// lightp.c:
Bool lightp_(int);

// nobjs.c:
Bool nobjs_(int/*, int*/);

// np1.c:
int sparse_(const int *, int, Bool);

// np2.c:
int getobj_(int, int, int);
int schlst_(int, int, int, int, int, int);

// np3.c:
Bool synmch_(void/*int*/);

// np.c:
void rdline_(char *, int);
Bool parse_(char *, Bool);
void orphan_(int, int, int, int, int);

// nrooms.c:
Bool rappl2_(int);

// objcts.c:
Bool oappli_(int, int);

// rooms.c:
Bool rappl1_(int);

// rtim.c:
void itime_(int *, int *, int *);
int rnd_(int);
void exit_(void);

// sobjs.c:
Bool sobjs_(int, int);

// sverbs.c:
Bool sverbs_(int);

// verbs.c:
Bool vappli_(int);
Bool clockd_(void/*int*/);

// villns.c:
Bool trollp_(void/*int*/);
Bool cyclop_(void/*int*/);
Bool thiefp_(void/*int*/);

#endif // OnceOnly
