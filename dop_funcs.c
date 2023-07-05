#include "dop_funcs.h"

int getIntInInterval(int* n, int x, int y){
	int is_correct = 0;
    while (!is_correct){
        int res = scanf("%d", n);
        switch (res) {
            case -1:
                printf("\nExiting...\n");
                return RES_EOF;
            case 0:
                printf("Wrong input format\n");
                scanf("%*[^\n]");
                break;
            case 1:
                if (*n >= x && *n <= y){ return RES_OK; }
                printf("Wrong input format. Number must be between %d and %d.\n", x, y);
                break;
            default:
                return RES_ERR;
        }
    }
}

int getUInt(unsigned int* n){
    int is_correct = 0;
    while (!is_correct){
        int res = scanf("%u", n);
        switch (res) {
            case -1:
                printf("\nExiting...\n");
                return RES_EOF;
            case 0:
                printf("Wrong input format\n");
                scanf("%*[^\n]");
                break;
            case 1:
                is_correct = 1;
                return RES_OK;
            default:
                return RES_ERR;
        }
    }
}

char* myreadline(FILE* file, const char* msg){
	if (msg) { printf("%s", msg); }
	char* str = (char*)malloc(sizeof(char));
	str[0] = '\0';
	char* buf = (char*)malloc(BUFSIZE*sizeof(char));
	for (int i = 0; i < BUFSIZE; i++){
		buf[i] = '\0';
	}
	int n = 0;
	int len = 0;
	do {
		if (file){ n = fscanf(file, "%80[^\n]", buf); }
        else { n = scanf("%80[^\n]", buf); }
		if (n < 0){
			free(str);
			str = NULL;
		} else if (n == 0){
            if (file){ fscanf(file, "%*c"); }
            else { scanf("%*c"); }
		} else {
			len += strlen(buf);
			str = (char*)realloc(str, len+1);
			strcat(str, buf);
		}
	} while (n>0);
	free(buf);
	return str;
}
