#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 100

typedef struct {
	int length;
	char* base;
	int top;
}*OpStack;

OpStack Init_OpStack() {
	OpStack s;
	s = (OpStack)malloc(sizeof(OpStack));
	s->base = (char*)malloc(STACKSIZE * sizeof(char));
	s->top = 0;
	s->length = STACKSIZE;
	return s;
}



char Pop_OpStack(OpStack s) {
	return s->base[--s->top];
}

void Push_OpStack(OpStack s, char c) {
	s->base[s->top++] = c;
}

int Len_OpStack(OpStack s) {
	return s->top;
}

main() {
	char c;
	char op;
	OpStack s;
	s = Init_OpStack();
	while ((c = getchar())) {
		switch (c) 
		{
		case 'EOF':
			exit(0);
		case '+':case '-':
		{
			if (Len_OpStack(s) == 0 || s->base[s->top - 1] == '(') {
				Push_OpStack(s, c);
			}
			else {
				while (Len_OpStack(s) != 0 && s->base[s->top - 1] != '(') {
					op = Pop_OpStack(s);
					printf("%c", op);
				}
				Push_OpStack(s, c);
			}
			break;
		}

		case '*':case '/':
		{
			if (Len_OpStack(s) == 0 || s->base[s->top - 1] == '(' || s->base[s->top - 1] == '-' || s->base[s->top - 1] == '+') {
				Push_OpStack(s, c);
			}
			else {
				while (Len_OpStack(s) != 0 && s->base[s->top - 1] != '(' && s->base[s->top - 1] != '-' && s->base[s->top - 1] != '+') {
					op = Pop_OpStack(s);
					printf("%c", op);
				}
				Push_OpStack(s, c);
			}
			break;
		}

		case '(':
			Push_OpStack(s, c);
			break;

		case ')':
		{
			while ((op = Pop_OpStack(s)) != '(') {
				printf("%c", op);
			}
			break;
		}

		case '\n':
		{
			while (Len_OpStack(s) != 0) {
				op = Pop_OpStack(s);
				printf("%c", op);
			}
			exit(0);
		}

		default:
			printf("%c", c);
			break;
		}
	}
}