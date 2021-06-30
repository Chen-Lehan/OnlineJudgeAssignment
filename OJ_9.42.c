#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define OK 1

typedef enum { LEAF, BRANCH, HEAD } NodeKind;
typedef enum { True, False } bool;

typedef struct TrieTreeNode {
	char symbol;
	struct TrieTreeNode* next, * first;
	NodeKind kind;
}TrieTreeNode, * TrieTree;

TrieTreeNode* LeafNode() {
	TrieTreeNode* lnode;
	if (!(lnode = (TrieTreeNode*)malloc(sizeof(TrieTreeNode))))
		exit(ERROR);
	lnode->kind = LEAF;
	lnode->first = NULL;
	lnode->next = NULL;
	lnode->symbol = EOF;
	return lnode;
}

TrieTree Init_TrieTree() {
	TrieTree T;
	if (!(T = (TrieTree)malloc(sizeof(TrieTreeNode))))
		exit(ERROR);
	T->first = NULL;
	T->next = NULL;
	T->kind = HEAD;
}

int Insert_TrieTree(TrieTree T) {
	char c;
	TrieTreeNode* p = T;
	while (c = getchar()) {
		TrieTreeNode* node;
		if (!(node = (TrieTreeNode*)malloc(sizeof(TrieTreeNode))))
			exit(ERROR);
		if (c == '\n') {
			node->symbol = EOF;
			node->kind = LEAF;
			node->first = NULL;
			node->next = p->first;
			p->first = node;
			break;
		}
		node->symbol = c;
		
		if (!p->first) {
			node->kind = BRANCH;
			node->next = NULL;
			node->first = NULL;
			p->first = node;
			p = p->first;
		}
		else {
			if (c == p->first->symbol)
				p = p->first;
			else if (c < p->first->symbol) {
				node->kind = BRANCH;
				node->next = p->first;
				node->first = NULL;
				p->first = node;
				p = p->first;
			}
			else {
				for (p = p->first; p->next; p = p->next) {
					if (p->next) {
						if (c < p->next->symbol)
							break;
					}
				}
				if (p && c == p->symbol)
					continue;
				node->kind = BRANCH;
				node->next = p->next;
				node->first = NULL;
				p->next = node;
				p = p->next;
			}
		}
	}
	return OK;
}

void Clear_Line() {
	char c;
	while (c = getchar()) {
		if (c == '\n')
			break;
	}
}

int Del_TrieTree(TrieTree T) {
	char c;
	TrieTreeNode* p = T;
	c = getchar();
	if (c == '\n') {
		if (p->first) {
			if (p->first->kind == LEAF) {
				TrieTreeNode* q = p->first->next;
				free(p->first);
				p->first = q;
				return OK;
			}
		}
		return 0;
	}
	else {
		for (p = p->first; p; p = p->next) {
			if (c <= p->symbol) {
				if (c != p->symbol) {
					Clear_Line();
					return 0;
				}
				else {
					if (!Del_TrieTree(p))
						return 0;
					else if (!p->first) {
						if (T->first == p) {
							T->first = p->next;
							free(p);
							return OK;
						}
						else {
							TrieTreeNode* q;
							for (q = T->first; q->next != p; q = q->next);
							q->next = p->next;
							free(p);
							return OK;
						}
					}
					else
						return OK;
				}
			}
		}
		Clear_Line();
		return 0;
	}
}

bool Search_TrieTree(TrieTree T) {
	if (!T->first)
		return False;
	char c;
	TrieTreeNode* p = T;
	c = getchar();
	if (c == '\n') {
		if (p->first) {
			if (p->first->kind == LEAF)
				return True;
		}
		return False;
	}
	else {
		for (p = p->first; p; p = p->next) {
			if (c <= p->symbol) {
				if (c != p->symbol) {
					Clear_Line();
					return False;
				}
				else
					return Search_TrieTree(p);
			}
		}
		Clear_Line();
		return False;
	}
}

main() {
	char c;
	int first = 1;
	TrieTree T;
	T = Init_TrieTree();
	while (c = getchar()) {
		switch (c) {
		case '1':
			getchar();
			Insert_TrieTree(T);
			break;

		case '2':
			getchar();
			Del_TrieTree(T);
			break;

		case '3':
			getchar();
			if (!first)
				printf("\n");
			if (Search_TrieTree(T) == True)
				printf("True");
			else
				printf("False");
			first = 0;
			break;
		}
		if (c == EOF)
			break;
	}
}