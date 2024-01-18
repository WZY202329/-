#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

typedef struct QNode{
	int data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;//循环队列


void InitQueue(LinkQueue &Q){
	//构造一个空队列
	Q.front = Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit (0);//分配存储空间失败
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q,int e){
	//入队列
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) exit (0); //分配存储空间失败
	p->data=e;p->next = NULL;
	Q.rear->next=p;
	Q.rear = p;
}

void DeQueue(LinkQueue &Q,int &e){
	//出队列
	QueuePtr p;
	if(Q.front == Q.rear) exit(0);//如果队列为空
	p = Q.front->next;
	e = p->data;
	Q.front -> next = p->next;
	if(Q.rear == p) Q.rear=Q.front;
	free(p);
}

int zhanshiQueue(LinkQueue &Q){
	QueuePtr p;
	p = Q.front->next;
	while(p){
		
		printf("%d",p->data);
		p = p->next;
		
	}
	return 1;
}

int main(){
	LinkQueue Q;
	int e=0;
	int order;

	InitQueue(Q);

	do{
		printf("请输入：");
		scanf("%d",&order);
		if(order == 0){
			break;}
		if(order%2 ==0){
			DeQueue(Q,e);
			zhanshiQueue(Q);
			printf("\n");
			}
		if(order%2 == 1){
			EnQueue(Q,order);
			zhanshiQueue(Q);
			printf("\n");}

	}while(order!=0);
}