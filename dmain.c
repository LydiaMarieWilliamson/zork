// DUNGEON-- MAIN PROGRAM

// COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142
// ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED
// WRITTEN BY R. M. SUPNIK

#include "extern.h"
#include "common.h"

int main(void) {
// 1) INITIALIZE DATA STRUCTURES
// 2) PLAY GAME

   if (init_()) {
      game_();
   }
// 						!IF INIT, PLAY GAME.
   exit_();
// 						!DONE
   return 0;
}
