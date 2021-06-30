#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 100
#define ElemType int

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

void F(int n, SqStack s) {
	if (n == 0) {
		return;
	}
	Push_SqStack(s, n);
	F(n/2, s);
}

main() {
	int n;
	scanf("%d",&n);

	SqStack s;
	s = Init_SqStack();

	F(n, s);
	int prd = 1;
	while (Len_SqStack(s) != 0) {
		prd = prd * Pop_SqStack(s);
	}
	printf("%d", prd);
}