#include <stdio.h>

int result(int i) {
	int result = 1;
	int j;
	if (i == 0) {
		return 1;
	}
	for (j = 1; j <= i; j++) {
		result = result * 2 * j;
	}
	return result;
}

int main() {
	int n, arrise;
	scanf("%d %d", &n, &arrise);
	if (n > 11) {
		printf("-1");
		return 0;
	}
	if (n > arrise) {
		printf("-1");
		return 0;
	}
	else {
		int array[11];
		int i;
		for (i = 0; i < n; i++) {
			array[i] = result(i);
			if (i == 0) {
				printf("%d", array[i]);
			}
			else {
				printf(" %d", array[i]);
			}
		}
	}
	
}