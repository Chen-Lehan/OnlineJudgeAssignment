#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define ERROR -1
#define TElemType int

typedef struct BiTNode {
	TElemType data;
	struct BiTNode* left, * right;
}BiTree;

BiTree* Init_BiTree() {
	BiTree* T;
	if (!(T = (BiTree*)malloc(sizeof(BiTree))) ||
		!(T->left = (BiTree*)malloc(sizeof(BiTree))) ||
		!(T->right = (BiTree*)malloc(sizeof(BiTree))))
		exit(ERROR);
	T->left = NULL;
	T->right = NULL;
	return T;
}

void Reverse_BiTree(BiTree* T) {
	if (T) {
		Reverse_BiTree(T->left);
		Reverse_BiTree(T->right);
		BiTree* N;
		N = Init_BiTree();
		N = T->left;
		T->left = T->right;
		T->right = N;
	}
}

typedef struct Array {
	int* base;
	int length;
}Array;

Array* Init_Array(int length) {
	Array* array;
	if (!(array = (Array*)malloc(sizeof(Array))) ||
		!(array->base = (int*)malloc(MAXSIZE * sizeof(int))))
		exit(ERROR);
	array->length = 0;
	return array;
}

int Get_Array(Array* array) {
	char c;
	int data = 0, signal = 1, i = 0;
	do {
		c = getchar();
		switch (c) {
		case ' ': case '\n': case EOF:
			data = data * signal;
			array->base[i++] = data;
			array->length++;
			data = 0;
			signal = 1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			data = data * 10 + c - '0';
			break;

		case '-':
			signal = -1;
			break;

		default:break;
		}
	} while (c != '\n' && c != 'EOF');
	return i;
}

void Print_Array(Array* array) {
	int i;
	for (i = 0; i < array->length; i++) {
		if (i == 0)
			printf("%d", array->base[i]);
		else
			printf(" %d", array->base[i]);
	}
}

main() {
	Array* L, * R;
	L = Init_Array(MAXSIZE);
	R = Init_Array(MAXSIZE);
	Get_Array(L);
	Get_Array(R);
	Print_Array(R);
	printf("\n");
	Print_Array(L);
}