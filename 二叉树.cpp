#include"stdio.h"
#include"malloc.h"
#define MAX 100

typedef struct BiTNode{
	//二叉链表
	char data;
	struct BiTNode *lchild,*rchild;//左右孩子指针
}BiTNode,*BiTree;

int CreateBiTree(BiTree &T){
	//按先序次序输入二叉树中结点值，*字符表示空树，构造二叉树T
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
		T->data = ch;           //生成根节点  
		CreateBiTree(T->lchild);//构造左子树
		CreateBiTree(T->rchild);//构造右字数
	}
	return 1;
}//CreateBiTree

void PreOrderTraverse(BiTree T){
	//先序遍历二叉树T的递归算法
	if(T){
		printf("%c\t",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}//PerOrderTraverse

void InOrderTraverse(BiTree T){
	//中序遍历二叉树T的递归运算
	if(T){
		InOrderTraverse(T->lchild);
		printf("%c\t",T->data);
		InOrderTraverse(T->rchild);
	}
}//InOrderTraverse

void PostOrderTraverse(BiTree T){
	//后序遍历二叉树T的递归运算
	if(T){
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c\t",T->data);
	}
}//PostOrderTraverse

void PerOrderCounter(BiTree T,int &count,int &count1){
	//统计所有结点以及叶子结点的个数
	if(T){
		if((!T->lchild)&&(!T->rchild)){
			count1 ++;//叶子结点的个数
		}
		count ++;//所有结点的个数
		PerOrderCounter(T->lchild,count,count1);
		PerOrderCounter(T->rchild,count,count1);
	}
}//PerOrderCounter

void main(){
	BiTree T;
	int i=0;
	int j=0;
	int order;


	printf("1.创造一个二叉树，并按先序次序输入二叉树中结点值，*字符表示空树");
	printf("\n");
	printf("2.先序遍历二叉树T");
	printf("\n");
	printf("3.中序遍历二叉树T");
	printf("\n");
	printf("4.后序遍历二叉树T");
	printf("\n");
	printf("5.统计所有结点以及叶子结点的个数");
	printf("\n");
	do{
		printf("\n");
		printf("请输入：");
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
				printf("所用结点的个数：%d\n",i);
				printf("叶子结点的个数：%d\n",j);
				break;
			default:
				printf("\nerror\n");
				break;
	    }
	}while (order!=0);
}