#
# Makefile that builds btest and other helper programs for the CS:APP data lab
#
CC = gcc
CFLAGS = -O -Wall -m64 -g
LIBS = -lm

all: btest ptest

btest: btest.c bits.c decl.c tests.c btest.h bits.h common.c common.h
	$(CC) $(CFLAGS) $(LIBS) -o btest bits.c btest.c decl.c tests.c common.c

ptest: ptest.c pointer.c common.c common.h
	$(CC) $(CFLAGS) -Wno-unused-variable -o ptest ptest.c pointer.c common.c

# Forces a recompile. Used by the driver program.
btestexplicit:
	$(CC) $(CFLAGS) $(LIBS) -o btest bits.c btest.c decl.c tests.c common.c

clean:
	rm -f *.o btest ptest *~

test: btest ptest
	./btest
	./ptest
