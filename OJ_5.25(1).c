#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define ElemType int
#define ERROR -1

typedef struct {
	int i, j;
	ElemType data;
}Tripple;

typedef struct {
	Tripple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix;

TSMatrix* Init_TSMatrix(int mu, int nu, int  tu) {
	TSMatrix* A;
	int i;
	if(!(A = (TSMatrix*)malloc(sizeof(TSMatrix))))
		exit(ERROR);
	A->mu = mu;
	A->nu = nu;
	A->tu = tu;
	for (i = 0; i <= A->tu; i++) {
		A->data[i].data = 0;
	}
	return A;
}

void GetLocfB(TSMatrix* A) {
	int m, n;
	m = A->mu;
	n = A->nu;
	int i, j, data;
	for (j = 0, i = 0; j < m*n; j++) {
		scanf("%d", &data);
		if (data != 0) {
			A->data[i].i = j / n;
			A->data[i].j = j % n;
			i++;
		}
	}
}

TSMatrix* Add_TSMatrix(TSMatrix* A, TSMatrix* B) {
	TSMatrix* C;
	C = Init_TSMatrix(A->mu, A->nu, 0);
	int p, q, comp;	
	//comp为0时表示A->data[p]与B->data[q]指向同一位置，为1表示A->data[p]坐标小于B->data[q]，为-1表示A->data[p]坐标大于B->data[q]
	
	for (p = 0, q = 0, comp=0; p < A->tu && q < B->tu;) {
		if (A->data[p].i < B->data[q].i) {
			C->data[C->tu] = A->data[p];
			C->tu++;
			p++;
			comp = 1;
		}
		else if (A->data[p].i > B->data[q].i) {
			C->data[C->tu] = B->data[q];
			C->tu++;
			q++;
			comp = -1;
		}
		else {
			if (A->data[p].j < B->data[q].j) {
				C->data[C->tu] = A->data[p];
				C->tu++;
				p++;
				comp = 1;
			}
			else if (A->data[p].j > B->data[q].j) {
				C->data[C->tu] = B->data[q];
				C->tu++;
				q++;
				comp = -1;
			}
			else {
				C->data[C->tu] = A->data[p];
				C->data[C->tu].data += B->data[q].data;
				p++;
				q++;
				if (C->data[C->tu].data != 0) {
					C->tu++;
				}
				else {
					C->data[C->tu].i = C->mu;
					C->data[C->tu].j = C->nu;
				}
				comp = 0;
			}
		}
	}
	while (p < A->tu) {
		C->data[C->tu++] = A->data[p++];
	}
	while (q < B->tu) {
		C->data[C->tu++] = B->data[q++];
	}
	return C;
}

void Print_TSMatrix(TSMatrix* C) {
	int i, j, k;
	for (i = 0; i < C->tu; i++) {
		if (i == 0) {
			printf("%d", C->data[i].data);
		}
		else {
			printf(" %d", C->data[i].data);
		}
	}
	for (i = 0, k = 0; i < C->mu; i++) {
		for (j = 0; j < C->nu; j++) {
			if (j == 0) {
				printf("\n");
			}
			if (C->data[k].i == i && C->data[k].j == j) {
				if (j == 0) {
					printf("1");
				}
				else {
					printf(" 1");
				}
				k++;
			}
			else {
				if (j == 0) {
					printf("0");
				}
				else {
					printf(" 0");
				}
			}
		}
	}
}

main() {
	int m1, n1;
	char c;
	scanf("%d%d", &m1, &n1);
	getchar();

	TSMatrix* A, * B;
	A = Init_TSMatrix(m1, n1, 0);
	B = Init_TSMatrix(m1, n1, 0);
	int signal = 1;
	while (c = getchar()) {
		switch (c) {
		case '-':
			signal = -1;
			break;
		
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			A->data[A->tu].data = A->data[A->tu].data * 10 + c - '0';
			break;

		case ' ': case '\n':
			A->data[A->tu++].data *= signal;
			signal = 1;
			A->data[A->tu].data = 0;
			break;

		default:
			exit(ERROR);
		}

		if (c == '\n')
			break;
	}
	GetLocfB(A);
	getchar();

	signal = 1;
	while (c = getchar()) {
		switch (c) {
		case '-':
			signal = -1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			B->data[B->tu].data = B->data[B->tu].data * 10 + c - '0';
			break;

		case ' ': case '\n':
			B->data[B->tu++].data *= signal;
			signal = 1;
			B->data[B->tu].data = 0;
			break;

		default:
			exit(ERROR);
		}

		if (c == '\n')
			break;
	}
	GetLocfB(B);

	TSMatrix* C;
	C = Add_TSMatrix(A, B);

	Print_TSMatrix(C);
}

/*
****************************
**    算法的时间复杂度估计    *
****************************
* 获取V矩阵的时间复杂度为O(tu)
* 获取B矩阵的时间复杂度为O(m*n)
* 矩阵加法的时间复杂度为O(tu)
* 打印矩阵的时间复杂度为O(m*n)
*/