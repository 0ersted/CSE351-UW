#
# Students' Makefile for the Malloc Lab
#
CC = gcc
CFLAGS = -Wall -g

OBJS = mm.o memlib.o fsecs.o fcyc.o clock.o ftimer.o
OBJS-REALLOC = mm-realloc.o memlib.o fsecs.o fcyc.o clock.o ftimer.o
OBJS-GC = mm-gc.o memlib.o fsecs.o fcyc.o clock.o ftimer.o

mdriver: mdriver.o $(OBJS)
	$(CC) $(CFLAGS) -o mdriver mdriver.o $(OBJS)

mdriver.o: mdriver.c fsecs.h fcyc.h clock.h memlib.h config.h mm.h

mdriver-realloc: mdriver-realloc.o  $(OBJS-REALLOC)
	$(CC) $(CFLAGS) -o mdriver-realloc mdriver-realloc.o $(OBJS-REALLOC)

mdriver-realloc.o: mdriver-realloc.c fsecs.h fcyc.h clock.h memlib.h config.h mm.h

mdriver-garbage: GarbageCollectorDriver.o $(OBJS-GC)
	$(CC) $(CFLAGS) -o mdriver-garbage GarbageCollectorDriver.o $(OBJS-GC)

mdriver-garbage.o: GarbageCollectorDriver.c fsecs.h fcyc.h clock.h memlib.h config.h mm.h


memlib.o: memlib.c memlib.h
mm.o: mm.c mm.h memlib.h
mm-realloc.o: mm.c mm-realloc.c mm.h memlib.h
mm-gc.o: mm.c mm-gc.c mm.h memlib.h
fsecs.o: fsecs.c fsecs.h config.h
fcyc.o: fcyc.c fcyc.h
ftimer.o: ftimer.c ftimer.h config.h
clock.o: clock.c clock.h

clean:
	rm -f *~ *.o mdriver mdriver-realloc mdriver-garbage
