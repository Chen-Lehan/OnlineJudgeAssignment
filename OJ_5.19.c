#include <stdio.h>
#include <stdlib.h>
#define ElemType int

typedef struct {
	ElemType* base;
	int top;
	int length;
}SqStack;

typedef struct Matrix2D {
	ElemType** base;
	int height;
	int width;
}Matrix2D;

SqStack* Init_SqStack(int length) {
	SqStack* s;
	s = (SqStack*)malloc(sizeof(SqStack));
	s->base = (ElemType*)malloc(length * sizeof(ElemType));
	s->length = length;
	s->top = 0;
	return s;
}

void Clear_SqStack(SqStack* s) {
	s->top = 0;
}

void Push_SqStack(SqStack* s, ElemType data) {
	s->base[s->top++] = data;
}

ElemType Pop_SqStack(SqStack* s) {
	return s->base[--s->top];
}

Matrix2D* Init_Matrix(int height, int width) {
	Matrix2D* matrix;
	matrix = (Matrix2D*)malloc(sizeof(Matrix2D));
	matrix->base = (ElemType**)malloc(height * 16 * sizeof(ElemType*));
	int i;
	for (i = 0; i < height; i++) {
		matrix->base[i] = (ElemType*)malloc(width * sizeof(ElemType));
	}
	return matrix;
}

main() {
	int height, width;
	scanf("%d%d", &height, &width);
	getchar();

	Matrix2D* matrix;
	matrix = Init_Matrix(height, width);

	int i, j, k, count = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			scanf("%d", &matrix->base[i][j]);
		}
		getchar();
	}

	int* maxln;
	int max;
	SqStack* s;
	maxln = (int*)malloc(height * sizeof(int));
	s = Init_SqStack(height);
	for (i = 0; i < height; i++) {
		maxln[i] = matrix->base[i][0];
		for (j = 0; j < width - 1; j++) {
			if (maxln[i] > matrix->base[i][j + 1]) {
				maxln[i] = matrix->base[i][j + 1];
			}
		}
	}
	for (i = 0, max = maxln[0]; i < height; i++) {
		if (max < maxln[i]) {
			Clear_SqStack(s);
			Push_SqStack(s, i);
			max = maxln[i];
		}
		else if (max == maxln[i]) {
			Push_SqStack(s, i);
		}
	}

	do {
		i = Pop_SqStack(s);
		for (j = 0; j < width; j++) {
			if (matrix->base[i][j] != max) {
				continue;
			}
			for (k = 0; k < height; k++) {
				if (matrix->base[i][j] < matrix->base[k][j]) {
					count--;
					break;
				}
			}
			count++;
		}
	} while (s->top != 0);

	for (i = 0; i < count; i++) {
		if (i == 0) {
			printf("%d", max);
		}
		else {
			printf(" %d", max);
		}
	}
}