#ifndef QUEUE_H
#define QUEUE_H

#define MAXQSIZE 100		// 最大队列长度

// 队列节点的数据类型
typedef struct {
	int ArrivalTime;
	int Duration;
} QElemType;

// 队列节点
typedef struct QNode {
	QElemType data;
	struct QNode* next;
} QNode, * QueuePtr;

// 链队列
typedef struct {
	QueuePtr front;
	QueuePtr rear;
} LinkQueue;

// 顺序队列
typedef struct {
	QElemType* base;
	int front;
	int rear;
} SqQueue;

// 函数的声明
int init_queue(LinkQueue* Q);
int destroy_queue(LinkQueue* Q);
int en_queue(LinkQueue* Q, QElemType e);
int de_queue(LinkQueue* Q, QElemType* e);
void print_queue(LinkQueue* Q);

#endif