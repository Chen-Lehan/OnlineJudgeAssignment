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

typedef struct {
	ElemType* base;
	int top;
}SqStack;

bool DFS_kPath_Existence(AGraph* G, int from, int to, int k) {
	if (k < 0 || visited[from - 1] == 1)
		return False;
	if (from == to && k == 0)
		return True;
	else {
		visited[from - 1] = 1;
		NodeLink* node = G->v[from - 1].first;
		while (node) {
			if (DFS_kPath_Existence(G, node->vindex, to, k - 1) == True)
				return True;
			else
				node = node->next;
		}
		if (!node) {
			visited[from - 1] = 0;
			return False;
		}
	}
}

main() {
	AGraph* G;
	int n, k, from, to;
	char c;
	scanf("%d%c%d", &n, &c, &k);
	scanf("%d%c%d", &from, &c, &to);
	G = Get_AGraph(n);
	if (DFS_kPath_Existence(G, from, to, k) == True)
		printf("yes");
	else
		printf("no");
}