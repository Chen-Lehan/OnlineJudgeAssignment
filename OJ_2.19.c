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

int Rm_Sec_SqList(int from, int to, SqList* L) {
	int i, j, l;
	l = L->length;
	for (i = 0, j = 0; j < l; j++) {
		if (L->base[j] < to && L->base[j] > from) {
			L->length--;
		}
		else {
			L->base[i] = L->base[j];
			i++;
		}
	}
}

main() {
	SqList A;
	int d, from, to;
	char c;
	Init_SqList(LISTSIZE, &A);

	do {
		scanf("%d", &d);
		c = getchar();
		Add_Elem_SqList(d, &A);
	} while (c != '\n');

	scanf("%d %d", &from, &to);
	Rm_Sec_SqList(from, to, &A);

	for (d = 0; d < A.length; d++) {
		if (d == 0) {
			printf("%d", A.base[d]);
		}
		else {
			printf(" %d", A.base[d]);
		}
	}
}