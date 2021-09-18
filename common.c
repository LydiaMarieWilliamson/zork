#include "extern.h"
#include "common.h"

// The common block initializations and variable definitions used in dungeon

// These are the initializations of the common blocks corresponding to the ‟data” statements in the orignal Fortran source,
// as well as the definition of the common block variables.

// The initialized common block definitions were in dmain.f in the original Fortran source,
// and will be later restored back to dmain.c

// Unlisted:
// common /star/
// int mbase, strbit;
struct starCB star_;

// common /time/
// int pltime, shour, smin, ssec;
struct timeCB time_;

// common /vers/
const struct versCB vers_ = (struct versCB){
   vmaj: 2, vmin: 7, vedit: 'A'
};

// common /hyper/
const struct hyperCB hyper_ = (struct hyperCB){
   hfactr: 500
};

// common /bats/
const struct batsCB bats_ = (struct batsCB){
   batdrp: { 66, 67, 68, 69, 70, 71, 72, 65, 73 }
};

// parser.h:
// common /prsvec/
// int prsa, prsi, prso;
// Bool prswon;
// int prscon;
struct prsvecCB prsvec_;

// common /orphs/
// int oflag, oact, oslot, oprep, oname;
struct orphsCB orphs_;

// common /last/
// int lastit;
struct lastCB last_;

// common /pv/
// int act, o1, o2, p1, p2;
struct pvCB pv_;

// common /syntax/
// int vflag, dobj, dfl1, dfl2, dfw1, dfw2, iobj, ifl1, ifl2, ifw1, ifw2;
struct syntaxCB syntax_;

// gamestat.h:
// common /play/
// int winner, here;
// Bool telflg;
struct playCB play_;

// rooms.h:
// common /rooms/
// int rlnt, rdesc1[200], rdesc2[200], rexit[200], ractio[200], rval[200], rflag[200];
struct roomsCB rooms_;

// rflag.h:
// Room flags.
// common /rflag/
// enum rflagCB {
//    RSEEN = 32768, RLIGHT = 16384, RLAND = 8192, RWATER = 4096, RAIR = 2048, RSACRD = 1024,
//    RFILL = 512, RMUNG = 256, RBUCK = 128, RHOUSE = 64, RNWALL = 32, REND = 16
// };

// rindex.h:
// common /rindex/
const struct rindexCB rindex_ = (struct rindexCB){
   whous: 2, lroom: 8, cella: 9, mtrol: 10, maze1: 11, mgrat: 25, maz15: 30, fore1: 31,
   fore3: 33, clear: 36, reser: 40, strea: 42, egypt: 44, echor: 49, tshaf: 61, bshaf: 76,
   mmach: 77, dome: 79, mtorc: 80, carou: 83, riddl: 91, lld2: 94, temp1: 96, temp2: 97,
   maint: 100, blroo: 102, treas: 103, rivr1: 107, rivr2: 108, rivr3: 109, mcycl: 101, rivr4: 112,
   rivr5: 113, fchmp: 114, falls: 120, mbarr: 119, mrain: 121, pog: 122, vlbot: 126, vair1: 127,
   vair2: 128, vair3: 129, vair4: 130, ledg2: 131, ledg3: 132, ledg4: 133, msafe: 135, cager: 140,
   caged: 141, twell: 142, bwell: 143, alice: 144, alism: 145, alitr: 146, mtree: 147, bkent: 148,
   bkvw: 151, bktwi: 153, bkvau: 154, bkbox: 155, crypt: 157, tstrs: 158, mrant: 159, mreye: 160,
   mra: 161, mrb: 162, mrc: 163, mrg: 164, mrd: 165, fdoor: 166, mrae: 167, mrce: 171,
   mrcw: 172, mrge: 173, mrgw: 174, mrdw: 176, inmir: 177, scorr: 179, ncorr: 182, parap: 183,
   cell: 184, pcell: 185, ncell: 186, cpant: 188, cpout: 189, cpuzz: 190
};

// xsrch.h:
// common /xsrch/
const struct xsrchCB xsrch_ = (struct xsrchCB){
   xmin: 1024, xmax: 16384, xdown: 10240, xup: 9216, xnorth: 1024,
   xsouth: 5120, xenter: 13312, xexit: 14336, xeast: 3072, xwest: 7168
};

// objects.h:
// common /objcts/
// int olnt, odesc1[220], odesc2[220], odesco[220], oactio[220], oflag1[220], oflag2[220], ofval[220], otval[220], osize[220], ocapac[220], oroom[220], oadv[220], ocan[220], oread[220];
struct objctsCB objcts_;

