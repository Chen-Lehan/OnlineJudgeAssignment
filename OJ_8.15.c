#include <stdio.h>
#include <stdlib.h>
#define ERROR -1

typedef struct {
	int* base;
	int length;
}Array;

typedef struct {
	int lowbound;
	int highbound;
	int size;
}Space;

main() {
	Space space;
	scanf("%d%d%d", &space.lowbound, &space.highbound, &space.size);
	int blocknum = (space.highbound - space.lowbound) / space.size;
	Array* array;
	if (!(array = (Array*)malloc(sizeof(Array))))
		exit(ERROR);
	if (blocknum <= 0)
		exit(ERROR);
	if (!(array->base = (int*)malloc(blocknum * sizeof(int))))
		exit(ERROR);
	
	int i;
	array->length = blocknum;
	for (i = 0; i < blocknum; i++) {
		scanf("%d", &array->base[i]);
	}
	int start = 1;
	for (i = 0; i < array->length;) {
		if (array->base[i] == 0) {
			if (!start)
				printf("\n");
			start = 0;
			printf("0");
			int start = i;
			int length;
			for (length = 0; array->base[i] == 0; i++, length++);
			printf(" %d %d", start * space.size + space.lowbound, length * space.size);
		}
		else
			i++;
	}
	if (start == 1)
		printf("0 0 0");
}