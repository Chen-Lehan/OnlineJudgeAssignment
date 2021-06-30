#include <stdio.h>
#include <stdlib.h>
#define AtomType char
#define ElemType char
#define ERROR -1
#define STACKSIZE 100
#define INCREASEMENT 10

typedef enum { ATOM, LIST } ElemTag;
typedef struct GLNode {
	ElemTag Tag;
	union
	{
		AtomType atom;
		struct GLNode* hp;
	};
	struct GLNode* tp;
}*GLList, GLNode;

typedef struct {
	int length;
	ElemType* base;
	int top;
}SqStack;

SqStack* Init_SqStack() {
	SqStack* s;
	if (!(s = (SqStack*)malloc(sizeof(SqStack))) ||
		!(s->base = (ElemType*)malloc(STACKSIZE * sizeof(ElemType))))
		exit(ERROR);
	s->length = STACKSIZE;
	s->top = 0;
	return s;
}

void Push_SqStack(SqStack* s, ElemType data) {
	if (s->top < s->length)
		s->base[s->top++] = data;
	else {
		if (!(s->base = (ElemType*)realloc(s->base, (s->length + INCREASEMENT) * sizeof(ElemType))))
			exit(ERROR);
		s->base[s->top++] = data;
	}
}

ElemType Pop_SqStack(SqStack* s) {
	if (s->top == 0)
		exit(ERROR);
	else
		return s->base[--s->top];
}

GLList Get_GLList() {
	char c;
	GLList L;
	if (!(L = (GLList)malloc(sizeof(GLNode))))
		exit(ERROR);
	
	SqStack* s;
	s = Init_SqStack();
	GLNode* p;
	if (!(p = (GLNode*)malloc(sizeof(GLNode))))
		exit(ERROR);
	do {
		c = getchar();
		switch (c) {
		case '(':
			Push_SqStack(s, c);
			L->Tag = LIST;
			L->hp = Get_GLList();
			p = L->hp;
			break;

		case ')':
			Pop_SqStack(s);
			break;

		case ',':
			p->tp = Get_GLList();
			p = p->tp;
			break;

		default:
			L->Tag = ATOM;
			L->atom = c;
			break;

		}
	} while (s->top);
	L->tp = NULL;
	return L;
}

void Remove_GLList(GLList L, AtomType c) {
	if (L->Tag == ATOM) {
		if (L->atom == c)
			L = NULL;
	}
	else {
		GLNode* p, * pnext;
		for (p = L, pnext = L->hp; pnext;) {
			if (pnext->Tag == ATOM) {
				if (pnext->atom == c) {
					if (p == L) {
						pnext = pnext->tp;
						p->hp = pnext;
					}
					else {
						pnext = pnext->tp;
						p->tp = pnext;
					}
				}
				else {
					p = pnext;
					pnext = p->tp;
				}
			}
			else {
				Remove_GLList(pnext, c);
				if (pnext->Tag == LIST) {
					if (pnext->hp == NULL) {
						if (p == L) {
							pnext = pnext->tp;
							p->hp = pnext;
						}
						else {
							pnext = pnext->tp;
							p->tp = pnext;
						}
					}
					else {
						p = pnext;
						pnext = pnext->tp;
					}
				}
			}
		}
	}
}

void Print_GLList(GLList L) {
	if (L == NULL || (L->Tag == LIST && L->hp == NULL)) {
		printf("-1");
	}
	else {
		if (L->Tag == ATOM)
			printf("%c", L->atom);
		else {
			GLNode* p;
			printf("(");
			for (p = L->hp; p; p = p->tp) {
				Print_GLList(p);
				if (p->tp)
					printf(",");
			}
			printf(")");
		}

	}
}

main() {
	GLList L;
	L = Get_GLList();

	char c;
	getchar();
	scanf("%c", &c);
	Remove_GLList(L, c);
	Print_GLList(L);
}

