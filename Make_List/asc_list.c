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
	top=p=(PERSON *)malloc(sizeof(PERSON));	//空っぽで可哀想な最初のメモリ確保
	while(fgets(LINE,100,fp)!=NULL){
		p->next=(PERSON*)malloc(sizeof(PERSON));	//空っぽだったpの次にメモリ確保
		sscanf(LINE,"%s",p->next->name);
		p = p->next;	//pにp->nextのアドレスを渡し、pはnameが入ってる場所を指している。
	}
	p->next = NULL;	//終了条件

	top = top->next;	//最初は空っぽの可哀想なメモリ確保さんだからほっといて次のnameの入ってるところに移動
	while(top!=NULL){
		printf("%s\n",top->name);
		top=top->next;
	}

	return 0;

}
