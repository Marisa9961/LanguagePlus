#include<stdio.h>
#include<string.h>
#include"Token.h"

enum DFA_Lexcial{
    Start,//开始
    Num,//数字
    Num_End,
    Char,//字母下划线
    Char_End,
    Space,//空格回车
    Symbol,//符号
    Token_End,
    Unknown,//非法
    Mixed_Wrong,//混合输入
    File_End//文件读取结束
}DFA_Lexcial_State;

inline static void Token_Next(int *const i_token){
    //token指向下一个存储单元
    *i_token += 1;
}

inline static void Temp_Clear(int *const i_temp){
    //数字 字母 符号 确认合法存入后，缓存区temp清零
    memset(temp, 0, sizeof temp);
    //temp指向首单元，存入新的token缓存
    *i_temp = -1;
}

inline static void Buff_Next(int *const i_buff,int *const i_temp){
    *i_buff += 1;
    *i_temp += 1;
    temp[*i_temp] = buffer[*i_buff];
}

inline static int isNum(char temp){
    if(temp >= '0' && temp <= '9')
       return 1;
    else return 0;
}

inline static int isChar(char temp){
    if((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z') || (temp == '_'))
       return 1;
    else return 0;
}

inline static int isSpace(char temp){
    if(temp == ' ' || temp == '\n')
       return 1;
    else return 0;
}

static int Char_to_Num(int i_temp){
    int sum = 0;
    int factor = 1;
    for(int i = i_temp - 1; i >= 0; i--){
            sum +=(temp[i] - '0') * factor;
            factor *= 10;
    }
    return sum;
}

int Lexcial_Check(void){
    DFA_Lexcial_State = Start;
    int i_temp = 0;//用于temp的遍历
    int i_buff = 0;//用于buffer的遍历
    int i_token = 0;//用于token的遍历

    temp[0] = buffer[0];//初始化

    do{
        switch(DFA_Lexcial_State){
                case Start:{
                    if(isNum(temp[i_temp])){
                        DFA_Lexcial_State = Num;
                    }
                    else if(isChar(temp[i_temp])){
                        DFA_Lexcial_State = Char;
                    }
                    else if(isSpace(temp[i_temp])){
                        DFA_Lexcial_State = Space;
                    }
                    else if(temp[i_temp] == '+' ||temp[i_temp] == '='){
                        DFA_Lexcial_State = Symbol;
                    }
                    else if(temp[i_temp] == '\0'){
                        DFA_Lexcial_State = File_End;
                    }
                    else{
                        DFA_Lexcial_State = Unknown;
                    }
                    continue;
                }
                case Num:{
                    if(isNum(temp[i_temp]));
                    else if(isSpace(temp[i_temp])){
                        DFA_Lexcial_State = Num_End;
                        continue;
                    }
                    else{
                        DFA_Lexcial_State = Mixed_Wrong;
                        continue;
                    }
                    Buff_Next(&i_buff, &i_temp);
                    continue;
                }
                case Num_End:{
                    token[i_token].type = Val;
                    token[i_token].val = Char_to_Num(i_temp);
                    DFA_Lexcial_State = Token_End;
                    continue;
                }
                case Char:{
                    if(isNum(temp[i_temp]) || isChar(temp[i_temp]));
                    else if(isSpace(temp[i_temp])){
                        DFA_Lexcial_State = Char_End;
                        continue;
                    }
                    else{
                        DFA_Lexcial_State = Mixed_Wrong;
                        continue;
                    }
                    Buff_Next(&i_buff, &i_temp);
                    continue;
                }
                case Char_End:{
                    temp[i_temp] = '\0';
                    token[i_token].type = Id;
                    strcpy(token[i_token].id, temp);
                    if(!strcmp(token[i_token].id, "echo"))
                        token[i_token].type = Echo;//echo情况判断
                    DFA_Lexcial_State = Token_End;
                    continue;
                }
                case Symbol:{
                    if(temp[0] == '+'){
                        token[i_token].type = Add;
                        token[i_token].sym = '+';
                    }
                    else if(temp[0] == '='){
                        token[i_token].type = Equal;
                        token[i_token].sym = '=';
                    }
                    DFA_Lexcial_State = Token_End;
                    continue;
                }
                case Space:{
                    Temp_Clear(&i_temp);
                    Buff_Next(&i_buff, &i_temp);
                    DFA_Lexcial_State = Start;
                    continue;
                }
                case Token_End:{
                    Token_Next(&i_token);
                    Temp_Clear(&i_temp);
                    Buff_Next(&i_buff, &i_temp);
                    DFA_Lexcial_State = Start;
                    continue;
                }
                case Mixed_Wrong:{
                    printf("ERROR: Wrong mixed expression '%s'\n",temp);
                    return 1;
                }
                case Unknown:{
                    printf("Error: Unrecognized identifier `%s`\n",temp);
                    return 1;
                }
            }
    }while(DFA_Lexcial_State != File_End);

    if(token[0].type == Null){//错误:没有任何有效token
        printf("Error: No any token was detected\n");
        return 1;
    } 

    return 0;
}

void Lexical_Test(void){
    if(Lexcial_Check()){
        printf("Lexical mission Failed\n");
    }
    else{
        printf("Lexical mission Completed\n");
        for(int i = 0; token[i].type != Null; i++){
            if(token[i].type == Val)
                printf("NO.%d\tVal: %d\n",i,token[i].val);
            else if(token[i].type == Id)
                printf("NO.%d\tId:  %s\n",i,token[i].id);
            else if(token[i].type == Add)
                printf("NO.%d\tSym: %c\n",i,token[i].sym);
            else if(token[i].type == Equal)
                printf("NO.%d\tSym: %c\n",i,token[i].sym);
            else if(token[i].type == Echo)
                printf("NO.%d\tEcho\n",i);
        }
    }
}