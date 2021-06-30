#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 100
#define MAXLINE 100
#define ElemType char

typedef struct {
	int length;
	ElemType* base;
	int top;
}*SqStack;

SqStack Init_SqStack() {
	SqStack s;
	s = (SqStack)malloc(sizeof(SqStack));
	s->base = (ElemType*)malloc(STACKSIZE * sizeof(ElemType));
	s->length = STACKSIZE;
	s->top = 0;
	return s;
}

void Push_SqStack(SqStack s, ElemType data) {
	s->base[s->top++] = data;
}

ElemType Pop_SqStack(SqStack s) {
	return s->base[--s->top];
}

int Len_SqStack(SqStack s) {
	return s->top;
}

int getline(char s[], int lim) {
	int  c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		s[i] = c;
	}

	if (c == '\n') {
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

main() {
	char str[100];
	int len;
	while ((len = getline(str, MAXLINE)) != 0) {
		int i, j, status;
		status = 1;
		for (i = 0, j = len - 3; i < j; i++, j--) {
			if (str[i] == str[j]) {
				continue;
			}
			else {
				status = 0;
				break;
			}
		}
		printf("%d\n", status);
	}
}