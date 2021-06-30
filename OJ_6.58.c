#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define MAXSIZE 100
#define TElemType int

typedef enum { Link, Thread } PointerThr;

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

typedef struct BiThrNode {
	TElemType data;
	PointerThr ltag, rtag;
	struct BiThrNode* left, * right;
}BiThrTree;

BiThrTree* pre;

BiThrTree* Init_BiThrTree() {
	BiThrTree* T;
	if (!(T = (BiThrTree*)malloc(sizeof(BiThrTree))) ||
		!(T->left = (BiThrTree*)malloc(sizeof(BiThrTree))) ||
		!(T->right = (BiThrTree*)malloc(sizeof(BiThrTree))))
		exit(ERROR);
	T->left = NULL;
	T->right = NULL;
	return T;
}

void InThreading(BiThrTree* T) {
	if (T) {
		InThreading(T->left);
		if (!T->left) {
			T->ltag = Thread;
			T->left = pre;
		}
		if (!pre->right) {
			pre->rtag = Thread;
			pre->right = T;
		}
		pre = T;
		InThreading(T->right);
	}
}

BiThrTree* Inorder_Threading(BiThrTree* T) {
	BiThrTree* Thrt;
	if (!(Thrt = (BiThrTree*)malloc(sizeof(BiThrTree))))
		exit(ERROR);

	Thrt->ltag = Link;
	Thrt->rtag = Thread;
	Thrt->right = Thrt;
	if (!T)
		Thrt->left = Thrt;
	else {
		pre = Init_BiThrTree();
		Thrt->left = T;
		pre = Thrt;
		InThreading(T);
		pre->right = Thrt;
		pre->rtag = Thread;
		Thrt->right = pre;
	}
	return(Thrt);
}

BiThrTree** Assign_BiTree(Array* L, Array* R) {
	int* data, i, j;
	int n = L->length - 1;
	if (L->length != R->length || L->base[0] != R->base[0])
		exit(ERROR);

	if (!(data = (int*)malloc((L->length - 1.0) * sizeof(int))))
		exit(ERROR);

	for (i = 0, j = 0; i < L->length - 1, j < L->length - 1;) {
		if (j == 0) {
			data[i++] = L->base[j++];
		}
		else {
			if (L->base[j] != 0) {
				data[i++] = L->base[j];
			}
			if (R->base[j] != 0) {
				data[i++] = R->base[j];
			}
			j++;
		}

	}//获取L与R数组中的元素

	if (L->length < 1)
		exit(ERROR);
	else if (L->length == 2) {
		BiThrTree** T;
		if (!(T = (BiThrTree**)malloc(sizeof(BiThrTree*))) ||
			!(T[0] = (BiThrTree*)malloc(sizeof(BiThrTree))) ||
			!(T[0]->left = (BiThrTree*)malloc(sizeof(BiThrTree))) ||
			!(T[0]->right = (BiThrTree*)malloc(sizeof(BiThrTree))))
			exit(ERROR);
		T[0]->data = L->base[0];
		T[0]->ltag = Thread;
		T[0]->rtag = Thread;
		T[0]->left = NULL;
		T[0]->right = NULL;
		return T;
	}
	else if (L->length > 2) {
		BiThrTree** T;
		if (!(T = (BiThrTree**)malloc((L->length - 1.0) * sizeof(BiThrTree*))))
			exit(ERROR);

		for (i = 0; i < n; i++) {
			if (!(T[i] = (BiThrTree*)malloc(sizeof(BiThrTree))) ||
				!(T[i]->left = (BiThrTree*)malloc(sizeof(BiThrTree))) ||
				!(T[i]->left = (BiThrTree*)malloc(sizeof(BiThrTree))))
				exit(ERROR);
			T[i]->data = data[i];
		}

		for (i = 1; i < L->length; i++) {
			if (L->base[i] == 0) {
				T[i - 1]->ltag = Thread;
				T[i - 1]->left = NULL;
			}
			else {
				for (j = 0; j < n; j++) {
					if (T[j]->data == L->base[i]) {
						T[i - 1]->ltag = Link;
						T[i - 1]->left = T[j];
						break;
					}
				}
			}
		}

		for (i = 1; i < R->length; i++) {
			if (R->base[i] == 0) {
				T[i - 1]->rtag = Thread;
				T[i - 1]->right = NULL;
			}
			else {
				for (j = 0; j < n; j++) {
					if (T[j]->data == R->base[i]) {
						T[i - 1]->rtag = Link;
						T[i - 1]->right= T[j];
						break;
					}
				}
			}
		}
		return T;
	}
	else
		exit(ERROR);
}

void Inorder_Print_BiThrTree(BiThrTree* Thrt) {
	BiThrTree* p;
	for (p = Thrt; p->ltag == Link; p = p->left);
	printf("%d", p->data);
	for (p = p->right; p != Thrt;) {
		printf(" %d", p->data);
		if (p->rtag == Link) {
			p = p->right;
			while (p->ltag == Link)
				p = p->left;
		}
		else {
			p = p->right;
		}
	}
}

main() {
	int p, i, j;
	Array* L1, * R1;
	Array* L2, * R2;
	BiThrTree** T1, ** T2;
	L1 = Init_Array(MAXSIZE);
	R1 = Init_Array(MAXSIZE);
	L2 = Init_Array(MAXSIZE);
	R2 = Init_Array(MAXSIZE);
	Get_Array(L1);
	Get_Array(R1);
	T1 = Assign_BiTree(L1, R1);
	scanf("%d", &p);
	getchar();
	Get_Array(L2);
	Get_Array(R2);
	T2 = Assign_BiTree(L2, R2);

	for (i = 0; i < L1->length - 1; i++) {
		if (T1[i]->data == p) {
			T2[0]->right = T1[i]->left;
			T1[i]->left = T2[0];

			if (T1[i]->left)
				T2[0]->rtag = Link;
			else
				T2[0]->rtag = Thread;

			if (T2[0])
				T1[i]->ltag = Link;
			else
				T1[i]->ltag = Thread;

			break;
		}
	}

	BiThrTree* Thrt = Inorder_Threading(T1[0]);
	Inorder_Print_BiThrTree(Thrt);
}