#include <stdio.h>
#include <stdlib.h>
#define ERROR -1

typedef struct space {
	int tag;
	int base;
	int size;
	struct space* next;
}space;

space* GetSpace() {
	space* base = NULL;
	char c;
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			c = getchar();
		space* node;
		if (!(node = (space*)malloc(sizeof(space))))
			exit(ERROR);
		if (2 != scanf("%d%d", &node->base, &node->size))
			exit(ERROR);
		node->tag = 0;
		c = getchar();

		if (!base) {
			node->next = NULL;
			base = node;
		}
		else {
			space* p;
			for (p = base; p; p = p->next) {
				if (p->next && p->next->base >= node->base + node->size) {
					node->next = p->next;
					p->next = node;
					break;
				}
				else if (!p->next) {
					node->next = NULL;
					p->next = node;
					break;
				}
			}
		}
	}
	space* p;
	for (p = base; p;) {
		if (p->next) {
			if (p->base + p->size == p->next->base) {
				p->size = p->size + p->next->size;
				space* q = p->next->next;
				free(p->next);
				p->next = q;
			}
			else {
				p = p->next;
			}
		}
		else {
			p = p->next;
		}
	}
	return base;
}

void PrintSpace(space* base) {
	space* p;
	for (p = base; p; p = p->next) {
		printf("%d %d %d", p->tag, p->base, p->size);
		if (p->next)
			printf("\n");
	}
}

main() {
	space* base;
	base = GetSpace();
	PrintSpace(base);
}