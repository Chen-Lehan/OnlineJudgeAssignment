#include<stdio.h>
#include<stdlib.h>
#define STACKSIZE 100
#define ElemType char

typedef struct {
	int stacksize;
	ElemType* bottom;
	int top;
}SqStack;

SqStack* Init_SqStack() {
	SqStack* s;
	s = (SqStack*)malloc(sizeof(SqStack));
	s->bottom = (ElemType*)malloc(STACKSIZE * sizeof(ElemType));
	s->top = 0;
	s->stacksize = STACKSIZE;
	return s;
}

void Push_SqStack(SqStack* s, ElemType data) {
	s->bottom[s->top++] = data;
}

ElemType Pop_SqStack(SqStack* s) {
	return s->bottom[--s->top];
}

int Len_SqStack(SqStack* s) {
	return s->top;
}

main() {
	char c, d;
	SqStack* s;
	s = Init_SqStack();
	while ((c = getchar()) != '&') {
		Push_SqStack(s, c);
		if (c == EOF || c == '\n') {
			printf("0");
			exit(0);
		}
	}
	while (Len_SqStack(s) != 0) {
		c = getchar();
		d = Pop_SqStack(s);
		if (d != c) {
			printf("0");
			exit(0);
		}
	}
	c = getchar();
	d = getchar();
	if (c == '@' && (d == '\n' || d == EOF)) {
		printf("1");
	}
	else {
		printf("0");
	}
}