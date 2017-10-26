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

segment :       data_segment
	|	text_segment
	|	code_segment
        ;



text_segment : SEG_TEXT text_definitions ;

text_definitions : %empty
	|	text_definition text_definitions
        ;

text_definition : LIT_STRING
	|	IDENTIFIER LIT_STRING
        ;



data_segment : SEG_DATA data_definitions ;

data_definitions : %empty
	|	data_definition data_definitions
        ;

data_definition : data_decl
	|	data_alloc
        ;

data_decl : EQU numbers
	|	IDENTIFIER EQU numbers
        ;

data_alloc : RES LIT_NUMBER
	|	RES LIT_NUMBER LIT_NUMBER
	|	IDENTIFIER RES LIT_NUMBER
	|	IDENTIFIER RES LIT_NUMBER LIT_NUMBER
        ;

numbers : LIT_NUMBER
	|	numbers LIT_NUMBER
        ;



code_segment : SEG_CODE instructions ;

instructions : %empty
	|	instructions instruction
        ;

instruction : stack_operation
	|	io_operation
	|	memory_operation
	|	arithmetic_logic_operation
	|	branching_operation
	|	IDENTIFIER instruction
        ;


stack_operation : PUSH IDENTIFIER
	|	PUSH LIT_NUMBER
	|	DUP
	|	DROP
	|	SWAP
	|	ROT
        ;

io_operation : PUTC
	|	PUTI
	|	PUTS
	|	GETC
        ;

memory_operation : LOAD
	|	STORE
        ;

arithmetic_logic_operation : ADD
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

branching_operation : JUMP IDENTIFIER
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
