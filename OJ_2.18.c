#include <stdio.h>
#define LISTSIZE 200

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

void Rm_SqList(int i, SqList* L) {
	int j;
	for (j = i; j < (L->length - 1); j++) {
		L->base[j] = L->base[j + 1];
	}
	L->length--;
}

main() {
	SqList A;
	int d;
	char c;
	Init_SqList(LISTSIZE, &A);
	
	do {
		scanf("%d", &d);
		c = getchar();
		Add_Elem_SqList(d, &A);
	} while (c != '\n');

	scanf("%d", &d);
	Rm_SqList(d, &A);
	if (A.length == 0) {
		printf("NULL");
	}
	else {
		for (d = 0; d < A.length; d++) {
			if (d == 0) {
				printf("%d", A.base[d]);
			}
			else {
				printf(" %d", A.base[d]);
			}
		}
	}
}