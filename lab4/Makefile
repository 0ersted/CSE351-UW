#
# Student makefile for Cache Lab
# Note: requires a 64-bit x86-64 system 
#
CC = gcc
CFLAGS_TEST = -Wall
CFLAGS_TRANS = -g -Wall -Werror -std=c99 -m64

all: test-trans tracegen

test-trans: test-trans.c trans.o cachelab.c cachelab.h
	$(CC) $(CFLAGS_TRANS) -o test-trans test-trans.c cachelab.c trans.o 

tracegen: tracegen.c trans.o cachelab.c
	$(CC) $(CFLAGS_TRANS) -O0 -o tracegen tracegen.c trans.o cachelab.c

trans.o: trans.c
	$(CC) $(CFLAGS_TRANS) -O0 -c trans.c

.FORCE:

cache-test: .FORCE cache-test-skel.c $(TEST_CACHE)
#	ifndef TEST_CACHE
#	$(error You did not define TEST_CACHE!)
#	endif

	$(CC) $(CFLAGS_TEST) cache-test-skel.c $(TEST_CACHE) -o $@    
    
#
# Clean the src dirctory
#
clean:
#    rm -rf *.o
	rm -f *.tar
#    rm -f csim
	rm -f test-trans tracegen
	rm -f trace.all trace.f*
#    rm -f .csim_results .marker
	rm -f trace.tmp
	rm -f trans.o
	rm -f .csim_results
	rm -f .marker
	rm -f cache-test
