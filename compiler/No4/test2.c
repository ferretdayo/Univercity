#include <stdio.h>
#include <string.h>

#define BUF_MAX 256
#define M_ENDOFFILE -2
#define ROW_MAX 6
#define COL_MAX 8
#define S_UD -1
#define S_0 0
#define S_1 1
#define S_2 2
#define S_3 3
#define S_4 4
#define S_5 5
#define M_UD -1
#define M_ID 0
#define M_NUM 1
#define M_SPC 2
#define M_NL 3
#define M_INT 4
#define F_NO 0
#define F_YES 1

char buf[BUF_MAX];
char yytext[BUF_MAX];
int n_processed;
int n_total;

int ns_table[6][8] = {
	{S_1 ,S_3 ,S_2 ,S_4 ,S_5 ,S_UD,F_NO ,M_UD },
	{S_1 ,S_1 ,S_1 ,S_UD,S_UD,S_UD,F_YES,M_ID },
	{S_UD,S_2 ,S_2 ,S_UD,S_UD,S_UD,F_YES,M_NUM},
	{S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_NUM},
	{S_UD,S_UD,S_UD,S_4 ,S_UD,S_UD,F_YES,M_SPC},
	{S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_NL },
};

int next_state(int q,char c){
	int col;
	if(c >= 'a' && c <= 'z') col = 0;
	else if(c == '0') col = 1;
	else if(c >= '1' && c <= '9') col = 2;
	else if(c == ' ') col = 3;
	else if(c == '\n') col = 4;
	else col = 5;
	return ns_table[q][col];
}

int is_final(int q){
	return ns_table[q][COL_MAX-2];
}

int marker(int q){
	return ns_table[q][COL_MAX-1];
}

int algorithm2_2(char str[]){
	int i = 0;
	int q = 0;
	int i_final = 0;
	int q_final = 0;
	char c;
	while(1){
		if(is_final(q) == F_YES){
			i_final = i;
			q_final = q;
		}
		c = str[i];
		if(next_state(q,c) != S_UD){
			q = next_state(q,c);
			i++;
		}else{
			break;
		}
	}
	if(i_final == 0){
		i_final = 1;
	}
	strncpy(yytext,str,i_final);
	yytext[i_final] = '\0';
	//yytextが"int"の場合とそうでない場合
	if(strcmp(yytext,"int") == 0){
		return M_INT;
	}else{
		return marker(q_final);
	}
}

void init_buf(){
	fgets(buf,BUF_MAX,stdin);
	n_total = strlen(buf);
	n_processed = 0;
}

int scan(){
	int ret;
	char *cp;
	if(n_processed == n_total){
		cp = fgets(buf,BUF_MAX,stdin);
		if(cp == NULL) return M_ENDOFFILE;
		n_total = strlen(buf);
		n_processed = 0;
	}
	cp = &buf[n_processed];
	ret = algorithm2_2(cp);
	n_processed += strlen(yytext);
	return ret;
}

int main(){
	int m;
	init_buf();
	while(1){
		m = scan();
		if(m == M_ENDOFFILE) break;
		switch(m){
			case M_ID:
				printf("Identifier : [%s]\n",yytext);
				break;
			case M_NUM:
				printf("Number : [%s]\n",yytext);
				break;
			case M_SPC:
				printf("Space : [%s]\n",yytext);
				break;
			case M_NL:
				printf("NL\n");
				break;
			case M_INT:
				printf("INT : [%s]\n",yytext);
				break;
			default:
				printf("lexical error : [%s]\n",yytext);
				break;
		}
	}
	return 0;
}
