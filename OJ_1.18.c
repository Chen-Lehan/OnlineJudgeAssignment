#include <stdio.h>

main() {
	struct perf
	{
		int score[2];
	};
	struct perf A, B, C, D, E;
	A.score[0] = 0;
	A.score[1] = 0;
	B.score[0] = 0;
	B.score[1] = 0;
	C.score[0] = 0;
	C.score[1] = 0;
	D.score[0] = 0;
	D.score[1] = 0;
	E.score[0] = 0;
	E.score[1] = 0;
	char n, g, s, c;
	int score;
	do {
		do {
			c = getchar();
		} while (c != EOF && c != ' ');
		if (c == EOF)
			break;
		scanf("%c %c %d", &g, &s, &score);
		switch (s)
		{
			case 'A':
				if (g == 'M') {
					A.score[0] += score;
				}
				else if (g == 'F') {
					A.score[1] += score;
				}
				break;
			case 'B':
				if (g == 'M') {
					B.score[0] += score;
				}
				else if (g == 'F') {
					B.score[1] += score;
				}
				break;
			case 'C':
				if (g == 'M') {
					C.score[0] += score;
				}
				else if (g == 'F') {
					C.score[1] += score;
				}
				break;
			case 'D':
				if (g == 'M') {
					D.score[0] += score;
				}
				else if (g == 'F') {
					D.score[1] += score;
				}
				break;
			case 'E':
				if (g == 'M') {
					E.score[0] += score;
				}
				else if (g == 'F') {
					E.score[1] += score;
				}
				break;
			default:
				break;
		}
	} while (c != EOF);
	if (A.score[0] != 0) {
		printf("A M %d\n", A.score[0]);
	}
	if (A.score[1] != 0) {
		printf("A F %d\n", A.score[1]);
	}
	if (A.score[0] != 0 || A.score[1] != 0) {
		printf("A %d\n", A.score[0] + A.score[1]);
	}

	if (B.score[0] != 0) {
		printf("B M %d\n", B.score[0]);
	}
	if (B.score[1] != 0) {
		printf("B F %d\n", B.score[1]);
	}
	if (B.score[0] != 0 || B.score[1] != 0) {
		printf("B %d\n", B.score[0] + B.score[1]);
	}

	if (C.score[0] != 0) {
		printf("C M %d\n", C.score[0]);
	}
	if (C.score[1] != 0) {
		printf("C F %d\n", C.score[1]);
	}
	if (C.score[0] != 0 || C.score[1] != 0) {
		printf("C %d\n", C.score[0] + C.score[1]);
	}

	if (D.score[0] != 0) {
		printf("D M %d\n", D.score[0]);
	}
	if (D.score[1] != 0) {
		printf("D F %d\n", D.score[1]);
	}
	if (D.score[0] != 0 || D.score[1] != 0) {
		printf("D %d\n", D.score[0] + D.score[1]);
	}

	if (E.score[0] != 0) {
		printf("E M %d\n", E.score[0]);
	}
	if (E.score[1] != 0) {
		printf("E F %d\n", E.score[1]);
	}
	if (E.score[0] != 0 || E.score[1] != 0) {
		printf("E %d\n", E.score[0] + E.score[1]);
	}
}