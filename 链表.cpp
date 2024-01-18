#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

typedef struct LNode{
    //���嵥����
	int data;
	//���ָ��ָ����
	struct LNode *next;
}LNode, *LinkList;

void InitList(LinkList &L){
//����һ��������
	L = (LinkList)malloc(sizeof(LNode));//��̬����洢�ռ�
	if(!L){
		printf("\nerror\n");
		return;
	}//����洢����ʧ��
	L->next = NULL;
}//����һ��������

void CreatList(LinkList &L,int n){
//����һ����ͷ���ĵ�����L
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	int i;
	LinkList p;
	printf("\n������%d������\n",n);
	for(i = n;i>0;--i){
		p = (LinkList)malloc(sizeof(LNode)); //�����½��
		scanf_s("%d",&p->data);
		p->next = L->next;
		L->next = p;
	}
}//����һ����ͷ���ĵ�����

void ClearList(LinkList &L){
	//��յ�����
	LinkList p,q;
	p = L->next;
	q = L->next;
	while(L->next != NULL){
		q = p->next;
		p->next = q->next;
		free(q);
	}//whileѭ������������ͷ���������
}//�������

void ListLength(LinkList L){
	//�������ʵ�ʳ���
	int count = 0;
	LinkList p = L->next;
	while(p!=NULL){
		p = p->next;
		count++;
	}//ͨ��whileѭ���õ�����ĳ���
	printf("\n��ʱ�������ʵ�ʳ���Ϊ%d\n",count);
}//�������ʵ�ʳ���

void ListEmpty(LinkList L){
	//��鵥�����Ƿ�Ϊ��
	LinkList p;
	p = L->next;
	if(p==NULL){
		printf("\n��ʱ�ĵ�����Ϊ�ձ�\n");
	}
	else{
		printf("\n��ʱ�ĵ�����Ϊ�ձ�\n");
	}
}//��鵥�����Ƿ�Ϊ�ձ�

void ListTraver(LinkList L){
	//����������������ӡ���е�Ԫ��
	LinkList p = L->next;
	while(p){
		printf("\n%6d\n",p->data);
		p = p->next;
	}//whileѭ������������ӡ
}//ListTraver

int Locate(LinkList L,int e){
	//����ֵΪe��Ԫ��
	LinkList p = L->next;
	while(p){
		if(p->data == e){
			printf("\n���ҳɹ�\n");
			return 1;
		}
		else{
			p = p->next;
			return -1;
		}
	}//whileѭ����������Ѱ����Ӧ��Ԫ��
}//����Ԫ���Ƿ���������

int ListInsert(LinkList &L,int i,int e){
	//�ڵ�i��λ��֮ǰ����ֵΪe��Ԫ��
	LinkList p= L,s;
	int j = 0;
	while(p && j<i-1){
		p = p->next;
		++j;
	}//whileѭ��Ѱ�ҵ�i-1�����
	if(!p || j>i-1){
		printf("\nδ�ҵ���%d��λ��\n",i);
		return -1;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}//����Ԫ��

int ListDelete(LinkList &L,int i,int &e){
	//ɾ����i��Ԫ�أ�����e����ֵ
	LinkList p = L,s;
	int j = 0;
	while(p->next && j<i-1){
		p = p->next;
		++j;
	}//whileѰ�ҵ�i����㣬��pָ����ǰ��
	if(!(p->next) || j>i-1){
		printf("\nδ�ҵ���%d��λ��\n",i);
		return -1;
	}
	s = p->next;
	p->next = s->next;
	e = s->data;
	free(s);
	return 1;
}//ɾ�������е�Ԫ��

void main(){
	LinkList L;
	int n,i,e = 0;
	int order;
	char yes_no;

	system("cls");

	printf("\t\t           ��  ��  ��\n");
    printf("\t\t*************************************************\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t1.Init a LinkList  ��ʼ��һ������\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t2.Create a LinkList ����һ������\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t3.Clear a LinkList  ���һ������\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t4.Caculate the Length of LinkList  �����ʵ�ʳ���\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t5.Check the LinkList whether is empty  ��������Ƿ�Ϊ��\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t6.Traver the LinkList  ��������������ӡ���е�Ԫ��\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t7.Locate a elem  �������в���ĳ��Ԫ��\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t8.Insert a elem  �����������Ԫ��\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t9.Delete a elem  ��������ɾ��ĳ��Ԫ��\n");
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
				printf("\n������Ԫ�صĸ���n:\n");
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
				printf("\n����������Ҫ���ҵ�Ԫ�ص�ֵe:\n");
				scanf("%d",&e);
				Locate(L,e);
				if(-1){
					printf("\n����ʧ��\n");
				}
				break;
		    case 8:
			    printf("\n������Ҫ�����Ԫ�ص�λ��i:\n");
			    scanf("%d %d",&e,&i);
			    ListInsert(L,i,e);
			    break;
		    case 9:
			    printf("\n����������Ҫɾ����Ԫ�ص�λ��i:\n");
			    scanf("%d",&i);
			    ListDelete(L,i,e);
			    break;
		    case 10:
			    break;
		    default:
			    printf("\nerr\n");
		}//ѡ��Ҫִ�еĲ���
		if(order == 0){
			break;
		}
		printf("\n\n\n\n\n----------------------------------------------\n");
		printf("Ҫ����ѡ����(Y/N)?");
		do
		{
			yes_no = getchar();
		}while(yes_no!='Y' && yes_no!='y' && yes_no!='N' && yes_no!='n');
	}while(yes_no!='N' && yes_no!='n');
}