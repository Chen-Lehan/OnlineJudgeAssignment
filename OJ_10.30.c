#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
#define MAXNUM 20

typedef enum { False, True } bool;

typedef struct {
	int from;
	int to;
}section;

typedef struct {
	section* base;
	int top;
}SqStack;

SqStack* Init_SqStack(int length) {
	SqStack* S;
	if (!(S = (SqStack*)malloc(sizeof(SqStack))))
		exit(ERROR);
	if (!(S->base = (section*)malloc(length * sizeof(section))))
		exit(ERROR);
	S->top = 0;
	return S;
}

section Pop_SqStack(SqStack* S) {
	return S->base[--S->top];
}

void Push_SqStack(SqStack* S, section data) {
	S->base[S->top++] = data;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

main() {
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

	SqStack* S;
	S = Init_SqStack(i);
	section sec;
	sec.from = 0;
	sec.to = i - 1;
	Push_SqStack(S, sec);
	while (S->top) {
		sec = Pop_SqStack(S);
		if (sec.from + 2 < sec.to) {
			int pivot = sec.from;
			int j = sec.to;
			while (pivot != j) {
				if (pivot < j) {
					if (data[pivot] > data[j]) {
						swap(&data[pivot], &data[j]);
						swap(&pivot, &j);
						j++;
					}
					else {
						j--;
					}
				}
				else {
					if (data[pivot] < data[j]) {
						swap(&data[pivot], &data[j]);
						swap(&pivot, &j);
						j--;
					}
					else {
						j++;
					}
				}
			}
			section sec1 = { sec.from,pivot - 1 };
			section sec2 = { pivot + 1,sec.to };
			Push_SqStack(S, sec2);
			Push_SqStack(S, sec1);
		}
		else if (sec.from + 2 > sec.to) {
			if (data[sec.from] > data[sec.to])
				swap(&data[sec.from], &data[sec.to]);
		}
		else {
			int l = sec.from;
			int m = sec.from + 1;
			int r = sec.to;
			if (data[l] > data[m]) {
				if (data[m] > data[r])
					swap(&data[l], &data[r]);
				else {
					if (data[l] > data[r]) {
						swap(&data[l], &data[m]);
						swap(&data[m], &data[r]);
					}
					else
						swap(&data[l], &data[m]);
				}
			}
			else {
				if (data[m] > data[r]) {
					if (data[l] > data[r]) {
						swap(&data[m], &data[r]);
						swap(&data[l], &data[m]);
					}
					else {
						swap(&data[m], &data[r]);
					}
				}
			}
		}
	}
	for (d = 0; d < i; d++) {
		printf("%d", data[d]);
		if (d != i - 1) {
			printf(" ");
		}
	}
}