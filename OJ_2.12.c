#include <stdio.h>
#define LISTSIZE 100

typedef struct{
		char* base;
		int length;
		int listsize;
	}SqList;

int Init_SqList(SqList* L) {
	L->base = (int*)malloc(LISTSIZE * sizeof(char));
	if (!L->base) exit(0);
	L->length = 0;
	L->listsize = LISTSIZE;
	return 1;
}

void Add_Elem_SqList(char i, SqList* L) {
	L->base[L->length] = i;
	L->length++;
}

int Comp_SqList(SqList A, SqList B) {
	if (A.length == 0 && B.length == 0) {
		return 0;
	}
	else if (A.length == 0) {
		return 1;
	}
	else if (B.length == 0) {
		return 2;
	}
	else if (A.base[0] < B.base[0]) {
		return 1;
	}
	else if (A.base[0] > B.base[0]) {
		return 2;
	}
	else {
		A.base++;
		A.listsize--;
		A.length--;
		B.base++;
		B.listsize--;
		B.length--;
		return Comp_SqList(A, B);
	}
}

main() {
	SqList A, B;
	Init_SqList(&A);
	Init_SqList(&B);

	int i;
	char c, d;

	do {
		d = getchar();
		Add_Elem_SqList(d, &A);
		c = getchar();
	} while (c != '\n');
	do {
		d = getchar();
		Add_Elem_SqList(d, &B);
		c = getchar();
	} while (c != '\n');

	printf("%d", Comp_SqList(A, B));

}