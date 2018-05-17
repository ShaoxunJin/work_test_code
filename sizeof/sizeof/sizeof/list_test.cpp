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
		pnew->next = NULL;//��һ��ָ��Ϊnull
		tail->next = pnew;//�ڵ�ǰ�����һ������ NODE
		tail = pnew;//��ǰ���ӵ����һ����Ϊtail
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
		p = p->next;//��i+1��ָ�������ڵ�i��ָ��
		//�����Ŀ�����жϵ�indexָ���Ƿ�Ϊ��
		if (NULL == p)
		{
			printf("index : %d not exit !", index);
			return;
		}
	}

	//������� ������indexλ��ֱ�Ӳ���
	//ԭʼ������ֵ���µĲ����������Ļ�
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
	//q�Ǽ�����ɾ���Ľڵ�
	q = p->next;
	p->next = q->next;
	delete q;
}

//��ʾhead֮�����е���ֵ
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
	
	printf("����������б�\n");
	display(head);
	pnew = new NODE();
	assert(NULL != pnew);
	pnew->score = 88;
	insert_list(head, pnew, 3);
	printf("���������� �� \n");
	display(head);
	delete_list(head, 3);
	printf("ɾ��������� �� \n");
	display(head);

	NODE *new_head = new NODE();
	new_head->score = 99;
	add_list_head(head, new_head);
	printf("����ͷ֮������� �� \n");
	display(head);

	NODE *new_tail = new NODE();
	if (NULL != new_tail)
	{
		printf("NULL != new_tail\n");
	}
	new_tail->score = 111;
	add_list_tail(head, new_tail);
	printf("����β֮������� \n");
	display(head);
	
	Pfree(head);

	function_out;
}




