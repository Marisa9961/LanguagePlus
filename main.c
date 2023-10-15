#include<stdio.h>
#include"OpenFile.h"
#include"Lexcial_New.h"
#include"Grammar.h"
#include"Executor.h"

int main(){
    
    Open_File();
    Lexical_Test();
    Grammar_Test();
    Code_Translate_Test();
    Executor();
    return 0;

}