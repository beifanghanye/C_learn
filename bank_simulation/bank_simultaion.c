#include <stdio.h>
#include <stdlib.h>
#include "bank_simulation.h"
#include <time.h>

// 队列的相关操作
// 初始化队列
void initLinkQueue(LinkQueue* queue)
{
	if (!queue)
	{
		printf("Parameter error\n");
		exit(1);
	}
	// 为队列头尾指针分配空间并指向同一空间
	queue->front = queue->rear = (QNode*)malloc(sizeof(QNode));
	if (!queue->front)
	{
		printf("Memeory allocation error\n");
		exit(1);
	}

	queue->front->next = NULL;
	queue->len = 0;
}

// 判断队列是否为空
int isQueueEmpty(LinkQueue* queue)
{
	return queue->len == 0;
}

// 入队
void enQueue(LinkQueue* queue, QNode * node)
{
	if (!queue || !node)
	{
		printf("Parameter error\n");
		exit(1);
	}

	QNode* enNode = (QNode*)malloc(sizeof(QNode));
	if (!enNode)
	{
		printf("Memory allocation error\n");
		exit(1);
	}

	*enNode = *node;
	enNode->next = NULL;

	queue->rear->next = enNode;
	queue->rear = enNode;

	queue->len++;
}

// 出队
int deQueue(LinkQueue* queue, QNode* node)
{
	if (!queue || !node)
	{
		printf("Parameter error\n");
		exit(1);
	}

	if (isQueueEmpty(queue))
	{
		return 0;
	}

	QNode* deNode = queue->front->next;
	queue->front->next = deNode->next;
	if (deNode == queue->rear)
	{
		queue->rear = queue->front;
	}
	*node = *deNode;
	free(deNode);

	queue->len--;
	return 1;
}

// 找寻排队人数最少的队列
int findMin(LinkQueue* queue, int n)
{
	if (!queue || !n)
	{
		printf("Parameter error\n");
		exit(1);
	}

	int min = queue[0].len;
	int minQueue = 0;

	for (int i = 1; i < n; i++)
	{
		if (queue[i].len < min)
		{
			min = queue[i].len;
			minQueue = i;
		}
	}

	return minQueue;
}

// 显示队列内容
void displayQueue(LinkQueue* queue, int index)
{
	if (!queue)
	{
		printf("Patameter error\n");
		exit(1);
	}

	if (isQueueEmpty(queue))
	{
		printf("queue %d: empty\n");
		return;
	}

	QNode* p = queue->front->next;
	printf("queue %d：");
	while (p)
	{
		printf("(%d, %d)", p->arrivalTime, p->duration);
		if (!p->next)
		{
			printf("\n");
		}
		else
		{
			printf("->");
		}
		p = p->next;
	}
}

// 链表的相关操作
// 初始化链表
void initLinkList(LinkList* list)
{
	if (!list)
	{
		printf("Parameter error\n");
		exit(1);
	}

	list->head = (LNode*)malloc(sizeof(LNode));
	if (!list->head)
	{
		printf("Memory allocation error\n");
		exit(1);
	}

	list->head->next = NULL;
}

// 判断链表是否为空
int isLinkListEmpty(LinkList* list)
{
	return list->head->next == NULL;
}

// 向链表中插入结点（按照 LNode 的 occurTime 升序）
void addLinkList(LinkList* list, LNode* node)
{
	if (!list || !node)
	{
		printf("Parameter error\n");
		exit(1);
	}

	LNode* addNode = (LNode *)malloc(sizeof(LNode));
	if (!addNode)
	{
		printf("Memory allocation error\n");
		exit(1);
	}

	*addNode = *node;
	addNode->next = NULL;

	LNode* p = list->head;
	LNode* q = p->next;

	while (q)
	{
		if (addNode->occurTime <= q->occurTime)
		{
			p->next = addNode;
			addNode->next = q;
			return;
		}
		p = q;
		q = p->next;
	}

	p->next = addNode;
}

// 删除链表的第一个结点，并存储在 deNode 中
void deLinkList(LinkList* list, LNode* deNode)
{
	if (!list || !deNode)
	{
		printf("Patameter error\n");
		exit(1);
	}

	if (isLinkListEmpty(list))
	{
		printf("The list is NULL\n");
		exit(1);
	}

	LNode* node = list->head->next;
	*deNode = *node;
	list->head->next = node->next;

	free(node);
}

