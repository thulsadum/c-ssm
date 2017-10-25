%{
     #include "ssm.tab.h"
%}

%x STRING

%%

              char sbuf[4096];
              char *psbuf;


 /* segments */
"SEG DATA"    return T_SEG_DATA;
"SEG TEXT"    return T_SEG_TEXT;
"SEG CODE"    return T_SEG_CODE;

 /* operations */
"push"        return T_PUSH;
"drop"        return T_DROP;
"swap"        return T_SWAP;
"rot"         return T_ROT;

"putc"        return T_PUTC;
"puti"        return T_PUTI;
"puts"        return T_PUTS;
"getc"        return T_GETC;

"load"        return T_LOAD;
"store"       return T_STORE;

"add"         return T_ADD;
"sub"         return T_SUB;
"mul"         return T_MUL;
"div"         return T_DIV;
"mod"         return T_MOD;
"and"         return T_AND;
"or"          return T_OR;
"xor"         return T_XOR;
"not"         return T_NOT;
"gt"          return T_GT;
"ge"          return T_GE;
"eq"          return T_EQ;
"le"          return T_LE;
"lt"          return T_LT;

"jump"        return T_JUMP;
"call"        return T_CALL;
"return"      return T_RETURN;
"when"        return T_WHEN;
"unless"      return T_UNLESS;

\"          { /* begin string */
     psbuf = sbuf; BEGIN(STRING);
            }

<STRING>\"  { /* end string */
     BEGIN(INITIAL);
     *psbuf = '\0';
     yylval.T_LIT_STRING = strdup( yytext );
     return T_LIT_STRING;            
            }

<STRING>\\n    *psbuf++ = '\n';
<STRING>\\t    *psbuf++ = '\r';
<STRING>\\r    *psbuf++ = '\r';
<STRING>\\b    *psbuf++ = '\b';
<STRING>\\f    *psbuf++ = '\f';

<STRING>\\(.|\n)    *psbuf++ = yytext[1];

<STRING>[^\"]    *psbuf++ = *yytext;
