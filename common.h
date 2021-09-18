#ifndef OnceOnlyCommon_h
#define OnceOnlyCommon_h

// The common block structures and variable declarations used in dungeon.

// These are the structures which encapsulate the variables contained in common blocks, in the original Fortran source,
// as well as #defines that which corresponds to the aliasing given by the ‟equivalence” statements in the source.
// Everything is collated together because it was never really modular in the first place:
// most includes were included in most Fortran files.

// Unlisted:
// common /star/
extern struct starCB {
   int mbase, strbit;
} star_;
#define star_1 star_

// common /time/
extern struct timeCB {
   int pltime, shour, smin, ssec;
} time_;
#define time_1 time_

// common /vers/
extern const struct versCB {
   int vmaj, vmin, vedit;
} vers_;
#define vers_1 vers_

// common /hyper/
extern const struct hyperCB {
   int hfactr;
} hyper_;
#define hyper_1 hyper_

// common /bats/
extern const struct batsCB {
   const int batdrp[9];
} bats_;
#define bats_1 bats_

// parser.h:
// common /prsvec/
extern struct prsvecCB {
   int prsa, prsi, prso;
   Bool prswon;
   int prscon;
} prsvec_;
#define prsvec_1 prsvec_

// common /orphs/
extern struct orphsCB {
   int oflag, oact, oslot, oprep, oname;
} orphs_;
#define orphs_1 orphs_
#define orp ((int *)&orphs_1)

// common /last/
extern struct lastCB {
   int lastit;
} last_;
#define last_1 last_

