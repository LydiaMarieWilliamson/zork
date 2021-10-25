// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).

// The common block structures and variable declarations used in dungeon.

// These are the structures which encapsulate the variables contained in common blocks, in the original Fortran source,
// as well as #defines that which corresponds to the aliasing given by the ‟equivalence” statements in the source.
// Everything is collated together because it was never really modular in the first place:
// most includes were included in most Fortran files.

#include <stdio.h>

// Unlisted:
// common /star/
extern struct starCB {
   int mbase, strbit;
} star;

// common /time/
extern struct timeCB {
   long pltime, stime;
} time_;

// common /vers/
extern const int vmaj, vmin;
extern const char vedit;

// common /hyper/
extern const int hfactr;

// common /bats/
extern const int batdrp[];
extern const size_t batdrpN;

// parser.h:
// Parser Output
// common /prsvec/
extern struct prsvecCB {
   int prsa, prsi, prso;
   bool prswon;
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
#define eqr ((int *)&rooms + 1) // int eqr[6][200]; equivalence(rdesc1, eqr);
#define rrand (rooms.rval) // int rrand[200]; equivalence(rval, rrand);

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
enum rindexCB {
   WHousRX = 2, LRoomRX = 8, CellaRX = 9, MTrolRX = 10, Maze1RX = 11, MGratRX = 25, Maz15RX = 30, Fore1RX = 31,
   Fore3RX = 33, ClearRX = 36, ReserRX = 40, StreaRX = 42, EgyptRX = 44, EchoRRX = 49, TShafRX = 61, BShafRX = 76,
   MMachRX = 77, DomeRX = 79, MTorcRX = 80, CarouRX = 83, RiddlRX = 91, Lld2RX = 94, Temp1RX = 96, Temp2RX = 97,
   MaintRX = 100, BlRooRX = 102, TreasRX = 103, Rivr1RX = 107, Rivr2RX = 108, Rivr3RX = 109, MCyclRX = 101, Rivr4RX = 112,
   Rivr5RX = 113, FChmpRX = 114, FallsRX = 120, MBarrRX = 119, MRainRX = 121, PogRX = 122, VlBotRX = 126, Vair1RX = 127,
   Vair2RX = 128, Vair3RX = 129, Vair4RX = 130, Ledg2RX = 131, Ledg3RX = 132, Ledg4RX = 133, MSafeRX = 135, CageRRX = 140,
   CageDRX = 141, TWellRX = 142, BWellRX = 143, AliCeRX = 144, AliSmRX = 145, AliTrRX = 146, MTreeRX = 147, BkEntRX = 148,
   BkVwRX = 151, BkTwiRX = 153, BkVauRX = 154, BkBoxRX = 155, CryptRX = 157, TStrsRX = 158, MrAntRX = 159, MrEyeRX = 160,
   MrArX = 161, MrBrX = 162, MrCrX = 163, MrGrX = 164, MrDrX = 165, FDoorRX = 166, MrAerX = 167, MrCerX = 171,
   MrCwrX = 172, MrGerX = 173, MrGwrX = 174, MrDwrX = 176, InMirRX = 177, SCorrRX = 179, NCorrRX = 182, ParapRX = 183,
   CellRX = 184, PCellRX = 185, NCellRX = 186, CpAntRX = 188, CpOutRX = 189, CPuzzRX = 190
};

// xsrch.h:
// common /xsrch/
enum xsrchCB {
   MinDX = 02000, MaxDX = 040000, UpDX = 022000, DownDX = 024000,
   NorthDX = 02000, SouthDX = 012000, EnterDX = 032000, ExitDX = 034000,
   EastDX = 06000, WestDX = 016000
};

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
   VillO = 0x80, STagO = 0x40, TryO = 0x20, NoChO = 0x10,
   OpenO = 8, TChO = 4, VehO = 2, SchO = 1
};

// oindex.h:
// common /oindex/
enum oindexCB {
   GarliOX = 2, FoodOX = 3, GunkOX = 4, CoalOX = 5, MachiOX = 7, DiamoOX = 8, TCaseOX = 9, BottlOX = 10,
   WaterOX = 11, RopeOX = 12, KnifeOX = 13, SwordOX = 14, LampOX = 15, BLampOX = 16, RugOX = 17, LeaveOX = 18,
   TrollOX = 19, AxeOX = 20, RKnifOX = 21, KeysOX = 23, IceOX = 30, BarOX = 26, CoffiOX = 33, TorchOX = 34,
   TBaskOX = 35, FBaskOX = 36, IrBoxOX = 39, GhostOX = 42, TrunkOX = 45, BellOX = 46, BookOX = 47, CandlOX = 48,
   MatchOX = 51, TubeOX = 54, PuttyOX = 55, WrencOX = 56, ScrewOX = 57, CycloOX = 58, ChaliOX = 59, ThiefOX = 61,
   StillOX = 62, WindoOX = 63, GrateOX = 65, DoorOX = 66, HPoleOX = 71, LeakOX = 78, RButtOX = 79, RailiOX = 75,
   PotOX = 85, StatuOX = 86, IBoatOX = 87, DBoatOX = 88, PumpOX = 89, RBoatOX = 90, StickOX = 92, BuoyOX = 94,
   ShoveOX = 96, BalloOX = 98, RecepOX = 99, GuanoOX = 97, BRopeOX = 101, Hook1OX = 102, Hook2OX = 103, SafeOX = 105,
   SSlotOX = 107, BrickOX = 109, FuseOX = 110, GnomeOX = 111, BlaBeOX = 112, DBallOX = 113, TombOX = 119, LCaseOX = 123,
   CageOX = 124, RCageOX = 125, SpherOX = 126, SqButOX = 127, FlaskOX = 132, PoolOX = 133, SaffrOX = 134, BuckeOX = 137,
   ECakeOX = 138, OrIceOX = 139, RdIceOX = 140, BlIceOX = 141, RobotOX = 142, FTreeOX = 145, BillsOX = 148, PortrOX = 149,
   ScolOX = 151, ZGnomOX = 152, EggOX = 154, BEggOX = 155, BaublOX = 156, CanarOX = 157, BCanaOX = 158, YlWalOX = 159,
   RdWalOX = 161, PinDrOX = 164, RBeamOX = 171, ODoorOX = 172, QDoorOX = 173, CDoorOX = 175, Num1OX = 178, Num8OX = 185,
   WarniOX = 186, CSlitOX = 187, GCardOX = 188, StlDrOX = 189, HandsOX = 200, WallOX = 198, LungsOX = 201, SailoOX = 196,
   AviatOX = 202, TeethOX = 197, ItObjOX = 192, EveryOX = 194, ValuaOX = 195, OPlayOX = 193, WNortOX = 205, GWateOX = 209,
   MasterOX = 215
};

