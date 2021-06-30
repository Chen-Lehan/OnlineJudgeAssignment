#include <stdio.h>
#include <stdlib.h>

main() {
	int array[102];
	char c;
	int n, a, i, j;
	j = 0;
	do {
		scanf("%d", &array[j++]);
		c = getchar();
	} while (c != '\n');
	
	scanf("%d", &a);
	for (i = 0; i <= j; i++) {
		if (array[i] < a && i != j) {

		}
		else {
			n = array[i];
			array[i] = a;
			a = n;
		}
	}
	

	for (i = 0; i <= j; i++) {
		if (i == 0) {
			printf("%d", array[i]);
		}
		else {
			printf(" %d", array[i]);
		}
	}
}