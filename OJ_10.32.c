#include <stdio.h>

main() {
	int R, W, B;
	char c;
	R = 0;
	W = 0;
	B = 0;
	while (c = getchar()) {
		switch (c)
		{
		case '1': 
			R++;
			break;
		case '2':
			W++;
			break;
		case '3':
			B++;
			break;
		default:
			break;
		}
		if (c == '\n')
			break;
	}
	
	int i;
	for (i = 0; i < R; i++) {
		if (i != 0)
			printf(" ");
		printf("1");
	}
	for (i = 0; i < W; i++) {
		printf(" 2");
	}
	for (i = 0; i < B; i++) {
		printf(" 3");
	}
}