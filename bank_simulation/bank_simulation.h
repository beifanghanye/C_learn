#ifndef BANK_SIMULATION_H
#define BANK_SIMULATION_H

#define MIN 1
#define MAX 20
#define CLOSE_TIME 200000000000

// 需要两种数据结构：队列和链表
// 1.队列：用来模拟客户排队
// 2.链表：事件表，用来进行事件驱动

// 队列的定义
// 队列结点的定义，也就是每个客户的定义
typedef struct QNode {
	int arrivalTime;		// 客户的到达时间
	int duration;			// 客户的服务时间
	struct QNode* next;
}QNode, Client;

// 队列的定义
typedef struct LinkQueue {
	QNode* front;
	QNode* rear;
	int len;
} LinkQueue, ClientQueue;

// 链表的定义
// 链表结点的定义，也就是每个事件的定义
typedef struct LNode {
	int occurTime;		// 事件的发生时间
	int nType;			// 事件的种类
	struct LNode* next;
} LNode, Event;

// 链表（事件表）的定义
typedef struct LinkList {
	LNode* head;
} LinkList, EventList;

// 函数声明
void initLinkQueue(LinkQueue* queue);
int isQueueEmpty(LinkQueue* queue);
void enQueue(LinkQueue* queue, QNode* node);
int deQueue(LinkQueue* queue, QNode* node);
int findMin(LinkQueue* queue, int n);
void displayQueue(LinkQueue* queue, int index);
void initLinkList(LinkList* list);
int isLinkListEmpty(LinkList* list);
void addLinkList(LinkList* list, LNode* node);
void deLinkList(LinkList* list, LNode* deNode);
void displayLinkList(LinkList* list);
double bankSimulation();
#endif