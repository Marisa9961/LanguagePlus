#include<stdio.h>
#include"Token.h"
#include"Grammar.h"

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