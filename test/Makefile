CC=gcc
CFLAGS=-pedantic -Wall -ggdb
YACC=bison
YFLAGS=-d
LEX=flex
# LFLAGS=
LDFLAGS=

TESTFILES=test_segments test_symtab



all: test

test: $(TESTFILES)
	for t in $(TESTFILES); do ./$$t; done

test_segments: test_segments.o ../src/segment.o
	$(CC) -o $@ $^


test_symtab: test_symtab.o ../src/symtab.o
	$(CC) -o $@ $^


clean:
	-rm $(TESTFILES)
	-rm *.o
