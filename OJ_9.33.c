#include <stdio.h>
#include <stdlib.h>
#define ERROR -1

typedef struct BSTreeNode {
	struct BSTreeNode* lchild, * rchild;
	int data;
}*BSTree, BSTreeNode;

BSTree Insert_BSTree(BSTree T, int data) {
	if (!T) {
		BSTree T1;
		if (!(T1 = (BSTree)malloc(sizeof(BSTreeNode))))
			exit(ERROR);
		T1->lchild = NULL;
		T1->rchild = NULL;
		T1->data = data;
		T = T1;
		return T1;
	}
	else {
		if (T->data < data) {
			T->rchild = Insert_BSTree(T->rchild, data);
		}
		else if (T->data > data) {
			T->lchild = Insert_BSTree(T->lchild, data);
		}
		return T;
	}
}

void Print_BSTree(BSTreeNode* T, int lowerbound) {
	if (T) {
		Print_BSTree(T->rchild, lowerbound);
		if (T->data >= lowerbound) {
			if (T->rchild)
				printf(" ");
			printf("%d", T->data);
			Print_BSTree(T->lchild, lowerbound);
		}
	}
}

main() {
	int data = 0;
	int sign = 1;
	char c;
	BSTree T;
	T = NULL;
	while (c = getchar()) {
		switch (c) {
		case '-': 
			sign = -1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			data = data * 10 + c - '0';
			break;

		case ' ': case '\n':
			data = data * sign;
			T = Insert_BSTree(T, data);
			data = 0;
			sign = 1;
			break;
		}
		if (c == '\n')
			break;
	}

	int lowerbound;
	scanf("%d", &lowerbound);

	Print_BSTree(T, lowerbound);
}
