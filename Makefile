## Makefile for Dungeon/Zork

## Where to install the program
BINDIR = /usr/games

## Where to install the data file
LIBDIR = /usr/games/lib

## Where to install the man page
MANDIR = /usr/share/man

## The Dungeon/Zork program provides a ‟more” facility which tries to figure out how many rows the terminal has.
## Several mechanisms are supported for determining this; the most common one has been left uncommented.
## If you have trouble, especially when linking, you may have to select a different option.

## more option 1: use the termcap routines.
## On some systems the LIBS variable may need to be set to -lcurses.
## On some it may need to be /usr/lib/termcap.o.
## These options are commented out below.
#LIBS = -ltermcap
#TERMFLAG =
#LIBS = -lcurses
#LIBS = /usr/lib/termcap.o

## more option 2: use the terminfo routines.
## On some systems the LIBS variable needs to be -lcursesX,
## but probably all such systems support the termcap routines (option 1) anyhow.
#LIBS = -lcurses
#TERMFLAG = -DMORE_TERMINFO

## more option 3: assume all terminals have 24 rows
#LIBS =
#TERMFLAG = -DMORE_24

## more option 4: don't use the more facility at all
LIBS =
TERMFLAG = -DMORE_NONE

## End of more options

## Uncomment the following line if you want to have access to the game debugging tool.
## This is invoked by typing ‟gdt”.
## It is not much use except for debugging.
GDTFLAG = -DALLOW_GDT

## Compilation flags
## Development
CFLAGS = -g #-static
## Production
#CFLAGS = -O2 #-static
## On SCO Unix Development System 3.2.2a, the const type qualifier does not work correctly when using cc.
## The following line will cause it to not be used and should be uncommented.
#CFLAGS= -O -Dconst=

## Object files
OBJS =	common.o local.o \
	actors.o ballop.o blkdata.o clockr.o demons.o dgame.o dinit.o dmain.o dso1.o dso2.o dso3.o \
	dso4.o dso5.o dso6.o dso7.o dsub.o dverb1.o dverb2.o gdt.o lightp.o nobjs.o np1.o \
	np2.o np3.o np.o nrooms.o objcts.o rooms.o rtim.o sobjs.o sverbs.o verbs.o villns.o

#APP = dungeon
APP = Zork

$(APP): $(OBJS) dtextc.dat
	$(CC) $(CFLAGS) -o $(APP) $(OBJS) $(LIBS)

install: $(APP) dtextc.dat
	mkdir -p $(BINDIR) $(LIBDIR) $(MANDIR)/man6
	cp $(APP) $(BINDIR)
	cp dtextc.dat $(LIBDIR)
	cp $(APP).6 $(MANDIR)/man6/

test: $(APP)
	./$(APP) <Test.in >Ex && diff -d Test.ex Ex && rm Ex

clean:
	rm -f $(OBJS)
	rm -f core dsave.dat *~
	rm -f Ex
clobber: clean
	rm -f $(APP)

dtextc.dat:
	cat dtextc.uu1 dtextc.uu2 dtextc.uu3 dtextc.uu4 | uudecode

dinit.o: dinit.c
	$(CC) $(CFLAGS) $(GDTFLAG) -DStoryFile=\"$(LIBDIR)/dtextc.dat\" -c dinit.c

dgame.o: dgame.c
	$(CC) $(CFLAGS) $(GDTFLAG) -c dgame.c

gdt.o: gdt.c
	$(CC) $(CFLAGS) $(GDTFLAG) -c gdt.c

local.o: local.c
	$(CC) $(CFLAGS) $(GDTFLAG) $(TERMFLAG) -c local.c

$(OBJS): extern.h common.h
