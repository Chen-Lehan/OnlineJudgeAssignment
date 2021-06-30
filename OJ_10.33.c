#include <stdio.h>
#include <stdlib.h>
#define ERROR -1 

typedef struct LinkListNode{
	struct LinkListNode* next;
	int data;
}LinkListNode, *LinkList;

LinkList Insert_LinkList(LinkList L, int data) {
	LinkListNode* p;
	if (!L) {
		if (!(p = (LinkListNode*)malloc(sizeof(LinkListNode))))
			exit(ERROR);
		p->data = data;
		p->next = NULL;
		return p;
	}
	if (L->data >= data) {
		if (!(p = (LinkListNode*)malloc(sizeof(LinkListNode))))
			exit(ERROR);
		p->data = data;
		p->next = L;
		return p;
	}
	else {
		for (p = L; p->next; p = p->next) {
			if (p->next->data >= data)
				break;
		}
		LinkListNode* node;
		if (!(node = (LinkListNode*)malloc(sizeof(LinkListNode))))
			exit(ERROR);
		node->data = data;
		node->next = p->next;
		p->next = node;
		return L;
	}
}

void Print_LinkList(LinkList L) {
	LinkListNode* p;
	for (p = L; p; p = p->next) {
		if (p != L)
			printf(" ");
		printf("%d", p->data);
	}
}

main() {
	char c;
	int data = 0;
	int sign = 1;
	LinkList L = NULL;
	while (c = getchar()) {
		switch (c) {
		case ' ': case '\n':
			data = data * sign;
			L = Insert_LinkList(L, data);
			data = 0;
			sign = 1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			data = data * 10 + c - '0';
			break;

		case '-':
			sign = -1;
		}
		if (c == '\n')
			break;
	}
	Print_LinkList(L);
}