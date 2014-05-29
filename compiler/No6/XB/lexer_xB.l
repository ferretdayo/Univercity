%{
#include "token_xB.h"
%}

%%

"print"		{return M_PRINT;}
"end"			{return M_END;}
";"			{return M_SEMIC;}
"add"			{return M_ADD;}
"sub"			{return M_SUB;}
"def"			{return M_DEF;}
"read"		{return M_READ;}
"begin"		{return M_BEGIN;}
"set"			{return M_SET;}
"if"			{return M_IF;}
"while"		{return M_WHILE;}
"then"		{return M_THEN;}
"do"			{return M_DO;}
"else"		{return M_ELSE;}
"eq"			{return M_EQ;}
"less"		{return M_LESS;}
" "+			{return M_SPC;}
"\n"			{return M_NL;}
[a-z][a-z0-9]*	{return M_ID;}
0|[1-9][0-9]*	{return M_NUM;}
.			{return M_UD;}
