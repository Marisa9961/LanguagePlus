#ifndef __TOKEN_H
#define __TOKEN_H

struct Token{int type; int val; char id[64]; char sym;};
enum Type {Null,Val,Id,Add,Equal,Echo};

extern int line[64];
extern char temp[256];
extern char buffer[512];
extern struct Token token[256];

#endif