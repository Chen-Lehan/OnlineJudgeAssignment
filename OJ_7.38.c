#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define ELemType char

typedef struct node{
	int vindex;
	struct node* next;
}NodeLink;

typedef struct {
	ELemType vertex;
	NodeLink* first;
}vert;

typedef struct {
	int vexnum, edgenum;
	vert* v;
}AGraph;

void Get_Edge(AGraph* G, int i) {
	char c;
	c = getchar();
	G->v[i].vertex = c;
	c = getchar();
	if (c == '\n')
		G->v[i].first = NULL;
	else {
		NodeLink* p, * q;
		if (!(p = (NodeLink*)malloc(sizeof(NodeLink))) ||
			!(q = (NodeLink*)malloc(sizeof(NodeLink))))
			exit(ERROR);
		if (2 != scanf("%d%d", &q->vindex, &p->vindex))
			exit(ERROR);
		c = getchar();
		p->next = q;
		q->next = NULL;
		G->v[i].first = p;
	}
}

AGraph* Get_AGraph(int n) {
	AGraph* G;
	if (!(G = (AGraph*)malloc(sizeof(AGraph))) ||
		!(G->v = (vert*)malloc(n * sizeof(vert))))
		exit(ERROR);
	G->vexnum = n;

	int i;
	for (i = 0; i < n; i++) {
		Get_Edge(G, i);
	}
	return G;
}

void RP_AGraph(AGraph* G, int i) {
	NodeLink* node = G->v[i].first;
	while (node) {
		RP_AGraph(G, node->vindex);
		node = node->next;
	}
	printf("%c", G->v[i].vertex);
}

main() {
	AGraph* G;
	int n;
	if(!(scanf("%d", &n)))
		exit(ERROR);
	getchar();
	G = Get_AGraph(n);
	RP_AGraph(G, 0);
}