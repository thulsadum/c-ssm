CC=gcc
CFLAGS=-pedantic -Wall
YACC=bison
YFLAGS=-d
LEX=flex
# LFLAGS=
LDFLAGS=

TESTFILES=test_segments



all: test

test: $(TESTFILES)
	for t in $(TESTFILES); do ./$$t; done

test_segments: test_segments.o ../src/segment.o
	$(CC) -o $@ $^

clean:
	-rm $(TESTFILES)
	-rm *.o
