#include<iostream>
using namespace std;
#define MaxInt 32767
#define MVNum 100
//邻接表的结构体声明；
typedef struct {
	int vexs[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph, *AMGraphLink;

//队列的结构体声明；
typedef struct QNode
{
	int data;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//辅助数组Edge声明
struct {
	int Head;
	int Tail;
	int lowcost;
}Edge[MVNum];
int Vexset[MVNum];//辅助数组，表示各顶点自成一个连通分量；
bool visited[MVNum];
//函数定义开始；
void CreateUDN(AMGraphLink &G);//创建邻接表；
int LocateVex(AMGraphLink G, int ch);//确定元素在邻接表中的位置；
void DFS_AM(AMGraphLink G, int v);
void DFS(AMGraphLink G);//深度优先搜索遍历；
void BFS(AMGraphLink G);//广度优先搜索遍历；
void InitQueue(LinkQueue &Q);//初始化队列；
void EnQueue(LinkQueue &Q, int e);//进入队列；
void DeQueue(LinkQueue &Q, int &e);//从队列中删除；
int EmptyQueue(LinkQueue Q);//判断队列是否为空；
void MiniSpanTree_Kruskal(AMGraphLink G);//最小生成树函数
void Sort(AMGraphLink);//冒泡法排序函数；

int main()
{
	AMGraphLink G;
	CreateUDN(G);
	cout << "深度优先遍历：";
	DFS(G);
	cout << endl;
	cout << "广度优先遍历：";
	BFS(G);
	cout << endl;
	cout << "最小生成树：" << endl;;
	MiniSpanTree_Kruskal(G);
	system("pause");
	return 0;
}
void CreateUDN(AMGraphLink &G)//生成最短路径邻接表；
{
	G = new AMGraph;
	cin >> G->vexnum >> G->arcnum;
	int i, j, k, w;
	int v1, v2;
	for (i = 0; i < G->vexnum; i++)
	{
		cin >> G->vexs[i];
	}
	for (i = 0; i < G->vexnum; i++)
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = MaxInt;
		}
	for (k = 0; k < G->arcnum; k++)//依次将节点和边的信息录入邻接表和Edge数组；
	{
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		Edge[k].Head = v1;
		Edge[k].Tail = v2;
		Edge[k].lowcost = w;
		G->arcs[i][j] = w;
		G->arcs[j][i] = G->arcs[i][j];
	}
}

int LocateVex(AMGraphLink G, int ch)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
		if (G->vexs[i] == ch)
			return i;
}

void DFS_AM(AMGraphLink G, int v)
{
	cout << G->vexs[v];
	visited[v] = true;
	int w;
	for (w = 0; w < G->vexnum; w++)
	{
		if ((G->arcs[v][w] != MaxInt) && (!visited[w]))
			DFS_AM(G, w);
	}
}

void DFS(AMGraphLink G)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
		visited[i] = false;
	for (i = 0; i < G->vexnum; i++)
		if (!visited[i])
			DFS_AM(G, i);
}

void BFS(AMGraphLink G)
{
	int w;
	LinkQueue Q;
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		visited[i] = false;
	}
	InitQueue(Q);
	for (i = 0; i < G->vexnum; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			cout << G->vexs[i];
			EnQueue(Q, i);
		}
		while (!EmptyQueue(Q))
		{
			DeQueue(Q, i);
			for (w = 0; w < G->vexnum; w++)
				if (!visited[w] && G->arcs[i][w] != MaxInt)
				{
					visited[w] = true;
					cout << G->vexs[w];
					EnQueue(Q, w);
				}
		}
	}
}

void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = new QNode;
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q, int e)
{
	QueuePtr p = new QNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

void DeQueue(LinkQueue &Q, int &e)
{
	if (Q.front == Q.rear)
		return;
	QueuePtr p;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	delete p;
}

int EmptyQueue(LinkQueue Q)
{
	if (Q.front == Q.front)
		return 1;
	else
		return 0;
}

void MiniSpanTree_Kruskal(AMGraphLink G)
{
	Sort(G);
	int i, j;
	int v1, v2, vs1, vs2;
	for (i = 0; i < G->vexnum; i++)
		Vexset[i] = i;
	for (i = 0; i < G->arcnum; i++)
	{
		v1 = LocateVex(G, Edge[i].Head);
		v2 = LocateVex(G, Edge[i].Tail);
		vs1 = Vexset[v1];
		vs2 = Vexset[v2];
		if (vs1 != vs2)
		{
			cout << Edge[i].Head << "-->" << Edge[i].Tail;
			cout << endl;
			for (j = 0; j < G->vexnum; j++)
				if (Vexset[j] == vs2)
					Vexset[j] = vs1;
		}
	}
}

void Sort(AMGraphLink G)
{
	int i, j;
	int temp;
	for (i = 0; i <(G->arcnum - 1); i++)
		for (j = 0; j < G->arcnum - 1 - i; j++)
		{
			if (Edge[j].lowcost > Edge[j + 1].lowcost)
			{
				temp = Edge[j].Tail;
				Edge[j].Tail = Edge[j + 1].Tail;
				Edge[j + 1].Tail = temp;
				temp = Edge[j].Head;
				Edge[j].Head = Edge[j + 1].Head;
				Edge[j + 1].Head = temp;
				temp = Edge[j].lowcost;
				Edge[j].lowcost = Edge[j + 1].lowcost;
				Edge[j + 1].lowcost = temp;
			}
		}
}
