#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 80
#define ElemType char
#define STACKSIZE 100
#define INCREASEMENT 20

typedef struct Chunk {
	char c[CHUNKSIZE];
	struct  Chunk* next;
}Chunk;

typedef struct {
	Chunk* head;
	Chunk* tail;
	int curlen;
}*LString, LNode;

typedef struct {
	ElemType* bottom;
	int top;
	int length;
}*SqStack;

SqStack Init_SqStack() {
	SqStack s;
	s = (SqStack)malloc(sizeof(SqStack));
	s->bottom = (ElemType*)malloc(STACKSIZE * sizeof(ElemType));
	s->length = STACKSIZE;
	s->top = 0;
	return s;
}

void Push_SqStack(SqStack s, ElemType data) {
	if (s->top < s->length) {
		s->bottom[s->top++] = data;
	}
	else {
		s->bottom = (ElemType*)realloc(s->bottom, (s->length + INCREASEMENT) * sizeof(ElemType));
		s->length += INCREASEMENT;
		s->bottom[s->top++] = data;
	}
}

ElemType Pop_SqStack(SqStack s) {
	return s->bottom[--s->top];
}

LString Init_LString() {
	LNode* string;
	string = (LNode*)malloc(sizeof(LNode));
	string->curlen = 1;
	string->head = (Chunk*)malloc(sizeof(Chunk));
	string->head->next = NULL;
	string->head->c[0] = '\0';
	string->tail = string->head;
	return string;
}

void Extend_LString(LString s, char c) {
	int i = 0;
	for (; s->tail->c[i] != '\0'; i++) {

	}
	s->tail->c[i] = c;
	if (i == CHUNKSIZE - 1) {
		Chunk* chk;
		chk = (Chunk*)malloc(CHUNKSIZE * sizeof(char));
		chk->next = NULL;
		s->tail->next = chk;
		s->tail = chk;
		s->tail->c[0] = '\0';
		s->curlen++;
	}
	else {
		s->tail->c[i + 1] = '\0';
	}
}

main() {
	SqStack stack;
	LString string;
	stack = Init_SqStack();
	string = Init_LString();

	int length;
	scanf("%d", &length);
	getchar();

	char c;
	while ((c = getchar()) != EOF && c != '\n') {
		Extend_LString(string, c);
	}

	int i, count = 1;
	Chunk* chk;
	for (chk = string->head; count <= length; count++, chk = chk->next) {
		for (i = 0; i < CHUNKSIZE && count <= length; i++, count++) {
			if (count < (length + 1.0) / 2) {
				Push_SqStack(stack, chk->c[i]);
			}
			else if (count > (length + 1.0) / 2) {
				if (chk->c[i] != Pop_SqStack(stack)) {
					printf("0");
					exit(0);
				}
			}
		}
	}
	printf("1");
}


