#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token_xB.h"

#define BUF_MAX 256
#define M_EMPTY -3

char buf[BUF_MAX];
char yytext[BUF_MAX];
int n_processed;
int n_total;
int saved_marker;	//切り出しと消費を区別
int yylval;		//yylex()の戻り値の型の指定

void init_buf();
void syntax_error();
int nexttoken();
void parse_T();
void parse_S();
void parse_D();
void parse_B();
void parse_L();
void parse_C();
void parse_E();
void parse_V();
int scan();
int parse();
void eat_token();
int yylex();

void init_buf(){
	n_total = 0;
	n_processed = 0;
	saved_marker = M_EMPTY;
}

void syntax_error(){
	fprintf(stderr,"Syntax Error.\n");
	exit(-1);
}

int nexttoken(){
	int m;
	if(saved_marker != M_EMPTY){	//前回scan()した結果が残っている
		m = saved_marker;
	}else{
		m = scan();
		while(m == M_SPC || m == M_NL){	//読み飛ばし
			m = scan();
		}
		saved_marker = m;
	}
	return m;
}

void parse_T(){
	int m = nexttoken();
	if(m == M_ENDOFFILE){
		//nothing
	}else if(m == M_DEF){
		parse_S();
		parse_L();
	}else if(m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		parse_L();
	}else{
		syntax_error();
	}
}

void parse_S(){
	int m = nexttoken();
	if(m == M_ENDOFFILE){
	
	}else if(m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		//nothing
	}else if(m == M_DEF){
		parse_D();
		parse_S();
	}else{
		syntax_error();
	}
}

void parse_D(){
	int m = nexttoken();
	if(m == M_DEF){
		eat_token();
		m = nexttoken();
		if(m == M_ID){
			eat_token();
			parse_E();
			m = nexttoken();
			if(m == M_SEMIC){
				eat_token();
			}else{
				syntax_error();
			}
		}else{
			syntax_error();
		}
	}else{
		syntax_error();
	}
}

void parse_L(){
	int m = nexttoken();
	if(m == M_ENDOFFILE){
		//nothing	
	}else if(m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		parse_C();
		parse_L();
	}else if(m == M_END){
		//nothing
	}else{
		syntax_error();
	}
}

void parse_B(){
	int m = nexttoken();
	if(m == M_BEGIN){
		eat_token();
		parse_L();
		m = nexttoken();
		if(m == M_END){
			eat_token();
		}else{
			syntax_error();
		}
	}else if(m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		parse_C();
	}else{
		syntax_error();
	}
}

void parse_C(){
	int m = nexttoken();
	if(m == M_PRINT){
		eat_token();
		parse_E();
		m = nexttoken();
		if(m == M_SEMIC){
			eat_token();
		}else{
			syntax_error();
		}
	}else if(m == M_READ){
		eat_token();
		m = nexttoken();
		if(m == M_ID){
			eat_token();
			m = nexttoken();
			if(m == M_SEMIC){
				eat_token();
			}else{
				syntax_error();
			}
		}else{
			syntax_error();
		}
	}else if(m == M_SET){
		eat_token();
		m = nexttoken();
		if(m == M_ID){
			eat_token();
			parse_E();
			m = nexttoken();
			if(m == M_SEMIC){
				eat_token();
			}else{
				syntax_error();
			}
		}else{
			syntax_error();
		}
	}else if(m == M_IF){
		eat_token();
		parse_E();
		m = nexttoken();
		if(m == M_THEN){
			eat_token();
			parse_B();
			m = nexttoken();
			if(m == M_ELSE){
				eat_token();
				parse_B();
			}else{
				syntax_error();
			}
		}else{
			syntax_error();
		}
	}else if(m == M_WHILE){
		eat_token();
		parse_E();
		m = nexttoken();
		if(m == M_DO){
			eat_token();
			parse_B();
		}else{
			syntax_error();
		}
	}else{
		syntax_error();
	}
}

void parse_E(){
	int m = nexttoken();
	if(m == M_ID){
		eat_token();		//IDは読み終わった
	}else if(m == M_NUM){	//NUMの場合
		eat_token();
	}else if(m == M_ADD){
		eat_token();
		parse_E();
		parse_E();
	}else if(m == M_SUB){
		eat_token();
		parse_E();
		parse_E();
	}else if(m == M_EQ){
		eat_token();
		parse_E();
		parse_E();
	}else if(m == M_LESS){
		eat_token();
		parse_E();
		parse_E();
	}else{
		syntax_error();
	}
}

int parse(){
	parse_T();		//出発記号に関する解析関数を呼び出す
	if(nexttoken() != M_ENDOFFILE) syntax_error();
	return 0;
}

void eat_token(){
	saved_marker = M_EMPTY;
}

int scan(){
	int m = yylex();	//lexによって作られる関数、入力の末尾では0が返される
	return m;
}

int main(){
	init_buf();
	parse();
	fprintf(stderr,"OK\n");
	return 0;
}

