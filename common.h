// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).

// The common block structures and variable declarations used in dungeon.

// These are the structures which encapsulate the variables contained in common blocks, in the original Fortran source,
// as well as #defines that which corresponds to the aliasing given by the ‟equivalence” statements in the source.
// Everything is collated together because it was never really modular in the first place:
// most includes were included in most Fortran files.

// Unlisted:
// common /star/
extern struct starCB {
   int mbase, strbit;
} star;

// common /time/
extern struct timeCB {
   int pltime, shour, smin, ssec;
} time_;

// common /vers/
extern const struct versCB {
   int vmaj, vmin;
   char vedit;
} vers;

// common /hyper/
extern const struct hyperCB {
   int hfactr;
} hyper;

// common /bats/
extern const struct batsCB {
   const int batdrp[9];
} bats;

// parser.h:
// Parser Output
// common /prsvec/
extern struct prsvecCB {
   int prsa, prsi, prso;
   Bool prswon;
   int prscon;
} prsvec;

// Parser State
// common /orphs/
extern struct orphsCB {
   int oflag, oact, oslot, oprep, oname;
} orphs;
#define orp ((int *)&orphs) // int orp[5]; equivalence (orphs.oflag, orp);

// common /last/
extern struct lastCB {
   int lastit;
} last;

// common /pv/
extern struct pvCB {
   int act, o1, o2, p1, p2;
} pv;
#define objvec ((int *)&pv + 1) // int objvec[2]; equivalence (objvec[1], pv.o1);
#define prpvec ((int *)&pv + 3) // int prpvec[2]; equivalence (prpvec[1], pv.p1);
#define pvec ((int *)&pv) // int pvec[5]; equivalence (pvec, pv.act);

// common /syntax/
extern struct syntaxCB {
   int vflag, dobj, dfl1, dfl2, dfw1, dfw2;
   int iobj, ifl1, ifl2, ifw1, ifw2;
} syntax;
#define syn ((int *)&syntax) // int syn[11]; equivalence (syntax.vflag, syn);

// Syntax flags
// common /synflg/
enum synflgCB {
   DirS = 0x4000, IndS = 0x2000, StdS = 0x1000, FlipS = 0x800, DrivS = 0x400, VMaskS = 0x1ff
};

// Object flags
// common /objflg/
enum objflgCB {
   AbitV = 0x4000, RbitV = 0x2000, TbitV = 0x1000, CbitV = 0x800, EbitV = 0x400, FbitV = 0x200, PMaskV = 0x1ff
};

// vocab.h:
// Vocabularies
// common /buzvoc/ int bvoc[20];
extern const int bvoc[];

// common /prpvoc/ int pvoc[45];
extern const int pvoc[];

// common /dirvoc/ int dvoc[75];
extern const int dvoc[];

// common /adjvoc/ int avoc[405];
extern const int avoc[];

// common /vrbvoc/ int vvoc[935];
extern const int vvoc[];

// common /objvoc/ int ovoc[1021];
extern const int ovoc[];

// gamestat.h:
// Game State
// common /play/
extern struct playCB {
   int winner, here;
   Bool telflg;
} play;

// rooms.h:
// Rooms
// common /rooms/
extern struct roomsCB {
   int rlnt, rdesc1[200], rdesc2[200], rexit[200], ractio[200], rval[200], rflag[200];
} rooms;
#define eqr ((int *)&rooms + 1) // int eqr[5][200]; equivalence(rdesc1, eqr);
#define rrand ((int *)&rooms + 601) // int rrand[200]; equivalence(rval, rrand);

// rflag.h:
// Room flags
// common /rflag/
enum rflagCB {
   SeenR = 0x8000, LightR = 0x4000, LandR = 0x2000, WaterR = 0x1000,
   AirR = 0x800, SacrdR = 0x400, FillR = 0x200, MungR = 0x100,
   BuckR = 0x80, HouseR = 0x40, NWallR = 0x20, EndR = 0x10
};

