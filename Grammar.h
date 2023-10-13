#ifndef __GRAMMAR_H
#define __GRAMMAR_H

int Grammar_Check(void);
void Grammar_Test(void);
void Code_Translate(void);
void Code_Translate_Test(void);

enum Act{E_Null,E_Mov,E_Add,E_Print};
struct Exec_Example{int Act; int Dest; int Src;};

extern struct Exec_Example Exec_Code[256];

#endif