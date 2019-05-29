#if 1
#include <stdio.h>
#include <string.h>

#define MAX 64
typedef struct
{
	int queue[MAX];
	int rear;
	int front;
} QUEUE;

QUEUE queue;

void init( QUEUE *q )
{
	memset( q->queue, 0, sizeof q->queue);
	q->rear = q->front = 0;
}
void put( QUEUE *q, int data)
{
	q->queue[q->rear] = data;
	q->rear = (q->rear+1)%MAX;
}
int get(QUEUE *q)
{
	int temp = q->queue[q->front];
	q->front = (q->front+1)%MAX;
	return temp;
}
int is_empty(QUEUE *q)
{
	return q->rear == q->front;
}

int is_full(QUEUE *q)
{
	return (q->rear+1)%MAX == q->front;
}

int main()
{
	put(&queue,1);
	put(&queue,2);
	put(&queue,3);
	printf("%d\n", get(&queue));
	printf("%d\n", get(&queue));
	printf("%d\n", get(&queue));
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <string.h>

#define MAX 64
typedef struct
{
	int queue[MAX];
	int rear;
	int front;
} QUEUE;

QUEUE queue;

void init()
{
	memset( queue.queue, 0, sizeof queue);
	queue.rear = queue.front = 0;
}
void put(int data)
{
	queue.queue[queue.rear] = data;
	queue.rear = (queue.rear+1)%MAX;
}
int get(void)
{
	int temp = queue.queue[queue.front];
	queue.front = (queue.front+1)%MAX;
	return temp;
}
int is_empty()
{
	return queue.rear == queue.front;
}

int is_full()
{
	return (queue.rear+1)%MAX == queue.front;
}

int main()
{
	put(1);
	put(2);
	put(3);
	printf("%d\n", get());
	printf("%d\n", get());
	printf("%d\n", get());
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <string.h>

#define MAX 64
int queue[MAX];
int rear;
int front;

void init()
{
	memset( queue, 0, sizeof queue);
	rear = front = 0;
}
void put(int data)
{
	queue[rear] = data;
	rear = (rear+1)%MAX;
}
int get(void)
{
	int temp = queue[front];
	front = (front+1)%MAX;
	return temp;
}
int is_empty()
{
	return rear == front;
}

int is_full()
{
	return (rear+1)%MAX == front;
}

int main()
{
	put(1);
	put(2);
	put(3);
	printf("%d\n", get());
	printf("%d\n", get());
	printf("%d\n", get());
	return 0;
}
#endif
