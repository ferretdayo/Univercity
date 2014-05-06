#include <stdio.h>
#include <string.h>

#define LENGTH 256
int pos;
char error[2][20] = {"数字の表現がおかしいです。","式がおかしいです。"};
int check;
/*
	単語を一つ切り出す
	引数 : 文字列
	戻り値 : 引数の文字列の先頭に対応する文字
*/

char scan(char *str){
	char ch;
	int flg=0; //前に打ったものの判断(数字:1,演算子:2)
	int ope=0; //演算子
	int num=0; //数字
	if(strncmp(str,"ichi",4) == 0){
		ch = '1';
		pos += 4;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"ni",2) == 0){
		ch = '2';
		pos += 2;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"san",3) == 0){
		ch = '3';
		pos += 3;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"shi",3) == 0){
		ch = '4';
		pos += 3;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"go",2) == 0){
		ch = '5';
		pos += 2;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"roku",4) == 0){
		ch = '6';
		pos += 4;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"shichi",6) == 0){
		ch = '7';
		pos += 6;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"hachi",5) == 0){
		ch = '8';
		pos += 5;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"ku",2) == 0){
		ch = '9';
		pos += 2;
		if(flg == 1){
			num++;
		}
		flg=1;
	}else if(strncmp(str,"tasu",4) == 0){
		ch = '+';
		pos += 4;
		if(flg == 2){
			ope++;
		}
		flg == 2;
	}else if(strncmp(str,"hiku",4) == 0){
		ch = '-';
		pos += 4;
		if(flg == 2){
			ope++;
		}
		flg == 2;
	}else{
		ch = 'x';
		pos += 1;
		check = 3;
	}
	if(ope >= 1){	//演算子が2個以上
		check = 2;
	}else if(num >= 1){
		check = 1;
	}
	return ch;
}

int main(){
	char ib[LENGTH];
	char ob[LENGTH];
	int j;
	int error_flg = 0;
	//読み込み
	fgets(ib,LENGTH,stdin);
	//切り分け
	pos = 0;
	//式の判別(数字:1,演算子:2,それ以外:-1)
	check = 0;
	j = 0;
	while(ib[pos] != '\n'){
		ob[j] = scan(&ib[pos]);
		if(ob[j] == 'x'){
			
		j++;
	}
	ob[j] = '\0';

	printf(" -> %s\n",ob);
	return 0;
}
