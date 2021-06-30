#include <stdio.h>
#include <stdlib.h>
#define Status int
#define OVERFLOW 1
#define OK 1
#define ERROR 0
#define MAXLENGTH 100

typedef struct {
	char* ch;
	int length;
}HString;

typedef struct {
	int* base;
	int length;
}array;

HString* StrConcat(HString S1, HString S2) {
	HString* T;
	if (!(T = (HString*)malloc(sizeof(HString)))) {
		exit(ERROR);
	}
	if (!(T->ch = (char*)malloc((S1.length + S2.length) * sizeof(char)))) {
		exit(ERROR);
	}
	int i;
	for (i = 0; i < S1.length; i++) {
		T->ch[i] = S1.ch[i];
	}
	for (i = 0; i < S2.length; i++) {
		T->ch[S1.length + i] = S2.ch[i];
	}
	T->length = S1.length + S2.length;
	return T;
}

Status StrAssign(HString* S, char s[]) {
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
}

array StrDelete(HString* R, HString* S, HString* T) {
	int i, j, k, same;
	array arr;
	if (!(arr.base = (int*)malloc(MAXLENGTH * sizeof(int)))) {
		exit(ERROR);
	}
	arr.length = 0;

	for (i = 0, same = 0; i < S->length; i++, same = 0) {
		for (j = 0; j < R->length; j++) {
			if (S->ch[i] == R->ch[j]) {
				same = 1;
				break;
			}
		}
		if (same == 1) {
			continue;
		}
		else {
			for (k = 0; k < T->length; k++) {
				if (S->ch[i] == T->ch[k]) {
					same = 1;
					break;
				}
			}
			if (same == 1) {
				continue;
			}
			else {
				if (!(R->ch = (char*)realloc(R->ch, (R->length + 1) * sizeof(char)))) {
					exit(ERROR);
				}
				R->ch[R->length++] = S->ch[i];
				arr.base[arr.length++] = i;
			}
		}
	}
	return arr;
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
	HString* S, * T, *R;
	char str[MAXLENGTH];
	if (!(S = (HString*)malloc(sizeof(HString))) ||
		!(T = (HString*)malloc(sizeof(HString))) ||
		!(R = (HString*)malloc(sizeof(HString)))) {
		exit(ERROR);
	}
	S->ch = NULL;
	S->length = 0;
	T->ch = NULL;
	T->length = 0;
	R->ch = NULL;
	R->length = 0;

	getline(str, MAXLENGTH);
	StrAssign(S, str);
	getline(str, MAXLENGTH);
	StrAssign(T, str);
	
	array arr;
	arr = StrDelete(R, S, T);

	if (arr.length == 0) {
		printf("-1");
	}
	else {
		int i;
		for (i = 0; i < arr.length; i++) {
			printf("%c", R->ch[i]);
		}
		printf(" ");
		for (i = 0; i < arr.length; i++) {
			printf("%d", arr.base[i]);
		}
	}
}