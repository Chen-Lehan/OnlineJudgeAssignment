#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define MAXLENGTH 30
#define ElemType int 

typedef enum {True, False} bool;

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

typedef struct {
	int length;
	int* base;
}Array;

Array* Get_Array() {
	int data[MAXLENGTH];
	int length = 0;
	char c = ' ';
	while (c != '\n') {
		if (!(scanf("%d", &data[length])))
			exit(ERROR);
		length++;
		c = getchar();
	}

	Array* A;
	if (!(A = (Array*)malloc(sizeof(Array))) ||
		!(A->base = (int*)malloc(length * sizeof(int))))
		exit(ERROR);
	A->length = length;
	int i;
	for (i = 0; i < length; i++) {
		A->base[i] = data[i];
	}
	return A;
}

int* visited;

AGraph* Get_AGraph() {
	AGraph* G;
	if (!(G = (AGraph*)malloc(sizeof(AGraph))))
		exit(ERROR);
	if (!(scanf("%d", &G->vexnum)))
		exit(ERROR);
	if (G->vexnum <= 0)
		exit(ERROR);
	if (!(G->v = (vert*)malloc(G->vexnum * sizeof(vert))) | 
		!(visited = (int*)malloc(G->vexnum * sizeof(int))))
		exit(ERROR);
	
	int i;
	for (i = 0; i < G->vexnum; i++) {
		G->v[i].vertex = i + 1;
		G->v[i].first = NULL;
		visited[i] = 0;
	}

	Array* s, * fst, * lst;
	s = Get_Array();
	fst = Get_Array();
	lst = Get_Array();

	for (i = 0; i < G->vexnum; i++) {
		int first, last;
		first = fst->base[i + 1];
		last = lst->base[i + 1];
		if (first >= last)
			continue;
		else {
			int j;
			for (j = first; j < last; j++) {
				NodeLink* node;
				if (!(node = (NodeLink*)malloc(sizeof(NodeLink))))
					exit(ERROR);
				node->vindex = s->base[j];
				node->next = G->v[i].first;
				G->v[i].first = node;
			}
		}
	}
	return G;
}

bool DFS_Loop_Existence(AGraph* G, int from) {
	if (visited[from - 1] == 1)
		return True;
	else {
		visited[from - 1] = 1;
	}

	int vexindex = from - 1;
	NodeLink* node = G->v[vexindex].first;
	while (node) {
		if (DFS_Loop_Existence(G, node->vindex) == True)
			return True;
		else node = node->next;
	}
	if (!node)
		return False;
}


main() {
	AGraph* G;
	G = Get_AGraph();
	if (DFS_Loop_Existence(G, 1) == True)
		printf("yes");
	else
		printf("no");
}