// common /oroom2/
// int r2lnt, oroom2[20], rroom2[20];
struct oroom2CB oroom2_;

// oflags.h:
// Object flags.
// common /oflags/
// enum oflagsCB {
//    VISIBT = 32768, READBT = 16384, TAKEBT = 8192, DOORBT = 4096, TRANBT = 2048, FOODBT = 1024, NDSCBT = 512, DRNKBT = 256,
//    CONTBT = 128, LITEBT = 64, VICTBT = 32, BURNBT = 16, FLAMBT = 8, TOOLBT = 4, TURNBT = 2, ONBT = 1,
//    FINDBT = 32768, SLEPBT = 16384, SCRDBT = 8192, TIEBT = 4096, CLMBBT = 2048, ACTRBT = 1024, WEAPBT = 512, FITEBT = 256,
//    VILLBT = 128, STAGBT = 64, TRYBT = 32, NOCHBT = 16, OPENBT = 8, TCHBT = 4, VEHBT = 2, SCHBT = 1
// };

// oindex.h:
// common /oindex/
const struct oindexCB oindex_ = (struct oindexCB){
   garli: 2, food: 3, gunk: 4, coal: 5, machi: 7, diamo: 8, tcase: 9, bottl: 10,
   water: 11, rope: 12, knife: 13, sword: 14, lamp: 15, blamp: 16, rug: 17, leave: 18,
   troll: 19, axe: 20, rknif: 21, keys: 23, ice: 30, bar: 26, coffi: 33, torch: 34,
   tbask: 35, fbask: 36, irbox: 39, ghost: 42, trunk: 45, bell: 46, book: 47, candl: 48,
   match: 51, tube: 54, putty: 55, wrenc: 56, screw: 57, cyclo: 58, chali: 59, thief: 61,
   still: 62, windo: 63, grate: 65, door: 66, hpole: 71, leak: 78, rbutt: 79, raili: 75,
   pot: 85, statu: 86, iboat: 87, dboat: 88, pump: 89, rboat: 90, stick: 92, buoy: 94,
   shove: 96, ballo: 98, recep: 99, guano: 97, brope: 101, hook1: 102, hook2: 103, safe: 105,
   sslot: 107, brick: 109, fuse: 110, gnome: 111, blabe: 112, dball: 113, tomb: 119, lcase: 123,
   cage: 124, rcage: 125, spher: 126, sqbut: 127, flask: 132, pool: 133, saffr: 134, bucke: 137,
   ecake: 138, orice: 139, rdice: 140, blice: 141, robot: 142, ftree: 145, bills: 148, portr: 149,
   scol: 151, zgnom: 152, egg: 154, begg: 155, baubl: 156, canar: 157, bcana: 158, ylwal: 159,
   rdwal: 161, pindr: 164, rbeam: 171, odoor: 172, qdoor: 173, cdoor: 175, num1: 178, num8: 185,
   warni: 186, cslit: 187, gcard: 188, stldr: 189, hands: 200, wall: 198, lungs: 201, sailo: 196,
   aviat: 202, teeth: 197, itobj: 192, every: 194, valua: 195, oplay: 193, wnort: 205, gwate: 209, master: 215
};

// clock.h:
// common /cevent/
// int clnt, ctick[25], cactio[25];
// Bool cflag[25];
struct ceventCB cevent_;

// common /cindex/
const struct cindexCB cindex_ = (struct cindexCB){
   cevcur: 1, cevmnt: 2, cevlnt: 3, cevmat: 4, cevcnd: 5, cevbal: 6, cevbrn: 7, cevfus: 8,
   cevled: 9, cevsaf: 10, cevvlg: 11, cevgno: 12, cevbuc: 13, cevsph: 14, cevegh: 15, cevfor: 16,
   cevscl: 17, cevzgi: 18, cevzgo: 19, cevste: 20, cevmrs: 21, cevpin: 22, cevinq: 23, cevfol: 24
};

// advers.h:
// common /advs/
// int alnt, aroom[4], ascore[4], avehic[4], aobj[4], aactio[4], astren[4], aflag[4];
struct advsCB advs_;

// common /aflags/
const struct aflagsCB aflags_ = (struct aflagsCB){
   astag: 32768
};

// common /aindex/
const struct aindexCB aindex_ = (struct aindexCB){
   player: 1, arobot: 2, amastr: 3
};

