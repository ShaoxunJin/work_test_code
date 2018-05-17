#include "stdafx.h"
#include "LIST.h"


NODE *create()
{
	function_in;

	NODE *head, *tail, *pnew;
	int score;
	int nbr;
	head = new NODE();
	assert(NULL != head);

	head->next = NULL;
	tail = head;
	printf("Please input linker number : \n");
	scanf("%d", &nbr);

	printf("Please input score : \n");
	while(nbr--)
	{
		scanf("%d", &score);
		//assert(0 <= score);
		if (0 > score)
		{
			break;
		}
		//
		pnew = new NODE();
		pnew->score = score;
		pnew->next = NULL;//下一个指定为null
		tail->next = pnew;//在当前的最后一个增加 NODE
		tail = pnew;//当前增加的最后一个作为tail
	}
	function_out;
	return head;
}


void insert_list(NODE *head, NODE *pnew, int index)
{
	function_in;

	assert(NULL != head && NULL != pnew);
	NODE *p;
	p = head;

	for (int i = 0; i < index && NULL != p; ++i)
	{
		p = p->next;//第i+1个指针来自于第i个指针
		//这里的目的是判断第index指针是否为空
		if (NULL == p)
		{
			printf("index : %d not exit !", index);
			return;
		}
	}

	//如果存在 则在这index位置直接插入
	//原始参数赋值给新的参数，这样的话
	//cout<<"p->score = "<<p->score<<endl;
	pnew->next = p->next;
	p->next = pnew;
	//cout<<"p->score = "<<p->score<<endl;
	//cout<<"p->next->score = "<<p->next->score<<endl;

	function_out;
}

void delete_list(NODE *head, int index)
{
	NODE *p,*q;
	int j;
	if (0 == index)
	{
		printf("index = %d\n", index);
		return;
	}
	p = head;
	for (j = 1; j < index && NULL != p; ++j)
	{
		p = p->next;
		if (NULL == p)
		{
			printf("index %d not exit!\n", index);
			return;
		}
	}
	//q是即将被删除的节点
	q = p->next;
	p->next = q->next;
	delete q;
}

//显示head之后所有的数值
void display(NODE *head)
{
	NODE *p;
	for (p = head->next; p != NULL; p = p->next)
	{
		printf("p->next = %d\n", p->score);
	}
}

//
void Pfree(NODE *head)
{
	function_in;
	
	NODE *p, *q;
	p = head;
	while (NULL != p->next)
	{
		q = p->next;
		p->next = q->next;
		delete q;
	}
	delete head;
	
	if (NULL == head)
	{
		printf("head->next = NULL \n");
	}

	function_out;
}

void add_list_head(NODE* &head, NODE *pnew)
{
	function_in;
	NODE *p;

	assert(NULL != head && NULL != pnew);
	//p = head;
	pnew->next = head->next;
	//cout<<"pnew->score = "<<pnew->score<<endl;
	//cout<<"head->score = "<<head->score<<endl;
	head->next = pnew;

	//cout<<"pnew->score = "<<pnew->score<<endl;
	//cout<<"head->score = "<<head->score<<endl;

	function_out;
}

void add_list_tail(NODE *&head, NODE *pnew)
{
	function_in;
	//find the tail
	NODE *p = head;
	while (NULL != p->next)
	{
		p = p->next;
	}
	p->next = pnew;

	function_out;
}

void list_main()
{
	function_in;
	
	NODE* head, *pnew;
	head = create();
	assert(NULL != head);
	
	printf("输出创建的列表：\n");
	display(head);
	pnew = new NODE();
	assert(NULL != pnew);
	pnew->score = 88;
	insert_list(head, pnew, 3);
	printf("插入后的链表 ： \n");
	display(head);
	delete_list(head, 3);
	printf("删除后的链表 ： \n");
	display(head);

	NODE *new_head = new NODE();
	new_head->score = 99;
	add_list_head(head, new_head);
	printf("插入头之后的链表 ： \n");
	display(head);

	NODE *new_tail = new NODE();
	if (NULL != new_tail)
	{
		printf("NULL != new_tail\n");
	}
	new_tail->score = 111;
	add_list_tail(head, new_tail);
	printf("插入尾之后的链表： \n");
	display(head);
	
	Pfree(head);

	function_out;
}




