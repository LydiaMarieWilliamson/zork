// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

static bool infest(int);

// Intermove fight demon
void fightd(void) {
// Initialized data
   const int rout = 1;

// System generated locals
   int i__1, i__2;

// Local variables
   bool f;
   int i, j, ra;
   int obj;
   int res;
   int out;

// FIGHTD, PAGE 2

   i__1 = vill.vlnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP THRU VILLAINS.
      vill.vopps[i - 1] = 0;
// 						!CLEAR OPPONENT SLOT.
      obj = vill.villns[i - 1];
// 						!GET OBJECT NO.
      ra = objcts.oactio[obj - 1];
// 						!GET HIS ACTION.
      if (play.here != objcts.oroom[obj - 1]) {
         goto L2200;
      }
// 						!ADVENTURER STILL HERE?
      if (obj == ThiefOX && findex_0.thfenf) {
         goto L2400;
      }
// 						!THIEF ENGROSSED?
      if (objcts.ocapac[obj - 1] >= 0) {
         goto L2050;
      }
// 						!YES, VILL AWAKE?
      if (vill.vprob[i - 1] == 0 || !prob(vill.vprob[i - 1], vill.vprob[i - 1])) {
         goto L2025;
      }
      objcts.ocapac[obj - 1] = (i__2 = objcts.ocapac[obj - 1], abs(i__2));
      vill.vprob[i - 1] = 0;
      if (ra == 0) {
         goto L2400;
      }
// 						!ANYTHING TO DO?
      prsvec.prsa = InXW;
// 						!YES, WAKE HIM UP.
      f = oappli(ra, 0);
      goto L2400;
// 						!NOTHING ELSE HAPPENS.

   L2025:
      vill.vprob[i - 1] += 10;
// 						!INCREASE WAKEUP PROB.
      goto L2400;
// 						!NOTHING ELSE.

   L2050:
      if ((objcts.oflag2[obj - 1] & FiteO) == 0) {
         goto L2100;
      }
      vill.vopps[i - 1] = obj;
// 						!FIGHTING, SET UP OPP.
      goto L2400;

   L2100:
      if (ra == 0) {
         goto L2400;
      }
// 						!NOT FIGHTING,
      prsvec.prsa = FrstQW;
// 						!SET UP PROBABILITY
      if (!oappli(ra, 0)) {
         goto L2400;
      }
// 						!OF FIGHTING.
      objcts.oflag2[obj - 1] |= FiteO;
      vill.vopps[i - 1] = obj;
// 						!SET UP OPP.
      goto L2400;

   L2200:
      if ((objcts.oflag2[obj - 1] & FiteO) == 0 || ra == 0) {
         goto L2300;
      }
      prsvec.prsa = FightW;
// 						!HAVE A FIGHT.
      f = oappli(ra, 0);
   L2300:
      if (obj == ThiefOX) {
         findex_0.thfenf = false;
      }
// 						!TURN OFF ENGROSSED.
      advs.aflag[PlayerAX - 1] &= ~STagA;
      objcts.oflag2[obj - 1] &= ~(STagO + FiteO);
      if (objcts.ocapac[obj - 1] >= 0 || ra == 0) {
         goto L2400;
      }
      prsvec.prsa = InXW;
// 						!WAKE HIM UP.
      f = oappli(ra, 0);
      objcts.ocapac[obj - 1] = (i__2 = objcts.ocapac[obj - 1], abs(i__2));
   L2400:
      ;
   }
// FIGHTD, PAGE 3

// NOW DO ACTUAL COUNTERBLOWS.

   out = 0;
// 						!ASSUME HERO OK.
L2600:
   i__1 = vill.vlnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP THRU OPPS.
      j = vill.vopps[i - 1];
      if (j == 0) {
         goto L2700;
      }
// 						!SLOT EMPTY?
      prsvec.prscon = 1;
// 						!STOP CMD STREAM.
      ra = objcts.oactio[j - 1];
      if (ra == 0) {
         goto L2650;
      }
// 						!VILLAIN ACTION?
      prsvec.prsa = FightW;
// 						!SEE IF
      if (oappli(ra, 0)) {
         goto L2700;
      }
// 						!SPECIAL ACTION.
   L2650:
      res = blow(PlayerAX, j, vill.vmelee[i - 1], false, out);
