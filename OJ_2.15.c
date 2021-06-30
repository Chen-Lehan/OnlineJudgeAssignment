#include <stdio.h>

typedef struct {
	int* base;
	int length;
	int listsize;
}SqList;

void Add_Elem_SqList(int i, SqList* L) {
	L->base[L->length] = i;
	L->length++;
}

int Init_SqList(int listsize, SqList* L) {
	L->base = (int*)malloc(listsize * sizeof(int));
	if (!L->base) exit(0);
	L->length = 0;
	L->listsize = listsize;
	return 1;
}

void Merge_SqList(SqList A, SqList B, SqList* C) {
	int i;
	Init_SqList(A.listsize + B.listsize, C);
	for (i = 0; i < A.length; i++) {
		Add_Elem_SqList(A.base[i], C);
	}
	for (i = 0; i < B.length; i++) {
		Add_Elem_SqList(B.base[i], C);
	}
}

main() {
	SqList A, B, C;
	int A_size, B_size, d;
	char c;
	scanf("%d %d", &A_size, &B_size);
	getchar();
	Init_SqList(A_size, &A);
	Init_SqList(B_size, &B);

	do {
		scanf("%d", &d);
		c = getchar();
		Add_Elem_SqList(d, &A);
	} while (c != '\n');
	do {
		scanf("%d", &d);
		c = getchar();
		Add_Elem_SqList(d, &B);
	} while (c != '\n');

	Merge_SqList(B, A, &C);
	for (d = 0; d < C.length; d++) {
		if (d == 0) {
			printf("%d", C.base[d]);
		}
		else {
			printf(" %d", C.base[d]);
		}
	}
}