#include <stdio.h>
#include <string.h>

#define BUF_MAX 256
#define M_ENDOFFILE -2
#define ROW_MAX 10
#define COL_MAX 15
#define S_UD -1
#define S_0 0
#define S_1 1
#define S_2 2
#define S_3 3
#define S_4 4
#define S_5 5
#define S_6 6
#define S_7 7
#define S_8 8
#define S_9 9
#define M_UD -1
#define M_ID 0
#define M_NUM 1
#define M_SPC 2
#define M_NL 3
#define M_INT 4
#define M_IF 5
#define F_NO 0
#define F_YES 1

char buf[BUF_MAX];
char yytext[BUF_MAX];
int n_processed;	//今どこまで見ているかの変数
int n_total;		//トータルの文字列の数

int ns_table[10][15] = {
	//          0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,   13,  14
	/*        a-z,   0, 1-9,空白,改行,   i,   n,   t,   f,  !i, !n!f, !t,   他,受理系,マーカ */
	/*0*/	{S_UD,S_3 ,S_2 ,S_4 ,S_5 ,S_6 ,S_UD,S_UD,S_UD,S_1 ,S_UD,S_UD,S_UD,F_NO ,M_UD },
	/*1*/	{S_1 ,S_1 ,S_1 ,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_ID },
	/*2*/	{S_UD,S_2 ,S_2 ,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_NUM},
	/*3*/	{S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_NUM},
	/*4*/	{S_UD,S_UD,S_UD,S_4 ,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_SPC},
	/*5*/	{S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_NL },
	/*6*/	{S_UD,S_1 ,S_1 ,S_UD,S_UD,S_UD,S_7 ,S_UD,S_9 ,S_UD,S_1 ,S_UD,S_UD,F_YES,M_ID },
	/*7*/	{S_UD,S_1 ,S_1 ,S_UD,S_UD,S_UD,S_UD,S_8 ,S_UD,S_UD,S_UD,S_1 ,S_UD,F_YES,M_ID },
	/*8*/	{S_1 ,S_1 ,S_1 ,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_INT},
	/*9*/	{S_1 ,S_1 ,S_1 ,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,S_UD,F_YES,M_IF }
	};

int next_state(int q,char c){
	int col;
	if(q == 0){
		if(c == 'i') col = 5;
		else if((c >= 'a' && c <= 'h')||(c >= 'j' && c <= 'z')) col = 9;
	}else if(q == 6){
		if(c == 'n') col = 6;
		else if(c == 'f') col = 8;
		else if((c >= 'a' && c <= 'e')||(c >= 'g' && c <= 'm')||(c >= 'o' && c <= 'z')) col = 10;
	}else if(q == 7){
		if(c == 't') col = 7;
		else if((c >= 'a' && c <= 's')||(c >= 'u' && c <= 'z')) col = 11;
	}else if(c >= 'a' && c <= 'z') col = 0;
	else col = 12;
	if(c == '0') col = 1;
	else if(c >= '1' && c <= '9') col = 2;
	else if(c == ' ') col = 3;
	else if(c == '\n') col = 4;
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
		//受理可能なら文字列の長さをi_finalに、IDかINTかNUMなどの判定結果となる行番号をq_finalに
		if(is_final(q) == F_YES){
			i_final = i;
			q_final = q;
		}
		c = str[i];
		//次の状態がS_UDでない場合、次に行く行番号qを変数qに代入し、文字列の長さのiをインクリメント
		if(next_state(q,c) != S_UD){
			q = next_state(q,c);
			i++;
		}else{
			break;
		}
	}
	//次の状態がS_UDかつ１文字だった場合、
	if(i_final == 0){
		i_final = 1;
	}
	strncpy(yytext,str,i_final);
	yytext[i_final] = '\0';
	return marker(q_final);
}

void init_buf(){
	fgets(buf,BUF_MAX,stdin);
	n_total = strlen(buf);
	n_processed = 0;
}

int scan(){
	int ret;
	char *cp;
	//最後まで見た場合
	if(n_processed == n_total){
		cp = fgets(buf,BUF_MAX,stdin);
		//何も入力されなかった場合
		if(cp == NULL) return M_ENDOFFILE;
		n_total = strlen(buf);
		n_processed = 0;
	}
	cp = &buf[n_processed];	//abc 123なら最初にaのアドレス、次に のアドレス、次に1のアドレスをcpに
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
			case M_IF:
				printf("IF : [%s]\n",yytext);
				break;
			default:
				printf("lexical error : [%s]\n",yytext);
				break;
		}
	}
	return 0;
}
