#include<iostream>
#include<stack>
#include<queue>
using namespace std;

#define VerNum 100/*最大顶点数为100*/
bool visited[VerNum];
typedef int VerType;/*顶点类型为整形型*/
typedef int EdType;/*产边的权值为整形*/




typedef struct
{
	VerType vexs[VerNum];
	EdType edges[VerNum][VerNum];
	int n;//顶点数
	int	e;//边数
	int book[VerNum];//判断是否被访问过的节点
}MGraph;/*MGraph是以邻接矩阵存储的图类型*/


void CreateMGraph(MGraph *G)/*建立有向图G的邻接矩阵存储*/
{
	int i,j,k,w;
	char ch;
	printf("请输入顶点数和边数(输入格式：顶点数，边数):\n");
	scanf("%d,%d",&(G->n),&(G->e));
	printf("请输入顶点信息（输入格式：顶点号<CR回车>）:\n");
	for(i=0;i<G->n;i++)
		scanf("\n%c",&(G->vexs[i]));
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++)
			G->edges[i][j]=0;/*初始化邻接矩阵*/
	printf("请输入每条边对应的两个顶点的序号（输入格式为：i,j,w）:\n");
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
	printf("邻接矩阵为：\n");
	for(i=0;i<G->n;i++){
		for(j=0;j<G->n;j++)
			printf("%5d",G->edges[i][j]);
	        printf("\n");
	}
}

//深度优先搜索
void DFS(MGraph *G,int ves)
{
	stack<int> s;//创建一个栈
	printf("%d",ves);

	G->book[ves] = 1;//已经访问过节点ves了
	s.push(ves);//入栈

	while(!s.empty())
	{
		int data,i;
		data=s.top();//去top的顶点
		for(i=0;i<G->n;i++)
		{
			if(G->edges[data][i] !=0&&G->book[i] !=1)
			{
				printf("%d",i);
				G->book[i]=1;
				s.push(i);
				break;//开始遍历下一个点的邻接矩阵
			}
		}
		if(i == G->n)//data相邻的节点都访问结束了
		{
			s.pop();
		}
	}

}
//广度优先搜索
void BFS(MGraph *G,int ves)
{
	queue<int> q;
	printf("%d",ves);//打印ves
	visited[ves]=1;//顶点ves已被访问
	q.push(ves);//入队列

	while(!q.empty())
	{
		int data,i,w;
		data = q.front();//将队头元素出队，开始访问u的所有邻接点
		q.pop();
		for(i=0;i<G->n;i++)
		{
			if(G->edges[data][i]&&!visited[i])//顶点u和w间有边，且顶点未被访问
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
	printf("接下来进行深度优先搜索：\n");
	printf("请输入起点：\n");
	scanf("%d",&e);
	DFS(&g,e);
	printf("\n");
	printf("接下来进行广度优先搜索：\n");
	printf("请输入起点：\n");
	scanf("%d",&a);
	BFS(&g,a);
	printf("\n");
}