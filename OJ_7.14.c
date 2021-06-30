#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define ElemType int
#define MAX_VERTEX_NUM 30

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
	vert v[MAX_VERTEX_NUM];
} AGraph;

void Get_Edge(AGraph* G) {
	int from, to;
	char c;
	scanf("%d%c%d", &from, &c, &to);
	G->v[from].vertex = from;
	NodeLink* node, * p;
	if (!(node = (NodeLink*)malloc(sizeof(NodeLink))))
		exit(ERROR);
	node->vindex = to;
	if (G->v[from].first && G->v[from].first->vindex > to) {
		for (p = G->v[from].first; p->next && p->next->vindex > to; p = p->next);
		node->next = p->next;
		p->next = node;
	}
	else {
		node->next = G->v[from].first;
		G->v[from].first = node;
	}
	getchar();
}

AGraph* Get_AGraph() {
	AGraph* G;
	char c;
	if (!(G = (AGraph*)malloc(sizeof(AGraph))))
		exit(ERROR);
	scanf("%d%c%d", &G->vexnum, &c, &G->edgenum);
	int i;
	for (i = 0; i < MAX_VERTEX_NUM; i++) {
		G->v[i].first = NULL;
		G->v[i].vertex = i;
	}
	G->v[0].vertex = -1;
	for (i = 0; i < G->edgenum; i++)
		Get_Edge(G);
	return G;
}

void Print_AGraph(AGraph* G) {
	int base = 0 - G->v[0].vertex;
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

main() {
	AGraph* G;
	G = Get_AGraph();
	Print_AGraph(G);
}