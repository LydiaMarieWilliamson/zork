## Makefile for Dungeon/Zork

## The system link command (or else copy).
#LN=cp
#LN=ln -sf

## The system remove command.
#RM=del
RM=rm -f

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

.c.o:
	$(CC) $(CFLAGS) -c $<

$(APP): $(OBJS)
	$(CC) $(CFLAGS) -o $(APP) $(OBJS) $(LIBS)

install: $(APP)
	cp $(APP) $(BINDIR)
	cp dindx.dat $(LIBDIR)
	cp dtext.dat $(LIBDIR)
	mkdir -p $(BINDIR) $(LIBDIR) $(MANDIR)/man6
	cp $(APP).6 $(MANDIR)/man6/

test: $(APP)
	@./$(APP) 655600000 <Test0.in > Ex0 && diff -d Test0.ex Ex0 && rm Ex0 && \
	./$(APP) 657578356 <Test1.in > Ex1 && diff -d Test1.ex Ex1 && rm Ex1 && \
	./$(APP) 655596513 <Test2.in > Ex2 && diff -d Test2.ex Ex2 && rm Ex2 && \
	./$(APP) 655596508 <Test2.in > Ex3 && diff -d Test3.ex Ex3 && rm Ex3 && \
	./$(APP) 655596587 <Test2.in > Ex4 && diff -d Test4.ex Ex4 && rm Ex4 && \
	./$(APP) 655596590 <Test2.in > Ex5 && diff -d Test5.ex Ex5 && rm Ex5 && \
	./$(APP) 655596594 <Test2.in > Ex6 && diff -d Test6.ex Ex6 && rm Ex6 && \
	./$(APP) 655596596 <Test2.in > Ex7 && diff -d Test7.ex Ex7 && rm Ex7 && \
	./$(APP) 657577982 <Test2.in > Ex8 && diff -d Test8.ex Ex8 && rm Ex8 && \
	./$(APP) 657577797 <Test2.in > Ex9 && diff -d Test9.ex Ex9 && rm Ex9 && \
	echo "Tests passed."

clean:
	$(RM) $(OBJS)
	$(RM) core dsave.dat *~
untest:
	$(RM) Ex*
clobber: clean untest
	$(RM) $(APP)

dinit.o: dinit.c
	$(CC) $(CFLAGS) $(GDTFLAG) -DIndexFile=\"$(LIBDIR)/dindx.dat\" -DStoryFile=\"$(LIBDIR)/dtext.dat\" -c dinit.c
dgame.o: dgame.c
	$(CC) $(CFLAGS) $(GDTFLAG) -c dgame.c
gdt.o: gdt.c
	$(CC) $(CFLAGS) $(GDTFLAG) -c gdt.c
local.o: local.c
	$(CC) $(CFLAGS) $(GDTFLAG) $(TERMFLAG) -c local.c

$(OBJS): extern.h common.h
