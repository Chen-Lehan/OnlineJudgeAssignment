#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define MAXLEN 100

typedef struct StrNode {
	char c;
	struct StrNode* succ;
	struct StrNode* next;
}StrNode;

typedef struct {
	StrNode* head;
	StrNode* tail;
}*String;

String Init_String() {
	String string;
	if (!(string = (String)malloc(2 * sizeof(StrNode*))) ||
		!(string->head = (StrNode*)malloc(sizeof(StrNode))) ||
		!(string->tail = (StrNode*)malloc(sizeof(StrNode))))
		exit(ERROR);
	string->head->next = NULL;
	string->head->succ = NULL;
	string->tail = string->head;
	return string;
}

void Extend_String(String S) {
	StrNode* node;
	if (!(node = (StrNode*)malloc(sizeof(StrNode))) ||
		!(node->succ = (StrNode*)malloc(sizeof(StrNode))) ||
		!(node->next = (StrNode*)malloc(sizeof(StrNode)))) 
		exit(ERROR);
	node->next = NULL;
	node->succ = NULL;
	S->tail->succ = node;
	S->tail = node;
}

void Assign_String(String S, char str[]) {
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		Extend_String(S);
		S->tail->c = str[i];
	}
}

void getnext(String S, int mode) {
	if (mode == 0) {
		int i;
		StrNode* p, * q;
		for (i = 1, p = S->head->succ, q = S->head; p != S->tail; p = p->succ, i++) {
			if (i == 1) {
				p->next = q;
				p->succ->next = p;
				q = q->succ;
			}
			else {
				while (p->c != q->c && q!= S->head) {
					q = q->next;
				}
				p->succ->next = q->succ;
				q = q->succ;
			}
		}
	}
	else if (mode == 1) {
		StrNode* p;
		for (p = S->head; p != S->tail; p = p->succ) {
			p->succ->next = p;
		}
	}
}//mode为1表示求S的next，mode为0表示求T的next

int getline(char s[], int lim) {
	int  c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		s[i] = c;
	}

	s[i] = '\0';
	return i;
}

main() {
	String S, T;
	S = Init_String();
	T = Init_String();

	int Tlen;
	char str[MAXLEN];
	getline(str, MAXLEN);
	getline(str, MAXLEN);
	Assign_String(S, str);
	Tlen = getline(str, MAXLEN);
	Assign_String(T, str);

	getnext(S, 0);
	getnext(T, 0);

	StrNode* p, * q;
	int loc = 0;

	for (p = S->head, q = T->head, loc = 0;;) {
		if (!p || !q) {
			printf("-1");
			exit(0);
		}
		if (q == T->head) {
			p = p->succ;
			loc++;
			q = q->succ;
		}
		else {
			if (p->c == q->c) {
				if (q == T->tail) {
					printf("%d", loc - Tlen);
					exit(0);
				}
				else {
					q = q->succ;
					if (p == S->tail) {
						printf("-1");
						exit(0);
					}
					else {
						p = p->succ;
						loc++;
					}
				}
			}
			else {
				q = q->next;
			}
		}
	}
}