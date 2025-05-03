%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include "parser.tab.h"

// For debug purposes
//#define DEBUG_TOKENS

int comment_nesting = 0;
%}

%option noyywrap
%option yylineno
%option noinput
%option nounput

/* Regular definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+\.{DIGIT}+([eE][+-]?{DIGIT}+)?
WHITESPACE  [ \t\r\n]+
COMMENT     "//".*

%x COMMENT

%%
{WHITESPACE}    { /* Skip whitespace */ }
{COMMENT}       { /* Skip single-line comments */ }

"/*"            { BEGIN(COMMENT); comment_nesting++; }
<COMMENT>"/*"   { comment_nesting++; }
<COMMENT>"*/"   { 
                    comment_nesting--; 
                    if(comment_nesting == 0) 
                        BEGIN(INITIAL); 
                }
<COMMENT>.|\n   { /* Skip multi-line comment content */ }

 /* Keywords */
"int"           { 
                    #ifdef DEBUG_TOKENS
                    printf("TOKEN: INT\\n"); 
                    #endif
                    return INT; 
                }
"float"         { return FLOAT; }
"bool"          { return BOOL; }
"void"          { return VOID; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"return"        { return RETURN; }
"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"true"          { 
                    yylval.bool_val = true; 
                    #ifdef DEBUG_TOKENS
                    printf("TOKEN: BOOL_LITERAL (true)\\n"); 
                    #endif
                    return BOOL_LITERAL; 
                }
"false"         { 
                    yylval.bool_val = false; 
                    #ifdef DEBUG_TOKENS
                    printf("TOKEN: BOOL_LITERAL (false)\\n"); 
                    #endif
                    return BOOL_LITERAL; 
                }
"print"         { return PRINT; }
"read"          { return READ; }

 /* Operators */
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"="             { return '='; }
"=="            { return EQ; }
"!="            { return NEQ; }
"<"             { return '<'; }
">"             { return '>'; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return '!'; }

 /* Delimiters */
"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
";"             { return ';'; }
","             { return ','; }
":"             { return ':'; }

 /* Literals */
{INTEGER}       { 
                    yylval.int_val = atoi(yytext); 
                    #ifdef DEBUG_TOKENS
                    printf("TOKEN: INT_LITERAL (%d)\\n", yylval.int_val); 
                    #endif
                    return INT_LITERAL; 
                }

{FLOAT}         { 
                    yylval.float_val = atof(yytext); 
                    #ifdef DEBUG_TOKENS
                    printf("TOKEN: FLOAT_LITERAL (%f)\\n", yylval.float_val); 
                    #endif
                    return FLOAT_LITERAL; 
                }

 /* String literal */
\"[^\"]*\"      { 
                    yylval.string_val = strdup(yytext + 1);  // Skip the opening quote
                    yylval.string_val[strlen(yylval.string_val) - 1] = '\0';  // Remove the closing quote
                    return STRING_LITERAL; 
                }

 /* Identifiers */
{ID}            { 
                    yylval.string_val = strdup(yytext);
                    return IDENTIFIER; 
                }

 /* Error handling */
.               { 
                    fprintf(stderr, "Line %d: Lexical error: Unknown token '%s'\\n", yylineno, yytext); 
                }

%%