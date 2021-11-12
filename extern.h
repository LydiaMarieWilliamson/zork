// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).

// The functions for dungeon.

// The remnant of f2c.h (begin)
// Assumes C99, which is now (well into the 21st century) POSIX.
// That means: boolean types, function prototypes, ‟rb” and ‟wb” for fopen(), ‟const”, ‟void”, etc.
#include <stdbool.h>
#include <stdlib.h> // For abs().
#include <stdio.h>

// This type will be nativized to ‟bool”, after it's made OK to do so.
typedef int Bool; // Logical.

#define min(A, B)	((A) <= (B)? (A): (B))
#define max(A, B)	((A) >= (B)? (A): (B))

// local.c:
bool protct(void);
bool wizard(void);

// The remnant of f2c.h (begin)
extern unsigned IOErrs;
FILE *OpenInF(const char *File, const char *Mode);
int GetWord(FILE *InF);
long GetLong(FILE *InF);
void GetWords(int Lim, int *WordP, FILE *InF);
void GetLongs(int Lim, long *LongP, FILE *InF);
void GetFlags(int Lim, bool *FlagP, FILE *InF);

void more_init(void);
char *more_input(char *, size_t);
void more_output(const char *, ...);
// The remnant of f2c.h (end)

// actors.c:
bool aappli(int);
void thiefd(void);

// ballop.c:
bool ballop(int);

// clockr.c:
void cevapp(int);

// demons.c:
void fightd(void);
int blow(int, int, int, bool, int);
void swordd(void);

// dgame.c:
void game_(void);

// dinit.c:
bool init(int AC, char *AV[]);

// dso1.c:
void princr(bool, int);
void invent(int);
void princo(int, int);

// dso2.c:
bool moveto(int, int);
void score(bool);
void scrupd(int);

// dso3.c:
bool findxt(int, int);
int fwim(int, int, int, int, int, bool);
bool yesno(int, int, int);

// dso4.c:
int robadv(int, int, int, int);
int robrm(int, int, int, int, int);
bool winnin(int, int);
int fights(int, bool);
int vilstr(int);

// dso5.c:
long gttime(void);
bool opncls(int, int, int);
bool lit(int);
int weight(int, int, int);

// dso6.c:
bool ghere(int, int);
int mrhere(int);

// dso7.c:
void encryp(const char *, char *);
void cpgoto(int);
void cpinfo(int, int);

// dsub.c:
void rspeak(int);
void rspsub(int, int);
void rspsb2(int, int, int);
bool objact(void);
void bug(int, int);
void newsta(int, int, int, int, int);
bool qhere(int, int);
bool qempty(int);
void jigsup(int);
int oactor(int);
bool prob(int, int);
bool rmdesc(int);
bool rappli(int);

// dverb1.c:
bool take(bool);
bool drop(void);
bool put(void);
void valuac(int);

// dverb2.c:
void savegm(void);
void rstrgm(void);
bool walk(void);

// gdt.c:
void gdt(void);

// lightp.c:
bool lightp(int);

// nobjs.c:
bool nobjs(int);

// np1.c:
int sparse(const int *, int, bool);

// np2.c:
int getobj(int, int, int);
int schlst(int, int, int, int, int, int);

// np3.c:
bool synmch(void);

// np.c:
void rdline(char *, size_t, int);
bool parse(char *, bool);
void orphan(int, int, int, int, int);

// nrooms.c:
bool rappl2(int);

// objcts.c:
bool oappli(int, int);

// rooms.c:
bool rappl1(int);

// rtim.c:
long time2001(void);
void inirnd(long);
int rnd(int);
void exit_(void);

// sobjs.c:
bool sobjs(int, int);

// sverbs.c:
bool sverbs(int);

// verbs.c:
bool vappli(int);
bool clockd(void);

// villns.c:
bool trollp(void);
bool cyclop(void);
bool thiefp(void);
