#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define TElemType char

typedef enum {True, False} bool;

typedef struct BiTreeNode {
	TElemType data;
	struct BiTreeNode* lchild, * rchild;
}BiTreeNode, * BiTree;

BiTree Get_BiTree() {
	char c;
	c = getchar();
	if (c == '^') {
		return NULL;
	}
	else {
		BiTree T;
		if (!(T = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
			exit(ERROR);
		T->data = c;
		T->lchild = Get_BiTree();
		T->rchild = Get_BiTree();
		return T;
	}
}

bool IsChild(BiTreeNode* p, TElemType data) {
	if ((p->lchild && p->lchild->data == data) || (p->rchild && p->rchild->data == data))
		return True;
	else {
		bool left, right;
		if (p->lchild)
			left = IsChild(p->lchild, data);
		else
			left = False;
		if (p->rchild)
			right = IsChild(p->rchild, data);
		else
			right = False;

		if (left == True || right == True)
			return True;
		else
			return False;
	}
}

BiTreeNode* CommonAncestor(BiTree T, TElemType data1, TElemType data2) {
	if (T) {
		if (IsChild(T, data1) == True && IsChild(T, data2) == True) {
			BiTreeNode* left, * right;
			left = CommonAncestor(T->lchild, data1, data2);
			right = CommonAncestor(T->rchild, data1, data2);
			if (left)
				return left;
			if (right)
				return right;
			return T;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

main() {
	BiTree T;
	BiTreeNode* CA;
	BiTreeNode* Head;
	if (!(Head = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
		return ERROR;
	T = Get_BiTree();
	Head->lchild = T;
	Head->rchild = NULL;
	char data1, data2;
	getchar();
	data1 = getchar();
	getchar();
	data2 = getchar();
	
	CA = CommonAncestor(Head, data1, data2);
	if (CA) {
		if (CA == Head)
			printf("%c", T->data);
		else
			printf("%c", CA->data);
	}
	else
		printf("-1");
}