#include<stdio.h>
#include<string.h>
#include"token.h"

struct Exec_Example{//指令样例
    int Act;
    int Dest;
    int Src;
}Exec_Code[256];

struct Id_Defined{//已定义过的变量id
    char id[64];
    int i_token;
}Id_Def[256];

enum DFA_Grammar{//语法检定的状态
    Start,//开始
    Assign,//赋值语句
    Output,//输出语句
    End,//结束
};

enum Act{//执行器的命令类型
    E_Null,//无内容
    E_Mov,//赋值
    E_Add,//相加
    E_Print//输出
};

static int Line_Separate(void){
    int i_token = 0;//用于token数组的定位
    int i_line = 0;//用于line数组的遍历
    while(token[i_token].type != '\0'){
        if(token[i_token].type == Equal || token[i_token].type == Echo){
            line[i_line] = i_token;
            i_line ++;
        }
        i_token ++;
    }

    if(i_line == 0){
        //若未找到任何有效命令 直接退出
        return 1;
    }
    else
        line[i_line] = i_token + 1;//line数组的最后一位手动添加一个行 否则最后一行就没有下一行了

    return 0;
}

static int Add_Check(int i_line){
    int i_token = line[i_line] + 1;//i_token是这一行的起点
    int i_line_next = i_line + 1;//i_line_next是下一行的起点

    if(token[i_token].type == Val || token[i_token].type == Id){
        //对第一位单独检定 后续只要保持 ‘+’‘变量或值’ 的格式即可
        i_token ++;
    }
    else return 1;//出错即报错

    while(i_token < line[i_line_next] - 1){
        if(token[i_token].type == Add && (token[i_token + 1].type == Val || token[i_token + 1].type == Id)){
            //正常运行 检查下一组
        }
        else return 1;   //出错即报错

        i_token += 2;
    }

    return 0;
}

int Grammar_Check(void){
    int DFA_State = Start;
    int i_token = 0;//用于token数组的遍历
    int i_line = 0;//token[line[i_line]]即为token的分行处

    if(Line_Separate()){//进行粗略分行 填充line数组
        printf("No effective command founded\n");//若没有发现任何有效命令 则直接报错
        return 1;
    }

    do{
        switch (DFA_State){
            case Start:{
                if(token[line[i_line]].type == Equal)
                    DFA_State = Assign;
                else if(token[line[i_line]].type == Echo)
                    DFA_State = Output;
                else
                    DFA_State = End;
                continue;
            }
            case Assign:{
                if(line[i_line] == 0){
                    //防止第一句就缺失等号左侧 造成数组越界
                    printf("Missing an identifier after assign operator `%c`\n",token[line[i_line]].sym);
                    return 1;
                }
                else if(token[1].type != Equal){
                    //防止第一句等号左侧乱打一堆无效符号 导致忽略检测
                    printf("Wrong express before assign operator in line '%d'\n", i_line + 1);
                    return 1;
                }
                else if(token[line[i_line] - 1].type != Id){
                    //等号左侧不是一个Id
                    printf("Wrong identifier before assign operator in line '%d'\n", i_line + 1);
                    return 1;
                }
                else if(Add_Check(i_line)){
                    //等号右侧表达式排列有误
                    printf("Wrong express after assign operator in line '%d'\n", i_line + 1);
                    return 1;
                }
                i_line ++;
                DFA_State = Start;
                continue;
            }
            case Output:{
                if(Add_Check(i_line)){
                    //echo右侧表达式排列有误
                    printf("Wrong express after echo operator in line '%d'\n", i_line + 1);
                    return 1;
                }
                i_line ++;
                DFA_State = Start;
                continue;
            }
        }
    }while(DFA_State != End);

    return 0;
}

void Grammar_Test(void){
    if(Grammar_Check()){
        printf("Grammar mission failed!\n");
    }
    else printf("Grammar mission completed!\n");
}

static int Id_Def_Check(int *i_token){
    if(token[*i_token].type == Id && token[*i_token].sym != 't'){
        //此时express中的id是已声明过的 需要定义到同一个地址
        for(int i = 0; strcmp(Id_Def[i].id,"\0"); i++){
            if(!strcmp(token[*i_token].id, Id_Def[i].id)){
                //变量匹配成功 将其地址指向第一次声明的地址
                //也就是所有这样的变量都将指向同一个的地址
                *i_token = Id_Def[i].i_token;
                return 1;
            }
        }
    }
    else if (token[*i_token].type == Val);//只是数字就忽视
    else return 0;
}

