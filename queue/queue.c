#include <stdlib.h>
#include "queue.h"


// 构造一个空队列
int init_queue(LinkQueue* Q)
{
	if (!Q)
	{
		printf("Parameter error");
		exit(1);
	}

	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
	{
		printf("Overflow");
		exit(1);
	}

	Q->front->next = NULL;

	return 1;
}

// 销毁队列
int destroy_queue(LinkQueue* Q)
{
	if (!Q)
	{
		printf("Parameter error");
		exit(1);
	}

	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}

	return 1;
}

// 插入元素 e 为Q的新的队尾元素
int en_queue(LinkQueue* Q, QElemType e)
{
	if (!Q)
	{
		printf("Parameter error");
		exit(1);
	}

	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		printf("Overflow");
		exit(1);
	}

	p->data = e;
	p->next = NULL;

	Q->rear->next = p;
	Q->rear = p;
	
	return 1;
}

// 若队列不为空，则删除 Q 的队头元素，用 e 返回其值，并返回 1
// 否则返回 0 
int de_queue(LinkQueue* Q, QElemType* e)
{
	if (!Q || !e)
	{
		printf("Parameter error");
		exit(1);
	}

	if (Q->front == Q->rear)
	{
		return 0;
	}

	QueuePtr p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)
	{
		Q->rear = Q->front;
	}
	free(p);
	return 1;
}

// 打印链队列
void print_queue(LinkQueue* Q)
{
	if (!Q)
	{
		printf("Parameter error");
		return;
	}

	if (Q->front == Q->rear)
	{
		printf("NULL\n");
		return;
	}

	QueuePtr p = Q->front->next;
	while (p)
	{
		printf("data:%d\naddress:%p\n\n", p->data, p);
		p = p->next;
	}
}

