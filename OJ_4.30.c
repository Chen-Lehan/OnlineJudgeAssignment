#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define MAXSIZE 100

static int from;

typedef struct {
	char* str;
	int length;
}String;

String* Init_String() {
	String* string;
	if (!(string = (String*)malloc(sizeof(String))) ||
		!(string->str = (char*)malloc(MAXSIZE * sizeof(char))))
		exit(ERROR);
	string->length = 0;
	return string;
}

String* Sub_String(String* S, int base, int length) {
	if (length == 0)
		return NULL;
	if (S->length < base + length - 1 || base < 0)
		exit(ERROR);
	String* Sub;
	if (!(Sub = (String*)malloc(sizeof(String))) ||
		!(Sub->str = (char*)malloc(MAXSIZE * sizeof(char))))
		exit(ERROR);
	Sub->length = length;

	int i;
	for (i = 0; i < length; i++) {
		Sub->str[i] = S->str[base + i];
	}
	return Sub;

}

int GetMax(int* A, int length) {
	int max, i;
	for (i = 0, max = A[0]; i < length; i++) {
		if (max < A[i])
			max = A[i];
	}
	return max;
}

int LRSub_String(String* S) {
	int* next;
	if (!(next = (int*)malloc(S->length * sizeof(int))))
		exit(ERROR);
	int i, j, k;
	for (i = 0; i < S->length;) {
		if (i == 0) {
			next[i++] = 0;
		}
		else {
			if (S->str[i] == S->str[next[i - 1]]) {
				next[i] = next[i - 1] + 1;
				i++;
			}
			else {
				int p = next[i - 1];
				while (S->str[p] != S->str[i] && p) {
					p = next[p - 1];
				}
				if (p == 0 && S->str[p] != S->str[i]) {
					next[i++] = (int)0;
				}
				else {
					next[i++] = p + 1;
				}
			}
		}
	}

	j = GetMax(next, S->length);
	if (S->length != 1)
		k = LRSub_String(Sub_String(S, 1, S->length - 1));
	else
		k = 0;

	if (j >= k) {
		from = 0;
		return j;
	}
	else {
		from++;
		return k;
	}	
}

int getline(char s[], int lim) {
	int  c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		s[i] = c;
	}

	return i;
}

main() {
	from = 0;
	String* S, *LRSub;
	int length, i;
	char c;
	if (!(S = (String*)malloc(sizeof(String))) ||
		!(S->str = (char*)malloc(MAXSIZE * sizeof(char)))||
		!(LRSub = (String*)malloc(sizeof(String))) ||
		!(LRSub->str = (char*)malloc(MAXSIZE * sizeof(char))))
		exit(ERROR);
	S->length = getline(S->str, MAXSIZE);
	length = LRSub_String(S);
	if (length == 0)
		printf("-1");
	else {
		for (i = 0; i < length; i++) {
			c = S->str[from + i];
			putchar(c);
		}
		printf(" %d", from);
	}
}