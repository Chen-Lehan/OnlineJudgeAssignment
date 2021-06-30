#include <stdio.h>
#include <stdlib.h>

main() {
	int x, n, i, result;
	int* array;
	scanf("%d %d", &x, &n);
	array = (int*)malloc((n + 1) * sizeof(int));
	for (i = 0; i < n + 1; i++) {
		scanf("%d", array + i);
	}
	result = 0;
	for (i = n; i >= 0; i--) {
		result = result * x + array[i];
	}
	printf("%d", result);
}