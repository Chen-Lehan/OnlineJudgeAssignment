#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define ElemType int
#define MAXLENGTH 10

typedef struct {
	ElemType** base;
	int size;
}Matrix2D;

Matrix2D* Init_Matrix2D(int size) {
	int i;
	Matrix2D* M;
	if (!(M = (Matrix2D*)malloc(sizeof(Matrix2D))))
		exit(ERROR);
	M->size = size;
	if (M->size <= 0)
		exit(ERROR);
	if (!(M->base = (ElemType**)malloc(M->size * sizeof(ElemType*))))
		exit(ERROR);
	for (i = 0; i < M->size; i++) {
		if (!(M->base[i] = (ElemType*)malloc(M->size * sizeof(ElemType))))
			exit(ERROR);
	}
	return M;
}

Matrix2D* Get_Matrix2D() {
	int i, j, size;
	Matrix2D* M;
	scanf("%d", &size);
	M = Init_Matrix2D(size);

	for (i = 0; i < M->size; i++) {
		for (j = 0; j < M->size; j++) {
			scanf("%d", &M->base[i][j]);
		}
	}

	return M;
}

void Print_Matrix2D(Matrix2D* M) {
	int i, j;
	for (i = 0; i < M->size; i++) {
		for (j = 0; j < M->size; j++) {
			printf("%d", M->base[i][j]);
			if (j != M->size - 1)
				printf(" ");
		}
		if (i != M->size - 1)
			printf("\n");
	}
}

Matrix2D* Del_Vex(Matrix2D* M, int vex) {
	Matrix2D* N;
	N = Init_Matrix2D(M->size - 1);
	if (vex < 0 || vex >= M->size)
		exit(ERROR);
	int i, j, k, l;
	for (i = 0, k = 0; i < M->size; i++) {
		if (i != vex) {
			for (j = 0, l = 0; j < M->size; j++) {
				if (j != vex) {
					N->base[k][l] = M->base[i][j];
					l++;
				}
			}
			k++;
		}
	}
	return N;
}

Matrix2D* Ins_Vex(Matrix2D* M, int vex) {
	Matrix2D* N;
	N = Init_Matrix2D(M->size + 1);
	if (vex < 0 || vex >= M->size)
		exit(ERROR);
	int i, j, k, l;
	for (i = 0, k = 0; i < M->size; k++) {
		if (k != vex) {
			for (j = 0, l = 0; j < M->size; l++) {
				if (l != vex) {
					N->base[k][l] = M->base[i][j];
					j++;
				}
				else {
					N->base[k][l] = 0;
				}
			}
			i++;
		}
		else {
			for (l = 0; l < N->size; l++) {
				N->base[k][l] = 0;
			}
		}
	}
	return N;
}

void Del_Arc(Matrix2D* M, int vex1, int vex2) {
	M->base[vex1][vex2] = 0;
	M->base[vex2][vex1] = 0;
}

void Ins_Arc(Matrix2D* M, int vex1, int vex2) {
	M->base[vex1][vex2] = 1;
	M->base[vex2][vex1] = 1;
}

int getline(char s[]) {
	int  c, i;

	for (i = 0; i < MAXLENGTH - 1 && (c = getchar()) != EOF && c != '\n' && c != ' '; i++) {
		s[i] = c;
	}

	if (c == '\n') {
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

main() {
	Matrix2D* M;
	int vex1, vex2;
	M = Get_Matrix2D();
	char s[MAXLENGTH];
	while (getline(s)) {
		if (s[0] == 'D') {
			if(s[1] == 'V'){
				scanf("%d",&vex1);
				M = Del_Vex(M, vex1);
				getchar();
			}
			else if (s[1] == 'A') {
				scanf("%d%d", &vex1, &vex2);
				Del_Arc(M, vex1, vex2);
				getchar();
			}
		}
		else if (s[0] == 'I') {
			if (s[1] == 'V') {
				scanf("%d", &vex1);
				M = Ins_Vex(M, vex1);
				getchar();
			}
			else if (s[1] == 'A') {
				scanf("%d%d", &vex1, &vex2);
				Ins_Arc(M, vex1, vex2);
				getchar();
			}
		}
	}
	Print_Matrix2D(M);
}