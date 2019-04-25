%{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    using namespace std;

    void yyerror(char const *s);
    int sym[26]; /* symbol table */
%}

%code requires {
    #include "../include/AST.hpp"
    /* prototypes */
    OperationNode *opr(int oper, int nops, ...);
    int yylex(void);
}

%union {
    int iValue; /* integer value */
    char sIndex; /* symbol table index */
    Node *nPtr; /* node pointer */
    string *text; /* yytext */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token <text> TADD TSUB TMUL TDIV TGE TLE TEQ TNE TLT TGT 
%token WHILE IF

%type <nPtr> stmt expr stmt_list

%nonassoc IFX
%nonassoc ELSE
%left TGE TLE TEQ TNE TLT TGT 
%left TADD TSUB
%left TMUL TDIV
%nonassoc UMINUS

%%
program:
    function { YYACCEPT; }
    ;

function:
    function stmt { $2->generateCode(); delete $2;}
    | /* NULL */
    ;

stmt:
    ';' { $$ = opr(';', 2, NULL, NULL); }
    | expr ';' { $$ = $1; }
    | VARIABLE '=' expr ';' { $$ = opr('=', 2, new IdentifierNode($1), $3); }
    | WHILE '(' expr ')' stmt { $$ = opr(WHILE, 2, $3, $5); }
    | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
    | IF '(' expr ')' stmt ELSE stmt
    { $$ = opr(IF, 3, $3, $5, $7); }
    | '{' stmt_list '}' { $$ = $2; }
    ;

stmt_list:
    stmt { $$ = $1; }
    | stmt_list stmt { $$ = opr(';', 2, $1, $2); }
    ;

expr:
    INTEGER { $$ = new ConstantNode($1); }
    | VARIABLE { $$ = new IdentifierNode($1); }
    | expr TADD expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TSUB expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TMUL expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TDIV expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TGE expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TLE expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TEQ expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TNE expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TLT expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | expr TGT expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | '(' expr ')' { $$ = $2; }
    ;
%%

OperationNode *opr(int oper, int nops, ...) {
    va_list ap;
    Node **operands = new Node*[nops];
    va_start(ap, nops);
    for (int i = 0; i < nops; i++)
       operands[i] = va_arg(ap, Node*);
    va_end(ap);
    return new OperationNode(oper, nops, operands);
}

void yyerror(char const *s) {
    printf("Error: %s\n", s);
}