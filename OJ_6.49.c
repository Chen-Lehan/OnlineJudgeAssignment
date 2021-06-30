#include <stdio.h>
#include <stdlib.h>
#define ERROR -1 
typedef enum {True,False} bool;

#define MAXSIZE 100
#define SElemType BiTreeNode
#define TElemType char

typedef struct BiTreeNode {
	TElemType data;
	struct BiTreeNode* left, * right;
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
				node->left = NULL;
			else
				node->left = &base[pointer - 1];

			signal = 1;
			pointer = 0;
			break;

		case '\n':
			if (signal == -1)
				node->right = NULL;
			else
				node->right = &base[pointer - 1];

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

bool IsFull(BiTree T) {
	if (T->left && T->right) {
		int ldepth = 0, rdepth = 0;
		BiTreeNode* node;
		for (node = T; node->left; node = node->left, ldepth++);
		for (node = T; node->right; node = node->right, rdepth++);
		if (ldepth != rdepth)
			return False;
		else {
			if (IsFull(T->left) == True && IsFull(T->right) == True)
				return True;
			else
				return False;
		}
	}
	else if (T->left || T->right)
		return False;
	else
		return True;
}

bool IsComplete(BiTree T) {
	if (!T->left && T->right)
		return False;
	else if (T->left && !T->right) {
		if (!(T->left->left || T->left->right))
			return True;
		else
			return False;
	}
	else if (T->left && T->right) {
		bool lfull, rfull;
		lfull = IsFull(T->left);
		rfull = IsFull(T->right);
		if (lfull == False && rfull == False)
			return False;
		else {
			int ldepth = 0, rdepth = 0;
			BiTreeNode* node;
			for (node = T; node->left; node = node->left, ldepth++);
			for (node = T; node->right; node = node->right, rdepth++);

			if (ldepth == rdepth) {
				if (lfull == True && rfull == True)
					return True;
				else
					return False;
			}
			else if (ldepth == rdepth + 1) {
				if (lfull == True && IsComplete(T->right) == True)
					return True;
				else if (rfull == True && IsComplete(T->left) == True)
					return True;
				else
					return False;
			}
			else
				return False;
		}
	}
	else
		return True;
}

main() {
	BiTreeNode* base;
	if (!(base = (BiTreeNode*)malloc(MAXSIZE * sizeof(BiTreeNode))))
		exit(ERROR);

	int i = 0;
	if (!(base[i].left = (BiTreeNode*)malloc(sizeof(BiTreeNode))) ||
		!(base[i].right = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
		exit(ERROR);
	while (getnode(&base[i], base)) {
		i++;
		if (!(base[i].left = (BiTreeNode*)malloc(sizeof(BiTreeNode))) ||
			!(base[i].right = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
			exit(ERROR);
	}
	
	bool Comp;
	Comp = IsComplete(&base[0]);
	if (Comp == True)
		printf("Yes");
	else
		printf("No");
}