// rindex.h:
// common /rindex/
extern const struct rindexCB {
   int whous, lroom, cella, mtrol, maze1, mgrat, maz15, fore1, fore3, clear, reser, strea, egypt, echor, tshaf, bshaf, mmach, dome, mtorc, carou, riddl, lld2, temp1, temp2, maint, blroo, treas, rivr1, rivr2, rivr3, mcycl, rivr4, rivr5, fchmp, falls, mbarr, mrain, pog, vlbot, vair1, vair2, vair3, vair4, ledg2, ledg3, ledg4, msafe, cager, caged, twell, bwell, alice, alism, alitr, mtree, bkent, bkvw, bktwi, bkvau, bkbox, crypt, tstrs, mrant, mreye, mra, mrb, mrc, mrg, mrd, fdoor, mrae, mrce, mrcw, mrge, mrgw, mrdw, inmir, scorr, ncorr, parap, cell, pcell, ncell, cpant, cpout, cpuzz;
} rindex_;

// xsrch.h:
// common /xsrch/
extern const struct xsrchCB {
   int xmin, xmax, xdown, xup, xnorth, xsouth, xenter, xexit, xeast, xwest;
} xsrch;

// objects.h:
// Objects
// common /objcts/
extern struct objctsCB {
   int olnt, odesc1[220], odesc2[220], odesco[220], oactio[220], oflag1[220], oflag2[220], ofval[220], otval[220], osize[220], ocapac[220], oroom[220], oadv[220], ocan[220], oread[220];
} objcts;
#define eqo ((int *)&objcts + 1) // int eqo[14][220]; equivalence(odesc1, eqo);

// common /oroom2/
extern struct oroom2CB {
   int r2lnt, oroom2[20], rroom2[20];
} oroom2_;

// oflags.h:
// Object flags
// common /oflags/
enum oflagsCB {
   VisiO = 0x8000, ReadO = 0x4000, TakeO = 0x2000, DoorO = 0x1000,
   TranO = 0x800, FoodO = 0x400, NDscO = 0x200, DrnkO = 0x100,
   ContO = 0x80, LiteO = 0x40, VictO = 0x20, BurnO = 0x10,
   FlamO = 8, ToolO = 4, TurnO = 2, OnO = 1,
   FindO = 0x8000, SlepO = 0x4000, ScrDO = 0x2000, TieO = 0x1000,
   ClmbO = 0x800, ActrO = 0x400, WeapO = 0x200, FiteO = 0x100,
   VillO = 0x80, StagO = 0x40, TryO = 0x20, NoChO = 0x10,
   OpenO = 8, TChO = 4, VehO = 2, SchO = 1
};

// oindex.h:
// common /oindex/
extern const struct oindexCB {
   int garli, food, gunk, coal, machi, diamo, tcase, bottl, water, rope, knife, sword, lamp, blamp, rug, leave, troll, axe, rknif, keys, ice, bar, coffi, torch, tbask, fbask, irbox, ghost, trunk, bell, book, candl, match, tube, putty, wrenc, screw, cyclo, chali, thief, still, windo, grate, door, hpole, leak, rbutt, raili, pot, statu, iboat, dboat, pump, rboat, stick, buoy, shove, ballo, recep, guano, brope, hook1, hook2, safe, sslot, brick, fuse, gnome, blabe, dball, tomb, lcase, cage, rcage, spher, sqbut, flask, pool, saffr, bucke, ecake, orice, rdice, blice, robot, ftree, bills, portr, scol, zgnom, egg, begg, baubl, canar, bcana, ylwal, rdwal, pindr, rbeam, odoor, qdoor, cdoor, num1, num8, warni, cslit, gcard, stldr, hands, wall, lungs, sailo, aviat, teeth, itobj, every, valua, oplay, wnort, gwate, master;
} oindex;

// clock.h:
// Clock Interrupts
// common /cevent/
extern struct ceventCB {
   int clnt, ctick[25], cactio[25];
   Bool cflag[25];
} cevent;
#define eqc ((int *)&cevent + 1) // int eqc[2][25]; equivalence(ctick, eqc);

// common /cindex/
extern const struct cindexCB {
   int cevcur, cevmnt, cevlnt, cevmat, cevcnd, cevbal, cevbrn, cevfus, cevled, cevsaf, cevvlg, cevgno, cevbuc, cevsph, cevegh, cevfor, cevscl, cevzgi, cevzgo, cevste, cevmrs, cevpin, cevinq, cevfol;
} cindex;

// advers.h:
// Adventurers
// common /advs/
extern struct advsCB {
   int alnt, aroom[4], ascore[4], avehic[4], aobj[4], aactio[4], astren[4], aflag[4];
} advs;
#define eqa ((int *)&advs + 1) // int eqa[7][4]; equivalence(aroom, eqa);

