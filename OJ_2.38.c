#include <stdio.h>
#include <stdlib.h>
#define ElemType int

typedef struct DuLnode {
	ElemType data;
	int freq;
	int first_visit;
	struct DuLnode* next;
	struct DuLnode* prior;
}DuLnode, *DuLinkList;

DuLinkList Init_List() {
	DuLnode* head;
	head = (DuLinkList)malloc(sizeof(DuLnode));
	head->next = head;
	head->prior = head;
	head->data = 0;
	head->freq = 0;
	head->first_visit = 0;
 	return head;
}

void Insert_List(DuLinkList L, int data, int freq, int first_time) {
	DuLnode* p;
	p = (DuLnode*)malloc(sizeof(DuLnode));
	p->next = L;
	p->prior = L->prior;
	p->prior->next = p;
	L->prior = p;
	p->data = data;
	p->freq = freq;
	p->first_visit = first_time;
}

void Visit_List(DuLinkList L, int data) {
	DuLnode* p = L->next;
	int count;
	for (count = 1; p != L; p = p->next) {
		if (p->freq != 0) {
			count++;
		}
	}
	for (p = p->next; p != L; p = p->next) {
		if (p->data == data) {
			p->freq++;
			if (p->freq == 1) {
				p->first_visit = count;
			}
		}
	}
}

DuLinkList Locate(DuLinkList L) {
	DuLinkList L_new;
	L_new = Init_List();
	DuLnode* p, * q;
	for (p = L->next; p != L; p = p->next) {
		if (L_new->next == L_new) {
			Insert_List(L_new, p->data, p->freq, p->first_visit);
		}
		else {
			for (q = L_new->next; q != L_new; q = q->next) {
				if (p->freq > q->freq ||
					(p->freq == q->freq && p->first_visit < q->first_visit)) {
					DuLnode* r;
					r = (DuLnode*)malloc(sizeof(DuLnode));
					r->prior = q->prior;
					r->next = q;
					r->next->prior = r;
					r->prior->next = r;
					r->data = p->data;
					r->freq = p->freq;
					r->first_visit = p->first_visit;
					break;
				}
			}
			if (q == L_new) {
				DuLnode* r;
				r = (DuLnode*)malloc(sizeof(DuLnode));
				r->prior = L_new->prior;
				r->next = L_new;
				r->next->prior = r;
				r->prior->next = r;
				r->data = p->data;
				r->freq = p->freq;
				r->first_visit = p->first_visit;
			}
		}
	}
	return L_new;
}

main() {
	DuLinkList L;
	DuLnode* p;
	L = Init_List();
	
	char c;
	int i, length, data;
	scanf("%d", &length);

	for (i = 0; i < length; i++) {
		scanf("%d", &data);
		Insert_List(L, data, 0, 0);
	}

	do {
		scanf("%d", &data);
		Visit_List(L, data);
		c = getchar();
	} while (c != '\n');

/*	for (p = L->next; p != L; p = p->next) {
		printf("data:%d ", p->data);
		printf("freq:%d ", p->freq);
		printf("fv:%d\n", p->first_visit);
	}
*/
	DuLinkList L_new;
	L_new = Locate(L);
	for (p = L_new->next; p->next != L_new; p = p->next) {
		printf("%d ", p->data);
	}
	printf("%d", p->data);	
}