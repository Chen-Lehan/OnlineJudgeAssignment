#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define ElemType int

typedef struct BiTreeNode {
	struct BiTreeNode* lchild;
	struct BiTreeNode* rchild;
	ElemType data;
}BiTreeNode, * BiTree;

BiTree Get_BiTree() {
	int data;
	if (!scanf("%d", &data))
		exit(ERROR);
	if (data == -1) {
		return NULL;
	}
	else {
		BiTree T;
		if (!(T = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
			exit(ERROR);
		T->data = data;
		T->lchild = Get_BiTree();
		T->rchild = Get_BiTree();
		return T;
	}
}

void Insert_BiTree(BiTree T, ElemType data) {
	if (data == T->data)
		return;
	else if (data < T->data) {
		if (T->lchild)
			Insert_BiTree(T->lchild, data);
		else {
			BiTreeNode* node;
			if (!(node = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
				exit(ERROR);
			node->data = data;
			node->lchild = NULL;
			node->rchild = NULL;
			T->lchild = node;
		}
	}
	else {
		if (T->rchild)
			Insert_BiTree(T->rchild, data);
		else {
			BiTreeNode* node;
			if (!(node = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
				exit(ERROR);
			node->data = data;
			node->lchild = NULL;
			node->rchild = NULL;
			T->rchild = node;
		}
	}
}

void Combine_BiTree(BiTree T1, BiTree T2) {
	Insert_BiTree(T1, T2->data);
	if (T2->lchild)
		Combine_BiTree(T1, T2->lchild);
	if (T2->rchild)
		Combine_BiTree(T1, T2->rchild);
}

void Print_BiTreeInOrder(BiTree T) {
	if (T->lchild) {
		Print_BiTreeInOrder(T->lchild);
		printf(" ");
	}
	printf("%d", T->data);
	if (T->rchild) {
		printf(" ");
		Print_BiTreeInOrder(T->rchild);
	}
}

main() {
	BiTree T1, T2;
	T1 = Get_BiTree();
	T2 = Get_BiTree();
	Combine_BiTree(T1, T2);
	Print_BiTreeInOrder(T1);
}