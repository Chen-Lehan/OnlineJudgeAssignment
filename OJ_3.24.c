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

void g(int m, int n, SqStack s) {
	if (m == 0) {
		return;
	}
	Push_SqStack(s, n);
	g(m - 1, 2 * n, s);
}

main() {
	int m, n;
	char c;
	scanf("%d%c%d", &m, &c, &n);

	SqStack s;
	s = Init_SqStack();

	g(m, n, s);
	int sum = 0;
	while (Len_SqStack(s) != 0) {
		sum = sum + Pop_SqStack(s);
	}
	printf("%d", sum);
}