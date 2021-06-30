#include <stdio.h>
#include <stdlib.h>
#define ElemType PolyTerm
#define STACKSIZE 100

typedef struct {
	int coef;
	int expo;
}PolyTerm;

typedef struct PolyNode {
	PolyTerm data;
	struct PolyNode* next;
} PolyNode, * PolyLink;

typedef PolyLink LinkedPoly;

typedef struct {
	int StackSize;
	ElemType* base;
	int top;
}SqStack;

LinkedPoly Init_LinkedPoly() {
	LinkedPoly l;
	l = (LinkedPoly)malloc(sizeof(PolyNode));
	l->next = l;
	l->data.coef = 0;
	l->data.expo = 0;
	return l;
}

PolyNode* Init_PolyNode(PolyTerm data) {
	PolyNode* p;
	p = (LinkedPoly)malloc(sizeof(PolyNode));
	p->data = data;
	return p;
}

void Insert_PolyNode(LinkedPoly l, PolyTerm p) {
	PolyNode* q = l;
	for (; q->next != l; q = q->next) {
		if (q->next->data.expo < p.expo) {
			PolyNode* r;
			r = Init_PolyNode(p);
			r->next = q->next;
			q->next = r;
			return;
		}
		else if (q->next->data.expo == p.expo) {
			q->next->data.coef += p.coef;
			return;
		}
		else
			continue;
	}
	PolyNode* r;
	r = Init_PolyNode(p);
	r->next = q->next;
	q->next = r;
	return;
}

void Remove_PolyNode(PolyNode* p) {
	p->next = p->next->next;
}

void Print_LinkedPoly(LinkedPoly l) {
	PolyNode* p = l;
	
	if (l->next == l) {
		printf("0");
	}
	
	for (; p->next != l; p = p->next) {
		if (p == l) {
			if (p->next->data.coef < 0) {
				switch (p->next->data.expo) {
				case 0:
					printf("- %d", -p->next->data.coef);
					break;

				case 1:
					printf("- %dx", -p->next->data.coef);
					break;

				default:
					printf("- %dx^%d", -p->next->data.coef, p->next->data.expo);
					break;
				}
			}
			else {
				switch (p->next->data.expo) {
				case 0:
					printf("%d", p->next->data.coef);
					break;

				case 1:
					printf("%dx", p->next->data.coef);
					break;

				default:
					printf("%dx^%d", p->next->data.coef, p->next->data.expo);
					break;
				}
			}
		}
		else {
			if (p->next->data.coef < 0) {
				switch (p->next->data.expo) {
				case 0:
					printf(" - %d", -p->next->data.coef);
					break;

				case 1:
					printf(" - %dx", -p->next->data.coef);
					break;

				default:
					printf(" - %dx^%d", -p->next->data.coef, p->next->data.expo);
					break;
				}
			}
			else {
				switch (p->next->data.expo) {
				case 0:
					printf(" + %d", p->next->data.coef);
					break;

				case 1:
					printf(" + %dx", p->next->data.coef);
					break;

				default:
					printf(" + %dx^%d", p->next->data.coef, p->next->data.expo);
					break;
				}
			}
		}
	}

	
}

SqStack* Init_SqStack() {
	SqStack* s;
	s = (SqStack*)malloc(sizeof(SqStack));
	s->base = (ElemType*)malloc(STACKSIZE * sizeof(ElemType));
	s->StackSize = STACKSIZE;
	s->base->coef = 0;
	s->base->expo = 0;
	s->top = 0;
	return s;
}

PolyTerm Pop_SqStack(SqStack* s) {
	if (s->top > 0) {
		ElemType p;
		p.coef = s->base[s->top - 1].coef;
		p.expo = s->base[s->top - 1].expo;
		s->top--;
		return p;
	}
}

int Len_SqStack(SqStack* s) {
	return s->top;
}

main() {
	char c;
	int coef;
	int expo;
	int sign;
	int is_empty = 1;	//is_empty为1表示栈为空;为0表示栈不为空
	int status = 0;		//status为0表示向系数输入;为1表示向指数输出;为-1表示检测到x;为2表示检测到符号

	SqStack* s;
	s = Init_SqStack();
	do {
		c = getchar();

		switch (c)
		{
		case ' ':
			break;

		case '\n':
			if (status == 0) {
				s->base[s->top - 1].expo = 0;
			}
			break;

		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':
			if (is_empty) {
				s->top++;
				is_empty = 0;
				sign = 1;
			}
			if (status == 0 || status == 2) {
				s->base[s->top - 1].coef = s->base[s->top - 1].coef * 10 + c - '0';
				status = 0;
			}
			else if (status == 1) {
				s->base[s->top - 1].expo = s->base[s->top - 1].expo * 10 + c - '0';
			}
			break;

		case 'x':
			if (is_empty) {
				s->top++;
				is_empty = 0;
				sign = 1;
				s->base[s->top - 1].coef = sign;
			}
			if (status == 2) {
				s->base[s->top - 1].coef = sign;
				status = -1;
				s->base[s->top - 1].expo = 1;
				
				break;
			}
			status = -1;
			s->base[s->top - 1].coef = s->base[s->top - 1].coef * sign;
			s->base[s->top - 1].expo = 1;
			break;

		case '+':
			if (is_empty) {
				s->top++;
				is_empty = 0;
			}
			if (status == 0) {
				sign = 1;
				status = 2;
				s->base[s->top - 1].coef = 0;
			}
			else {
				sign = 1;
				is_empty = 0;
				s->top++;
				status = 2;
				s->base[s->top - 1].coef = 0;
			}
			break;

		case '-':
			if (is_empty) {
				s->top++;
				is_empty = 0;
			}
			if (status == 0) {
				sign = -1;
				status = 2;
				s->base[s->top - 1].coef = 0;
			}
			else {
				sign = -1;
				is_empty = 0;
				s->top++;
				status = 2;
				s->base[s->top - 1].coef = 0;
				break;
			}
			break;

		case '^':
			status = 1;
			s->base[s->top - 1].expo = 0;
			break;

		default:
			break;
		}
	} while (c != EOF && c != '\n');

	LinkedPoly l;
	l = Init_LinkedPoly();

	for (; Len_SqStack(s) != 0;) {
		PolyTerm data;
		data = Pop_SqStack(s);
		Insert_PolyNode(l, data);
	}

	//开始求导
	PolyNode* p = l;
	for (; p->next != l;) {
		if (p->next->data.expo == 0 || p->next->data.coef == 0) {
			Remove_PolyNode(p);
		}
		else {
			p->next->data.coef *= p->next->data.expo;
			p->next->data.expo--;
			p = p->next;
		}
	}

	Print_LinkedPoly(l);
}