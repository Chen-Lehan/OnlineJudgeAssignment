#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define MAXLENGTH 30
#define ElemType char

typedef struct node {
	ElemType data;
	struct node* lchild, * rchild;
}BiTreeNode, *BiTree;

typedef struct {
	ElemType base[MAXLENGTH];
	int length;
}array;

void Get_BiTreefArray(BiTree T,array pre,array in) {
	if (!(T->lchild = (BiTree)malloc(sizeof(BiTreeNode))) ||
		!(T->rchild = (BiTree)malloc(sizeof(BiTreeNode))))
		exit(ERROR);
	T->data = pre.base[0];

	int pos, i;
	array leftpre, leftin, rightpre, rightin;

	for (pos = 0; pre.base[0] != in.base[pos]; pos++);
	
	for (i = 0, leftpre.length = 0; leftpre.length != pos; i++, leftpre.length++)
		leftpre.base[i] = pre.base[i + 1];

	for (i = 0, leftin.length = 0; leftin.length != pos; i++, leftin.length++)
		leftin.base[i] = in.base[i];
	
	for (i = 0, rightpre.length = 0; rightpre.length != pre.length - 1 - pos; i++, rightpre.length++)
		rightpre.base[i] = pre.base[i + pos + 1];
	
	for (i = 0, rightin.length = 0; rightin.length != in.length - 1 - pos; i++, rightin.length++)
		rightin.base[i] = in.base[i + pos + 1];

	if (leftin.length)
		Get_BiTreefArray(T->lchild, leftpre, leftin);
	else
		T->lchild = NULL;

	if (rightin.length)
		Get_BiTreefArray(T->rchild, rightpre, rightin);
	else
		T->rchild = NULL;
}

void Print_BiTreePost(BiTree T) {
	if (T->lchild)
		Print_BiTreePost(T->lchild);
	if (T->rchild)
		Print_BiTreePost(T->rchild);
	printf("%c",T->data);
}

main() {
	array pre, in, post;
	char c;
	pre.length = 0;
	in.length = 0;
	while ((c = getchar()) && c != '\n')
		pre.base[pre.length++] = c;
	while ((c = getchar()) && c != '\n')
		in.base[in.length++] = c;
	BiTree T;
	if (!(T = (BiTree)malloc(sizeof(BiTreeNode))))
		exit(ERROR);
	Get_BiTreefArray(T, pre, in);
	
	Print_BiTreePost(T);
}