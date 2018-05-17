#ifndef _LIST_H
#define _LIST_H

#include "head_file.h"

struct node
{
	int score;
	struct node *next;
};

typedef struct node NODE;

NODE *create();

//index:第index个节点
void insert_list(NODE *head, NODE *pnew, int index);

void delete_list(NODE *head, int index);

void display(NODE *head);

void Pfree(NODE *head);

void add_list_head(NODE *&head, NODE *pnew);

void add_list_tail(NODE *&head, NODE *pnew);

void list_main();



#endif