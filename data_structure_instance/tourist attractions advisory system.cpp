#include<iostream>
#include<string.h>
using namespace std;
#pragma warning(disable:4996)//VS预处理命令，用于忽略_s；可忽略；
#define MaxInt 32767
#define MVNum 100
#define MaxLength 50

typedef struct Vexs {
	char tourist[20];
}Vexs;

typedef struct Arcs {
	char wayto[10];
	int length;
}Arcs;

typedef struct {
	Vexs vexs[MVNum];
	Arcs arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph, *AMGraphLink;

//函数定义开始；
void CreateUDN(AMGraphLink &G);//创建邻接表；
void ShortestPath_DIJ(AMGraphLink G, char vstart[], char vend[]);//迪杰斯特拉算法；
int LocateVex(AMGraphLink G, char ch[]);//确定v1，v2在表中的位置；
void DFS(AMGraphLink G, int k, int v, int e);
void Print(AMGraphLink G, int len);
void DFS_AM(AMGraphLink G, int v, int e);
int ReturnNumV1(AMGraphLink G, char v1[]);
int ReturnNumV2(AMGraphLink G, char v2[]);
int temp[20];//定义暂存数组用于存放逆序生成的路径；
bool visited[MVNum];
int flag;
int solution[MVNum];
int sumcount = 0;

int main()
{
	char v0[20], v1[20];
	int v, e;
	AMGraphLink G = NULL;
	CreateUDN(G);
	while (1)
	{
		cout << "\n请输入起点和终点：";
		cin >> v0 >> v1;
		ShortestPath_DIJ(G, v0, v1);
		v = ReturnNumV1(G, v0);
		e = ReturnNumV1(G, v1);
		cout << "-----以下是全部路径-----" << endl;
		DFS_AM(G, v, e);
		sumcount = 0;
	}
	system("pause");
	return 0;
}

void CreateUDN(AMGraphLink &G)//生成最短路径邻接表；
{
	G = new AMGraph;
	cout << "\n请输入景点数目和路径数目：";
	cin >> G->vexnum >> G->arcnum;
	int i, j, k, w;
	char v1[20], v2[20];
	char wayto[10];
	cout << "\n请依次输入" << G->vexnum << "个节点的名称：" << endl;
	for (i = 0; i < G->vexnum; i++)
	{
		cin >> G->vexs[i].tourist;
	}
	for (i = 0; i < G->vexnum; i++)
		for (j = 0; j < G->vexnum; j++)
		{
			strcpy(G->arcs[i][j].wayto, "NULL");
			G->arcs[i][j].length = MaxInt;
		}
	cout << "\n请依次输入景点与景点的<名称>   <距离>   <到达方式>:" << endl;
	for (k = 0; k < G->arcnum; k++)
	{
		cin >> v1 >> v2 >> w >> wayto;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G->arcs[i][j].length = w;
		strcpy(G->arcs[i][j].wayto, wayto);
		//strcpy(G->arcs[j][i].wayto, G->arcs[i][j].wayto);//无向图
		//G->arcs[j][i].length = G->arcs[i][j].length;
	}
}

void ShortestPath_DIJ(AMGraphLink G, char vstart[], char vend[])//执行DIJ算法；
{
	int n, w, i, min, v, j;
	int v0, v1;
	int tempcount = 1;//令计数器初始化为1；
	v0 = LocateVex(G, vstart);
	v1 = LocateVex(G, vend);
	n = G->vexnum;
	int S[MaxLength], D[MaxLength], Path[MaxLength];
	for (v = 0; v < n; ++v)
	{
		S[v] = -1;
		D[v] = G->arcs[v0][v].length;
		if (D[v] < MaxInt)
			Path[v] = v0;
		else
			Path[v] = -1;
		S[v0] = 1;
		D[v0] = 0;
	}
	for (i = 0; i < n; ++i)
	{
		min = MaxInt;
		for (w = 0; w < n; w++)
			if (S[w] == -1 && (D[w] < min))
			{
				v = w;
				min = D[w];
			}
		S[v] = 1;
		for (w = 0; w < n; ++w)
			if (S[w] == -1 && (D[v] + G->arcs[v][w].length < D[w]))
			{
				D[w] = D[v] + G->arcs[v][w].length;
				Path[w] = v;
			}
	}
	temp[0] = v1;//开始输出最短路径；
	j = Path[v1];
	while (j != -1)
	{
		temp[tempcount] = j;
		j = Path[j];
		tempcount++;
		temp[tempcount] = '\0';
	}
	cout << "\n[最短距离是]";
	cout << D[v1] << endl;//输出最短路径的长度；
	cout << "[最短到达方式]：";
	cout << G->vexs[temp[tempcount-1]].tourist;
	for (i = tempcount - 2; i >= 0; i--)
		cout << "[" << G->arcs[temp[i + 1]][temp[i]].wayto << "]-->" << G->vexs[temp[i]].tourist;
	cout << "\n" << endl;
}

int LocateVex(AMGraphLink G, char ch[])
{
	int i;
	for (i = 0; i < G->vexnum; i++)
		if (strcmp(G->vexs[i].tourist, ch) == 0)
			return i;
}

void DFS(AMGraphLink G, int k, int v, int e)
{
	solution[k] = v;
	visited[v] = true;//将访问过的置为true;
	if (v == e)
		Print(G, k);
	int w;
	for (w = 0; w < G->vexnum; ++w)//依次检查v所有的邻接点w，
	{
		if (!visited[w] && G->arcs[v][w].length != MaxInt)
			DFS(G, k + 1, w, e);//对未访问的邻接点w调用DFS；
	}
	visited[v] = false;
}

void Print(AMGraphLink G, int len)
{
	flag = 1;
	int sum = 0, i;
	sumcount++;
	cout << "[这是第" << sumcount << "种]" << endl;
	cout << G->vexs[solution[1]].tourist;
	for (i = 2; i <= len; ++i) //第一个点已经打印,打印剩下的点
	{
		cout << "[" << G->arcs[solution[i - 1]][solution[i]].wayto << "]-->" << G->vexs[solution[i]].tourist;
		sum += G->arcs[solution[i - 1]][solution[i]].length;
	}
	cout << endl << "该路径总路程为:" << sum  << endl;
	cout << endl;
}

void DFS_AM(AMGraphLink G, int v, int e)
{
	flag = 0;//有无路径标记
	memset(visited, 0, sizeof(visited));
	DFS(G, 1, v, e);//从第一步起点开始
	if (!flag) 
		cout << "无可行路径!" << endl;
}

int ReturnNumV1(AMGraphLink G, char v1[])
{
	int i;
	for (i = 0; i < G->arcnum; i++)
		if (strcmp(G->vexs[i].tourist, v1) == 0)
			return i;
}

int ReturnNumV2(AMGraphLink G, char v2[])
{
	int i;
	for (i = 0; i < G->arcnum; i++)
		if (strcmp(G->vexs[i].tourist, v2) == 0)
			return i;
}
