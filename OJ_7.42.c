#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define ElemType int 

typedef enum { True, False }bool;

typedef struct node {
	int vindex;
	int length;
	struct node* next;
}NodeLink;

typedef struct {
	ElemType vertex;
	NodeLink* first;
}vert;

typedef struct {
	int vexnum, edgenum;
	vert* v;
}AGraph;

bool Get_Edge(AGraph* G) {
	char c;
	int from, to, length;
	from = 0;
	while ((c = getchar()) != EOF && c != '-')
		from = from * 10 + c - '0';
	if (c == EOF)
		return False;
	scanf("%d%d", &to, &length);
	NodeLink* p, * q;
	if (!(p = (NodeLink*)malloc(sizeof(NodeLink))) ||
		!(q = (NodeLink*)malloc(sizeof(NodeLink))))
		exit(ERROR);
	
	p->length = length;
	p->vindex = to;
	p->next = G->v[from - 1].first;
	G->v[from - 1].first = p;

	q->length = length;
	q->vindex = from;
	q->next = G->v[to - 1].first;
	G->v[to - 1].first = q;

	return True;
}

AGraph* Get_AGraph(int n) {
	if (n <= 0)
		exit(ERROR);
	AGraph* G;
	if (!(G = (AGraph*)malloc(sizeof(AGraph))) ||
		!(G->v = (vert*)malloc(n * sizeof(vert))))
		exit(ERROR);
	G->vexnum = n;
	int i;
	for (i = 0; i < n; i++) {
		G->v[i].first = NULL;
		G->v[i].vertex = i + 1;
	}
	
	while (Get_Edge(G) == True)
		getchar();
	return G;
}

void Print_MinPath(AGraph* G, int src) {
	bool* S;
	int* lengths;
	if (G->vexnum <= 0)
		exit(ERROR);
	if (!(S = (bool*)malloc(G->vexnum * sizeof(bool))) |
		!(lengths = (int*)malloc(G->vexnum * sizeof(int))))
		exit(ERROR);
	int i;
	for (i = 0; i < G->vexnum; i++) {
		S[i] = False;
	}
	S[src - 1] = True;
	lengths[src - 1] = 0;
	NodeLink* node = NULL;
	int from;
	while (1) {
		node = NULL;
		for (i = 0; i < G->vexnum; i++) {
			if (S[i] == False)
				continue;
			else {
				NodeLink* p = G->v[i].first;
				for (; p; p = p->next) {
					if (S[p->vindex - 1] == True)
						continue;
					if (!node) {
						node = p;
						from = i;
					}
					else {
						if (node->length + lengths[from] > p->length + lengths[i]) {
							node = p;
							from = i;
						}
					}
				}
			}
		}
		if (!node)
			break;
		S[node->vindex - 1] = True;
		lengths[node->vindex - 1] = lengths[from] + node->length;
	}
	int j;
	for (i = 0, j = 0; i < G->vexnum; i++) {
		if (lengths[i] == 0)
			continue;
		if (j == 0)
			printf("%d", lengths[i]);
		else
			printf(",%d", lengths[i]);
		j++;
	}
}

main() {
	printf("%d", sizeof(int));
	AGraph* G;
	int n, src;
	scanf("%d%d", &n, &src);
	getchar();
	G = Get_AGraph(n);

	Print_MinPath(G, src);
}
