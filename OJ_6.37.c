#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
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

	SqStack* S;
	int start = 1;
	S = Init_SqStack();
	Push_SqStack(S, base[0]);
	BiTreeNode node;

	while (S->top != 0) {
		if (S->base[S->top - 1].left && S->base[S->top - 1].right) {
			node = Pop_SqStack(S);
			if (start) {
				printf("%c",node.data);
				start = 0;
			}
			else {
				printf(" %c", node.data);
			}
			Push_SqStack(S, node.right[0]);
			Push_SqStack(S, node.left[0]);
		}
		else if (S->base[S->top - 1].left) {
			node = Pop_SqStack(S);
			if (start) {
				printf("%c", node.data);
				start = 0;
			}
			else {
				printf(" %c", node.data);
			}
			Push_SqStack(S, node.left[0]);
		}
		else if (S->base[S->top - 1].right) {
			node = Pop_SqStack(S);
			if (start) {
				printf("%c", node.data);
				start = 0;
			}
			else {
				printf(" %c", node.data);
			}
			Push_SqStack(S, node.right[0]);
		}
		else {
			node = Pop_SqStack(S);
			if (start) {
				printf("%c", node.data);
				start = 0;
			}
			else {
				printf(" %c", node.data);
			}
		}
	}
}