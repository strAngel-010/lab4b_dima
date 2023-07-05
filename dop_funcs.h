#ifndef AUX_FUNCS_H
#define AUX_FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum NUMS{
	RES_OK = 0,
	RES_ERR = 1,
	RES_EOF = -1,
	BUFSIZE = 81,
};

int getIntInInterval(int* n, int x, int y);
int getUInt(unsigned int* n);
char* myreadline(FILE* file, const char* msg);

#endif
