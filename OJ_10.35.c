#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define HEAPSIZE 40

typedef struct TriTreeNode {
	int data;
	struct TriTreeNode* left, * mid, * right;
}TriTreeNode,*TriTree;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Build_Heap(TriTreeNode* base[HEAPSIZE], int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		if (!(base[i]->left = (TriTreeNode*)malloc(sizeof(TriTreeNode))) ||
			!(base[i]->mid = (TriTreeNode*)malloc(sizeof(TriTreeNode))) ||
			!(base[i]->right = (TriTreeNode*)malloc(sizeof(TriTreeNode))))
			exit(ERROR);
	}

	for (i = 0, j = 1; i < size; i++) {
		if (j < size)
			base[i]->left = base[j++];
		else
			base[i]->left = NULL;
		if (j < size)
			base[i]->mid = base[j++];
		else
			base[i]->mid = NULL;
		if (j < size)
			base[i]->right = base[j++];
		else
			base[i]->right = NULL;
	}
}

void Init_Heap(TriTreeNode* node) {
	if (node) {
		if (node->right) {
			if (node->left->data <= node->mid->data && node->left->data <= node->right->data) {
				if (node->left->data < node->data) {
					swap(&node->left->data, &node->data);
					Init_Heap(node->left);
				}
			}
			else if (node->mid->data <= node->left->data && node->mid->data <= node->right->data) {
				if (node->mid->data < node->data) {
					swap(&node->mid->data, &node->data);
					Init_Heap(node->mid);
				}
			}
			else if (node->right->data <= node->left->data && node->right->data <= node->mid->data) {
				if (node->right->data < node->data) {
					swap(&node->right->data, &node->data);
					Init_Heap(node->right);
				}
			}
		}
		else if (node->mid) {
			if (node->left->data <= node->mid->data) {
				if (node->left->data < node->data) {
					swap(&node->left->data, &node->data);
					Init_Heap(node->left);
				}
			}
			else if (node->mid->data <= node->left->data) {
				if (node->mid->data < node->data) {
					swap(&node->mid->data, &node->data);
					Init_Heap(node->mid);
				}
			}
		}
		else if (node->left) {
			if (node->left->data < node->data) {
				swap(&node->left->data, &node->data);
				Init_Heap(node->left);
			}
		}	
	}
}

main() {
	TriTreeNode* base[HEAPSIZE];
	int i;
	for (i = 0; i < HEAPSIZE; i++) {
		if (!(base[i] = (TriTreeNode*)malloc(sizeof(TriTreeNode))))
			exit(ERROR);
	}
	char c;
	int data = 0;
	int sign = 1;
	int length = 0;
	while (c = getchar()) {
		switch (c) {
		case '-':
			sign = -1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			data = data * 10 + c - '0';
			break;

		case ' ': case '\n': {
			data = data * sign;
			base[length++]->data = data;
			data = 0;
			sign = 1;
			break;
		}
		}
		if (c == '\n')
			break;
	}
	Build_Heap(base, length);
	for (i = length - 1; i >= 0; i--) {
		Init_Heap(base[i]);
	}

	if (length == 0)
		exit(ERROR);

	while(length > 0) {
		printf("%d", base[0]->data);
		swap(&base[0]->data, &base[--length]->data);
		int j = (length - 1) / 3;
		int k = (length - 1) % 3;
		switch (k) {
		case 0:
			base[j]->left = NULL;
			break;

		case 1:
			base[j]->mid = NULL;
			break;

		case 2:
			base[j]->right = NULL;
			break;
		}
		Init_Heap(base[0]);
		if (length != 0)
			printf(" ");
	}
}