#include <stdio.h>
#include <stdlib.h>
#define ElemType int
#define MAXSIZE 100
#define ERROR -1

typedef struct OLNode {
	int i, j;
	ElemType data;
	struct OLNode* right, * down;
}OLNode, * Olink;

typedef struct {
	Olink* rhead, * chead;
	int mu, nu, tu;
}OLList;

OLList* Init_OLList(int mu, int nu, int tu) {
	OLList* M;
	int i;
	if (mu < 0 || nu < 0)
		exit(ERROR);
	else if (mu == 0 || nu == 0)
		M = NULL;
	else {
		if (!(M = (OLList*)malloc(sizeof(OLList))) ||
			!(M->rhead = (Olink*)malloc((mu + 1.0) * sizeof(Olink))) ||
			!(M->chead = (Olink*)malloc((nu + 1.0) * sizeof(Olink))))
			exit(ERROR);
		M->mu = mu;
		M->nu = nu;
		M->tu = tu;
		for (i = 0; i < M->mu; i++) {
			if (!(M->rhead[i] = (OLNode*)malloc(sizeof(OLNode))) ||
				!(M->rhead[i]->right = (OLNode*)malloc(sizeof(OLNode))) ||
				!(M->rhead[i]->down = (OLNode*)malloc(sizeof(OLNode))))
				exit(ERROR);

			M->rhead[i]->right = NULL;
			M->rhead[i]->i = i;
			M->rhead[i]->j = -1;
			if (i != 0)
				M->rhead[i - 1]->down = M->rhead[i];
			if (i == M->mu - 1)
				M->rhead[i]->down = NULL;
		}

		for (i = 0; i < M->nu; i++) {
			if (!(M->chead[i] = (OLNode*)malloc(sizeof(OLNode))) ||
				!(M->chead[i]->right = (OLNode*)malloc(sizeof(OLNode))) ||
				!(M->chead[i]->down = (OLNode*)malloc(sizeof(OLNode))))
				exit(ERROR);

			M->chead[i]->down = NULL;
			M->chead[i]->j = i;
			M->chead[i]->i = -1;
			if (i != 0)
				M->chead[i - 1]->right = M->chead[i];
			if (i == M->nu - 1)
				M->chead[i]->right = NULL;
		}
	}
	
	return M; 
}

void Assign_OLList(OLList* M, int V[]) {
	int m, n, data;
	for (m = 0, M->tu = 0; m < M->mu; m++) {
		for (n = 0; n < M->nu; n++) {
			scanf("%d", &data);
			if (data == 0)
				continue;
			else if (data == 1) {
				OLNode* node, * p;
				if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->down = (OLNode*)malloc(sizeof(OLNode))))
					exit(ERROR);
				node->data = V[M->tu++];
				node->down = NULL;
				node->right = NULL;
				node->i = m;
				node->j = n;

				for (p = M->chead[n]; p->down; p = p->down);
				p->down = node;
				for (p = M->rhead[m]; p->right; p = p->right);
				p->right = node;
			}
			else
				exit(ERROR);
		}
	}
}

