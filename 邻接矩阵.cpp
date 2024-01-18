#include<iostream>
#include<stack>
#include<queue>
using namespace std;

#define VerNum 100/*��󶥵���Ϊ100*/
bool visited[VerNum];
typedef int VerType;/*��������Ϊ������*/
typedef int EdType;/*���ߵ�ȨֵΪ����*/




typedef struct
{
	VerType vexs[VerNum];
	EdType edges[VerNum][VerNum];
	int n;//������
	int	e;//����
	int book[VerNum];//�ж��Ƿ񱻷��ʹ��Ľڵ�
}MGraph;/*MGraph�����ڽӾ���洢��ͼ����*/


void CreateMGraph(MGraph *G)/*��������ͼG���ڽӾ���洢*/
{
	int i,j,k,w;
	char ch;
	printf("�����붥�����ͱ���(�����ʽ��������������):\n");
	scanf("%d,%d",&(G->n),&(G->e));
	printf("�����붥����Ϣ�������ʽ�������<CR�س�>��:\n");
	for(i=0;i<G->n;i++)
		scanf("\n%c",&(G->vexs[i]));
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++)
			G->edges[i][j]=0;/*��ʼ���ڽӾ���*/
	printf("������ÿ���߶�Ӧ�������������ţ������ʽΪ��i,j,w��:\n");
	for(k=0;k<G->e;k++)
	{
		scanf("%d,%d,%d",&i,&j,&w);
		G->edges[i][j]=w;
		G->edges[j][i]=w;
	}
}

void print(MGraph *G)
{
	int i,j;
	printf("�ڽӾ���Ϊ��\n");
	for(i=0;i<G->n;i++){
		for(j=0;j<G->n;j++)
			printf("%5d",G->edges[i][j]);
	        printf("\n");
	}
}

//�����������
void DFS(MGraph *G,int ves)
{
	stack<int> s;//����һ��ջ
	printf("%d",ves);

	G->book[ves] = 1;//�Ѿ����ʹ��ڵ�ves��
	s.push(ves);//��ջ

	while(!s.empty())
	{
		int data,i;
		data=s.top();//ȥtop�Ķ���
		for(i=0;i<G->n;i++)
		{
			if(G->edges[data][i] !=0&&G->book[i] !=1)
			{
				printf("%d",i);
				G->book[i]=1;
				s.push(i);
				break;//��ʼ������һ������ڽӾ���
			}
		}
		if(i == G->n)//data���ڵĽڵ㶼���ʽ�����
		{
			s.pop();
		}
	}

}
//�����������
void BFS(MGraph *G,int ves)
{
	queue<int> q;
	printf("%d",ves);//��ӡves
	visited[ves]=1;//����ves�ѱ�����
	q.push(ves);//�����

	while(!q.empty())
	{
		int data,i,w;
		data = q.front();//����ͷԪ�س��ӣ���ʼ����u�������ڽӵ�
		q.pop();
		for(i=0;i<G->n;i++)
		{
			if(G->edges[data][i]&&!visited[i])//����u��w���бߣ��Ҷ���δ������
			{
				printf("%d",i);
				q.push(i);
				visited[i]=1;
			}
		}
	}
}
void main()
{
	int e,a;
	MGraph g;
	CreateMGraph(&g);
	print(&g);
	printf("�����������������������\n");
	printf("��������㣺\n");
	scanf("%d",&e);
	DFS(&g,e);
	printf("\n");
	printf("���������й������������\n");
	printf("��������㣺\n");
	scanf("%d",&a);
	BFS(&g,a);
	printf("\n");
}