// 						!STRIKE BLOW.
      if (res < 0) {
         return;
      }
// 						!IF HERO DEAD, EXIT.
      if (res == rout) {
         out = rnd(3) + 2;
      }
// 						!IF HERO OUT, SET FLG.
   L2700:
      ;
   }
   --out;
// 						!DECREMENT OUT COUNT.
   if (out > 0) {
      goto L2600;
   }
// 						!IF STILL OUT, GO AGAIN.
}

// Strike blow
int blow(int h, int v, int rmk, bool hflg, int out) {
// System generated locals
   int ret_val, i__1, i__2;

// Local variables
   int i, j, oa, ra, od, mi, dv, def;
   int tbl;
   int att, res;
   int dweap;
   int pblose;

// MISCELLANEOUS VARIABLES
   bool f;

// Initialized data
   const int rmiss = 0;
   const int rout = 1;
   const int rkill = 2;
   const int rstag = 5;
   const int rlose = 6;
   const int rhes = 7;
   const int rsit = 8;
   static const int def1r[3] = { 1, 2, 3 };
   static const int def2r[4] = { 13, 23, 24, 25 };
   static const int def3r[5] = { 35, 36, 46, 47, 57 };
   static const int rvectr[66] = {
      0, 0, 0, 0, 5, 5, 1, 1, 2, 2, 2, 2,
      0, 0, 0, 0, 0, 5, 5, 3, 3, 1,
      0, 0, 0, 5, 5, 3, 3, 3, 1, 2, 2, 2,
      0, 0, 0, 0, 0, 5, 5, 3, 3, 4, 4,
      0, 0, 0, 5, 5, 3, 3, 3, 4, 4, 4,
      0, 5, 5, 3, 3, 3, 3, 4, 4, 4
   };
   static const int rstate[45] = {
      5000, 3005, 3008, 4011, 3015, 3018, 1021, 0, 0,
      5022, 3027, 3030, 4033, 3037, 3040, 1043, 0, 0,
      4044, 2048, 4050, 4054, 5058, 4063, 4067, 3071, 1074,
      4075, 1079, 4080, 4084, 4088, 4092, 4096, 4100, 1104,
      4105, 2109, 4111, 4115, 4119, 4123, 4127, 3131, 3134
   };

// BLOW, PAGE 3

   ra = objcts.oactio[v - 1];
// 						!GET VILLAIN ACTION,
   dv = objcts.odesc2[v - 1];
// 						!DESCRIPTION.
   ret_val = rmiss;
// 						!ASSUME NO RESULT.
#if defined ALLOW_GDT
   more_output("BLOW 10-- %7d%7d%7d      %c%7d\n", h, v, rmk, hflg ? 'T' : 'F', out);
#endif
   if (!(hflg)) {
      goto L1000;
   }
// 						!HERO STRIKING BLOW?

// HERO IS ATTACKER, VILLAIN IS DEFENDER.

   pblose = 10;
// 						!BAD LK PROB.
   objcts.oflag2[v - 1] |= FiteO;
   if ((advs.aflag[h - 1] & STagA) == 0) {
      goto L100;
   }
   rspeak(591);
// 						!YES, CANT FIGHT.
   advs.aflag[h - 1] &= ~STagA;
   return ret_val;

L100:
   att = fights(h, true);
// 						!GET HIS STRENGTH.
   oa = att;
   def = vilstr(v);
// 						!GET VILL STRENGTH.
   od = def;
   dweap = 0;
// 						!ASSUME NO WEAPON.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!SEARCH VILLAIN.
      if (objcts.ocan[i - 1] == v && (objcts.oflag2[i - 1] & WeapO) != 0) {
         dweap = i;
      }
// L200:
   }
   if (v == advs.aobj[PlayerAX - 1]) {
      goto L300;
   }
// 						!KILLING SELF?
   if (def != 0) {
      goto L2000;
   }
// 						!DEFENDER ALIVE?
   rspsub(592, dv);
// 						!VILLAIN DEAD.
   return ret_val;

L300:
   jigsup(593);
// 						!KILLING SELF.
   return ret_val;

// VILLAIN IS ATTACKER, HERO IS DEFENDER.

L1000:
   pblose = 50;
