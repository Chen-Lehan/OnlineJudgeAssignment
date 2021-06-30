#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define TElemType int
#define MAXSIZE 100

typedef enum {Link, Thread} PointerThr;

typedef struct BiThrNode {
	TElemType data;
	PointerThr Ltag, Rtag;
	struct BiThrNode* left, * right;
}BiThrTree, BiThrNode;

void Del_Thread(BiThrTree* T) {
	if (T->Ltag == Link)
		Del_Thread(T->left);
	else
		T->left = NULL;
	if (T->Rtag == Link)
		Del_Thread(T->right);
	else
		T->right = NULL;
}

void Print_BiThrTree(BiThrTree** base, int n) {
	int i;
	printf("1");
	for (i = 0; i < n; i++) {
		if (base[i]->left)
			printf(" %d", base[i]->left->data);
		else
			printf(" 0");
	}
	printf("\n");
	printf("1");
	for (i = 0; i < n; i++) {
		if (base[i]->right)
			printf(" %d", base[i]->right->data);
		else
			printf(" 0");
	}
}

BiThrTree** Get_BiThrTree(int n) {
	BiThrTree** base;
	int i, left, right, preroot;
	int mentioned[15];

	if (n <= 0)
		exit(ERROR);

	if (!(base = (BiThrTree**)malloc(n * sizeof(BiThrTree*))))
		exit(ERROR);
	for (i = 0; i < n; i++) {
		mentioned[i] = 0;
		if(!(base[i] = (BiThrTree*)malloc(sizeof(BiThrTree))))
			exit(ERROR);
	}

	for (i = 0; i < n; i++) {
		scanf("%d%d%d", &base[i]->data, &left, &right);
		if (mentioned[i] == 0) {
			if (i == 0)
				preroot = i;
			else {
				base[preroot]->right = base[i];
				base[preroot]->Rtag = Link;
				preroot = i;
			}
		}
		if (left) {
			base[i]->left = base[left - 1];
			base[i]->Ltag = Link;
			mentioned[left - 1] = 1;
		}
		else {
			base[i]->Ltag = Thread;
			base[i]->left = NULL;
		}
		if (right) {
			base[i]->right = base[right - 1];
			base[i]->Rtag = Link;
			mentioned[right - 1] = 1;
		}
		else {
			base[i]->Rtag = Thread;
			base[i]->right = NULL;
		}
	}
	return base;
}

BiThrNode* pre;

void Preorder_PreThreading(BiThrTree* T) {
	if (T->Ltag == Link) {
		pre = T;
		Preorder_PreThreading(T->left);
	}
	else {
		T->left = pre;
		pre = T;
	}
	if (T->Rtag == Link) {
		Preorder_PreThreading(T->right);
	}
}

void Inorder_Threading(BiThrTree* T) {
	if (T->Ltag == Link)
		Inorder_Threading(T->left);
	else
		T->left = pre;
	if (pre && pre->Rtag == Thread)
		pre->right = T;
	pre = T;
	if (T->Rtag == Link)
		Inorder_Threading(T->right);
}

void Postorder_PostThreading(BiThrTree* T) {
	if (T->Ltag == Link)
		Postorder_PostThreading(T->left);
	if (T->Rtag == Link)
		Postorder_PostThreading(T->right);
	if (pre && pre->Rtag == Thread) {
		pre->right = T;
	}
	pre = T;
}

main() {
	BiThrTree** base;
	int n;
	scanf("%d", &n);
	base = Get_BiThrTree(n);
	pre = NULL;
	Preorder_PreThreading(base[0]);
	Print_BiThrTree(base, n);
	printf("\n");
	Del_Thread(base[0]);

	pre = NULL;
	Inorder_Threading(base[0]);
	Print_BiThrTree(base, n);
	printf("\n");
	Del_Thread(base[0]);

	pre = NULL;
	Postorder_PostThreading(base[0]);
	Print_BiThrTree(base, n);
}