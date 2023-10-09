#ifndef __TOKEN_H
#define __TOKEN_H

extern int line[64];
extern char temp[256];
extern char buffer[512];

struct Token{int type; int val; char id[64]; char sym;};
enum Type {Null,Val,Id,Add,Equal,Echo};

#endif