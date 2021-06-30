#include <stdio.h>
#include <stdlib.h>

int k_Fibonacci(int k, int m) {

	m++;
	int i,j;
	int n = 1;
	int* array = &n;
	array = (int*)malloc(m * sizeof(int));
	for (i = 0; i < k - 1; i++)
	{
		array[i] = 0;
	}
	array[k-1] = 1;
	i++;
	for (; i < m; i++) 
	{
		array[i] = 0;
		for (j = 0; j <= k; j++)
		{
			array[i] += array[i - j];
		}
	}
	printf("%d",array[m - 1]);

}

main() {
	int k, m;
	scanf("%d %d", &k, &m);
	k_Fibonacci(k, m);

}