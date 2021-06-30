#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define MAXSIZE 100

typedef struct String {
	char* base;
	int length;
}String;

String* Init_String() {
	String* S;
	if (!(S = (String*)malloc(sizeof(String))) ||
		!(S->base = (char*)malloc(MAXSIZE * sizeof(char))))
		exit(ERROR);
	S->length = 0;
	return S;
}

String* SubString(String* S, int base, int length) {
	String* Sub;
	Sub = Init_String();
	Sub->length = length;

	int i;
	for (i = 0; i < length; i++) {
		Sub->base[i] = S->base[base + i];
	}
	return Sub;
}

String* Concat_String(String* S1, String* S2) {
	String* S;
	S = Init_String();
	S->length = S1->length + S2->length;
	int i;
	for (i = 0; i < S1->length; i++) {
		S->base[i] = S1->base[i];
	}
	for (i = 0; i < S2->length; i++) {
		S->base[S1->length + i] = S2->base[i];
	}
	return S;
}

String* Replace_String(String* S, String* T, String* V) {
	int i;
	if (T->length > S->length)
		return;
	else {
		for (i = 0; i + T->length <= S->length; i++) {
			int same = 1;
			int j;
			for (j = 0; j < T->length; j++) {
				if (S->base[i + j] != T->base[j]) {
					same = 0;
					break;
				}
			}
			if (same == 1) {
				S = Concat_String(SubString(S, 0, i), Concat_String(V, SubString(S, i + T->length, S->length - T->length - i)));
			}
		}
	}
	return S;
}

int getline(char s[], int lim) {
	int  c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n' && c!= ' '; i++) {
		s[i] = c;
	}

	return i;
}

void Print_String(String* S) {
	int i;
	for (i = 0; i < S->length; i++) {
		printf("%c", S->base[i]);
	}
}

main() {
	String* S, * T, * V;
	S = Init_String();
	T = Init_String();
	V = Init_String();

	S->length = getline(S->base, MAXSIZE);
	T->length = getline(T->base, MAXSIZE);
	V->length = getline(V->base, MAXSIZE);
	S = Replace_String(S, T, V);
	
	Print_String(S);
}