// common /aflags/
extern const struct aflagsCB {
   int astag;
} aflags;

// common /aindex/
extern const struct aindexCB {
   int player, arobot, amastr;
} aindex;

// verbs.h:
// Verbs
// common /vindex/
extern const struct vindexCB {
   int cintw, deadxw, frstqw, inxw, outxw, walkiw, fightw, foow, readw, meltw, inflaw, deflaw, alarmw, exorcw, plugw, kickw, wavew, raisew, lowerw, rubw, pushw, untiew, tiew, tieupw, turnw, breatw, knockw, lookw, examiw, shakew, movew, trnonw, trnofw, openw, closew, findw, waitw, spinw, boardw, unboaw, takew, invenw, fillw, eatw, drinkw, burnw, mungw, killw, attacw, swingw, walkw, tellw, putw, dropw, givew, pourw, throww, digw, leapw, stayw, follow, hellow, lookiw, lookuw, pumpw, windw, clmbw, clmbuw, clmbdw, trntow;
} vindex;

// flags.h:
// Flags
// common /findex/
extern struct findexCB {
   Bool trollf, cagesf, bucktf, caroff, carozf, lwtidf, domef, glacrf, echof, riddlf, lldf, cyclof, magicf, litldf, safef, gnomef, gnodrf, mirrmf, egyptf, onpolf, blabf, brieff, superf, buoyf, grunlf, gatef, rainbf, cagetf, empthf, deflaf, glacmf, frobzf, endgmf, badlkf, thfenf, singsf, mrpshf, mropnf, wdopnf, mr1f, mr2f, inqstf, follwf, spellf, cpoutf, cpushf;
   int btief, binff, rvmnt, rvclr, rvcyc, rvsnd, rvgua, orrug, orcand, ormtch, orlamp, mdir, mloc, poleuf, quesno, nqatt, corrct, lcell, pnumb, acell, dcell, cphere;
} findex;
#define flags ((Bool *)&findex) // Bool flags[46]; equivalence(flags, trollf);
#define switch_ ((int *)&findex + 46) // int switch_[22]; equivalence(switch_, btief);

// debug.h:
// common /debug/
extern struct debugCB {
   int dbgflg, prsflg, gdtflg;
} debug;
#ifdef ALLOW_GDT
extern Bool dflag;
#endif

// villians.h:
// Villains And Demons
// common /hack/
extern struct hackCB {
   int thfpos;
   Bool thfflg, thfact, swdact;
   int swdsta;
} hack;

// common /vill/
extern struct villCB {
   int vlnt, villns[4], vprob[4], vopps[4], vbest[4], vmelee[4];
} vill;
#define eqv ((int *)&vill + 1) // int eqv[5][4]; equivalence(villns, eqv);

// state.h:
// common /state/
extern struct stateCB {
   int moves, deaths, rwscor, mxscor, mxload, ltshft, bloc, mungrm, hs, egscor, egmxsc;
} state;

// curxt.h:
// Current Exits
// common /curxt/
extern struct curxtCB {
   int xtype, xroom1, xstrng, xactio, xobj;
} curxt;
#define xflag ((int *)&curxt + 4) // int xflag; equivalence(xflag, xobj);

// xpars.h:
// common /xpars/
extern const struct xparsCB {
   int xrmask, xdmask, xfmask, xfshft, xashft, xelnt[4], xnorm, xno, xcond, xdoor, xlflag;
} xpars;

// io.h:
// I/O Variables
// common /input/
extern struct inputCB {
   int inlnt;
   char inbuf[78];
} input;

// screen.h:
// Screen Of Light
// common /screen/
extern struct screenCB {
   int fromdr, scolrm, scolac;
   const int scoldr[8], scolwl[12];
} screen;

// mindex.h:
// Message Index
// common /rmsg/
extern struct rmsgCB {
   int mlnt, mrloc, rtext[1050];
} rmsg;

// exits.h:
// Exits
// common /exits/
extern struct exitsCB {
   int xlnt, travel[900];
} exits;

// puzzle.h:
// Puzzle Room State
// common /puzzle/
extern struct puzzleCB {
   const int cpdr[16], cpwl[8];
   int cpvec[64];
} puzzle;
