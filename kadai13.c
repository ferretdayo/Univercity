#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person{
        char name[20]; //名前
        char sex; //性別
        int Japa; //国語
        int Math; //数学
        int Scie; //理科
        int Soci; //社会
        int Engl; //英語
        double ave; //その人の平均点
        struct person *next; //次の構造体へのぽいんた
}PERSON;

typedef struct{
        double Japa;
        double Math;
        double Scie;
        double Soci;
        double Engl;
        double ave;
}AVERAGE;

//その人の平均を求める関数
void average(PERSON *p){
        double sum=0;
        sum = p->Japa + p->Math + p->Scie + p->Soci + p->Engl;
        p->ave = sum / 5;
}

//リストを作成する関数
void makelist(PERSON *data,PERSON *first,FILE *fp){
        char line[256];
        while(fgets(line,256,fp)!=NULL){
                data->next=(PERSON*)malloc(sizeof(PERSON));
                sscanf(line,"%s %c %d %d %d %d %d",data->next->name,&data->next->sex,&data->next->Japa,&data->next->Math,&data->next->Scie,&data->next->Soci,&data->next->Engl);
                        data = data->next;
        }
        data->next=NULL;
}

void up_ave(AVERAGE p,PERSON *s,int select,char sex){
        int no=-1;
        while(no<0||no>7){
                puts("---------------------------------");
                puts("1. 国語の平均以上");
                puts("2. 算数の平均以上");
                puts("3. 理科の平均以上");
                puts("4. 社会の平均以上");
                puts("5. 英語の平均以上");
                puts("6. 5教科の平均点の平均以上");
                puts("0. メニュー画面に戻る");
                puts("---------------------------------");
                scanf("%d",&no);
        }
        if(no!=0){
                printf("\t名前\t性別\t国語\t算数\t理科\t社会\t英語\t平均点\n");
        }
        while(s!=NULL){
                switch(no){
                        case 1:
                                if(select==2){
                                        if(sex==s->sex){
                                                if(s->Japa>=p.Japa/*国語平均*/){
                                                        printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                                }
                                        }
                                }else{
                                        if(s->Japa>=p.Japa/*国語平均*/){
                                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                        }

                                }
                                s = s->next;
                                break;
                        case 2:
                                if(select==2){
                                        if(sex==s->sex){
                                                if(s->Math>=p.Math/*数学平均*/){
                                                        printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                                }
                                        }
                                }else{
                                        if(s->Math>=p.Math/*数学平均*/){
                                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                        }
                                }
                                s = s->next;
                                break;
                        case 3:
                                if(select==2){
                                        if(sex==s->sex){
                                                if(s->Scie>=p.Scie/*理科平均*/){
                                                        printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                                }
                                        }
                                }else{
                                        if(s->Scie>=p.Scie/*理科平均*/){
                                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                        }
                                }
                                s = s->next;
                                break;
                        case 4:
                                if(select==2){
                                        if(sex==s->sex){
                                                if(s->Soci>=p.Soci/*社会平均*/){
                                                        printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                                }
                                        }
                                }else{
                                        if(s->Soci>=p.Soci/*社会平均*/){
                                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                        }
                                }
                                s = s->next;
                                break;
                        case 5:
                                if(select==2){
                                        if(sex==s->sex){
                                                if(s->Engl>=p.Engl/*英語平均*/){
                                                        printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                                }
                                        }
                                }else{
                                        if(s->Engl>=p.Engl/*英語平均*/){
                                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                        }
                                }
                                s = s->next;
                                break;
                        case 6:
                                if(select==2){
                                        if(sex==s->sex){
                                                if(s->ave>=p.ave/*5教科平均*/){
                                                        printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                                }
                                        }
                                }else{
                                        if(s->ave>=p.ave/*5教科平均*/){
                                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",s->name,s->sex,s->Japa,s->Math,s->Scie,s->Soci,s->Engl,s->ave);
                                        }
                                }
                                s = s->next;
                                break;
                        default:
                                main();
                                break;
                }
        }
}

//出力する関数
void screen(PERSON *p,int select,char name[],char sex){
        AVERAGE s;
        PERSON *n=p;
        double Math=0,Japa=0,Scie=0,Soci=0,Engl=0,per=0;
        int count = 0;
        printf("\t名前\t性別\t国語\t算数\t理科\t社会\t英語\t平均点\n");
        while(p!=NULL){ //表示
                //名前検索
                if(select==1){
                        if(strcmp(name,p->name)==0){
                                average(p); //その人の平均を計算
                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",p->name,p->sex,p->Japa,p->Math,p->Scie,p->Soci,p->Engl,p->ave);
                                count++;
                        }
                        //次のポインタへ
                        p = p->next;
                //性別検索
                }else if(select==2){
                        if(sex==p->sex){
                                average(p); //その人の平均を計算
                                printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",p->name,p->sex,p->Japa,p->Math,p->Scie,p->Soci,p->Engl,p->ave);
                                //各教科の合計
                                Math += p->Math;
                                Japa += p->Japa;
                                Scie += p->Scie;
                                Soci += p->Soci;
                                Engl += p->Engl;
                                per += p->ave;
                                count++;
                        }
                                //次のポインタへ
                                p = p->next;
                //すべて表示
                }else if(select==0){
                        average(p); //その人の平均を計算
                        printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\t%.2f\n",p->name,p->sex,p->Japa,p->Math,p->Scie,p->Soci,p->Engl,p->ave);
                        //各教科の合計
                        Math += p->Math;
                        Japa += p->Japa;
                        Scie += p->Scie;
                        Soci += p->Soci;
                        Engl += p->Engl;
                        per += p->ave;
                        count++;
                        p=p->next;
                }
        }
        if(count>0){
                if(select!=1){
                        s.Japa = Japa/count;
                        s.Math = Math/count;
                        s.Scie = Scie/count;
                        s.Soci = Soci/count;
                        s.Engl = Engl/count;
                        s.ave = per/count;
                        printf("\t平均\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",Japa/count,Math/count,Scie/count,Soci/count,Engl/count,per/count);
                        up_ave(s,n,select,sex); //平均以上の表示
                }
        }else{
                printf("%d\n",count);
                puts("該当する人はいませんでした。");
        }
        
}


