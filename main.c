#include<stdio.h>
#include"Fopen.h"
#include"Lexcial.h"
#include"Grammar.h"
#include"Executor.h"

int main(){
    
    Fopen();
    Lexical_Test();
    Grammar_Test();
    Code_Translate_Test();
    Executor();
    return 0;

}