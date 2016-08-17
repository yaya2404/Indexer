#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct T{
	char *w;
};

char* TKGetNextToken(struct T *p);	

#endif
