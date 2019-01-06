%{
/*C lang stuff*/
#include "Node.h"
#include "output.hpp"
#include "parser.tab.hpp"
#include <string>

%}

%option noyywrap
%option yylineno



%%

void								return VOID;

int									return INT;

byte								return BYTE;

b									return B;

bool								return BOOL;

struct								return STRUCT;

and									return AND;

or									return OR;

not                                 return NOT;

true								return TRUE;

false								return FALSE;

return								return RETURN;

if									return IF;

else								return ELSE;

while								return WHILE;

break								return BREAK;

continue							return CONTINUE;

;									return SC;

,									return COMMA;

\.									return PERIOD;

\(									return LPAREN;

\)									return RPAREN;

\{									return LBRACE;

\}									return RBRACE;

=									return ASSIGN;

(==)|(!=)|(<)|(>)|(<=)|(>=)			return RELOP;

\+|\-|\*|\/							return BINOP;

[a-zA-Z][a-zA-Z0-9]*				{
                                        yylval.identifier = new Identifier(std::string(yytext));
                                        return ID;
                                    }

0|([1-9][0-9]*)						{
                                        yylval.identifier = new Identifier(std::string(yytext));
                                        return NUM;
                                    }

\"([^\n\r\"\\]|\\[rnt"\\])+\"		return STRING;

\/\/[^\r\n]*[ \r|\n|\r\n]?			;

[ \t\r\n]							;

.                                   {
                                        output::errorLex(yylineno);
                                        exit(0);
                                    }

%%

