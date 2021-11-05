#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#if __has_include(<readline/readline.h>)
#include <readline/readline.h>
#include <readline/history.h>
#endif
#include "char.h"

char* input(char* prompt) {
	char* buff, c;
	size_t size = 0;
	#ifdef _READLINE_H_
		buff = readline(prompt);
	#else
		printf("%s", prompt);
		buff = calloc(1, sizeof(char*));
		while((c = tolower(fgetc(stdin)))) {
			if(c == '\n') {
				break;
			}
			buff[size] = c;
			size++;
			char* temp = buff;
			buff = calloc(size+1, sizeof(char*));
			strcpy(buff, temp);
			free(temp);
		}
	#endif
	return buff;
}

string_t file_readlines(char* filename) {
	string_t string;
	string_init(&string);
	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int i=0;
	size_t size = ftell(f);
	char* buff = calloc(size, sizeof(char*));
	char_t temp;
	char_init(&temp);
	rewind(f);
	fread(buff, size, 1, f);
	while(buff[i] != '\0') {
		if(buff[i] != '\n') {
			char_push(&temp, buff[i]);
		} else {
			string_append(&string, temp.buff);
			char_free(&temp);
			char_init(&temp);
		}
		i++;
	}
	char_free(&temp);
	free(buff);
	fclose(f);
	return string;
}

int count(char* str, char c) {
	int amount = 0;
	for(int i=0;i<strlen(str);i++) {
		(str[i] == c) ? amount++ : 0;
	}
	return amount;
}

bool exist(char* str, char c) {
	for(int i=0;i<strlen(str);i++) {
		if(str[i] == c) return true;
	}
	return false;
}

int main() {
	string_t list = file_readlines("wordlist.txt");
	int i=0, pos = 1, start=0;
	char* word = input("Enter a word: ");
	char_tolower(word);
	while(1) {
		char* str = list.strings[i];
		int found = 1;
		for(int x=0;x<strlen(str);x++) {
			if(!exist(word, str[x])) {
				found = 0;
				break;
			}

			if(count(word, str[x]) < count(str, str[x])) {
				found = 0;
				break;
			}
		}
		if(found) {
			if(strcmp(str, word) != 0) {
				if(start == 0) {
					start = 1;
					printf("Words found in %s are:\n", word);
				}
				printf("%d.%s\n", pos, str);
				pos++;
			}
		}
		if(list.size-1 == i) {
			break;
		}
		i++;
	}
	if(!start) {
		printf("No Words found for %s\n", word);
	}
	free(word);
	string_free(&list);
	return 0;
}
