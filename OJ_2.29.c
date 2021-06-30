#include <stdio.h>
#include <stdlib.h>
#define LISTSIZE 100

typedef struct {
	char* base;
	int length;
	int listsize;
}SqList;

void Init_SqList(SqList* L) {
	L->base = (char*)malloc(LISTSIZE * sizeof(char));
	L->length = 0;
	L->listsize = LISTSIZE;
}

void Add_Elem_SqList(char c, SqList* L) {
	if (L->length < L->listsize) {
		L->base[L->length] = c;
		L->length++;
	}
}

void Rm_SqList(int i, SqList* L) {
	int j;
	for (j = i; j < (L->length - 1); j++) {
		L->base[j] = L->base[j + 1];
	}
	L->length--;
}

void Intsc_SqList(SqList A, SqList B, SqList* C) {
	int i, j;
	for (i = 0, j = 0; i < A.length && j < B.length;) {
		if (A.base[i] == B.base[j]) {
			Add_Elem_SqList(A.base[i], C);
			j++;
			i++;
		}
		else if (A.base[i] > B.base[j]) {
			j++;
		}
		else if (A.base[i] < B.base[j]) {
			i++;
		}
	}
}

void Diff_SqList(SqList* A, SqList B) {
	int i, j;
	int l = A->length;
	for (i = 0, j = 0; i < A->length && j < B.length;) {
		if (A->base[i] == B.base[j]) {
			Rm_SqList(i, A);
		}
		else if (A->base[i] > B.base[j]) {
			j++;
		}
		else if (A->base[i] < B.base[j]) {
			i++;
		}
	}
}

main() {
	SqList A, B, C, D;
	int i;
	char c;
	Init_SqList(&A);
	Init_SqList(&B);
	Init_SqList(&C);
	Init_SqList(&D);

	do {
		c = getchar();
		Add_Elem_SqList(c, &A);
		c = getchar();
	} while (c != '\n');
	
	do {
		c = getchar();
		Add_Elem_SqList(c, &B);
		c = getchar();
	} while (c != '\n');
	
	do {
		c = getchar();
		Add_Elem_SqList(c, &C);
		c = getchar();
	} while (c != '\n');

	Intsc_SqList(B, C, &D);
	Diff_SqList(&A, D);

	if (A.length == 0) {
		printf("NULL");
	}
	else {
		for (i = 0; i < A.length; i++) {
			if (i == 0) {
				printf("%c", A.base[i]);
			}
			else {
				printf(",%c", A.base[i]);
			}
		}
	}
}