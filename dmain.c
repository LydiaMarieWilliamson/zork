// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// These are the initialized definitions of the common blocks corresponding to the ‟data” statements in the orignal Fortran source,
// as well as the definition of the common block variables.

// MISCELLANEOUS VARIABLES

// Unlisted:
// common /star/
// int mbase, strbit;
struct starCB star;

// DUNGEON, PAGE 2

// DATA STATEMENTS FOR CONSTANT ARRAYS

// common /vers/
const int vmaj = 2, vmin = 8;
const char vedit = 'A';

// common /bats/
const int batdrp[] = { 66, 67, 68, 69, 70, 71, 72, 65, 73 };
const size_t batdrpN = sizeof batdrp/sizeof batdrp[0];

// common /hyper/
const int hfactr = 500;

// parser.h:
// common /synflg/
// enum synflgCB; // Declared and defined in common.h.

// common /objflg/
// enum objflgCB; // Declared and defined in common.h.

// screen.h:
// common /screen/
struct screenCB screen = (struct screenCB){
   fromdr: 0, scolrm: 0, scolac: 0,
   scoldr: { 1024, 153, 5120, 154, 3072, 152, 7168, 151 },
   scolwl: { 151, 207, 3072, 152, 208, 7168, 153, 206, 5120, 154, 205, 1024 }
};

// puzzle.h:
// common /puzzle/
struct puzzleCB puzzle = (struct puzzleCB){
   cpdr: { 1024, -8, 2048, -7, 3072, 1, 4096, 9, 5120, 8, 6144, 7, 7168, -1, 8192, -9 },
   cpwl: { 205, -8, 206, 8, 207, 1, 208, -1 },
   cpvec: {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 0, -1, 0, 0, -1, 0, 1,
      1, -1, 0, 1, 0, -2, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1,
      1, -3, 0, 0, -1, -1, 0, 1, 1, 0, 0, -1, 0, 0, 0, 1,
      1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
   }
};

// rflag.h:
// common /rflag/
// enum rflagCB; // Declared and defined in common.h.

// rindex.h:
// common /rindex/
// enum rindexCB; // Declared and defined in common.h.

// xsrch.h:
// common /xsrch/
// enum xsrchCB; // Declared and defined in common.h.

// xpars.h:
// common /xpars/
const struct xparsCB xpars = (struct xparsCB){
   xrmask: 0xff, xdmask: 0x7c00, xfmask: 0x03, xfshft: 0x100, xashft: 0x100,
   xelnt: { 1, 2, 3, 3 },
   xnorm: 1, xno: 2, xcond: 3, xdoor: 4, xlflag: 0x8000
};

// oflags.h:
// common /oflags/
// enum oflagsCB; // Declared and defined in common.h.

// oindex.h:
// common /oindex/
// enum oindexCB; // Declared and defined in common.h.

// clock.h:
// common /cindex/
// enum cindexCB; // Declared and defined in common.h.

// advers.h:
// common /aflags/
const int STagA = 0100000;

// common /aindex/
// enum aindexCB; // Declared and defined in common.h.

// verbs.h:
// common /vindex/
// enum vindexCB; // Declared and defined in common.h.

// Main program: dungeo
int main(int AC, char *AV[]) {
// DUNGEON, PAGE 3

// 1) INITIALIZE DATA STRUCTURES
// 2) PLAY GAME

   if (init(AC, AV)) {
      game_();
   }
// 						!IF INIT, PLAY GAME.
   exit_();
// 						!DONE
   return 0;
}
