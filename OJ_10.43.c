#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
#define MAXNUM 20

main(){
	int i = 0;
	int data[MAXNUM];
	char c;
	int d = 0;
	int sign = 1;
	while (c = getchar()) {
		switch (c) {
		case ' ': case '\n':
			data[i++] = d * sign;
			d = 0;
			sign = 1;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			d = d * 10 + c - '0';
			break;

		case '-':
			sign = -1;
			break;

		default:
			break;
		}
		if (c == '\n')
			break;
	}

	int count[MAXNUM];
	int j, k;
	for (j = 0; j < i; j++)
		count[j] = 0;

	for (j = 0; j < i; j++) {
		for (k = 0; k < i; k++) {
			if (data[k] < data[j])
				count[j]++;
		}
		if (j != 0)
			printf(" ");
		printf("%d", count[j]);
	}
}