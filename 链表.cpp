#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

typedef struct LNode{
    //定义单链表
	int data;
	//后继指针指针域
	struct LNode *next;
}LNode, *LinkList;

void InitList(LinkList &L){
//构造一个空链表
	L = (LinkList)malloc(sizeof(LNode));//动态分配存储空间
	if(!L){
		printf("\nerror\n");
		return;
	}//如果存储分配失败
	L->next = NULL;
}//构造一个空链表

void CreatList(LinkList &L,int n){
//建立一个带头结点的单链表L
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	int i;
	LinkList p;
	printf("\n请输入%d个整数\n",n);
	for(i = n;i>0;--i){
		p = (LinkList)malloc(sizeof(LNode)); //生成新结点
		scanf_s("%d",&p->data);
		p->next = L->next;
		L->next = p;
	}
}//创建一个带头结点的单链表

void ClearList(LinkList &L){
	//清空单链表
	LinkList p,q;
	p = L->next;
	q = L->next;
	while(L->next != NULL){
		q = p->next;
		p->next = q->next;
		free(q);
	}//while循环整个链表后释放所有数据
}//清空链表

void ListLength(LinkList L){
	//求单链表的实际长度
	int count = 0;
	LinkList p = L->next;
	while(p!=NULL){
		p = p->next;
		count++;
	}//通过while循环得到链表的长度
	printf("\n此时单链表的实际长度为%d\n",count);
}//求单链表的实际长度

void ListEmpty(LinkList L){
	//检查单链表是否为空
	LinkList p;
	p = L->next;
	if(p==NULL){
		printf("\n此时的单链表为空表\n");
	}
	else{
		printf("\n此时的单链表不为空表\n");
	}
}//检查单链表是否为空表

void ListTraver(LinkList L){
	//遍历整个单链表并打印其中的元素
	LinkList p = L->next;
	while(p){
		printf("\n%6d\n",p->data);
		p = p->next;
	}//while循环遍历链表并打印
}//ListTraver

int Locate(LinkList L,int e){
	//查找值为e的元素
	LinkList p = L->next;
	while(p){
		if(p->data == e){
			printf("\n查找成功\n");
			return 1;
		}
		else{
			p = p->next;
			return -1;
		}
	}//while循环遍历链表寻找相应的元素
}//查找元素是否在链表中

int ListInsert(LinkList &L,int i,int e){
	//在第i个位置之前插入值为e的元素
	LinkList p= L,s;
	int j = 0;
	while(p && j<i-1){
		p = p->next;
		++j;
	}//while循环寻找第i-1个结点
	if(!p || j>i-1){
		printf("\n未找到第%d个位置\n",i);
		return -1;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}//插入元素

int ListDelete(LinkList &L,int i,int &e){
	//删除第i个元素，并由e返回值
	LinkList p = L,s;
	int j = 0;
	while(p->next && j<i-1){
		p = p->next;
		++j;
	}//while寻找第i个结点，令p指向其前驱
	if(!(p->next) || j>i-1){
		printf("\n未找到第%d个位置\n",i);
		return -1;
	}
	s = p->next;
	p->next = s->next;
	e = s->data;
	free(s);
	return 1;
}//删除链表中的元素

void main(){
	LinkList L;
	int n,i,e = 0;
	int order;
	char yes_no;

	system("cls");

	printf("\t\t           主  菜  单\n");
    printf("\t\t*************************************************\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t1.Init a LinkList  初始化一个链表\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t2.Create a LinkList 创建一个链表\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t3.Clear a LinkList  清空一个链表\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t4.Caculate the Length of LinkList  链表的实际长度\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t5.Check the LinkList whether is empty  检查链表是否为空\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t6.Traver the LinkList  遍历整个链表并打印其中的元素\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t7.Locate a elem  在链表中查找某个元素\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t8.Insert a elem  在链表里插入元素\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t9.Delete a elem  在链表里删除某个元素\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t10.Exit\n");
	printf("\t\t-------------------------------------------------\n\n\n\n\n\n");
	do{
		printf("Plese enter your choice:");
		scanf_s("%d",&order);
		printf("\n");

		switch (order){
		    case 1:
				InitList(L);
				break;
			case 2:
				printf("\n请输入元素的个数n:\n");
				scanf("%d",&n);
				CreatList(L,n);
				break;
			case 3:
				ClearList(L);
				break;
			case 4:
				ListLength(L);
				break;
			case 5:
				ListEmpty(L);
				break;
			case 6:
				ListTraver(L);
				break;
		    case 7:
				printf("\n请输入所有要查找的元素的值e:\n");
				scanf("%d",&e);
				Locate(L,e);
				if(-1){
					printf("\n查找失败\n");
				}
				break;
		    case 8:
			    printf("\n请输入要插入的元素的位置i:\n");
			    scanf("%d %d",&e,&i);
			    ListInsert(L,i,e);
			    break;
		    case 9:
			    printf("\n请输入所有要删除的元素的位置i:\n");
			    scanf("%d",&i);
			    ListDelete(L,i,e);
			    break;
		    case 10:
			    break;
		    default:
			    printf("\nerr\n");
		}//选择要执行的步骤
		if(order == 0){
			break;
		}
		printf("\n\n\n\n\n----------------------------------------------\n");
		printf("要继续选择吗(Y/N)?");
		do
		{
			yes_no = getchar();
		}while(yes_no!='Y' && yes_no!='y' && yes_no!='N' && yes_no!='n');
	}while(yes_no!='N' && yes_no!='n');
}