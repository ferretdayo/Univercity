#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token_xB.h"
#include "tree_xB.h"

#define BUF_MAX 256
#define M_EMPTY -3

char buf[BUF_MAX];
extern char *yytext;
int n_processed;
int n_total;
int saved_marker;	//切り出しと消費を区別
int yylval;		//yylex()の戻り値の型の指定
struct T_t *parse_T();
struct S_t *parse_S();
struct D_t *parse_D();
struct L_t *parse_L();
struct B_t *parse_B();
struct C_t *parse_C();
struct E_t *parse_E();
struct T_t *parse();
void init_buf();
void syntax_error();
int nexttoken();
int scan();
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

struct T_t *parse_T(){
	struct T_t *t = malloc(sizeof(struct T_t));
	int m = nexttoken();
	if(m == M_ENDOFFILE || m == M_DEF || m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		t->kind = T_SL;		//タグの登録
		t->s = parse_S();
		t->l = parse_L();
	}else{
		syntax_error();
	}
	return t;
}

struct S_t *parse_S(){
	struct S_t *s = malloc(sizeof(struct S_t));
	int m = nexttoken();
	if(m == M_ENDOFFILE || m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		s->kind = S_EPS;	//タグの登録
	}else if(m == M_DEF){
		s->kind = S_DS;
		s->d = parse_D();
		s->s = parse_S();
	}else{
		syntax_error();
	}
	return s;
}

struct D_t *parse_D(){
	struct D_t *d = malloc(sizeof(struct D_t));
	int m = nexttoken();
	if(m == M_DEF){
		eat_token();
		d->kind = D_DEF;
		m = nexttoken();
		if(m == M_ID){
			eat_token();
			strcpy(d->str,yytext);
			d->e = parse_E();
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
	return d;
}

struct L_t *parse_L(){
	struct L_t *l = malloc(sizeof(struct L_t));
	int m = nexttoken();
	if(m == M_ENDOFFILE || m == M_END){
		l->kind = L_EPS;			
	}else if(m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		l->kind = L_CL;
		l->c = parse_C();
		l->l = parse_L();
	}else{
		syntax_error();
	}
	return l;
}

struct B_t *parse_B(){
	struct B_t *b = malloc(sizeof(struct B_t));
	int m = nexttoken();
	if(m == M_BEGIN){
		eat_token();
		b->kind = B_BEGIN;
		b->l = parse_L();
		m = nexttoken();
		if(m == M_END){
			eat_token();
		}else{
			syntax_error();
		}
	}else if(m == M_PRINT || m == M_READ || m == M_SET || m == M_IF || m == M_WHILE){
		b->kind = B_C;
		b->c = parse_C();
	}else{
		syntax_error();
	}
	return b;
}

struct C_t *parse_C(){
	struct C_t *c = malloc(sizeof(struct C_t));
	int m = nexttoken();
	if(m == M_PRINT){
		eat_token();
		c->kind = C_PRINT;
		c->e = parse_E();
		m = nexttoken();
		if(m == M_SEMIC){
			eat_token();
		}else{
			syntax_error();
		}
	}else if(m == M_READ){
		eat_token();
		c->kind = C_READ;
		m = nexttoken();
		if(m == M_ID){
			eat_token();
			strcpy(c->str,yytext);
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
		c->kind = C_SET;
		m = nexttoken();
		if(m == M_ID){
			eat_token();
			strcpy(c->str,yytext);
			c->e = parse_E();
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
		c->kind = C_IF;
		c->e = parse_E();
		m = nexttoken();
		if(m == M_THEN){
			eat_token();
			c->b_left = parse_B();
			m = nexttoken();
			if(m == M_ELSE){
				eat_token();
				c->b_right = parse_B();
			}else{
				syntax_error();
			}
		}else{
			syntax_error();
		}
	}else if(m == M_WHILE){
		eat_token();
		c->kind = C_WHILE;
		c->e = parse_E();
		m = nexttoken();
		if(m == M_DO){
			eat_token();
			c->b = parse_B();
		}else{
			syntax_error();
		}
	}else{
		syntax_error();
	}
	return c;
}

struct E_t *parse_E(){
	struct E_t *e = malloc(sizeof(struct E_t));
	int m = nexttoken();
	if(m == M_ID){
		eat_token();		//IDは読み終わった
		e->kind = E_ID;
		strcpy(e->str,yytext);	
	}else if(m == M_NUM){	//NUMの場合
		eat_token();
		e->kind = E_NUM;
		strcpy(e->str,yytext);
	}else if(m == M_ADD){
		eat_token();
		e->kind = E_ADD;
		e->e_left = parse_E();
		e->e_right = parse_E();
	}else if(m == M_SUB){
		eat_token();
		e->kind = E_SUB;
		e->e_left = parse_E();
		e->e_right = parse_E();
	}else if(m == M_EQ){
		eat_token();
		e->kind = E_EQ;
		e->e_left = parse_E();
		e->e_right = parse_E();
	}else if(m == M_LESS){
		eat_token();
		e->kind = E_LESS;
		e->e_left = parse_E();
		e->e_right = parse_E();
	}else{
		syntax_error();
	}
	return e;
}

struct T_t *parse(){
	struct T_t *tree;
	tree = parse_T();
	if(nexttoken() != M_ENDOFFILE) syntax_error();
	return tree;
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
	init_idtable();
	struct T_t *tree = parse();
	fprintf(stderr,"OK\n");
	check(tree);
	codegen(tree);
	return 0;
}
