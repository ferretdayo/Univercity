#include <stdio.h>
#include <stdlib.h>

typedef struct person{
	char name[100];
	struct person *next;
}PERSON;

int main(int argc,char *argv[]){
	int i;
	PERSON *top,*p;
	char LINE[100];
	FILE *fp;
	if(argc!=2){
		printf("引数がおかしいんじゃいこんにゃろ\n");
		return 0;
	}
	if((fp=fopen(argv[1],"r"))==NULL){
		printf("Open error\n");
		exit(1);
	}
	top=NULL;	//最後の終了条件のNULL
	while(fgets(LINE,100,fp)!=NULL){
		p=(PERSON*)malloc(sizeof(PERSON));
		sscanf(LINE,"%s",p->name);
		p->next = top;	//1回目はp->nextにNULL、2回目以降は作られているリストの先頭をp->nextに
		top = p;	//topを現在のリストの先頭のポインタpを渡す
	}

	while(top!=NULL){
		printf("%s\n",top->name);
		top=top->next;
	}

	return 0;

}
