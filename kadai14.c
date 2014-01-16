#include <stdio.h>
#include <time.h>
#include <string.h>

void result_screen(double dtime,int len){
	double typespeed;

	typespeed = len/(dtime/60);	//１分あたりのタイプ量
	printf("タイプスピード : %f , 入力数 : %d , 時間 : %f\n",typespeed,len,dtime);
	
}

void change(char *str){
	while(*str!='\n'){
		str++;
	}
	*str = '\0';
}

int main(){
	time_t start;
	time_t stop;
	int command;
	double diftime;
	char a[3];
	int i=0,len=0,no=0;
	char input[100];
	char *words[5] =	{"A bad workman quarrels with his tools.",
				"Every man is the architect of his own fortune.",
				"People who live in glass houses should not throw stones.",
				"A bird in the hand is worth two in the bush.",
				"As you make your bed, so you must lie in it."
				};

	while(1){
		command = 3;
		i=0;
		while(command<1||command>2){
			puts("-------------タイピングゲーム☆-------------");
			puts("1. 始める");
			puts("2. 終了");
			fgets(a,3,stdin);
			command=atoi(a);
		}	
		if(command==2){
			return 0;
		}
		if(command==1){
			time(&start);	//開始時刻の取得
			while(i<5){
				printf("----%d行目----\n",i+1);
				printf("%s\n",words[i]);
				fgets(input,100,stdin);
				change(input);
				if(strcmp(words[i],input)!=0/*文字列のチェック*/){
					len += strlen(input);
					continue;
				}
				len += strlen(input);
				i++;
			}
		}
		time(&stop);		//終了時刻の取得
		diftime = difftime(stop,start);	//経過時間
		result_screen(diftime,len);		//結果の表示
	}

	return 0;

}