static int Executor_Add(int i_token, int *i_exec){
    int i_right = i_token;
    int i_left = i_token - 2;
    
    if(Id_Def_Check(&i_right));
    else return 0; //出现未声明的变量
    if (Id_Def_Check(&i_left));
    else return 0; //出现未声明的变量

    Exec_Code[*i_exec].Act = E_Add;
    Exec_Code[*i_exec].Src = i_right;
    Exec_Code[*i_exec].Dest = i_left;
    *i_exec += 1;

    return 1;
}

static int Executor_Express(int i_line, int *i_exec){

    int i_first;
    int i_last;

    if(token[line[i_line + 1]].type == Equal || token[line[i_line + 1]].type == Null){
        i_first = line[i_line] + 1;//i_token行的起点
        i_last = line[i_line + 1] - 2;//i_token行的终点
    }
    else if(token[line[i_line + 1]].type == Echo){
        i_first = line[i_line] + 1;
        i_last = line[i_line + 1] - 1;//下一行是echo 而echo左侧并没有值
    }
    
    if(i_first == i_last){//对应于expres中仅有一个词的状态
        if(Id_Def_Check(&i_first));
        else return 1;
    }
    else{
        while(i_first < i_last){//对应于express中是一个表达式的状态
            if(Executor_Add(i_last, i_exec))
                i_last -= 2;
            else return 1;//出现未声明变量 报错
        }
    }

    return 0;
}

static void Executor_Assign(int i_line, int *i_exec, int *id_def){
    int i_first = line[i_line] - 1;//i_token行等号的左侧
    int i_last = line[i_line] + 1;//i_token行等号的右侧

    if(token[i_first].sym == '\0'){
        //等号左侧一定是个Id 借用Id的sym位作为是否声明过的变量
        token[i_first].sym = 't';//true
        strcpy(Id_Def[*id_def].id, token[i_first].id);//将id内容记录下来
        Id_Def[*id_def].i_token = i_first;//将token的绝对位置记录下来
        *id_def += 1;
    }

    Id_Def_Check(&i_last);

    Exec_Code[*i_exec].Act = E_Mov;
    Exec_Code[*i_exec].Src = i_last;
    Exec_Code[*i_exec].Dest = i_first;
    *i_exec += 1;
}

static void Executor_Output(int i_line, int *i_exec){
    int i_last = line[i_line] + 1;

    Id_Def_Check(&i_last);

    Exec_Code[*i_exec].Act = E_Print;
    Exec_Code[*i_exec].Src = i_last;//echo右侧的内容
    *i_exec += 1;
}

int Code_Translate(void){
    int DFA_State = Start;
    int i_line = 0;//token[line[i_line]]即为token的分行处
    int i_exec = 0;//用于Exec_Code数组的遍历
    int i_def = 0;//用于已声明变量数组的遍历

    if(token[0].type == Id){//开始前先将第一个id赋为已声明 初始化
        token[0].sym = 't';
        strcpy(Id_Def[i_def].id, token[0].id);//将id内容记录下来
        Id_Def[i_def].i_token = 0;//将token的绝对位置记录下来
        i_def += 1;
    }

    do{
        switch (DFA_State){
            case Start:{
                if(token[line[i_line]].type == Equal)
                    DFA_State = Assign;
                else if(token[line[i_line]].type == Echo)
                    DFA_State = Output;
                else
                    DFA_State = End;
                continue;
            }
            case Assign:{
                if(Executor_Express(i_line, &i_exec)){
                    //出现未声明过的变量
                    printf("An identifier was never declared in line %d\n",i_line + 1);
                    return 1;
                }
                Executor_Assign(i_line, &i_exec, &i_def);
                i_line ++;
                DFA_State = Start;
                continue;
            }
            case Output:{
                if(Executor_Express(i_line, &i_exec)){
                    //同上
                    printf("An identifier was never declared in line %d\n",i_line);
                    return 1;
                }
                Executor_Output(i_line, &i_exec);
                i_line ++;
                DFA_State = Start;
                continue;
            }
        }
    }while(DFA_State != End);

    return 0;
}

void Code_Translate_Test(void){

    if(Code_Translate()){
        printf("Code Translate Mission Failed!\n");
    }
    else{
        printf("Code Translate Mission Completed!\n");
        for(int i = 0;Exec_Code[i].Act != '\0';i++){
            if(Exec_Code[i].Act == E_Add)
                printf("NO.%d\tAdd:   %d,%d\n",i,Exec_Code[i].Dest,Exec_Code[i].Src);
            else if(Exec_Code[i].Act == E_Mov)
                printf("NO.%d\tMov:   %d,%d\n",i,Exec_Code[i].Dest,Exec_Code[i].Src);
            else if(Exec_Code[i].Act == E_Print)
                printf("NO.%d\tPrint: %d\n",i,Exec_Code[i].Src);
        }
    }
}