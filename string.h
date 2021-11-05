#ifndef STRING_LIST_H
#define STRING_LIST_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "char.h"

typedef struct string {
	char** strings;
	size_t size;
} string_t;

void string_init(string_t* string) {
	string->strings = malloc(1*sizeof(char*));
	string->size = 0;
}

void string_append(string_t* string, char* buff) {
	string->strings[string->size] = calloc(strlen(buff), sizeof(char*));
	strcpy(string->strings[string->size], buff);
	string->size++;
	string->strings = realloc(string->strings, (string->size+1)*sizeof(char*));
}

char* string_tolower(char* string) {
	size_t length = strlen(string);
	char* low = calloc(length, sizeof(char*));
	for(int i=0;i<length;i++) {
		low[i] = tolower(string[i]);
	}
	return low;
}

char* string_toupper(char* string) {
	size_t length = strlen(string);
	char* upper = calloc(length, sizeof(char*));
	for(int i=0;i<length;i++) {
		upper[i] = toupper(string[i]);
	}
	return upper;
}

char* string_capitalize(char* string) {
	size_t length = strlen(string);
	char* cap = calloc(strlen(string), sizeof(char*));
	cap[0] = toupper(string[0]);
	for(int i=1;i<length;i++) {
		cap[i] = string[i];
	}
	return cap;
}

bool string_find(string_t string, char* buff) {
	for(int i=0;i<string.size;i++) {
		if(strcmp(string.strings[i], buff) == 0) {
			return true;
		}
	}
	return false;
}

string_t string_split(char* str, char c) {
	string_t string;
	char_t temp;
	char_init(&temp);
	string_init(&string);
	for(int i=0;i<strlen(str);i++) {
		if(str[i] != c) {
			char_push(&temp, str[i]);
		} else {
			string_append(&string, temp.buff);
			char_free(&temp);
			char_init(&temp);
		}
	}
	return string;
}

void string_free(string_t* string) {
	for(int i=0;i<string->size;i++) {
		free(string->strings[i]);
	}
	free(string->strings);
	string->size = 0;
}
#endif
