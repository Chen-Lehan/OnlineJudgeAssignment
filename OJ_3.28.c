#include <stdio.h>
#include <stdlib.h>
#define CQUEUESIZE 100
#define ElemType char

typedef struct{
	ElemType data;
	struct QNode* next;
}QNode;

typedef struct {
	QNode* front;
	QNode* rear;
 }*CQueue;

CQueue Init_CQueue() {
	CQueue q;
	QNode* n;
	q = (CQueue)malloc(sizeof(CQueue));
	n = (QNode*)malloc(sizeof(QNode));
	n->next = NULL;
	q->front = n;
	q->rear = n;
	return q;
}

void EnCQueue(CQueue q, ElemType data) {
	q->rear->data = data;
	QNode* n;
	n = (QNode*)malloc(sizeof(QNode));
	n->next = NULL;
	q->rear->next = n;
	q->rear = q->rear->next;
}

ElemType DeCQueue(CQueue q) {
	ElemType data;
	QNode* p;
	p = q->front;
	data = q->front->data;
	q->front = q->front->next;
	free(p);
	return data;
}

int IsEmptyCQueue(CQueue q) {
	if (q->front->next == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

main() {
	int length, i;
	ElemType data;
	CQueue q;
	q = Init_CQueue();

	scanf("%d", &length);
	getchar();
	for (i = 0; i < length; i++) {
		scanf("%c", &data);
		getchar();
		EnCQueue(q, data);
	}
	while (IsEmptyCQueue(q)==0) {		//1ЮЊПе
		printf("%c", DeCQueue(q));
		if (!IsEmptyCQueue(q)) {
			printf(",");
		}
	}
}