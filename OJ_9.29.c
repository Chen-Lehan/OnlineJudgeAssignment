#include <stdlib.h>
#include <stdio.h>
#define ERROR -1

typedef struct LinkListNode{
	int data;
	struct LinkListNode* next;
}LinkListNode, *LinkList;

LinkList Insert_LinkList(LinkList L, int data) {
	if (!L) {
		LinkListNode* node;
		if (!(node = (LinkList)malloc(sizeof(LinkListNode))))
			exit(ERROR);

		node->data = data;
		node->next = node;
		return node;
	}
	else {
		LinkListNode* node, * p;
		if (!(node = (LinkList)malloc(sizeof(LinkListNode))))
			exit(ERROR);
		node->data = data;

		for (p = L; p; p = p->next) {
			if (p->data < data && data < p->next->data) {
				node->next = p->next;
				p->next = node;
				return L;
			}
			else if (p->data == data) {
				return L;
			}
			else if (p->data >= p->next->data) {
				node->next = p->next;
				p->next = node;
				return L;
			}
		}
	}
}

void In_LinkList(LinkList L, int data) {
	LinkListNode* t, * h;
	t = L;
	h = L;
	for (;;t = t->next) {
		if (t->data == data) {
			printf("1");
			break;
		}
		if (t->next == h) {
			printf("0");
			break;
		}
	}
}

main() {
	LinkList L = NULL;
	int data = 0;
	int sign = 1;
	char c;
	while (c = getchar()) {
		switch (c)
		{
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
			break;

		default:
			break;
		}
		if (c == '\n')
			break;
	}
	while (c = getchar()) {
		switch (c)
		{
		case ' ': case '\n':
			data = data * sign;
			In_LinkList(L, data);
			data = 0;
			sign = 1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			data = data * 10 + c - '0';
			break;

		case '-':
			sign = -1;
			break;

		default:
			break;
		}
		if (c == '\n')
			break;
		if (c == ' ')
			printf(" ");
	}
}