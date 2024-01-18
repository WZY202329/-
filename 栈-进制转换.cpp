#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

#define MAXQSIZE 100         //�����г���
#define STACK_INIT_SIZE 100  //�洢�ռ��ʼ������
#define STACKINCREMENT 10    //�洢�ռ��������

typedef struct{
	int *base;
	int *top;   //ջ��ָ��
	int stacksize;  //��ǰ�ѷ���Ĵ洢�ռ�
}SqStack; //ջ

/*typedef struct{
	int *base;  //��ʼ���Ķ�̬����洢�ռ�
	int front;
	int rear;
}SqQueue;//ѭ������
*/
int InitStack(SqStack &S){
	//����һ����ջ
	S.base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
	if(!S.base){
		printf("Error\n");
		return -1;
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return 1;
}//InitStack

int StackEmpty(SqStack S){
	//�ж�ջ�Ƿ�Ϊ��
	if(S.top == S.base){
		return 1;
	}
	else{
		return 0;
	}
}//StackEmpty

int Push(SqStack &S,int e){
	//��Ԫ����ջ
	if(S.top - S.base >= S.stacksize){
		//ջ����׷�Ӵ洢�ռ�
		S.base = (int *)realloc(S.base,(S.stacksize + STACKINCREMENT)*sizeof(int));
		if(!S.base){
			printf("Erroe\n");
			return -1;
		}
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*(S.top) = e;
	S.top ++;
	return 1;
}//Push.��ջ����

int Pop(SqStack &S,int &e){
	//ջԪ�س�ջ����e����ֵ
	if(S.top == S.base){
	    printf("Error\n");
		return -1;
	}
	e = *(--S.top);
	return -1;
}//Pop��ջ����

void Conversion(SqStack &S){
	//������ķǸ�ʮ������������ӡ���������Ƶ�����
	int N,e;
	InitStack(S);
	printf("������һ��ʮ���Ƶ�������");
	scanf_s("%d",&N);
	while(N){
		Push(S,N%2);
		N = N/2;
	}
	printf("\n��Ӧ�Ķ����Ƶ�����λ��\n");
	while(!StackEmpty(S)){
		Pop(S,e);
		printf("%d",e);
	}
}//Conversionʮ����ת���ɶ�����

void main(){
	SqStack S;
    //SqQueue Q;
	int e,order;
	char yes_no;

	printf("\t\t             ��  ��  \n");
	printf("\t\t*********************************************************\n");
	printf("\t\t1.Init the stack\n");
	printf("\t\t-----------------------------------------------------------\n");
	printf("\t\t2.Check the stack whether is empty �Ƿ�Ϊ��ջ\n");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t3.Insert the elem  \n");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t4.Delete the elem  \n");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t5.Trandfrom integer to binary integer  ʮ����ת��Ϊ������\n");
	printf("\t\t------------------------------------------------------------\n");
	do{
		printf("Plese enter your choice:");
		scanf_s("%d",&order);
		printf("\n");

		switch (order){
		    case 1:
				InitStack(S);
				break;
			case 2:
				StackEmpty(S);
				break;
			case 3:
				Push(S,e);
				break;
			case 4:
				Pop(S,e);
				break;
			case 5:
				Conversion(S);
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