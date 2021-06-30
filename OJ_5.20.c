#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define ElemType int

typedef struct {
	int height;
	int width;
	ElemType** base;
}Matrix2D;

Matrix2D* Init_Matrix2D(int height, int width) {
	Matrix2D* M;
	if (height < 1 || width < 1)
		exit(ERROR);

	if (!(M = (Matrix2D*)malloc(sizeof(Matrix2D))) ||
		!(M->base = (ElemType**)malloc(height * sizeof(ElemType*))))
		exit(ERROR);

	int i;
	for (i = 0; i < height; i++) {
		if (!(M->base[i] = (ElemType*)malloc(width * sizeof(ElemType))))
			exit(ERROR);
	}

	M->height = height;
	M->width = width;
	return M;
}

void Assign_Matrix2D(Matrix2D* M) {
	int i, j;
	for (i = 0; i < M->height; i++) {
		for (j = 0; j < M->width; j++) {
			scanf("%d", &M->base[i][j]);
		}
	}
}

main() {
	Matrix2D* M;
	int height, width;
	scanf("%d%d", &height, &width);
	M = Init_Matrix2D(height, width);
	Assign_Matrix2D(M);
	
	int i, j, start = 1;
	for (i = height - 1; i >= 0; i--) {
		for (j = width - 1; j >= 0; j--) {
			switch (M->base[i][j]) {
			case 0:
				break;

			case 1:
				if (i + j == 0) {
					if (start)
						printf("1");
					else
						printf("+1");
				}
				else if (i == 0) {
					if (start)
						printf("yE%d", j);
					else
						printf("+yE%d", j);
				}
				else if (j == 0) {
					if (start)
						printf("xE%d", i);
					else
						printf("+xE%d", i);
				}
				else {
					if (start)
						printf("xE%dyE%d", i, j);
					else
						printf("+xE%dyE%d", i, j);
				}
				start = 0;
				break;

			default:
				if (i + j == 0) {
					if (start)
						printf("%d",M->base[i][j]);
					else
						printf("+%d", M->base[i][j]);
				}
				else if (i == 0) {
					if (start)
						printf("%dyE%d", M->base[i][j], j);
					else
						printf("+%dyE%d", M->base[i][j], j);
				}
				else if (j == 0) {
					if (start)
						printf("%dxE%d", M->base[i][j], i);
					else
						printf("+%dxE%d", M->base[i][j], i);
				}
				else {
					if (start)
						printf("%dxE%dyE%d", M->base[i][j], i, j);
					else
						printf("+%dxE%dyE%d", M->base[i][j], i, j);
				}
				start = 0;
				break;
			}
		}
	}
}