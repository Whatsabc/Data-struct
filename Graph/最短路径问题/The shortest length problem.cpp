#include<iostream>
using namespace std;
#define MaxInt 32767
#define MVNum 100
#define MaxLength 50

typedef struct {
	char vexs[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph,*AMGraphLink;

//函数定义开始；
void CreateUDN(AMGraphLink &G);//创建邻接表；
void ShortestPath_DIJ(AMGraphLink G, char vstart,char vend);//迪杰斯特拉算法；
int LocateVex(AMGraphLink G,char ch);//确定v1，v2在表中的位置；
char Temp[50] = { 0 };//定义暂存数组用于存放逆序生成的路径；

int main()
{
	char v0, v1;
	AMGraphLink G=NULL;
	CreateUDN(G);
	cout << "请输入起点字母和终点字母：";
	cin >> v0 >> v1;
	ShortestPath_DIJ(G,v0,v1);
	system("pause");
	return 0;
}

void CreateUDN(AMGraphLink &G)//生成最短路径邻接表；
{
	G = new AMGraph;
	cin >> G->vexnum >> G->arcnum;
	int i, j, k, w;
	char v1, v2;
	for (i = 0; i < G->vexnum; i++)
	{
		cin >> G->vexs[i];
	}
	for (i = 0; i < G->vexnum; i++)
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = MaxInt;
		}
	for (k = 0; k < G->arcnum; k++)
	{
		cin >> v1 >> v2 >> w;
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G->arcs[i][j] = w;
		G->arcs[j][i] = G->arcs[i][j];
	}
}

void ShortestPath_DIJ(AMGraphLink G, char vstart,char vend)//执行DIJ算法；
{
	int n, w, i, min, v, j;
	int v0, v1;
	int tempcount=1;//令计数器初始化为1；
	v0 = LocateVex(G,vstart);
	v1 = LocateVex(G,vend);
	n = G->vexnum;
	int S[MaxLength] = { 0 };//定义三个辅助数组，注意将辅助数组置为空；
	int D[MaxLength] = { 0 };
	int Path[MaxLength] = { 0 };
	for (v = 0; v < n; ++v)
	{
		S[v] = -1;
		D[v] = G->arcs[v0][v];
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
			if (S[w] == -1 && (D[v] + G->arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G->arcs[v][w];
				Path[w] = v;
			}
	}
	cout << D[v1] << endl;//输出最短路径的长度；

	Temp[0]=G->vexs[v1];//开始输出最短路径；
	j = Path[v1];
	while (j != -1)
	{
		Temp[tempcount] = G->vexs[j];
		j = Path[j];
		tempcount++;
		Temp[tempcount] = '\0';
	}
	for (i = strlen(Temp) - 1; i >= 0; i--)
		cout << Temp[i]<<" ";
}

int LocateVex(AMGraphLink G,char ch)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
		if (G->vexs[i] == ch)
			return i;
}