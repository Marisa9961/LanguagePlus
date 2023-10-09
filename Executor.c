#include<stdio.h>
#include"Token.h"
#include"Grammar.h"

extern struct Token token[256];
extern struct Exec_Example Exec_Code[256];

void Executor(void){
    int i_code = 0;
    do{
        switch (Exec_Code[i_code].Act){
            case E_Mov:{
                token[Exec_Code[i_code].Dest].val = token[Exec_Code[i_code].Src].val;
                i_code ++;
                continue;
            }
            case E_Add:{
                token[Exec_Code[i_code].Dest].val += token[Exec_Code[i_code].Src].val;
                i_code ++;
                continue;
            }
            case E_Print:{
                printf("%d\n", token[Exec_Code[i_code].Src].val);
                i_code ++;
                continue;
            }
        }
    }while(Exec_Code[i_code].Act != E_Null);
}