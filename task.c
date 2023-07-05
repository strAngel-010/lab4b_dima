#define BUFSIZE 81
#define SEP " "

#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "mystring.h"

int edit_word(char* word, char** newword);
int is_empty(char* str);

int edit_line(char** str){
	if (is_empty(*str)){
		free(*str);
		*str = NULL;
		return 0;
	}

	char* newstr = NULL;

	char* origstr = *str;
	while (**str == ' '){
		(*str)++;
	}
	
	char* word = mystrtok(*str, SEP);
	char* newword = NULL;
	int func_res = 0;
	while (word){
		func_res = edit_word(word, &newword);
		if (func_res){
			printf("Error in edit_line\n");
			return 1;
		}
		
		int newwordlen = mystrlen(newword);
		if (newstr){
			int newstrlen = mystrlen(newstr);
			newstr = (char*)realloc(newstr, (newstrlen + newwordlen + 2)*sizeof(char));
			mystrcat(newstr, SEP);
		} else {
			newstr = (char*)malloc((newwordlen + 1)*sizeof(char));
			newstr[0] = '\0';
		}
		mystrcat(newstr, newword);		
					
		free(newword);
		newword = NULL;

		word = mystrtok(NULL, SEP);
	}

	free(origstr);
	(*str) = newstr;
	return 0;
}

int is_empty(char* str){
	while (*str != '\0'){
		if (*str != ' '){
			return 0;
		}
		str++;
	}
	return 1;
}

int edit_word(char* word, char** newword){
	*newword = NULL;
	int newwordlen = 0;
	int wordlen = (int)mystrlen(word);
	for (int i = 0; i < wordlen-1; ++i){
		if (word[i] != word[wordlen-1]){
			newwordlen++;
			*newword = (char*)realloc(*newword, newwordlen*sizeof(char));
			if (!(*newword)){
				printf("Error in edit_word\n");
				return 1;
			}

			(*newword)[newwordlen-1] = word[i];
		}
	}

	newwordlen += 2;
	*newword = (char*)realloc(*newword, newwordlen*sizeof(char));
	if (!(*newword)){
		printf("Error in edit_word\n");
		return 1;
	}

	(*newword)[newwordlen-2] = word[wordlen-1];
	(*newword)[newwordlen-1] = 0;
	return 0;
}

char* myreadline(const char* msg){
	printf("%s", msg);
	char* str = (char*)malloc(sizeof(char));
	str[0] = '\0';
	char* buf = (char*)malloc(BUFSIZE*sizeof(char));
	for (int i = 0; i < BUFSIZE; i++){
		buf[i] = '\0';
	}
	int n = 0;
	int len = 0;
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0){
			free(str);
			str = NULL;
		} else if (n == 0){
			scanf("%*c");
		} else {
			len += mystrlen(buf);
			str = (char*)realloc(str, len+1);
			mystrcat(str, buf);
		}
	} while (n>0);
	free(buf);
	return str;
}
