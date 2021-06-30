#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 100
#define ElemType char

typedef struct {
	int length;
	ElemType* base;
	int top;
}*SqStack;

SqStack Init_SqStack() {
	SqStack s;
	s = (SqStack)malloc(sizeof(SqStack));
	s->base = (ElemType*)malloc(STACKSIZE * sizeof(ElemType));
	s->length = STACKSIZE;
	s->top = 0;
	return s;
}

void Push_SqStack(SqStack s, ElemType data) {
	s->base[s->top++] = data;
}

ElemType Pop_SqStack(SqStack s) {
	return s->base[--s->top];
}

int Len_SqStack(SqStack s) {
	return s->length;
}

typedef struct {
	int height;
	int width;
	int** base;
}*img;

img Init_img(int height, int width) {
	img image;
	image = (img)malloc(sizeof(img));
	image->height = height;
	image->width = width;
	image->base = (int**)malloc(height * sizeof(int*));
	int i;
	for (i = 0; i < height; i++) {
		image->base[i] = (int*)malloc(width * sizeof(int));
	}
	return image;
}

void Get_img(img image) {
	int i, j;
	for (i = 0; i < image->height; i++) {
		for (j = 0; j < image->width; j++) {
			int data;
			scanf("%d", &data);
			image->base[i][j] = data;
		}
	}
}

void Paint_img(img image, int p_height, int p_width) {
	int data = image->base[p_height][p_width];
	image->base[p_height][p_width] = 2;
	if (p_height != 0) {
		if (data == image->base[p_height - 1][p_width]) {
			Paint_img(image, p_height - 1, p_width);
		}
	}
	if (p_width != 0) {
		if (data == image->base[p_height][p_width - 1]) {
			Paint_img(image, p_height, p_width - 1);
		}
	}
	if (p_height != image->height - 1) {
		if (data == image->base[p_height + 1][p_width]) {
			Paint_img(image, p_height + 1, p_width);
		}
	}
	if (p_height != image->width - 1) {
		if (data == image->base[p_height][p_width + 1]) {
			Paint_img(image, p_height, p_width + 1);
		}
	}
}

main() {
	int height, width, p_height, p_width;
	int dir;
	img image;

	scanf("%d%d%d%d%d", &height, &width, &p_height, &p_width, &dir);
	image = Init_img(height, width);
	Get_img(image);
	Paint_img(image, p_height, p_width);

	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			printf("%d", image->base[i][j]);
		}
		printf("\n");
	}

}