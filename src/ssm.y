%{
     #include <stdint.h>
     #include <stdio.h>
     
     int yylex(void);
     void yyerror(char const *);
%}

%token <char *> LIT_STRING IDENTIFIER
%token <int64_t> LIT_NUMBER

%token SEG_DATA SEG_TEXT SEG_CODE
%token PUSH DUP DROP SWAP ROT
%token PUTC PUTI PUTS GETC
%token LOAD STORE
%token ADD SUB MUL DIV MOD AND OR XOR NOT
%token GT GE EQ LE LT
%token JUMP WHEN UNLESS CALL RETURN 

    /* data KWs */
%token EQU RES
			
%define api.token.prefix {T_}
%define api.value.type union
%%

prog :
       %empty
     | segment prog
     ;

segment :       data-segment
	|	text-segment
	|	code-segment
        ;



text-segment : SEG_TEXT text-definitions ;

text-definitions : %empty
	|	text-definition text-definitions
        ;

text-definition : LIT_STRING
	|	IDENTIFIER LIT_STRING
        ;



data-segment : SEG_DATA data-definitions ;

data-definitions : %empty
	|	data-definition data-definitions
        ;

data-definition : data-decl
	|	data-alloc
        ;

data-decl : EQU numbers
	|	IDENTIFIER EQU numbers
        ;

data-alloc : RES LIT_NUMBER
	|	RES LIT_NUMBER LIT_NUMBER
	|	IDENTIFIER RES LIT_NUMBER
	|	IDENTIFIER RES LIT_NUMBER LIT_NUMBER
        ;

numbers : LIT_NUMBER
	|	numbers LIT_NUMBER
        ;



code-segment : SEG_CODE instructions ;

instructions : %empty
	|	instructions instruction
        ;

instruction : stack-operation
	|	io-operation
	|	memory-operation
	|	arithmetic-logic-operation
	|	branching-operation
	|	IDENTIFIER instruction
        ;


stack-operation : PUSH IDENTIFIER
	|	PUSH LIT_NUMBER
	|	DUP
	|	DROP
	|	SWAP
	|	ROT
        ;

io-operation : PUTC
	|	PUTI
	|	PUTS
	|	GETC
        ;

memory-operation : LOAD
	|	STORE
        ;

arithmetic-logic-operation : ADD
	|	SUB
	|	MUL
	|	DIV
	|	MOD
	|	AND
	|	OR
	|	XOR
	|	NOT
	|	GT
	|	GE
	|	EQ
	|	LE
	|	LT
        ;

branching-operation : JUMP IDENTIFIER
	|	CALL IDENTIFIER
	|	RETURN
	|	WHEN
	|	UNLESS
        ;




%%

void
yyerror(char const *msg)
{
    fprintf(stderr, "%s\n", msg);
}
