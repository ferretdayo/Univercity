#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree_xB.h"
#define VAR_MAX 1000
#define NAME_LENGTH_MAX 100

void check_L(struct L_t *l);
void check_C(struct C_t *c);
void check_E(struct E_t *e);
void check_B(struct B_t *b);
void check_T(struct T_t *t);
void check_D(struct D_t *d);
void check_S(struct S_t *s);
void check(struct T_t *tree);
void init_idtable();
int lookup_id(char name[]);
int register_id(char name[]);
void semantic_error();
void internal_error();
int repeat_var(char name[]);
void repetition_error();
void unused_var();
void used_var(char name[]);
void format_array();

int used_var_count[VAR_MAX];

struct IdTable_t *idtable;

struct VarInfo_t{	//IDの名前
	char name[NAME_LENGTH_MAX];
};

struct IdTable_t{	//識別表
	struct VarInfo_t var[VAR_MAX];
	int n_vars;	//登録されている変数の数
};

void check_T(struct T_t *t){
	if(t->kind == T_SL){
		check_S(t->s);
		check_L(t->l);
	}else{
		internal_error();
	}
}

void check_S(struct S_t *s){
	if(s->kind == S_EPS){
		/* do nothing */
	}else if(s->kind == S_DS){
		check_D(s->d);
		check_S(s->s);
	}else{
		internal_error();
	}
}

void check_D(struct D_t *d){
	if(d->kind == D_DEF){
		check_E(d->e);
		if(repeat_var(d->str) == -1){
			repetition_error();
		}
		register_id(d->str);
	}else{
		internal_error();
	}
}

void check_L(struct L_t *l){
	if(l->kind == L_EPS){
		/* do nothing */
	}else if(l->kind == L_CL){
		check_C(l->c);
		check_L(l->l);
	}else{
		internal_error();
	}
}

void check_B(struct B_t *b){
	if(b->kind == B_BEGIN){
		check_L(b->l);
	}else if(b->kind == B_C){
		check_C(b->c);
	}else{
		internal_error();
	}
}

void check_C(struct C_t *c){
	if(c->kind == C_PRINT){
		check_E(c->e);
	}else if(c->kind == C_READ){
		if(lookup_id(c->str) < 0){
			semantic_error();
		}
		used_var(c->str);
	}else if(c->kind == C_SET){
		check_E(c->e);
		if(lookup_id(c->str) < 0){
			semantic_error();
		}
		used_var(c->str);
	}else if(c->kind == C_IF){
		check_E(c->e);
		check_B(c->b_left);
		check_B(c->b_right);
	}else if(c->kind == C_WHILE){
		check_E(c->e);
		check_B(c->b);
	}else{
		internal_error();
	}
}

void check_E(struct E_t *e){
	if(e->kind == E_ID){
		if(lookup_id(e->str) < 0){
			semantic_error();
		}
		used_var(e->str);
	}else if(e->kind == E_NUM){
		/* do nothing */
	}else if(e->kind == E_ADD){	
		check_E(e->e_left);
		check_E(e->e_right);
	}else if(e->kind == E_SUB){
		check_E(e->e_left);
		check_E(e->e_right);
	}else if(e->kind == E_EQ){
		check_E(e->e_left);
		check_E(e->e_right);
	}else if(e->kind == E_LESS){
		check_E(e->e_left);
		check_E(e->e_right);
	}else{
		internal_error();
	}
}

void check(struct T_t *tree){
	format_array();		//配列の初期化(0を代入)
	check_T(tree);
	unused_var();		//未使用変数のcheck
}

int repeat_var(char name[]){
	int i;
	for(i = idtable->n_vars-1;i >= 0;i--){
		if(strcmp(idtable->var[i].name,name) == 0){
			return -1;
		}
	}
	return 1;
}

void used_var(char name[]){
	int i;
	for(i = idtable->n_vars-1;i >= 0;i--){
		if(strcmp(idtable->var[i].name,name)==0){
			used_var_count[i] = 1;
		}
	}
}

void unused_var(){
	int i;
	for(i = 0;i <= idtable->n_vars-1;i++){
		if(used_var_count[i] == 0){
			fprintf(stderr,"warning : %s unused variable.\n",idtable->var[i].name);
		}
	}
}

void format_array(){
	int i;
	for(i = 0;i < VAR_MAX;i++){
		used_var_count[i] = 0;
	}
}

void init_idtable(){
	idtable = malloc(sizeof(struct IdTable_t));
	idtable->n_vars = 0;
}

int lookup_id(char name[]){	//識別子の登録情報を検索
	int i;
	for(i = idtable->n_vars-1;i >= 0;i--){
		if(strcmp(idtable->var[i].name,name) == 0) break;
	}
	return i;
}

void repetition_error(){
	fprintf(stderr,"Repetition Error.\n");
	exit(-1);
}

int register_id(char name[]){	//識別子を識別表に登録
	int n = idtable->n_vars;
	if(n >= VAR_MAX) return -2;	//too many ids
	strcpy(idtable->var[n].name,name);
	idtable->n_vars++;
	return n;
}

void semantic_error(){
	fprintf(stderr,"Semantic Error.\n");
	exit(-1);
}
