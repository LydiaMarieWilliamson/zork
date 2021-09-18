#ifndef OnceOnlyFuncs_h
#define OnceOnlyFuncs_h

// funcs.h -- functions for dungeon
// Assumes C99, which is now (well into the 21st century) POSIX.
// That means: boolean types, function prototypes, "rb" and "wb" for fopen, "const", "void", etc.
#include <stdbool.h>

#define BINREAD "rb"
#define BINWRITE "wb"

typedef int Bool;

#define abs(X)		((X) >= 0? (X): -(X))
#define min(A, B)	((A) <= (B)? (A): (B))
#define max(A, B)	((A) >= (B)? (A): (B))

extern Bool protected(void);
extern Bool wizard(void);

extern void more_init(void);
extern void more_output(const char *);
extern void more_input(void);

extern void bug_(int, int);
extern void cevapp_(int);
extern void cpgoto_(int);
extern void cpinfo_(int, int);
extern void encryp_(const char *, char *);
extern void exit_(void);
extern void fightd_(void);
extern void game_(void);
extern void gdt_(void);
extern int gttime_(void);
extern void invent_(int);
extern void itime_(int *, int *, int *);
extern void jigsup_(int);
extern void newsta_(int, int, int, int, int);
extern void orphan_(int, int, int, int, int);
extern void princo_(int, int);
extern void princr_(Bool, int);
extern void rdline_(char *, int);
extern void rspeak_(int);
extern void rspsb2_(int, int, int);
extern void rspsub_(int, int);
extern void rstrgm_(void);
extern void savegm_(void);
extern void score_(Bool);
extern void scrupd_(int);
extern void swordd_(void);
extern void thiefd_(void);
extern void valuac_(int);
extern int blow_(int, int, int, Bool, int);
extern int fights_(int, Bool);
extern int fwim_(int, int, int, int, int, Bool);
extern int getobj_(int, int, int);
extern int schlst_(int, int, int, int, int, int);
extern int mrhere_(int);
extern int oactor_(int);
extern int rnd_(int);
extern int robadv_(int, int, int, int);
extern int robrm_(int, int, int, int, int);
extern int sparse_(const int *, int, Bool);
extern int vilstr_(int);
extern int weight_(int, int, int);
extern Bool aappli_(int);
extern Bool ballop_(int);
extern Bool clockd_(void/*int*/);
extern Bool cyclop_(void/*int*/);
extern Bool drop_(void/*Bool*/);
extern Bool findxt_(int, int);
extern Bool ghere_(int, int);
extern Bool init_(void);
extern Bool lightp_(int);
extern Bool lit_(int);
extern Bool moveto_(int, int);
extern Bool nobjs_(int/*, int*/);
extern Bool oappli_(int, int);
extern Bool objact_(void/*int*/);
extern Bool opncls_(int, int, int);
extern Bool parse_(char *, Bool);
extern Bool prob_(int, int);
extern Bool put_(void/*Bool*/);
extern Bool rappli_(int);
extern Bool rappl1_(int);
extern Bool rappl2_(int);
extern Bool rmdesc_(int);
extern Bool sobjs_(int, int);
extern Bool sverbs_(int);
extern Bool synmch_(void/*int*/);
extern Bool take_(Bool);
extern Bool thiefp_(void/*int*/);
extern Bool trollp_(void/*int*/);
extern Bool qempty_(int);
extern Bool qhere_(int, int);
extern Bool vappli_(int);
extern Bool walk_(void/*int*/);
extern Bool winnin_(int, int);
extern Bool yesno_(int, int, int);

#endif // OnceOnly
