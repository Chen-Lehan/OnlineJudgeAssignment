#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define m 10

typedef enum { True, False }bool;

int pow(int base, int expo) {
	int result = 1;
	int i;
	for (i = 0; i < expo; i++) {
		result = result * base;
	}
	return result;
}

typedef	struct WORD_b {
	struct WORD_b* llink;
	int tag;
	int kval;
	struct WORD_b* rlink;
	int base;
}WORD_b;

typedef struct HeadNode {
	int nodesize;
	WORD_b* first;
}FreeList[m + 1];

void Init_FreeList(FreeList list) {
	int i;
	for (i = 0; i < m + 1; i++) {
		list[i].nodesize = pow(2, i);
		list[i].first = NULL;
	}
}

bool IsBuddy(int kval, int base1, int base2) {
	if (base1 < base2) {
		if (base1 + pow(2, kval) == base2) {
			if (base1 % pow(2, kval + 1) == 0)
				return True;
		}
	}
	else if (base1 > base2) {
		if (base2 + pow(2, kval) == base1) {
			if (base2 % pow(2, kval + 1) == 0)
				return True;
		}
	}
	return False;
}

void _Get_FreeList(FreeList list, int kval, int base) {
	WORD_b* node;
	if (!(node = (WORD_b*)malloc(sizeof(WORD_b))))
		exit(ERROR);

	node->kval = kval;
	node->base = base;
	node->tag = 0;

	if (list[kval].first) {
		if (base < list[kval].first->base) {
			if (IsBuddy(kval, base, list[kval].first->base) == True) {
				if (list[kval].first->rlink == list[kval].first) {
					WORD_b* p = list[kval].first;
					list[kval].first = NULL;
					_Get_FreeList(list, kval + 1, base);
					free(p);
					free(node);
				}
				else {
					WORD_b* p = list[kval].first;
					list[kval].first = p->rlink;
					list[kval].first->llink = p->llink;
					list[kval].first->llink->rlink = p->rlink;
					_Get_FreeList(list, kval + 1, base);
					free(p);
					free(node);
				}
			}
			else {
				node->rlink = list[kval].first;
				node->llink = list[kval].first->llink;
				node->rlink->llink = node;
				node->llink->rlink = node;
				list[kval].first = node;
			}
		}
		else {
			WORD_b* p;
			for (p = list[kval].first; p->rlink->base > p->base; p = p->rlink) {
				if (p->base<base && p->rlink->base>base)
					break;
			}
			if (IsBuddy(kval, p->base, base) == True) {
				if (p == p->llink) {
					list[kval].first = NULL;
					if (p->base < base)
						_Get_FreeList(list, kval + 1, p->base);
					else
						_Get_FreeList(list, kval + 1, base);
					free(p);
					free(node);
				}
				else {
					p->llink->rlink = p->rlink;
					p->rlink->llink = p->llink;
					_Get_FreeList(list, kval + 1, p->base);
					if (list[kval].first == p)
						list[kval].first = p->rlink;
					free(p);
					free(node);
				}
			}
			else if (IsBuddy(kval, base, p->rlink->base) == True) {
				if (p == p->llink) {
					list[kval].first = NULL;
					_Get_FreeList(list, kval + 1, p->base);
					free(p);
					free(node);
				}
				else {
					p->rlink = p->rlink->rlink;
					p->rlink->llink = p;
					_Get_FreeList(list, kval + 1, base);
					free(p);
					free(node);
				}
			}
			else {
				node->llink = p;
				node->rlink = p->rlink;
				p->rlink = node;
				node->rlink->llink = node;
			}
		}
	}
	else {
		list[kval].first = node;
		node->rlink = node;
		node->llink = node;
	}
}

void Get_FreeList(FreeList list, int kval) {
	int base;
	char c;
	while (1) {
		base = 0;
		while (c = getchar()) {
			if (c == ' ' || c == '\n')
				break;
			else
				base = base * 10 + c - '0';
		}
		_Get_FreeList(list, kval, base);
		if (c == '\n')
			break;
	}
}

void Print_FreeList(FreeList list) {
	int i;
	int start = 1;
	for (i = 0; i < m + 1; i++) {
		if (list[i].first) {
			if (!start)
				printf("\n");
			start = 0;
			WORD_b* p;
			printf("%d", i);
			printf(" %d", list[i].first->base);
			for (p = list[i].first->rlink; p != list[i].first; p = p->rlink) {
				printf(" %d", p->base);
			}
		}
	}
}

main() {
	FreeList list;
	Init_FreeList(list);
	int kval;
	char c;
	while (1) {
		kval = 0;
		while (c = getchar()) {
			if (c == ' ' || c == '\n' || c == EOF)
				break;
			else
				kval = kval * 10 + c - '0';
		}
		if (c == '\n')
			continue;
		else if (c == EOF)
			break;

		Get_FreeList(list, kval);
	}
	Print_FreeList(list);
}