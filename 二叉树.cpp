#include"stdio.h"
#include"malloc.h"
#define MAX 100

typedef struct BiTNode{
	//��������
	char data;
	struct BiTNode *lchild,*rchild;//���Һ���ָ��
}BiTNode,*BiTree;

int CreateBiTree(BiTree &T){
	//�������������������н��ֵ��*�ַ���ʾ���������������T
	char ch;
	scanf("%c",&ch);
	if(ch == '*'){
		T = NULL;
		return 0;
	}
	else{
		if(!(T= (BiTNode *)malloc(sizeof(BiTNode)))){
			printf("\nError\n");
			return -1;
		}
		T->data = ch;           //���ɸ��ڵ�  
		CreateBiTree(T->lchild);//����������
		CreateBiTree(T->rchild);//����������
	}
	return 1;
}//CreateBiTree

void PreOrderTraverse(BiTree T){
	//�������������T�ĵݹ��㷨
	if(T){
		printf("%c\t",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}//PerOrderTraverse

void InOrderTraverse(BiTree T){
	//�������������T�ĵݹ�����
	if(T){
		InOrderTraverse(T->lchild);
		printf("%c\t",T->data);
		InOrderTraverse(T->rchild);
	}
}//InOrderTraverse

void PostOrderTraverse(BiTree T){
	//�������������T�ĵݹ�����
	if(T){
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c\t",T->data);
	}
}//PostOrderTraverse

void PerOrderCounter(BiTree T,int &count,int &count1){
	//ͳ�����н���Լ�Ҷ�ӽ��ĸ���
	if(T){
		if((!T->lchild)&&(!T->rchild)){
			count1 ++;//Ҷ�ӽ��ĸ���
		}
		count ++;//���н��ĸ���
		PerOrderCounter(T->lchild,count,count1);
		PerOrderCounter(T->rchild,count,count1);
	}
}//PerOrderCounter

void main(){
	BiTree T;
	int i=0;
	int j=0;
	int order;


	printf("1.����һ�������������������������������н��ֵ��*�ַ���ʾ����");
	printf("\n");
	printf("2.�������������T");
	printf("\n");
	printf("3.�������������T");
	printf("\n");
	printf("4.�������������T");
	printf("\n");
	printf("5.ͳ�����н���Լ�Ҷ�ӽ��ĸ���");
	printf("\n");
	do{
		printf("\n");
		printf("�����룺");
	    scanf("%d",&order);
	    printf("\n");
	    switch(order){
	        case 1:
				getchar();
			    CreateBiTree(T);
			    break;
		    case 2:
			    PreOrderTraverse(T);
			    break;
			case 3:
				InOrderTraverse(T);
			    break;
		    case 4:
			    PostOrderTraverse(T);
			    break;
			case 5:
				PerOrderCounter(T,i,j);
				printf("���ý��ĸ�����%d\n",i);
				printf("Ҷ�ӽ��ĸ�����%d\n",j);
				break;
			default:
				printf("\nerror\n");
				break;
	    }
	}while (order!=0);
}