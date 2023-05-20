/*
"But his delight is in the law of the LORD; and in his law doth he meditate day and night." Psalm 1:2

The purpose of the program is to help Christians to recite the Scripture well.

*/
#define Max 500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void reciting();
int firstpage();
void create();
void delete();
void update();
void each();

int main() {
    int in;
	while(1){
        in = firstpage();

        if(in == 1)
            reciting();
        else if(in == 2)
            create();
        else if(in == 3)
            delete();
        else if(in == 4)
            update();
        else if(in == 5)
            each();
        
        else
            printf("잘못된 입력입니다. 다시 입력하세요 \n\n");
        
    }
	return 0;
}


int firstpage(){//처음 페이지로 메뉴 고르고 그 값을 반환까지 함. 
    int in;
    //////////////////////첫 페이지 출력 내용 작성
	

    printf("1. reciting\n");
    printf("2. create\n");
    printf("3. delete\n");
    printf("4. update\n");
    printf("5. each\n\n");
	
	
/////it'll continue
	
	
    scanf("%d", &in);
    return in;

}



void reciting(){
    ///책선택
    FILE *book;
    book = fopen("booklist.txt", "r");
    int bi=0;
    char books[66][20], thebook[20];
	printf("책 선택: \n\n");
    while(!feof(book)){
        fscanf(book, "%s", books[bi]);
        printf("%d. %s\n", bi+1, books[bi]);
        bi++;
    }
    fclose(book);
    scanf("%d", &bi);
    strcpy(thebook, books[bi-1]);
    strcat(thebook, ".txt");

    printf("%s", thebook);

	//\

    int chap, vers, mode;
	printf("장 선택:");
	scanf("%d", &chap);
	printf("절 선택:");
	scanf("%d", &vers);
	
	printf("\n\n1. 따라쓰기\n2. 암송\n");
	scanf("%d", &mode);
	printf("도움말이 필요하면 ?을 누르시오\n");
	getchar();
	printf("\n\n\n");
	

	char* a, * t, * t1;
	a = (char*)malloc(Max);
	t = (char*)malloc(Max);
	t1 = (char*)malloc(Max);
	int v = -1, i;
	sprintf(a, "%d", chap);
	strcat(a, "장\n");
	printf("%s", a);
	FILE* f;
	f = fopen(thebook, "r");


	//searching wanted position
	while (!feof(f)) {//searching chapter
		fgets(t, Max, f);
		if (strlen(t) < 30)//pass if it is contents of verse
			if (strncmp(t, a, 4) == 0)
				break;
	}
	if (vers > 0)//if choose the verse
		while (!feof(f)) {
			fscanf(f, "%d. ", &v);
			fgets(a, Max, f);
			if (v == vers)
				break;
		}
	
	if (vers != v && strcmp(t, "\n") != 0 && vers != -1) {//if file ends without wanted result, finish the pg with error message
		printf("cannot be found\n");
		exit(0);
	}//end searching
    
	goto b2;

	while (!feof(f)) {
		fgets(t, Max, f);
		if (strcmp(t, "\n") == 0) {//단락 구분인 경우
			printf("\n");
			continue;
		}
		else if (strlen(t) < 30 && strstr(t, "장")) {//장이 넘어가는 경우
			v = 1;
			printf("\n\n%s\n", t);
			continue;
		}
		sscanf(t, "%d. %s", &v, t1);
		for (; t[0] != ' '; t++);//removing verse tag from t
		strcpy(a, ++t);
	b2:
		i = 0;
		printf("%d. ", v);
		if (mode == 1)
			printf("%s%d. ", a, v);//따라쓰기 틀
	b3://when * is input
		fgets(t, Max, stdin);
		if (strstr(t, "*")) {
			i -= 10;
			if (strstr(t, " *"))
				strcpy(strstr(t, " *"), " ");//기존 * 자리
			else
				strcpy(strstr(t, "*"), " ");

			if (i == -10)
				strcpy(t1, t);
			else
				strcat(t1, t);
			goto b3;
		}
		if (i < 0) {
			strcat(t1, t);
			strcpy(t, t1);
		}
		if (strcmp(t, "/\n") == 0) //jump to next verse
			continue;
		else if (strcmp(t, "+\n") == 0) {//show the contents of verse
			printf("%d. %s", v, a);
			goto b2;
		}
		else if (strcmp(t, ">\n") == 0) {//show the contents of verse
			printf("%d. %s", v, a);
			goto b2;
		}
		else if (strcmp(t, "?\n") == 0) {//jump to next verse
			printf("\n* 이어서 입력\n> 힌트\n/ 다음 절로 이동\n] 다음 단락으로 이동\n? 도움말\n- 종료\n\n");
			hint(t, thebook);
		}
		else if (strcmp(t, "]\n") == 0) //jump to next paragraph
			while (!feof(f)) {
				fgets(t, Max, f);
				if (strcmp(t, "\n") == 0)
					break;
			}
		if (strcmp(t, "-\n") == 0) //jump to next verse
			break; //변환됨.
		else if (strcmp(t, a) != 0)//t is input value, and a is net contents of verse
			goto b2;
	}
	fclose(f);
}


void create(){

}
void delete(){

}
void update(){

}


void hint(char str[] /* 구절 */ , char tf [] /*텍스트 파일 이름*/){
	int hn ; //원하는 힌트 번호
	printf("어떤 힌트를 원하시나요?\n 1. 첫글자 힌트\n 2. 글자 수 힌트\n 3. 챕터 힌트\n 0. 취소\n ");
	scanf("%d",&hn);
	if(strcmp(tf,"dayBibleVerse.txt")==0){
		if( hn == 1 ){
			printf("%c",str[3]);
		}
		if( hn == 2 ){
			printf("%lu",strlen(str));
		}
		if( hn == 3 ){
			while(1){ // str의 글자 하나씩 검사
				int n = 0 ;
				if(str[n] != '('){ // '('가 아니라면 continue 
					continue ; 
				}
				if(str[n] == ')'){ // '('가 나오면 
					while(str[n] != ')'){ // ')'가 나오기 전까지 프린트
						printf("%c",str[n]);
					}
				}
				break ; 
			}
		}
	}
	else if(strcmp(tf,"dayBibleVerse.txt")!=0){
		if( hn == 1 ) {
			printf("%c",str[3]);
		}
		if( hn == 2 ){
			printf("%lu",strlen(str));
		}
		if( hn == 3 ){
			printf("%c",str[0]);
		}
	}
}

void each(){
    FILE* fp ; 
    fp = fopen("dayBIbleVerse.txt","r");

    time_t x1;
    struct tm *p;
    x1 = time(NULL);
    p = localtime(&x1); // 시간함수
	int* t ;
    char  dv[128] ; 
	
	while(!feof(fp)){
		fscanf(fp,"%d",t); 
		if(*t== p->tm_mday){
			fgets(dv,128,fp);
			break ; 
		}
	}
   
	fclose(fp);
	printf("%s",dv);


}