// 显示链表内容
void displayLinkList(LinkList * list)
{
	if (!list)
	{
		printf("Parameter error\n");
		exit(1);
	}

	if (isLinkListEmpty(list))
	{
		printf("empty\n");
		return;
	}

	LNode* p = list->head->next;
	while (p)
	{
		printf("(%d, %d)", p->occurTime, p->nType);
		if (!p->next)
		{
			printf("\n");
		}
		else
		{
			printf("->");
		}
		p = p->next;
	}
}

// 银行排队模拟
double bankSimulation()
{
	// 设置随机数种子，随机生成 interTime，durTime
	srand(time(NULL));

	int totalTime = 0;		// 客户服务总时长
	int clientNum = 0;		// 客户数量

	// 创建事件表，队列
	EventList eventList;
	initLinkList(&eventList);

	ClientQueue clientQueue[4];		// 四个队列
	for (int i = 0; i < 4; i++)
	{
		initLinkQueue(clientQueue + i);
	}
	
	// 初始事件 occurTime 为 0，nType 为 -1，下一个事件为 NULL
	Event event = {
		0,
		-1,
		NULL
	};

	// 将初始事件插入事件表中
	addLinkList(&eventList, &event);

	int count = 1;		// 记录循环次数

	// 扫描事件表（事件驱动）
	while (!isLinkListEmpty(&eventList))
	{
		printf("----------第%d次循环----------\n", count++);
		printf("事件表：");
		displayLinkList(&eventList);
		printf("队列：\n");
		displayQueue(clientQueue + 0, 0);
		displayQueue(clientQueue + 1, 1);
		displayQueue(clientQueue + 2, 2);
		displayQueue(clientQueue + 3, 3);

		// 事件表为非空
		// 获取事件表第一个事件，并将其删除
		Event curEvent;
		deLinkList(&eventList, &curEvent);
		
		if (curEvent.nType == -1)
		{
			// 当前事件为到达事件
			clientNum++;
			int interTime = MIN + rand() % (MAX - MIN + 1);		// 下一位客户到达间隔时间
			int durTime = MIN + rand() % (MAX - MIN + 1);		// 当前客户服务时长

			

			// 记录当前到达客户信息
			Client curClient;
			curClient.arrivalTime = curEvent.occurTime;
			curClient.duration = durTime;
			curClient.next = NULL;

			int min = findMin(clientQueue, 4);		// 为当前客户寻找排队人数最少的队伍
			enQueue(clientQueue + min, &curClient);	// 当前客户入队

			if (curEvent.occurTime + interTime < CLOSE_TIME)
			{
				// 如果下一个顾客到达时间在银行结束营业之前
				// 记录其到达事件，并将其插入事件表中
				Event tempEvent;
				tempEvent.occurTime = curEvent.occurTime + interTime;
				tempEvent.nType = -1;
				tempEvent.next = NULL;
				addLinkList(&eventList, &tempEvent);

				

			}
			
			
			
			if (clientQueue[min].len == 1)
			{
				//当前客户为该队列的第一个客户，则需要记录其离开事件,并将其插入事件表中
				Event tempEvent;
				tempEvent.occurTime = curClient.arrivalTime + curClient.duration;
				tempEvent.nType = min;
				tempEvent.next = NULL;
				addLinkList(&eventList, &tempEvent);

				
			}

			
		}

		else
		{
			// 该事件为离开事件
			int win = curEvent.nType;		// 获取该客户离开队列序号
			Client client;
			deQueue(clientQueue + win, &client);
			totalTime += client.duration;	// 累加服务时长

			if (!isQueueEmpty(clientQueue + win))
			{
				// 当前离开队列不为空
				//	记录首位客户的离开事件，并将其插入事件表中
				Event tempEvent;
				tempEvent.occurTime = curEvent.occurTime + clientQueue[win].front->next->duration;
				tempEvent.nType = win;
				tempEvent.next = NULL;
				addLinkList(&eventList, &tempEvent);

				
			}
		}

		printf("\n");
	}
	return totalTime * 1.0 / clientNum;
}