// 						!BAD LK PROB.
   advs.aflag[h - 1] &= ~STagA;
   if ((objcts.oflag2[v - 1] & STagO) == 0) {
      goto L1200;
   }
   objcts.oflag2[v - 1] &= ~STagO;
   rspsub(594, dv);
// 						!DESCRIBE.
   return ret_val;

L1200:
   att = vilstr(v);
// 						!SET UP ATT, DEF.
   oa = att;
   def = fights(h, true);
   if (def <= 0) {
      return ret_val;
   }
// 						!DONT ALLOW DEAD DEF.
   od = fights(h, false);
   dweap = (i__1 = fwim(0, WeapO, 0, 0, h, true), abs(i__1));
// 						!FIND A WEAPON.
// BLOW, PAGE 4

// PARTIES ARE NOW EQUIPPED.  DEF CANNOT BE ZERO.
// ATT MUST BE > 0.

L2000:
#if defined ALLOW_GDT
   more_output("BLOW 2050-- %7d%7d%7d%7d%7d\n", att, oa, def, od, dweap);
#endif
   if (def > 0) {
      goto L2100;
   }
// 						!DEF ALIVE?
   res = rkill;
   if (hflg) {
      rspsub(595, dv);
   }
// 						!DEADER.
   goto L3000;

L2100:
   if (def == 2) goto L2300; else if (def > 2) goto L2400;/* else if (def < 2) goto L2200; */
// 						!DEF <2,=2,>2
L2200:
   att = min(att, 3);
// 						!SCALE ATT.
   tbl = def1r[att - 1];
// 						!CHOOSE TABLE.
   goto L2500;

L2300:
   att = min(att, 4);
// 						!SCALE ATT.
   tbl = def2r[att - 1];
// 						!CHOOSE TABLE.
   goto L2500;

L2400:
   att -= def;
// 						!SCALE ATT.
// Computing MIN
   i__1 = 2, i__2 = max(-2, att);
   att = min(i__1, i__2) + 3;
   tbl = def3r[att - 1];

L2500:
   res = rvectr[tbl + rnd(10) - 1];
// 						!GET RESULT.
   if (out == 0) {
      goto L2600;
   }
// 						!WAS HE OUT?
   if (res == rstag) {
      goto L2550;
   }
// 						!YES, STAG--> HES.
   res = rsit;
// 						!OTHERWISE, SITTING.
   goto L2600;
L2550:
   res = rhes;
L2600:
   if (res == rstag && dweap != 0 && prob(25, pblose)) {
      res = rlose;
   }

   mi = rstate[(rmk - 1) * 9 + res];
// 						!CHOOSE TABLE ENTRY.
   if (mi == 0) {
      goto L3000;
   }
   i__1 = mi / 1000;
   i = mi % 1000 + rnd(i__1) + star.mbase + 1;
   j = dv;
   if (!(hflg) && dweap != 0) {
      j = objcts.odesc2[dweap - 1];
   }

#if defined ALLOW_GDT
   more_output("BLOW 2650-- %7d%7d%7d%7d%7d\n", res, mi, i, j, star.mbase);
#endif
   rspsub(i, j);
// 						!PRESENT RESULT.
// BLOW, PAGE 5

// NOW APPLY RESULT

L3000:
   switch (res + 1) {
      case 1:
         goto L4000;
      case 2:
         goto L3100;
      case 3:
         goto L3200;
      case 4:
         goto L3300;
      case 5:
         goto L3400;
      case 6:
         goto L3500;
      case 7:
         goto L3600;
      case 8:
         goto L4000;
      case 9:
         goto L3200;
   }

L3100:
   if (hflg) {
      def = -def;
   }
// 						!UNCONSCIOUS.
   goto L4000;

L3200:
   def = 0;
// 						!KILLED OR SITTING DUCK.
   goto L4000;

L3300:
// Computing MAX
   i__1 = 0, i__2 = def - 1;
   def = max(i__1, i__2);
// 						!LIGHT WOUND.
   goto L4000;

L3400:
// Computing MAX
   i__1 = 0, i__2 = def - 2;
   def = max(i__1, i__2);
// 						!SERIOUS WOUND.
   goto L4000;

L3500:
   if (hflg) {
      goto L3550;
   }
// 						!STAGGERED.
   advs.aflag[h - 1] |= STagA;
   goto L4000;

