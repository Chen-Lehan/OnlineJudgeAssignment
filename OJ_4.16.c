#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define OK 1
#define MAXLENGTH 100

typedef struct {
	char* ch;
	int length;
}HString;

HString* SubString(HString* S, int pos, int len) {
	HString* Sub;
	if (pos < 0 || pos + len > S->length || len < 0)
		return ERROR;
	if(!(Sub = (HString*)malloc(sizeof(HString))))
		exit(ERROR);
	if (len == 0) {
		Sub->ch = NULL;
		Sub->length = 0;
		return Sub;
	}
	else {
		if(!(Sub->ch = (char*)malloc(len * sizeof(char))))
			exit(ERROR);
		int i;
		for (i = 0; i < len; i++) {
			Sub->ch[i] = S->ch[pos + i];
		}
		Sub->length = len;
		return Sub;
	}
}//pos的值从0开始

int StrCompare(HString* S1, HString* S2) {
	if (S1->ch == NULL && S2->ch == NULL) {
		return 0;
	}
	else if (S1->ch == NULL) {
		return -1;
	}
	else if (S2->ch == NULL){
		return 1;
	}
	else {
		if (S1->ch[0] == S2->ch[0]) {
			return StrCompare(SubString(S1, 1, S1->length - 1), SubString(S2, 1, S2->length - 1));
		}
		else if (S1->ch[0] > S2->ch[0]) {
			return 1;
		}
		else if (S1->ch[0] < S2->ch[0]) {
			return -1;
		}
	}
}

int StrAssign(HString* S, char s[]) {
	int i, length;
	for (length = 0; s[length] != '\0'; length++);
	if (S->ch) {
		free(S->ch);
	}
	if (!(S->ch = (char*)malloc(length * sizeof(char)))) {
		exit(ERROR);
	}
	for (i = 0; i < length; i++) {
		S->ch[i] = s[i];
	}
	S->length = length;
	return OK;
}

int getline(char s[], int lim) {
	int  c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != ' ' && c != '\n'; i++) {
		s[i] = c;
	}

	s[i] = '\0';
	return i;
}


main() {
	HString* S1, * S2;
	if (!(S1 = (HString*)malloc(sizeof(HString))) ||
		!(S2 = (HString*)malloc(sizeof(HString)))) {
		exit(ERROR);
	}
	S1->ch = NULL;
	S1->length = 0;
	S2->ch = NULL;
	S2->length = 0;
	char str[MAXLENGTH];
	getline(str, MAXLENGTH);
	StrAssign(S1, str);
	getline(str, MAXLENGTH);
	StrAssign(S2, str);
	printf("%d", StrCompare(S1, S2));
}