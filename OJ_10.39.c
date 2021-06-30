#include <stdlib.h>
#include <stdio.h>
#define ERROR -1
#define MAXSIZE 10000

typedef struct {
	int* base;
	int length;
}Array;

Array* Get_Array() {
	char c;
	int data = 0;
	Array* array;
	
	if (!(array = (Array*)malloc(sizeof(array))))
		exit(ERROR);
	if (!(array->base = (int*)malloc(MAXSIZE * sizeof(int))))
		exit(ERROR);
	array->length = 0;

	while (c = getchar()) {
		if (c == ' ' || c == '\n') {
			array->base[array->length++] = data;
			data = 0;
			if (c == '\n')
				break;
		}
		else {
			data = data * 10 + c - '0';
		}
	}
	return array;
}

void Insert_Array(Array* array, int data) {
	array->base[array->length++] = data;
}

Array* Combine_Array(Array* array1, Array* array2) {
	Array* array;
	if (!(array = (Array*)malloc(sizeof(array))))
		exit(ERROR);
	if (!(array->base = (int*)malloc(MAXSIZE * sizeof(int))))
		exit(ERROR);
	array->length = 0;

	int i, j;
	for (i = 0, j = 0; i < array1->length && j < array2->length;) {
		if (array1->base[i] < array2->base[j])
			Insert_Array(array, array1->base[i++]);
		else if (array1->base[i]>array2->base[j])
			Insert_Array(array, array2->base[j++]);
		else {
			Insert_Array(array, array1->base[i++]);
			j++;
		}
	}
	for (; i < array1->length; i++)
		Insert_Array(array, array1->base[i]);
	for (; j < array2->length; j++)
		Insert_Array(array, array2->base[j]);
	return array;
}

Print_Array(Array* array) {
	int i;
	for (i = 0; i < array->length; i++) {
		if (i != 0)
			printf(" ");
		printf("%d", array->base[i]);
	}
}

main() {
	Array* array, * array1, * array2;
	array1 = Get_Array();
	array2 = Get_Array();
	array = Combine_Array(array1, array2);
	Print_Array(array);
}
