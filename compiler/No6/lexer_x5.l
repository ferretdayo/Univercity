%{
#include "token_x5.h"
%}

%%

"print"		{return M_PRINT;}
"end"			{return M_END;}
";"			{return M_SEMIC;}
"add"			{return M_ADD;}
"sub"			{return M_SUB;}
"def"			{return M_DEF;}
" "+			{return M_SPC;}
"\n"			{return M_NL;}
[a-z][a-z0-9]*	{return M_ID;}
0|[1-9][0-9]*	{return M_NUM;}
.			{return M_UD;}
