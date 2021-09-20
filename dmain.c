// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// DUNGEON-- MAIN PROGRAM
int main(void) {
// 1) INITIALIZE DATA STRUCTURES
// 2) PLAY GAME

   if (init()) {
      game_();
   }
// 						!IF INIT, PLAY GAME.
   exit_();
// 						!DONE
   return 0;
}