int main(){
        int select;
        int no,count;
        int flg=0;
        char loadfile[20],name[10],sex,deletename[10];
        char input_sex,input_name[10];
        int input_Ja,input_Ma,input_Sc,input_So,input_En;
        PERSON *first=NULL,*data,*p,*del;
        FILE *fp;

        while(1){
                no=-1;
                select = -1;
		    count = 0;
                puts("------------Menu-----------");
                puts("1. データ読み取り");
                puts("2. 一覧表示");
                puts("3. データの追加");
		    puts("4. データの削除");
                puts("0. 終了");
                puts("---------------------------");
                printf("コマンド>>");
                scanf("%d",&no);

                if(no==0){
                        puts("[終了]");
				exit(1);
                        return 0;
                }

                if(no!=1&&no!=2&&no!=3&&no!=4){
                        printf("1,2,3,0の中から入力してください\n");
                        continue;
                }
                if(no==1){
                        puts("[データ読み込み]");
                        printf("ファイル名を入力してください>>");
                        scanf("%s",loadfile);
                        if((fp=fopen(loadfile,"r"))==NULL){
                                printf("%sが見つかりません\n",loadfile);
                                exit(1);
                        }
                        //ファイルの内容の読み込み
                        first=data=(PERSON*)malloc(sizeof(PERSON));
                        //リストの作成
                        makelist(data,first,fp);
                        printf("ファイル%sからデータを読み込みました。\n",loadfile);
                        flg=1; //読み込みしたのでflgを1にする
                        fclose(fp);
                }else if(no==2&&flg==1){
                        p = first->next; //最初は空なので、次のポインタから始める
                        while(select!=0&&select!=1&&select!=2){
                                puts("------------subMenu-----------");
                                puts("0. すべて表示");
                                puts("1. 名前検索");
                                puts("2. 性別検索");
                                puts("------------------------------");
                                printf("コマンド>>");
                                scanf("%d",&select);
                        }
                        if(select==1){
                                printf("名前を入力してください>>");
                                scanf("%s",name);
                        }
                        if(select==2){
                                printf("MorFを入力してください>>");
                                scanf("%*c%c",&sex);
                        }
                        //内容の表示する関数screenの呼出
                        screen(p,select,name,sex);
                        continue;
                }else if(flg==0){
                        puts("データの読み込みを先にしてください");
                }else if(no==3&&flg==1){                //データの追加
                        if((fp=fopen(loadfile,"a"))==NULL){
                                printf("ファイルが見つかりません\n");
                                exit(1);
                        }
                        printf("データ追加(名前　性別　国語の点　算数の点　理科の点　社会の点　英語の点)\n");
                        printf("input(name sex Japanese....)>>");
                        scanf("%s %*c%c %d %d %d %d %d",input_name,&input_sex,&input_Ja,&input_Ma,&input_Sc,&input_So,&input_En);
                        fprintf(fp,"%s %c %d %d %d %d %d\n",input_name,input_sex,input_Ja,input_Ma,input_Sc,input_So,input_En);
                        fclose(fp);
                        flg=0;
                }else if(no==4&&flg==1){
                        if((fp=fopen(loadfile,"w"))==NULL){
                                printf("ファイルが見つかりません\n");
                                exit(1);
                        }
			p = first->next;
			while(p!=NULL){
				printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\n",p->name,p->sex,p->Japa,p->Math,p->Scie,p->Soci,p->Engl);
				p=p->next;
			}
			printf("削除したいデータはどれですか？\n");
			printf("name >> ");
			scanf("%s",deletename);
			p = first -> next;
			del = first;
			while(p!=NULL){		//消す作業
				if(strcmp(deletename,p->name)==0){
					del -> next = p -> next;
					free(p);	//要らないところを削除
					count++;
				}
				del = del->next;
				p = p->next;
			}
			if(count==0){
				printf("%sが存在しません。\n",deletename);
				continue;
			}
			p = first->next;
			printf("結果\n");
			while(p!=NULL){
				printf("\t%s\t%c\t%d\t%d\t%d\t%d\t%d\n",p->name,p->sex,p->Japa,p->Math,p->Scie,p->Soci,p->Engl);
                 	　      fprintf(fp,"%s %c %d %d %d %d %d\n",p->name,p->sex,p->Japa,p->Math,p->Scie,p->Soci,p->Engl);
				p=p->next;
			}
			fclose(fp);
		}		
                        
    	}
        return 0;
}
