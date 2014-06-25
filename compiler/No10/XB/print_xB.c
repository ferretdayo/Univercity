#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_xB.h"
void print_T(struct T_t *t);
void print_S(struct S_t *s);
void print_D(struct D_t *d);
void print_B(struct B_t *b); 
void print_L(struct L_t *l);
void print_C(struct C_t *c);
void print_E(struct E_t *e);
void prologue();
void epilogue();
void codegen(struct T_t *tree);
void internal_error();

void print_C(struct C_t *c){
	if(c->kind == C_PRINT){
		printf("printf(\"%%d\\n\",");
		print_E(c->e);
		printf(");\n");
	}else if(c->kind == C_READ){
		printf("scanf(\"%%d\",&%s",c->str);
		printf(");\n");
		//to do
	}else if(c->kind == C_SET){
		printf("%s = ",c->str);
		print_E(c->e);
		printf(";\n");
	}else if(c->kind == C_IF){
		printf("if(");
		print_E(c->e);		//条件文
		printf("){\n");
		print_B(c->b_left);		//条件文がtrueの時の文
		printf("}else{\n");
		print_B(c->b_right);		//条件文がfalseの時の文
		printf("}\n");
	}else if(c->kind == C_WHILE){
		printf("while(");
		print_E(c->e);		//条件文
		printf("){\n");
		print_B(c->b);		//条件文がtrueの時の文
	}else{
		internal_error();
	}
}

void print_E(struct E_t *e){
	if(e->kind == E_ID){
		printf("%s",e->str);
	}else if(e->kind == E_NUM){
		printf("%s",e->str);
	}else if(e->kind == E_ADD){
		printf("(");
		print_E(e->e_left);
		printf("+");
		print_E(e->e_right);
		printf(")");
	}else if(e->kind == E_SUB){
		printf("(");
		print_E(e->e_left);
		printf("-");
		print_E(e->e_right);
		printf(")");
	}else if(e->kind == E_EQ){
		printf("(");
		print_E(e->e_left);
		printf("==");
		print_E(e->e_right);
		printf(")");
	}else if(e->kind == E_LESS){
		printf("(");
		print_E(e->e_left);
		printf("<");		//e_left < e_right
		print_E(e->e_right);
		printf(")");
	}else{
		internal_error();
	}
}

void print_L(struct L_t *l){
	if(l->kind == L_EPS){
		//do nothing
	}else if(l->kind == L_CL){
		print_C(l->c);
		print_L(l->l);
	}else{
		internal_error();
	}
}

void print_B(struct B_t *b){
	if(b->kind == B_BEGIN){
		print_L(b->l);
		printf("}\n");
	}else if(b->kind == B_C){
		print_C(b->c);
	}else{
		internal_error();
	}
}

void print_D(struct D_t *d){
	if(d->kind == D_DEF){
		printf("int %s = ",d->str);
		print_E(d->e);
		printf(";\n");
	}else{
		internal_error();
	}
}

void print_S(struct S_t *s){
	if(s->kind == S_EPS){
		//do nothing
	}else if(s->kind == S_DS){
		print_D(s->d);
		print_S(s->s);
	}else{
		internal_error();
	}
}

void print_T(struct T_t *t){
	if(t->kind == T_SL){
		print_S(t->s);
		print_L(t->l);
	}else{
		internal_error();
	}
}

void prologue(){
	printf("#include <stdio.h>\n");
	printf("int main() {\n");
}

void epilogue(){
	printf("return 0;\n");
	printf("}\n");
}

void codegen(struct T_t *tree){
	prologue();
	print_T(tree);
	epilogue();
}

void internal_error(){
	fprintf(stderr,"Internal Error.\n");
	exit(-1);
}
