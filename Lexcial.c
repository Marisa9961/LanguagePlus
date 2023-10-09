#include<stdio.h>
#include<string.h>
#include"Token.h"

extern struct Token token[256];

enum DFA_Lexcial{
    Start,//开始
    Num,//数字
    Char,//字母下划线
    Space,//空格回车
    Symbol,//符号
    Next,//进入下一位
    Unknown,//非法
    End//文件读取结束
};

void Token_Next(int *i_token){
    //token指向下一个存储单元
    *(i_token) += 1;
}

void Temp_Clear(int *i_temp){
    //数字 字母 符号 确认合法存入后，缓存区temp清零
    memset(temp, 0, sizeof temp);
    //temp指向首单元，存入新的token缓存
    *i_temp = -1;
}

int isNum(char temp){
    if(temp >= '0' && temp <= '9')
       return 1;
    else return 0;
}

int isChar(char temp){
    if((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z') || (temp == '_'))
       return 1;
    else return 0;
}

int Num_Check(int i_temp){
    for(int i = 0;i<i_temp;i++){
        if(isNum(temp[i]));
        else return 0;
    }
    return 1;
}

int Char_Check(int i_temp){
    if(isChar(temp[0]));//首位要单独拿出来验证
    else return 0;
    for(int i = 1;temp[i] != '\0';i++){
        if(isChar(temp[i]) || isNum(temp[i]));
        else return 0;
    }
    return 1;
}

int Space_Check(int *i_temp){
    if(temp[0] == ' ' || temp[0] == '\n'){
        Temp_Clear(i_temp);
        return 1;
    }
    else{
        temp[*i_temp] = '\0';//正常字符串末尾会遗留空格 手动清除
        return 0;
    }
}

int Char_to_Num(int i_temp){
    int sum = 0;
    int factor = 1;
    for(int i = i_temp - 1; i >= 0; i--){
            sum +=(temp[i] - '0') * factor;
            factor *= 10;
    }
    return sum;
}

int Token_Check(int i_temp,int i_token){
    if(Num_Check(i_temp)){
        token[i_token].type = Val;
        token[i_token].val = Char_to_Num(i_temp);
    }
    else if(Char_Check(i_temp)){
        token[i_token].type = Id;
        strcpy(token[i_token].id, temp);
        if(!strcmp(token[i_token].id, "echo"))
            token[i_token].type = Echo;
    }
    else if(temp[0] == '+' && temp[1] == '\0'){
        token[i_token].type = Add;
        token[i_token].sym = '+';
    }
    else if(temp[0] == '=' && temp[1] == '\0'){
        token[i_token].type = Equal;
        token[i_token].sym = '=';
    }
    else return 0;

    return 1;
}

int Lexcial_Check(void){
    int DFA_State = Start;
    int i_temp = 0;//用于temp的遍历
    int i_buff = 0;//用于buffer的遍历
    int i_token = 0;//用于token的遍历
    temp[0] = buffer[0];//初始化
    do{
        switch(DFA_State){
                case Start:{
                    if(isNum(temp[i_temp])){
                        DFA_State = Num;
                    }
                    else if(isChar(temp[i_temp])){
                        DFA_State = Char;
                    }
                    else if(temp[i_temp] == ' ' || temp[i_temp] == '\n'){
                        DFA_State = Space;
                    }
                    else if(temp[i_temp] == '+' ||temp[i_temp] == '='){
                        DFA_State = Symbol;
                    }
                    else if(temp[i_temp] == '\0'){
                        DFA_State = End;
                    }
                    else{
                        DFA_State = Unknown;
                    }
                    continue;
                }
                case Next:{
                    i_buff++;
                    i_temp++;
                    temp[i_temp] = buffer[i_buff];
                    DFA_State = Start;
                    continue;
                }
                case Num:
                case Char:
                case Symbol:{
                    DFA_State = Next;
                    continue;
                }
                case Space:{
                    if(Space_Check(&i_temp));
                    else if(Token_Check(i_temp, i_token)){
                        Token_Next(&i_token);
                        Temp_Clear(&i_temp);
                    }
                    else{
                        //出现了错误的混合表达
                        printf("ERROR: Wrong mixed expression '%s'\n",temp);
                        return 1;
                    } 
                    DFA_State = Next;
                    continue;
                }
                case Unknown:{
                    printf("Error: Unrecognized identifier `%s`\n",temp);
                    return 1;
                }
            }
    }while(DFA_State != End);

    if(token[0].type == Null){
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