#include <stdio.h>
#include <stdlib.h>
#define ERROR -1 
typedef enum { True, False } bool;

#define MAXSIZE 100
#define SElemType BiTreeNode
#define TElemType char

typedef struct BiTreeNode {
	TElemType data;
	struct BiTreeNode* child, * sibling;
}BiTreeNode, * BiTree;
typedef struct {
	SElemType* base;
	int length;
	int top;
}SqStack;

SqStack* Init_SqStack() {
	SqStack* S;
	if (!(S = (SqStack*)malloc(sizeof(SqStack))) ||
		!(S->base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType))))
		exit(ERROR);
	S->length = MAXSIZE;
	S->top = 0;
	return S;
}

void Push_SqStack(SqStack* S, SElemType data) {
	S->base[S->top++] = data;
}

SElemType Pop_SqStack(SqStack* S) {
	if (S->top <= 0)
		exit(ERROR);
	else
		return(S->base[--S->top]);
}

int getnode(BiTreeNode* node, BiTreeNode* base) {
	char c;
	int pointer = 0, signal = 1, dir = 0;		//dir为0表示准备输入左孩子，为1表示准备输入右孩子
	c = getchar();
	if (c == EOF)
		return(0);
	getchar();
	node->data = c;
	while (c = getchar()) {
		switch (c) {
		case ' ':
			if (signal == -1)
				node->child = NULL;
			else
				node->child = &base[pointer - 1];

			signal = 1;
			pointer = 0;
			break;

		case '\n':
			if (signal == -1)
				node->sibling = NULL;
			else
				node->sibling = &base[pointer - 1];

			signal = 1;
			pointer = 0;
			return(1);

		case 'EOF':
			return(0);

		case '-':
			signal = -1;
			break;

		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			pointer = pointer * 10 + c - '0';
			break;

		default:
			exit(ERROR);
		}
	}
}

void Print_BiTree(BiTree T, int layer) {
	int i;
	if (layer < 0)
		return(ERROR);

	printf("\n");
	for (i = 0; i < layer; i++) {
		printf("-");
	}
	printf("%c", T->data);
	if (T->child)
		Print_BiTree(T->child, layer + 1);
	if (T->sibling)
		Print_BiTree(T->sibling, layer);
}

main() {
	BiTreeNode* base;
	if (!(base = (BiTreeNode*)malloc(MAXSIZE * sizeof(BiTreeNode))))
		exit(ERROR);

	int i = 0;
	if (!(base[i].child = (BiTreeNode*)malloc(sizeof(BiTreeNode))) ||
		!(base[i].sibling = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
		exit(ERROR);
	while (getnode(&base[i], base)) {
		i++;
		if (!(base[i].child = (BiTreeNode*)malloc(sizeof(BiTreeNode))) ||
			!(base[i].sibling = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
			exit(ERROR);
	}

	printf("%c", base[0].data);
	if (base[0].child)
		Print_BiTree(base[0].child, 1);
}