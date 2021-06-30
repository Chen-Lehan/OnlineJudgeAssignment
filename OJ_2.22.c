#include <stdio.h>
#define LISTSIZE 200

typedef struct {
	char* base;
	int length;
	int listsize;
}SqList;

void Add_Elem_SqList(char i, SqList* L) {
	L->base[L->length] = i;
	L->length++;
}

int Init_SqList(int listsize, SqList* L) {
	L->base = (int*)malloc(listsize * sizeof(char));
	if (!L->base) exit(0);
	L->length = 0;
	L->listsize = listsize;
	return 1;
}

int Reverse_SqList(SqList* L) {
	int i, j;
	char k;
	for (i = 0, j = L->length - 1; i < j; i++, j--) {
		k = L->base[i];
		L->base[i] = L->base[j];
		L->base[j] = k;
	}
}

main() {
	SqList A;
	int i;
	char c;
	Init_SqList(LISTSIZE, &A);

	do {
		c = getchar();
		Add_Elem_SqList(c, &A);
		c = getchar();
	} while (c != '\n');

	Reverse_SqList(&A);

	for (i = 0; i < A.length; i++) {
		if (i == 0) {
			printf("%c", A.base[i]);
		}
		else {
			printf(",%c", A.base[i]);
		}
	}
}