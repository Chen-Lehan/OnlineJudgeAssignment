#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define OK 1

typedef struct LinkListNode {
	int data;
	struct LinkListNode* next;
}LinkListNode, * LinkList;

LinkList Insert_LinkList(LinkList L) {
	LinkListNode* p, * node;
	p = L;
	if (!(node = (LinkListNode*)malloc(sizeof(LinkListNode))))
		exit(ERROR);
	scanf("%d", &node->data);
	if (!L) {
		node->next = NULL;
		L = node;
	}
	else {
		if (node->data < p->data) {
			node->next = p;
			L = node; 
		}
		else {
			for (L = p; p->next; p = p->next) {
				if (node->data < p->next->data)
					break;
			}
			node->next = p->next;
			p->next = node;
		}
	}
	return L;
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
	int length, i;
	LinkList L = NULL;
	scanf("%d", &length);
	for (i = 0; i < length; i++) {
		L = Insert_LinkList(L);
	}
	Print_LinkList(L);
}