// common /pv/
extern struct pvCB {
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
extern struct syntaxCB {
   int vflag, dobj, dfl1, dfl2, dfw1, dfw2, iobj, ifl1, ifl2, ifw1, ifw2;
} syntax_;
#define syntax_1 syntax_
// int syn[11]; // equivalence (syntax_1.vflag, syn);
#define syn ((int *)&syntax_1)

// Syntax flags
// common /synflg/
// enum synflgCB {
//    SDIR = 16384, SIND = 8192, SSTD = 4096, SFLIP = 2048, SDRIV = 1024, SVMASK = 511
// };
#define SDIR (16384)
#define SIND (8192)
#define SSTD (4096)
#define SFLIP (2048)
#define SDRIV (1024)
#define SVMASK (511)

// Object flags
// common /objflg/
// enum objflgCB {
//    VABIT = 16384, VRBIT = 8192, VTBIT = 4096, VCBIT = 2048, VEBIT = 1024, VFBIT = 512, VPMASK = 511
// };
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
extern const struct buzvocCB {
   int bvoc[20];
} buzvoc_;
#define buzvoc_1 buzvoc_

// common /prpvoc/
extern const struct prpvocCB {
   int pvoc[45];
} prpvoc_;
#define prpvoc_1 prpvoc_

// common /dirvoc/
extern const struct dirvocCB {
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

// gamestat.h:
// common /play/
extern struct playCB {
   int winner, here;
   Bool telflg;
} play_;
#define play_1 play_

// rooms.h:
// common /rooms/
extern struct roomsCB {
   int rlnt, rdesc1[200], rdesc2[200], rexit[200], ractio[200], rval[200], rflag[200];
} rooms_;
#define rooms_1 rooms_
#define eqr ((int *)&rooms_1 + 1)
#define rrand ((int *)&rooms_1 + 601)

// rflag.h:
// Room flags.
// common /rflag/
// enum rflagCB {
//    RSEEN = 32768, RLIGHT = 16384, RLAND = 8192, RWATER = 4096, RAIR = 2048, RSACRD = 1024,
//    RFILL = 512, RMUNG = 256, RBUCK = 128, RHOUSE = 64, RNWALL = 32, REND = 16
// };
#define RSEEN (32768)
#define RLIGHT (16384)
#define RLAND (8192)
#define RWATER (4096)
#define RAIR (2048)
#define RSACRD (1024)
#define RFILL (512)
#define RMUNG (256)
#define RBUCK (128)
#define RHOUSE (64)
#define RNWALL (32)
#define REND (16)

// rindex.h:
// common /rindex/
extern const struct rindexCB {
   int whous, lroom, cella, mtrol, maze1, mgrat, maz15, fore1, fore3, clear, reser, strea, egypt, echor, tshaf, bshaf, mmach, dome, mtorc, carou, riddl, lld2, temp1, temp2, maint, blroo, treas, rivr1, rivr2, rivr3, mcycl, rivr4, rivr5, fchmp, falls,
      mbarr, mrain, pog, vlbot, vair1, vair2, vair3, vair4, ledg2, ledg3, ledg4, msafe, cager, caged, twell, bwell, alice, alism, alitr, mtree, bkent, bkvw, bktwi, bkvau, bkbox, crypt, tstrs, mrant, mreye, mra, mrb, mrc, mrg, mrd, fdoor, mrae, mrce, mrcw,
      mrge, mrgw, mrdw, inmir, scorr, ncorr, parap, cell, pcell, ncell, cpant, cpout, cpuzz;
} rindex_;
#define rindex_1 rindex_

// xsrch.h:
// common /xsrch/
extern const struct xsrchCB {
   int xmin, xmax, xdown, xup, xnorth, xsouth, xenter, xexit, xeast, xwest;
} xsrch_;
#define xsrch_1 xsrch_

// objects.h:
// common /objcts/
extern struct objctsCB {
   int olnt, odesc1[220], odesc2[220], odesco[220], oactio[220], oflag1[220], oflag2[220], ofval[220], otval[220], osize[220], ocapac[220], oroom[220], oadv[220], ocan[220], oread[220];
} objcts_;
#define objcts_1 objcts_
#define eqo ((int *)&objcts_1 + 1)

// common /oroom2/
extern struct oroom2CB {
   int r2lnt, oroom2[20], rroom2[20];
} oroom2_;
#define oroom2_1 oroom2_

// oflags.h:
// Object flags.
// common /oflags/
// enum oflagsCB {
//    VISIBT = 32768, READBT = 16384, TAKEBT = 8192, DOORBT = 4096, TRANBT = 2048, FOODBT = 1024, NDSCBT = 512, DRNKBT = 256,
//    CONTBT = 128, LITEBT = 64, VICTBT = 32, BURNBT = 16, FLAMBT = 8, TOOLBT = 4, TURNBT = 2, ONBT = 1,
//    FINDBT = 32768, SLEPBT = 16384, SCRDBT = 8192, TIEBT = 4096, CLMBBT = 2048, ACTRBT = 1024, WEAPBT = 512, FITEBT = 256,
//    VILLBT = 128, STAGBT = 64, TRYBT = 32, NOCHBT = 16, OPENBT = 8, TCHBT = 4, VEHBT = 2, SCHBT = 1
// };
#define VISIBT (32768)
#define READBT (16384)
#define TAKEBT (8192)
#define DOORBT (4096)
#define TRANBT (2048)
#define FOODBT (1024)
#define NDSCBT (512)
#define DRNKBT (256)
#define CONTBT (128)
#define LITEBT (64)
#define VICTBT (32)
#define BURNBT (16)
#define FLAMBT (8)
#define TOOLBT (4)
#define TURNBT (2)
#define ONBT (1)
#define FINDBT (32768)
#define SLEPBT (16384)
#define SCRDBT (8192)
#define TIEBT (4096)
#define CLMBBT (2048)
#define ACTRBT (1024)
#define WEAPBT (512)
#define FITEBT (256)
#define VILLBT (128)
#define STAGBT (64)
#define TRYBT (32)
#define NOCHBT (16)
#define OPENBT (8)
#define TCHBT (4)
#define VEHBT (2)
#define SCHBT (1)

// oindex.h:
// common /oindex/
extern const struct oindexCB {
   int garli, food, gunk, coal, machi, diamo, tcase, bottl, water, rope, knife, sword, lamp, blamp, rug, leave, troll, axe, rknif, keys, ice, bar, coffi, torch, tbask, fbask, irbox, ghost, trunk, bell, book, candl, match, tube, putty, wrenc, screw,
      cyclo, chali, thief, still, windo, grate, door, hpole, leak, rbutt, raili, pot, statu, iboat, dboat, pump, rboat, stick, buoy, shove, ballo, recep, guano, brope, hook1, hook2, safe, sslot, brick, fuse, gnome, blabe, dball, tomb, lcase, cage, rcage,
      spher, sqbut, flask, pool, saffr, bucke, ecake, orice, rdice, blice, robot, ftree, bills, portr, scol, zgnom, egg, begg, baubl, canar, bcana, ylwal, rdwal, pindr, rbeam, odoor, qdoor, cdoor, num1, num8, warni, cslit, gcard, stldr, hands, wall, lungs,
      sailo, aviat, teeth, itobj, every, valua, oplay, wnort, gwate, master;
} oindex_;
#define oindex_1 oindex_

// clock.h:
// common /cevent/
extern struct ceventCB {
   int clnt, ctick[25], cactio[25];
   Bool cflag[25];
} cevent_;
#define cevent_1 cevent_
#define eqc ((int *)&cevent_1 + 1)

// common /cindex/
extern const struct cindexCB {
   int cevcur, cevmnt, cevlnt, cevmat, cevcnd, cevbal, cevbrn, cevfus, cevled, cevsaf, cevvlg, cevgno, cevbuc, cevsph, cevegh, cevfor, cevscl, cevzgi, cevzgo, cevste, cevmrs, cevpin, cevinq, cevfol;
} cindex_;
#define cindex_1 cindex_

// advers.h:
// common /advs/
extern struct advsCB {
   int alnt, aroom[4], ascore[4], avehic[4], aobj[4], aactio[4], astren[4], aflag[4];
} advs_;
#define advs_1 advs_
#define eqa ((int *)&advs_1 + 1)

// common /aflags/
extern const struct aflagsCB {
   int astag;
} aflags_;
#define aflags_1 aflags_

// common /aindex/
extern const struct aindexCB {
   int player, arobot, amastr;
} aindex_;
#define aindex_1 aindex_

// verbs.h:
// common /vindex/
extern const struct vindexCB {
   int cintw, deadxw, frstqw, inxw, outxw, walkiw, fightw, foow, meltw, readw, inflaw, deflaw, alarmw, exorcw, plugw, kickw, wavew, raisew, lowerw, rubw, pushw, untiew, tiew, tieupw, turnw, breatw, knockw, lookw, examiw, shakew, movew, trnonw, trnofw,
      openw, closew, findw, waitw, spinw, boardw, unboaw, takew, invenw, fillw, eatw, drinkw, burnw, mungw, killw, attacw, swingw, walkw, tellw, putw, dropw, givew, pourw, throww, digw, leapw, stayw, follow, hellow, lookiw, lookuw, pumpw, windw, clmbw,
      clmbuw, clmbdw, trntow;
} vindex_;
#define vindex_1 vindex_

// flags.h:
// common /findex/
extern struct findexCB {
   Bool trollf, cagesf, bucktf, caroff, carozf, lwtidf, domef, glacrf, echof, riddlf, lldf, cyclof, magicf, litldf, safef, gnomef, gnodrf, mirrmf, egyptf, onpolf, blabf, brieff, superf, buoyf, grunlf, gatef, rainbf, cagetf, empthf, deflaf, glacmf,
      frobzf, endgmf, badlkf, thfenf, singsf, mrpshf, mropnf, wdopnf, mr1f, mr2f, inqstf, follwf, spellf, cpoutf, cpushf;
   int btief, binff, rvmnt, rvclr, rvcyc, rvsnd, rvgua, orrug, orcand, ormtch, orlamp, mdir, mloc, poleuf, quesno, nqatt, corrct, lcell, pnumb, acell, dcell, cphere;
} findex_;
#define findex_1 findex_
#define flags ((Bool *)&findex_1)
#define switch_ ((int *)&findex_1 + 46)

// debug.h:
// common /debug/
extern struct debugCB {
   int dbgflg, prsflg, gdtflg;
} debug_;
#define debug_1 debug_

// villians.h:
// common /hack/
extern struct hackCB {
   int thfpos;
   Bool thfflg, thfact, swdact;
   int swdsta;
} hack_;
#define hack_1 hack_

// common /vill/
extern struct villCB {
   int vlnt, villns[4], vprob[4], vopps[4], vbest[4], vmelee[4];
} vill_;
#define vill_1 vill_
#define eqv ((int *)&vill_1 + 1)

// state.h:
// common /state/
extern struct stateCB {
   int moves, deaths, rwscor, mxscor, mxload, ltshft, bloc, mungrm, hs, egscor, egmxsc;
} state_;
#define state_1 state_

// curxt.h:
// common /curxt/
extern struct curxtCB {
   int xtype, xroom1, xstrng, xactio, xobj;
} curxt_;
#define curxt_1 curxt_
#define xflag ((int *)&curxt_1 + 4)

// xpars.h:
// common /xpars/
extern const struct xparsCB {
   int xrmask, xdmask, xfmask, xfshft, xashft, xelnt[4], xnorm, xno, xcond, xdoor, xlflag;
} xpars_;
#define xpars_1 xpars_

// io.h:
// common /input/
extern struct inputCB {
   int inlnt;
   char inbuf[78];
} input_;
#define input_1 input_

// screen.h:
// common /screen/
extern struct screenCB {
   int fromdr, scolrm, scolac;
   const int scoldr[8], scolwl[12];
} screen_;
#define screen_1 screen_

// mindex.h:
// common /rmsg/
extern struct rmsgCB {
   int mlnt, mrloc, rtext[1050];
} rmsg_;
#define rmsg_1 rmsg_

// exits.h:
// common /exits/
extern struct exitsCB {
   int xlnt, travel[900];
} exits_;
#define exits_1 exits_

// puzzle.h:
// common /puzzle/
extern struct puzzleCB {
   const int cpdr[16], cpwl[8];
   int cpvec[64];
} puzzle_;
#define puzzle_1 puzzle_

#endif // OnceOnly
