#include <stdio.h>
#include <stdlib.h>
#define ERROR -1 
#define MAX_VERTEX_NUM 20
#define STACKSIZE 100
#define ElemType int 

typedef enum { True, False } bool;

typedef struct node {
	int vindex;
	struct node* next;
} NodeLink;

typedef struct {
	ElemType vertex;
	NodeLink* first;
}vert;

typedef struct {
	int vexnum, edgenum;
	vert* v;
} AGraph;

void Get_Edge(AGraph* G) {
	int from, to;
	char c;
	if (scanf("%d%c%d", &from, &c, &to) == 0)
		exit(ERROR);
	NodeLink* node, * p;
	if (!(node = (NodeLink*)malloc(sizeof(NodeLink))))
		exit(ERROR);
	node->vindex = to;
	if (G->v[from - 1].first && G->v[from - 1].first->vindex > to) {
		for (p = G->v[from - 1].first; p->next && p->next->vindex > to; p = p->next);
		node->next = p->next;
		p->next = node;
	}
	else {
		node->next = G->v[from - 1].first;
		G->v[from - 1].first = node;
	}
}

int* visited;

AGraph* Get_AGraph(int n) {
	AGraph* G;
	if (!(G = (AGraph*)malloc(sizeof(AGraph))))
		exit(ERROR);
	G->vexnum = n;
	if (G->vexnum <= 0)
		exit(ERROR);
	if (!(G->v = (vert*)malloc(G->vexnum * sizeof(vert))) ||
		!(visited = (int*)malloc(G->vexnum * sizeof(int))))
		exit(ERROR);
	getchar();
	int i;
	for (i = 0; i < G->vexnum; i++) {
		G->v[i].first = NULL;
		G->v[i].vertex = i + 1;
		visited[i] = 0;
	}

	char c = ',';
	for (G->edgenum = 0; c == ','; G->edgenum++) {
		Get_Edge(G);
		c = getchar();
	}
	return G;
}

void Print_AGraph(AGraph* G) {
	int base = 0;
	int i;
	for (i = 0; i < G->vexnum; i++) {
		printf("%d", G->v[base + i].vertex);
		if (G->v[base + i].first) {
			printf(" ");
			NodeLink* p = G->v[base + i].first;
			for (p = G->v[base + i].first; p; p = p->next) {
				if (p->next)
					printf("%d,", p->vindex);
				else
					printf("%d", p->vindex);
			}
		}
		if (i != G->vexnum - 1)
			printf("\n");
	}
}

int DFS_Path_MaxLength(AGraph* G, int from) {
	NodeLink* node = G->v[from - 1].first;
	int length = 0;
	while (node) {
		int len;
		len = DFS_Path_MaxLength(G, node->vindex);
		if (len + 1 > length)
			length = len + 1;
		node = node->next;
	}
	return length;
}

main() {
	AGraph* G;
	int n, i;
	scanf("%d", &n);
	G = Get_AGraph(n);
	for (i = 0; i < n; i++) {
		if (i == 0)
			printf("%d", DFS_Path_MaxLength(G, i + 1));
		else
			printf(",%d", DFS_Path_MaxLength(G, i + 1));
	}
}