#include<stdio.h>
#include<stdlib.h>
#define STACKSIZE 100
#define MAXLINE 100

typedef struct{
	int length;
	char* base;
	int top;
}SqStack;

SqStack* Init_SqStack(){
	SqStack * s;
	s = (SqStack*)malloc(sizeof(SqStack));
	s->base = (char*)malloc(STACKSIZE * sizeof(char));
	s->top = 0;
	return s;
}

char Pop_SqStack(SqStack* s) {
	return s->base[--s->top];
}

void Push_SqStack(SqStack* s, char c) {
	s->base[s->top++] = c;
}

int Len_SqStack(SqStack* s) {
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
	int len;
	char c;
	char str[MAXLINE];
	SqStack* s;
	s = Init_SqStack();
	while ((len = getline(str, MAXLINE)) > 0) {
		int i;
		for (i = 0; i < len; i++) {
			c = str[i];
			switch (str[i])
			{
			case '(':
				Push_SqStack(s, c);
				break;

			case ')':
				if (s->top == 0) {
					printf("0");
					while ((c = getchar()) != '\n') {
						;
					}
					printf("\n");
				}
				else {
					Pop_SqStack(s);
				}
				break;

			case '\n':
				if (Len_SqStack(s) == 0) {
					printf("1\n");
				}
				else {
					printf("0\n");
				}
				s = Init_SqStack();
				break;

			default:
				break;
			}



			/*switch (c)
			{
			case '(':
				Push_SqStack(s, c);
				break;

			case ')':
				if (s->top == 0) {
					printf("0");
					while ((c = getchar()) != '\n') {
						;
					}
					printf("\n");
				}
				else {
					Pop_SqStack(s);
				}
				break;

			case '\n':
				if (Len_SqStack(s) == 0) {
					printf("1\n");
				}
				else {
					printf("0\n");
				}
				s=Init_SqStack();
				break;

			default:
				break;
			}*/
		}
		/*if (Len_SqStack(s) == 0) {
			printf("1\n");
		}
		else {
			printf("0\n");
		}*/
	}
}