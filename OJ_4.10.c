#include <stdio.h>
#include <stdlib.h>
#define Status int
#define OVERFLOW 1
#define OK 1
#define ERROR 0

typedef struct {
	char* ch;
	int length;
}HString;

Status StrConcat(HString* T, HString S1, HString S2) {
	if (T->ch) {
		free(T->ch);
	}
	if (!(T->ch = (char*)malloc((S1.length + S2.length) * sizeof(char)))) {
		exit(OVERFLOW);
	}
	int i;
	for (i = 0; i < S1.length; i++) {
		T->ch[i] = S1.ch[i];
	}
	for (i = 0; i < S2.length; i++) {
		T->ch[i + S1.length] = S2.ch[i];
	}
	T->length = S1.length + S2.length;
	return OK;
}

Status SubString(HString* Sub, HString S, int pos, int len) {
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1) {
		return ERROR;
	}
	
	if (!len) {
		Sub->ch = NULL;
		Sub->length = 0;
	}
	else {
		if (!(Sub->ch = (char*)malloc(len * sizeof(char)))) {
			exit(ERROR);
		}
		int i;
		for (i = 0; i < len; i++) {
			Sub->ch[i] = S.ch[pos - 1 + i];
		}
		Sub->length = len;
	}
	return OK;
}

Status Init_HString(HString* S) {
	S->ch = NULL;
	S->length = 0;
	return OK;
}

main() {
	HString* S;
	HString R;
	HString T;
	if (!(S = (HString*)malloc(sizeof(HString)))) {
		exit(ERROR);
	}
	Init_HString(S);
	T.ch = (char*)malloc(sizeof(char));

	char c;
	int i, j;
	while ((c = getchar()) != EOF && c != '\n') {
		T.ch[0] = c;
		T.length = 1;

		if(!(R.ch = (char*)malloc(S->length * sizeof(char)))) {
			exit(ERROR);
		}
		for (i = 0; i < S->length; i++) {
			R.ch[i] = S->ch[i];
		}
		R.length = S->length;
		StrConcat(S, R, T);
	}

	HString* revS, * Sub;
	if (!(Sub = (HString*)malloc(sizeof(HString)))) {
		exit(ERROR);
	}
	if (!(revS = (HString*)malloc(sizeof(HString)))) {
		exit(ERROR);
	}
	Init_HString(revS);
	for (i = 0; i < S->length; i++) {
		if (!(R.ch = (char*)malloc(S->length * sizeof(char)))) {
			exit(ERROR);
		}
		for (j = 0; j < S->length; j++) {
			R.ch[j] = S->ch[j];
		}
		R.length = S->length;
		SubString(Sub, R, S->length - i, 1);
		
		if (!(R.ch = (char*)malloc(revS->length * sizeof(char)))) {
			exit(ERROR);
		}
		for (i = 0; i < revS->length; i++) {
			R.ch[i] = revS->ch[i];
		}
		R.length = revS->length;
		StrConcat(revS, R, *Sub);
	}

	for (i = 0; i < revS->length; i++) {
		printf("%c", revS->ch[i]);
	}
}