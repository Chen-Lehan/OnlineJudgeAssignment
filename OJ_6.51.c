#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define TElemType char

typedef enum {Plus, Multi, Minus} Op;

typedef struct BiTreeNode {
	TElemType data;
	struct BiTreeNode* lchild, * rchild;
}BiTreeNode, * BiTree;

BiTree Get_BiTree() {
	char c;
	c = getchar();
	if (c == '#') {
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

void Print_BiTree(BiTree T, Op preop) {
	if (T) {
		if (T->data == '*' || T->data == '/') {
			Print_BiTree(T->lchild, Multi);
			printf("%c", T->data);
			Print_BiTree(T->rchild, Multi);
		}
		else if (T->data == '+') {
			if (preop == Plus) {
				Print_BiTree(T->lchild, Plus);
				printf("%c", T->data);
				Print_BiTree(T->rchild, Plus);
			}
			else {
				printf("(");
				Print_BiTree(T->lchild, Plus);
				printf("%c", T->data);
				Print_BiTree(T->rchild, Plus);
				printf(")");
			}
		}
		else if (T->data == '-') {
			if (preop == Plus) {
				Print_BiTree(T->lchild, Plus);
				printf("%c", T->data);
				Print_BiTree(T->rchild, Minus);
			}
			else {
				printf("(");
				Print_BiTree(T->lchild, Plus);
				printf("%c", T->data);
				Print_BiTree(T->rchild, Minus);
				printf(")");
			}
		}
		else {
			printf("%c", T->data);
		}
	}
}

main() {
	BiTree T;
	if (!(T = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
		exit(ERROR);
	T = Get_BiTree();
	Print_BiTree(T, Plus);
}