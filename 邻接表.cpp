#include<iostream>
#include<queue>
#include<memory>

using namespace std;

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

typedef struct Edge{
	int adjvex;	        //��ָ��Ķ����λ�±�
	// EdgeType weight;    //Ȩֵ
	struct Edge *next;	//ָ����һ���ڽӵ�
}Edge;

typedef struct Vertex{
	VertexType value;  //������Ϣ
	Edge *firstedge;   //��ָ��
}Vertex, AdjList[MaxVertexNum];

typedef struct{
	AdjList adjList;
	int vexnum, edgenum;
}AdjListGraph;

// lookup index of vertex u in the graph
int LocateVex(const AdjListGraph& g, VertexType u)
{
    int i;
    for(i = 0; i < g.vexnum; ++i)
        if(u == g.adjList[i].value)
        {
            return i;
        }
            
    return -1;
}

void printGraph(const AdjListGraph& g)
{
    for(int i = 0; i < g.vexnum; i++)
    {
        cout << g.adjList[i].value;
        Edge* edge = g.adjList[i].firstedge;
        while(edge != nullptr)
        {
            cout << "->" << g.adjList[edge->adjvex].value;
            edge = edge->next;
        }
        cout << endl;
    }
}

void deleteGraph(AdjListGraph& g) {
    // TODO
}

void createGraph(AdjListGraph &g) {
    cout << "�����붥����: ";
    cin >> g.vexnum;
    cout << "���������: ";
    cin >> g.edgenum;
    
    cout << "�������������Ϣ: "<<endl;
    for (int i = 0; i < g.vexnum; i++) {
        cin >> g.adjList[i].value;
        g.adjList[i].firstedge = nullptr;
    }
    
    cout << "������ ������Ϣ:" << endl; 
    for (int e = 0; e < g.edgenum; e++) {
        VertexType v1, v2;
        cin >> v1 >> v2;
        int i = LocateVex(g, v1);
        int j = LocateVex(g, v2);
        if (i == -1 || j == -1) {
            cout << "Error edge info" << endl;
        }
        
        Edge* e1 = new Edge();
        e1->adjvex = j;
        e1->next = g.adjList[i].firstedge;
        g.adjList[i].firstedge = e1;
        
        Edge* e2 = new Edge();
        e2->adjvex = i;
        e2->next = g.adjList[j].firstedge;
        g.adjList[j].firstedge = e2;       
    }
}


bool visited[MaxVertexNum];
void BFS(const AdjListGraph& g) {
    for (int i = 0; i < g.vexnum; i++) {
        visited[i] = false;
    }
    queue<int> q;
    for (int i = 0; i < g.vexnum; i++) {
        if (!visited[i]) {
            visited[i] = true;
            // visit
            cout << g.adjList[i].value;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (Edge* edge = g.adjList[u].firstedge; edge != nullptr; edge = edge->next) {
                    if (!visited[edge->adjvex]) {
                        // visit
                        cout << g.adjList[edge->adjvex].value;
                        visited[edge->adjvex] = true;
                        q.push(edge->adjvex);
                    }
                }
            }
        }
    }
    cout << endl;
}

void dfs(const AdjListGraph& g, int u) {
    // visit
    cout << g.adjList[u].value;
    visited[u] = true;
    for (Edge* edge = g.adjList[u].firstedge; edge != nullptr; edge = edge->next) {
        if (!visited[edge->adjvex]) {
            dfs(g, edge->adjvex);
        }
        
    }
}

void DFS(const AdjListGraph& g) {
    for (int i = 0; i < g.vexnum; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < g.vexnum; i++) {
        if (!visited[i]) {
            dfs(g, i);
        }
    }
}

int main () {
    AdjListGraph g;
    createGraph(g);
	printf("�洢�ڽ�����Ϊ��\n");
    printGraph(g);
	printf("\n");
	printf("�����������Ϊ��\n");
    DFS(g);
	printf("\n");
	printf("�����������Ϊ��\n");
    BFS(g);
    deleteGraph(g);
}
