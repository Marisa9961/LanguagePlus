#include<stdio.h>
#include<string.h>
#include"Token.h"

static void Fread(FILE *fp, char FileDir[]){
    fp = fopen(FileDir, "r");
/*  
    检查文件是否读取成功
    if(fp == NULL)
        printf("File Open Failed !\n");
    else printf("File Open Succeed !\n");
*/
    fread(buffer, sizeof(buffer), 1, fp);
    strcat(buffer, " ");
    fclose(fp);
}

int Open_File(void){
    int i;
    char Custom[256] = "\0";
    FILE *fp = NULL;

    printf("Please input number to choose the file: 1~5\n");
    scanf("%d", &i);

    switch(i){
        case 1:{
            Fread(fp, "../Document/Examples/1_assign.pl");
            break;
        }
        case 2:{
            Fread(fp, "../Document/Examples/2_express.pl");
            break;
        }
        case 3:{
            Fread(fp, "../Document/Examples/3_number.pl");
            break;
        }
        case 4:{
            Fread(fp, "../Document/Examples/4_symbol.pl");
            break;
        }
        case 5:{
            Fread(fp, "../Document/Examples/5_test.pl");
            break;
        }
        case 6:{
            printf("Please Enter Any String:\n");
            fflush(stdin);//清空键入缓存
            gets(Custom);
            strcpy(buffer, Custom);
            strcat(buffer, " ");
            break;
        }
        default:{
            printf("Please input a correct choice(1~5) and restart the program\n");
            return 0;
        }
    }

    return 1;
}