// verbs.h:
// common /vindex/
const struct vindexCB vindex_ = (struct vindexCB){
   cintw: 1, deadxw: 2, frstqw: 3, inxw: 4, outxw: 5, walkiw: 6, fightw: 7, foow: 8,
   meltw: 101, readw: 100, inflaw: 102, deflaw: 103, alarmw: 104, exorcw: 105, plugw: 106, kickw: 107,
   wavew: 108, raisew: 109, lowerw: 110, rubw: 111, pushw: 112, untiew: 113, tiew: 114, tieupw: 115,
   turnw: 116, breatw: 117, knockw: 118, lookw: 119, examiw: 120, shakew: 121, movew: 122, trnonw: 123,
   trnofw: 124, openw: 125, closew: 126, findw: 127, waitw: 128, spinw: 129, boardw: 130, unboaw: 131,
   takew: 132, invenw: 133, fillw: 134, eatw: 135, drinkw: 136, burnw: 137, mungw: 138, killw: 139,
   attacw: 141, swingw: 140, walkw: 142, tellw: 143, putw: 144, dropw: 145, givew: 146, pourw: 147,
   throww: 148, digw: 89, leapw: 91, stayw: 73, follow: 85, hellow: 151, lookiw: 152, lookuw: 153,
   pumpw: 154, windw: 155, clmbw: 156, clmbuw: 157, clmbdw: 158, trntow: 159
};

// flags.h:
// common /findex/
// Bool trollf, cagesf, bucktf, caroff, carozf, lwtidf, domef, glacrf, echof, riddlf, lldf, cyclof, magicf, litldf, safef, gnomef, gnodrf, mirrmf, egyptf, onpolf, blabf, brieff, superf, buoyf, grunlf, gatef, rainbf, cagetf, empthf, deflaf, glacmf, frobzf, endgmf, badlkf, thfenf, singsf, mrpshf, mropnf, wdopnf, mr1f, mr2f, inqstf, follwf, spellf, cpoutf, cpushf;
// int btief, binff, rvmnt, rvclr, rvcyc, rvsnd, rvgua, orrug, orcand, ormtch, orlamp, mdir, mloc, poleuf, quesno, nqatt, corrct, lcell, pnumb, acell, dcell, cphere;
struct findexCB findex_;

// debug.h:
// common /debug/
// int dbgflg, prsflg, gdtflg;
struct debugCB debug_;

// villians.h:
// common /hack/
// int thfpos;
// Bool thfflg, thfact, swdact;
// int swdsta;
struct hackCB hack_;

// common /vill/
// int vlnt, villns[4], vprob[4], vopps[4], vbest[4], vmelee[4];
struct villCB vill_;

// state.h:
// common /state/
// int moves, deaths, rwscor, mxscor, mxload, ltshft, bloc, mungrm, hs, egscor, egmxsc;
struct stateCB state_;

// curxt.h:
// common /curxt/
// int xtype, xroom1, xstrng, xactio, xobj;
struct curxtCB curxt_;

// xpars.h:
// common /xpars/
const struct xparsCB xpars_ = (struct xparsCB){
   xrmask: 255, xdmask: 31744, xfmask: 3, xfshft: 256, xashft: 256,
   xelnt: { 1, 2, 3, 3 },
   xnorm: 1, xno: 2, xcond: 3, xdoor: 4, xlflag: 32768
};

// io.h:
// common /input/
// int inlnt;
// char inbuf[78];
struct inputCB input_;

// screen.h:
// common /screen/
struct screenCB screen_ = (struct screenCB){
   fromdr: 0, scolrm: 0, scolac: 0,
   scoldr: { 1024, 153, 5120, 154, 3072, 152, 7168, 151 },
   scolwl: { 151, 207, 3072, 152, 208, 7168, 153, 206, 5120, 154, 205, 1024 }
};

// mindex.h:
// common /rmsg/
// int mlnt, mrloc, rtext[1050];
struct rmsgCB rmsg_;

// exits.h:
// common /exits/
// int xlnt, travel[900];
struct exitsCB exits_;

// puzzle.h:
// common /puzzle/
struct puzzleCB puzzle_ = (struct puzzleCB){
   cpdr: { 1024, -8, 2048, -7, 3072, 1, 4096, 9, 5120, 8, 6144, 7, 7168, -1, 8192, -9 },
   cpwl: { 205, -8, 206, 8, 207, 1, 208, -1 },
   cpvec: {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 0, -1, 0, 0, -1, 0, 1,
      1, -1, 0, 1, 0, -2, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1,
      1, -3, 0, 0, -1, -1, 0, 1, 1, 0, 0, -1, 0, 0, 0, 1,
      1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
   }
};
