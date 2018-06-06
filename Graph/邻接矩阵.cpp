#include<iostream>
using namespace std;
#define MaxInt 32767
#define MVNum 100
typedef char VerTexType;//假设顶点的数据类型为字符型；
typedef int ArcType;//假设边的权值整型类型为整型；

typedef struct
{
	VerTexType vexs[MVNum];//顶点表；
	ArcType arcs[MVNum][MVNum];//邻接矩阵；
	int vexnum, arcnum;//图的点数和边数；
}AMGraph;

int main()
{
	int CreateUDN(AMGraph &G);
	system("pause");
	return 0;
}

int CreateUDN(AMGraph &G)
{
	int i, j, k;
	cin >> G.vexnum >> G.arcnum;//输入总顶点数，总边数；
	for (i = 0; i < G.vexnum; i++)
	{
		cin >> G.vexs[i];
	}
	for(i=0;i<G.vexnum;i++)//初始化邻接矩阵；
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = MaxInt;
		}
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2 >> w;//输入一条边依附的顶点和权值，[v1,v2 是顶点，w是权值]；
		i = LocateVex(G, v1);//LocateVex是一个函数，用于确定v1，v2在G中的位置，即顶点数组的下标；
		j = LocateVex(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];//置对称边权值为w；
	}
	return OK;
}
//若要建立无向图，只需要对上述算法做两处小小的改动，一是初始化邻接矩阵时，将边的权值都初始化为0；二是构造邻接矩阵时，将权值w改为常量1；