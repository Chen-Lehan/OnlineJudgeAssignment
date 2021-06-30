#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define ERROR -1

typedef struct Array{
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

int IsSon(int u, int v, Array* L, Array* R) {
	if (u && v) {
		if (L->base[v] == u || R->base[v] == u)
			return 1;
		else
			return(IsSon(u, L->base[v], L, R) || IsSon(u, R->base[v], L, R));
	}
	return 0;
}

main() {
	int u, v;
	Array* L, * R;
	L = Init_Array(MAXSIZE);
	R = Init_Array(MAXSIZE);
	Get_Array(L);
	Get_Array(R);
	scanf("%d%d", &u, &v);
	printf("%d", IsSon(u, v, L, R));
}