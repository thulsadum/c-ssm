CC=gcc
CFLAGS=-pedantic -Wall
YACC=bison
YFLAGS=-d
LEX=flex
# LFLAGS=
LDFLAGS=

OBJECTFILES=ssm.o ssm-parser.o ssm-lexer.o segment.o



all: ssm

ssm: $(OBJECTFILES)
	$(CC) $(LDFLAGS) -o$@ $^

ssm-parser.c: ssm-parser.y
	$(YACC) $(YFLAGS) $<
	mv ssm-parser{.tab,}.c


ssm-parser.tab.h: | ssm-parser.c
ssm-lexer.c : | ssm-parser.tab.h

clean:
	-rm ssm
	-rm ssm-{lexer,parser}.c ssm-parser.tab.h
	-rm $(OBJECTFILES)


.PHONY: compile
compile: $(OBJECTFILES)
