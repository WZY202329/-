#include<stdio.h>
#include<stdlib.h>
#define VertexMax 20//最大顶点数为100
#define MaxInt 32767//表示最大整数

typedef char VertexType;//每个顶点数据类型为字符型

typedef struct//邻接矩阵构建结构体
{
	VertexType Vertex[VertexMax];//存放顶点元素的一维数据
	int AdjMatrix[VertexMax][VertexMax];//邻接矩阵二维数组
	int vexnum,arcnum;//图的顶点数和边数
}MGraph;
typedef struct//辅助数组结构体（候选最短边）
{
	VertexType adjvex;//候选最短边的邻接点
	int lowcost;//候选最短边的权值
}ShortEdge;
int LocateVex(MGraph *G,VertexType v)//查找元素在一维数组Vertex[]中的下标，并返回下标
{
	int i;
	for(i=0;i<G->vexnum;i++)
	{
		if(v==G->Vertex[i])
		{
			return i;
		}
	}
	printf("No such Vertex!\n");
	return -1;
}
void CreateUDN(MGraph *G)//构建无向网
{
	int i,j;
	//1.输入定点数和边数
	printf("输入顶点数和边数：\n");
	printf("顶点数 n=");
	scanf("%d",&G->vexnum);
	printf("边数 e=");
	scanf("%d",&G->arcnum);
	printf("\n");

	printf("\n");
	//2.输入顶点元素
	printf("输入顶点元素(无需空格隔开)：");
	scanf("%s",&G->Vertex);
	printf("\n");
	//3.初始化矩阵
	for(i=0;i<G->vexnum;i++)
		for(j=0;j<G->vexnum;j++)
		{
			G->AdjMatrix[i][j]=MaxInt;
		}
	//4.构建邻接矩阵
	int n,m;
	VertexType v1,v2;
	int w;//v1->v2的权值

	printf("请输入边的信息和权值(AB,15):\n");
	for(i=0;i<G->arcnum;i++)
	{
		printf("请输入第%d条边信息以及权值：",i+1);
		scanf(" %c%c,%d",&v1,&v2,&w);
		n=LocateVex(G,v1);//获取v1对应的在Vertex数组中的坐标
		m=LocateVex(G,v2);//获取v2对应的在Vertex数组中的坐标

		if(n==-1||m==-1)
		{
			printf("NO This Vertex!\n");
			return;
		}
		G->AdjMatrix[n][m]=w;
		G->AdjMatrix[m][n]=w;//无向网仅此处不同
	}
}
void print(MGraph G){
	int i,j;
	printf("\n-----------------");
	printf("\n 邻接矩阵：\n\n");
	    printf("\t ");
		for(i=0;i<G.vexnum;i++)
		printf("\t%c",G.Vertex[i]);
		printf("\n");
		for(i=0;i<G.vexnum;i++)
		{
			printf("\t%c",G.Vertex[i]);
			for(j=0;j<G.vexnum;j++)
			{
				if(G.AdjMatrix[i][j]==MaxInt)
				printf("\t0");
				else printf("\t%d",G.AdjMatrix[i][j]);
			}
			printf("\n");
		}
}
int minimal(MGraph *G,ShortEdge *shortedge)
{
	int i,j;
	int min,loc;

	min=MaxInt;
	for(i=1;i<G->vexnum;i++)
	{
		if(min>shortedge[i].lowcost&&shortedge[i].lowcost!=0)
		{
			min=shortedge[i].lowcost;
			loc=i;
		}
	}
	return loc;
}
void MinSpanTree_Prim(MGraph *G,VertexType start)
{
	int i,j,k;
	ShortEdge shortedge[VertexMax];
	//1.处理起始点start
	k=LocateVex(G,start);
	for(i=0;i<G->vexnum;i++)
	{
		shortedge[i].adjvex=start;
		shortedge[i].lowcost=G->AdjMatrix[k][i];
	}
	shortedge[k].lowcost=0;

	//2.处理后续节点
	for(i=0;i<G->vexnum-1;i++)
	{
		k=minimal(G,shortedge);

		printf("%c->%c,%d\n",shortedge[k].adjvex,G->Vertex[k],shortedge[k].lowcost);
		shortedge[k].lowcost=0;
		for(j=0;j<G->vexnum;j++)//u中加入了新节点，可能出现新的最短路径，所以更新shartedge的数组
		{
			if(G->AdjMatrix[k][j]<shortedge[j].lowcost)//有新的最短路径出现的时候，将其替换进shortedge数组
			{
				shortedge[j].lowcost=G->AdjMatrix[k][j];
				shortedge[j].adjvex=G->Vertex[k];
			}
		}
	}
}
int main()
{
	VertexType start;
	MGraph G;
	CreateUDN(&G);
	print(G);

	printf("请输入起始点：");
	scanf(" %c",&start);//%c前面有空格
	MinSpanTree_Prim(&G,start);

	return 0;
}