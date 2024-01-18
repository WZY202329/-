#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

#define MAXQSIZE 100         //最大队列长度
#define STACK_INIT_SIZE 100  //存储空间初始分配量
#define STACKINCREMENT 10    //存储空间分配增量

typedef struct{
	int *base;
	int *top;   //栈顶指针
	int stacksize;  //当前已分配的存储空间
}SqStack; //栈

/*typedef struct{
	int *base;  //初始化的动态分配存储空间
	int front;
	int rear;
}SqQueue;//循环队列
*/
int InitStack(SqStack &S){
	//构造一个空栈
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
	//判断栈是否为空
	if(S.top == S.base){
		return 1;
	}
	else{
		return 0;
	}
}//StackEmpty

int Push(SqStack &S,int e){
	//将元素入栈
	if(S.top - S.base >= S.stacksize){
		//栈满，追加存储空间
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
}//Push.入栈操作

int Pop(SqStack &S,int &e){
	//栈元素出栈且用e返回值
	if(S.top == S.base){
	    printf("Error\n");
		return -1;
	}
	e = *(--S.top);
	return -1;
}//Pop出栈操作

void Conversion(SqStack &S){
	//对任意的非负十进制整数，打印输出其二进制的整数
	int N,e;
	InitStack(S);
	printf("请输入一个十进制的整数：");
	scanf_s("%d",&N);
	while(N){
		Push(S,N%2);
		N = N/2;
	}
	printf("\n对应的二进制的整数位：\n");
	while(!StackEmpty(S)){
		Pop(S,e);
		printf("%d",e);
	}
}//Conversion十进制转化成二进制

void main(){
	SqStack S;
    //SqQueue Q;
	int e,order;
	char yes_no;

	printf("\t\t             菜  单  \n");
	printf("\t\t*********************************************************\n");
	printf("\t\t1.Init the stack\n");
	printf("\t\t-----------------------------------------------------------\n");
	printf("\t\t2.Check the stack whether is empty 是否为空栈\n");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t3.Insert the elem  \n");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t4.Delete the elem  \n");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t5.Trandfrom integer to binary integer  十进制转化为二进制\n");
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