#include <stdio.h>
#include <stdlib.h>
#define ERROR -1 
typedef enum { True, False } bool;

#define MAXSIZE 100
#define TElemType int

typedef struct BiTreeNode {
	TElemType data;
	struct BiTreeNode* lchild, * rchild;
}BiTreeNode, * BiTree;

bool Is_BSTree(BiTree T) {
	if (!T)
		return True;
	else {
		if (Is_BSTree(T->lchild) == False)
			return False;
		else if (T->rchild == False)
			return False;
		else {
			if (T->lchild) {
				BiTreeNode* p;
				for (p = T->lchild; p->rchild; p = p->rchild);
				if (p->data > T->data)
					return False;
			}
			if (T->rchild) {
				BiTreeNode* p;
				for (p = T->rchild; p->lchild; p = p->lchild);
				if (p->data < T->data)
					return False;
			}
			return True;
		}
	}
}

main() {
	BiTreeNode* base;
	if (!(base = (BiTreeNode*)malloc(MAXSIZE * sizeof(BiTreeNode))))
		exit(ERROR);

	int i;
	int data;
	for (i = 0;; i++) {
		char c;
		data = 0;
		while (c = getchar()) {
			if (c == ' ' || c == EOF)
				break;
			data = data * 10 + c - '0';
		}
		if (c == EOF)
			break;

		if (!(base[i].lchild = (BiTreeNode*)malloc(sizeof(BiTreeNode))) ||
			!(base[i].rchild = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
			exit(ERROR);

		base[i].data = data;
		int left, right;
		scanf("%d%d", &left, &right);
		if (left < 0)
			base[i].lchild = NULL;
		else
			base[i].lchild = &base[left];
		if (right < 0)
			base[i].rchild = NULL;
		else
			base[i].rchild = &base[right];
		getchar();
	}

	bool is_bstree = Is_BSTree(base);
	if (is_bstree == True)
		printf("1");
	else
		printf("0");
}