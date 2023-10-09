#include<stdio.h>
#include<string.h>
#include"Token.h"
#include"Lexcial.h"

extern struct Token token[256];

void Fread(FILE *fp, char FileDir[]){
    fp = fopen(FileDir, "r");
/*  
    检查文件是否读取成功
    if(fp == NULL)
        printf("File Open Failed !\n");
    else printf("File Open Succeed !\n");
*/
    fread(buffer, sizeof(buffer), 1, fp);
    fclose(fp);
}

int Fopen(void){
    int i;
    char Custom[256] = "\0";
    FILE *fp = NULL;

    printf("Please input number to choose the file: 1~4\n");
    printf("(Or input 5 to choose the Custom Debug Mode)\n");
    Input:
    scanf("%d", &i);

    switch(i){
        case 1:{
            Fread(fp, "Examples/1_assign.pl");
            printf("%s",buffer);
            break;
        }
        case 2:{
            Fread(fp, "Examples/2_express.pl");
            break;
        }
        case 3:{
            Fread(fp, "Examples/3_number.pl");
            break;
        }
        case 4:{
            Fread(fp, "Examples/4_symbol.pl");
            break;
        }
        case 5:{
            printf("Please Enter Any String:\n");
            fflush(stdin);
            gets(Custom);
            strcpy(buffer, Custom);
            strcat(buffer, " ");
            break;
        }
        default:{
            printf("Please input a correct choice(1~5)\n");
            return 0;
        }
    }

    return 1;
}