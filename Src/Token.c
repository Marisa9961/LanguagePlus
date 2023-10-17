#include<stdio.h>

struct Token{int type; int val; char id[64]; char sym;};
struct Token token[256];

int line[64];
char temp[256];
char buffer[512];