L3550:
   objcts.oflag2[v - 1] |= STagO;
   goto L4000;

L3600:
   newsta(dweap, 0, play.here, 0, 0);
// 						!LOSE WEAPON.
   dweap = 0;
   if (hflg) {
      goto L4000;
   }
// 						!IF HERO, DONE.
   dweap = (i__1 = fwim(0, WeapO, 0, 0, h, true), abs(i__1));
// 						!GET NEW.
   if (dweap != 0) {
      rspsub(605, objcts.odesc2[dweap - 1]);
   }
// BLOW, PAGE 6

L4000:
   ret_val = res;
// 						!RETURN RESULT.
   if (!(hflg)) {
      goto L4500;
   }
// 						!HERO?
   objcts.ocapac[v - 1] = def;
// 						!STORE NEW CAPACITY.
   if (def != 0) {
      goto L4100;
   }
// 						!DEAD?
   objcts.oflag2[v - 1] &= ~FiteO;
   rspsub(572, dv);
// 						!HE DIES.
   newsta(v, 0, 0, 0, 0);
// 						!MAKE HIM DISAPPEAR.
   if (ra == 0) {
      return ret_val;
   }
// 						!IF NX TO DO, EXIT.
   prsvec.prsa = DeadXW;
// 						!LET HIM KNOW.
   f = oappli(ra, 0);
   return ret_val;

L4100:
   if (res != rout || ra == 0) {
      return ret_val;
   }
   prsvec.prsa = OutXW;
// 						!LET HIM BE OUT.
   f = oappli(ra, 0);
   return ret_val;

L4500:
   advs.astren[h - 1] = -10000;
// 						!ASSUME DEAD.
   if (def != 0) {
      advs.astren[h - 1] = def - od;
   }
   if (def >= od) {
      goto L4600;
   }
   cevent.ctick[CurCX - 1] = 30;
   cevent.cflag[CurCX - 1] = true;
L4600:
   if (fights(h, true) > 0) {
      return ret_val;
   }
   advs.astren[h - 1] = 1 - fights(h, false);
// 						!HE'S DEAD.
   jigsup(596);
   ret_val = -1;
   return ret_val;
}

// Sword intermove demon
void swordd(void) {
// System generated locals
   int i__1, i__2;

// Local variables
   int i, ng;

// SWORDD, PAGE 2

   if (objcts.oadv[SwordOX - 1] != PlayerAX) {
      goto L500;
   }
// 						!HOLDING SWORD?
   ng = 2;
// 						!ASSUME VILL CLOSE.
   if (infest(play.here)) {
      goto L300;
   }
// 						!VILL HERE?
   ng = 1;
   i__1 = MaxDX;
   i__2 = MinDX;
   for (i = MinDX; i__2 < 0 ? i >= i__1 : i <= i__1; i += i__2) {
// 						!NO, SEARCH ROOMS.
      if (!findxt(i, play.here)) {
         goto L200;
      }
// 						!ROOM THAT WAY?
      switch (curxt.xtype) {
         case 1:
            goto L50;
         case 2:
            goto L200;
         case 3:
            goto L50;
         case 4:
            goto L50;
      }
// 						!SEE IF ROOM AT ALL.
   L50:
      if (infest(curxt.xroom1)) {
         goto L300;
      }
// 						!CHECK ROOM.
   L200:
      ;
   }
   ng = 0;
// 						!NO GLOW.

L300:
   if (ng == hack.swdsta) {
      return;
   }
// 						!ANY STATE CHANGE?
   i__2 = ng + 495;
   rspeak(i__2);
// 						!YES, TELL NEW STATE.
   hack.swdsta = ng;
   return;

L500:
   hack.swdact = false;
// 						!DROPPED SWORD,
// return;
// 						!DISABLE DEMON.
}

// Subroutine to test for infested room
static bool infest(int r) {
// System generated locals
   bool ret_val;

   if (!findex_0.endgmf) {
      ret_val = objcts.oroom[CycloOX - 1] == r || objcts.oroom[TrollOX - 1] == r || objcts.oroom[ThiefOX - 1] == r && hack.thfact;
   } else {
      ret_val = r == MrGrX || r == MrGerX || r == MrGwrX || r == InMirRX && findex_1.mloc == MrGrX;
   }
   return ret_val;
}
