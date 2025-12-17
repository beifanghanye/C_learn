#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// 构建一个空队列
int init_sq_queue(SqQueue* Q)
{
	if (!Q)
	{
		printf("Patameter error");
		exit(1);
	}

	Q->base = (QElemType*)malloc(sizeof(QElemType) * MAXQSIZE);
	if (!Q->base)
	{
		printf("Overflow");
		exit(1);
	}

	Q->front = Q->rear = 0;

	return 1;
}

// 计算队列的长度
int queue_length(SqQueue* Q)
{
	return (Q->rear + MAXQSIZE - Q->front) % MAXQSIZE;
}

// 插入元素 e 为 Q 的新的队尾元素
int en_sq_queue(SqQueue* Q, QElemType e)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
	{
		return 0;
	}

	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;

	return 1;
}

int de_sq_queue(SqQueue* Q, QElemType * e)
{
	if (Q->rear == Q->front)
	{
		return 0;
	}

	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;

	return 1;
}