OLList* Add_OLList(OLList* A, OLList* B) {
	OLList* C;
	C = Init_OLList(A->mu, A->nu, 0);

	OLNode* p, * q, * r;
	int comp, i = 0;
	//comp为0时表示p与q指向同一位置，为1表示p坐标小于q，为-1表示p坐标大于q

	for (p = A->rhead[i]->right, q = B->rhead[i]->right, comp = 0; i < A->mu;) {
		p = A->rhead[i]->right;
		q = B->rhead[i]->right;
		for (; p && q;) {
			if (p->i > q->i) {
				/*OLNode* node;
				if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->down = (OLNode*)malloc(sizeof(OLNode))))
					exit(ERROR);
				node->data = q->data;
				node->i = q->i;
				node->j = q->j;
				node->down = NULL;
				node->right = NULL;

				for (r = C->chead[node->j]; r->down; r = r->down);
				r->down = node;
				for (r = C->rhead[node->i]; r->right; r = r->right);
				r->right = node;

				q = q->right;
				C->tu++;*/
			}
			else if (p->i < q->i) {
				/*OLNode* node;
				if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->down = (OLNode*)malloc(sizeof(OLNode))))
					exit(ERROR);
				node->data = p->data;
				node->i = p->i;
				node->j = p->j;
				node->down = NULL;
				node->right = NULL;

				for (r = C->chead[node->j]; r->down; r = r->down);
				r->down = node;
				for (r = C->rhead[node->i]; r->right; r = r->right);
				r->right = node;

				p = p->right;
				C->tu++;*/
			}
			else {
				if (p->j > q->j) {
					OLNode* node;
					if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
						!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
						!(node->down = (OLNode*)malloc(sizeof(OLNode))))
						exit(ERROR);
					node->data = q->data;
					node->i = q->i;
					node->j = q->j;
					node->down = NULL;
					node->right = NULL;

					for (r = C->chead[node->j]; r->down; r = r->down);
					r->down = node;
					for (r = C->rhead[node->i]; r->right; r = r->right);
					r->right = node;

					q = q->right;
					C->tu++;
				}
				else if (p->j < q->j) {
					OLNode* node;
					if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
						!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
						!(node->down = (OLNode*)malloc(sizeof(OLNode))))
						exit(ERROR);
					node->data = p->data;
					node->i = p->i;
					node->j = p->j;
					node->down = NULL;
					node->right = NULL;

					for (r = C->chead[node->j]; r->down; r = r->down);
					r->down = node;
					for (r = C->rhead[node->i]; r->right; r = r->right);
					r->right = node;

					p = p->right;
					C->tu++;
				}
				else {
					OLNode* node;
					if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
						!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
						!(node->down = (OLNode*)malloc(sizeof(OLNode))))
						exit(ERROR);
					node->data = p->data + q->data;
					if (node->data != 0) {
						node->i = p->i;
						node->j = p->j;
						node->down = NULL;
						node->right = NULL;

						for (r = C->chead[node->j]; r->down; r = r->down);
						r->down = node;
						for (r = C->rhead[node->i]; r->right; r = r->right);
						r->right = node;
						
						C->tu++;
					}
					p = p->right;
					q = q->right;
				}
			}
		}

		if (p) {
			for (r = C->rhead[i]; r->right; r = r->right);
			while (p) {
				OLNode* node;
				if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->down = (OLNode*)malloc(sizeof(OLNode))))
					exit(ERROR);
				node->data = p->data;
				node->i = p->i;
				node->j = p->j;
				node->right = NULL;
				node->down = NULL;

				r->right = node;
				r = r->right;
				p = p->right;
				C->tu++;
			}
		}

		if (q) {
			for (r = C->rhead[i]; r->right; r = r->right);
			while (q) {
				OLNode* node;
				if (!(node = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->right = (OLNode*)malloc(sizeof(OLNode))) ||
					!(node->down = (OLNode*)malloc(sizeof(OLNode))))
					exit(ERROR);
				node->data = q->data;
				node->i = q->i;
				node->j = q->j;
				node->right = NULL;
				node->down = NULL;

				r->right = node;
				r = r->right;
				q = q->right;
				C->tu++;
			}
		}

		i++;
	}
	return C;
}

void Print_OLList(OLList* A) {
	int i, j;
	OLNode* p;
	for (i = 0, j = 1; i < A->mu && j <= A->tu; i++) {
		p = A->rhead[i]->right;
		for (; p; p = p->right) {
			if (j < A->tu)
				printf("%d ", p->data);
			else
				printf("%d", p->data);
			j++;
		}
	}

	printf("\n");

	for (i = 0, j = 0; i < A->mu; i++) {
		p = A->rhead[i]->right;
		for (; j < A->nu && p;) {
			if (j < p->j) {
				printf("0");
				if (j != A->nu - 1)
					printf(" ");
				j++;
			}
			else if (j > p->j) {
				exit(ERROR);
			}
			else {
				printf("1");
				if (j != A->nu - 1) 
					printf(" ");
				j++;
				p = p->right;
			}
		}
		for (; j < A->nu; j++) {
			printf("0");
			if (j != A->nu - 1)
				printf(" ");
		}
		printf("\n");
		j = 0;
	}
}

main() {
	OLList* A, * B, * C;
	int m, n;
	scanf("%d%d", &m, &n);
	getchar();
	A = Init_OLList(m, n, 0);
	B = Init_OLList(m, n, 0);
	C = Init_OLList(m, n, 0);

	int V1[MAXSIZE],V2[MAXSIZE];
	V1[0] = 0;
	V2[0] = 0;
	int tu = 0;
	int signal = 1;
	char c;

	while (c = getchar()) {
		switch (c) {
		case '-':
			signal = -1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			V1[tu] = V1[tu] * 10 + c - '0';
			break;

		case ' ': case '\n':
			V1[tu++] *= signal;
			signal = 1;
			V1[tu] = 0;
			break;

		default:
			exit(ERROR);
		}

		if (c == '\n')
			break;
	}
	Assign_OLList(A, V1);
	getchar();
	
	tu = 0;
	while (c = getchar()) {
		switch (c) {
		case '-':
			signal = -1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			V2[tu] = V2[tu] * 10 + c - '0';
			break;

		case ' ': case '\n':
			V2[tu++] *= signal;
			signal = 1;
			V2[tu] = 0;
			break;

		default:
			exit(ERROR);
		}

		if (c == '\n')
			break;
	}
	Assign_OLList(B, V2); 
	getchar();
	
	C = Add_OLList(A, B);
	
	Print_OLList(C);
}

/*
*****************************
**    算法的时间复杂度估计    *
****************************
* 获取V矩阵的时间复杂度为O(tu)
* 获取B矩阵的时间复杂度为O(m*n)
* 矩阵加法的时间复杂度为O(tu)
* 打印矩阵的时间复杂度为O(m*n)
*/