// clock.h:
// Clock Interrupts
// common /cevent/
extern struct ceventCB {
   int clnt, ctick[25], cactio[25];
   bool cflag[25];
} cevent;
#define eqc ((int *)&cevent + 1) // int eqc[2][25]; equivalence(ctick, eqc);

// common /cindex/
enum cindexCB {
   CurCX = 1, MntCX = 2, LntCX = 3, MatCX = 4, CndCX = 5, BalCX = 6, BrnCX = 7, FusCX = 8,
   LedCX = 9, SafCX = 10, VlgCX = 11, GnoCX = 12, BucCX = 13, SphCX = 14, EghCX = 15, ForCX = 16,
   SclCX = 17, ZgICX = 18, ZgOCX = 19, SteCX = 20, MrsCX = 21, PinCX = 22, InqCX = 23, FolCX = 24
};

// advers.h:
// Adventurers
// common /advs/
extern struct advsCB {
   int alnt, aroom[4], ascore[4], avehic[4], aobj[4], aactio[4], astren[4], aflag[4];
} advs;
#define eqa ((int *)&advs + 1) // int eqa[7][4]; equivalence(aroom, eqa);

// common /aflags/
extern const int STagA;

// common /aindex/
enum aindexCB {
   PlayerAX = 1, RobotAX = 2, MastrAX = 3
};

// verbs.h:
// Verbs
// common /vindex/
enum vindexCB {
   CIntW = 1, DeadXW = 2, FrstQW = 3, InXW = 4, OutXW = 5, WalkIW = 6, FightW = 7, FooW = 8,
   MeltW = 100, ReadW = 101, InflaW = 102, DeflaW = 103, AlarmW = 104, ExorcW = 105, PlugW = 106, KickW = 107,
   WaveW = 108, RaiseW = 109, LowerW = 110, RubW = 111, PushW = 112, UnTieW = 113, TieW = 114, TieUpW = 115,
   TurnW = 116, BreatW = 117, KnockW = 118, LookW = 119, ExamiW = 120, ShakeW = 121, MoveW = 122, TrnOnW = 123,
   TrnOfW = 124, OpenW = 125, CloseW = 126, FindW = 127, WaitW = 128, SpinW = 129, BoardW = 130, UnboaW = 131,
   TakeW = 132, InvenW = 133, FillW = 134, EatW = 135, DrinkW = 136, BurnW = 137, MungW = 138, KillW = 139,
   AttacW = 141, SwingW = 140, WalkW = 142, TellW = 143, PutW = 144, DropW = 145, GiveW = 146, PourW = 147,
   ThrowW = 148, DigW = 89, LeapW = 91, StayW = 73, FolloW = 85, HelloW = 151, LookIW = 152, LookUW = 153,
   PumpW = 154, WindW = 155, ClmbW = 156, ClmbUW = 157, ClmbDW = 158, TrnToW = 159
};

// flags.h:
// Flags
// common /findex/
extern struct findexCB_0 {
   Bool trollf, cagesf, bucktf, caroff, carozf, lwtidf, domef, glacrf, echof, riddlf, lldf, cyclof, magicf, litldf, safef, gnomef, gnodrf, mirrmf, egyptf, onpolf, blabf, brieff, superf, buoyf, grunlf, gatef, rainbf, cagetf, empthf, deflaf, glacmf, frobzf, endgmf, badlkf, thfenf, singsf, mrpshf, mropnf, wdopnf, mr1f, mr2f, inqstf, follwf, spellf, cpoutf, cpushf;
} findex_0;
#define flags ((Bool *)&findex_0) // Bool flags[46]; equivalence(flags, trollf);
extern struct findexCB_1 {
   int btief, binff, rvmnt, rvclr, rvcyc, rvsnd, rvgua, orrug, orcand, ormtch, orlamp, mdir, mloc, poleuf, quesno, nqatt, corrct, lcell, pnumb, acell, dcell, cphere;
} findex_1;
#define switch_ ((int *)&findex_1) // int switch_[22]; equivalence(switch_, btief);

// debug.h:
// common /debug/
extern struct debugCB {
   int dbgflg, prsflg, gdtflg;
} debug;
#ifdef ALLOW_GDT
extern bool dflag;
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
#define xflag (curxt.xobj) // int xflag; equivalence(xflag, xobj);

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

// common /chan/
// LOGICAL UNIT NRS: 5=STDIN, 6=STDOUT
// extern FILE *stdin;
//                                              !TTY INPUT
// extern FILE *stdout;
extern FILE *StoryF;
//                                              !DATA BASE.

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
   int mlnt, rtext[1050];
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
