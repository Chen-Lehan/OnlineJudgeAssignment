#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 20
#define ERROR -1

typedef struct LinkListNode {
	int data;
	struct LinkListNode* next;
}LinkListNode, * LinkList;

LinkList Append_LinkList(LinkList L, LinkListNode* node) {
	if (!node)
		return L;
	if (!L)
		return node;
	else {
		LinkListNode* p;
		for (p = L; p->next; p = p->next);
		p->next = node;
		return L;
	}
}

LinkList BucketSort(LinkList L, int n) {
	LinkList base[10];
	int i, j;
	for (i = 0; i < 10; i++) {
		if (!(base[i] = (LinkList)malloc(sizeof(LinkListNode))))
			exit(ERROR);
		base[i]->next = NULL;
	}
	LinkListNode* p;
	for (p = L; p; p = p->next) {
		j = (p->data / (int)pow(10, n)) % 10;
		LinkListNode* node;
		if (!(node = (LinkListNode*)malloc(sizeof(LinkListNode))))
			exit(ERROR);
		node->data = p->data;
		node->next = NULL;
		base[j] = Append_LinkList(base[j], node);
	}
	LinkList L1 = NULL;
	for (i = 0; i < 10; i++) {
		L1 = Append_LinkList(L1, base[i]->next);
	}
	LinkListNode* q;
	for (p = L; p; p = q) {
		q = p->next;
		free(p);
	}
	return L1;
}

main() {
	char c;
	int data = 0;
	LinkList L = NULL;
	while (c = getchar()) {
		switch (c) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			data = data * 10 + c - '0';
			break;

		case ' ': case '\n': {
			LinkListNode * node;
			if (!(node = (LinkListNode*)malloc(sizeof(LinkListNode))))
				exit(ERROR);
			node->data = data;
			node->next = NULL;
			data = 0;
			L = Append_LinkList(L, node);
			break;
		}
		}
		if (c == '\n')
			break;
	}
	L = BucketSort(L, 0);
	L = BucketSort(L, 1);
	L = BucketSort(L, 2);
	L = BucketSort(L, 3);

	LinkListNode* p;
	for (p = L; p; p = p->next) {
		printf("%d", p->data);
		if (p->next)
			printf(" ");
	}
}