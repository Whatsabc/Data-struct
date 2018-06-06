//邻接表的建立和十字链表的定义；
//最小生成树；
#include<stdio.h>
using namespace std;
#define MVNum 100//

typedef struct ArcNode//定义边结点；
{
	int adjvex;//该边所指向顶点的位置；
	struct ArcNode *nextarc;//指向下一条边的指针；
	OtherInfo info;//与边的有关信息；
}ArcNode;

typedef struct VNode//表头节点的信息；
{
	VerTexType data;
	ArcNode *firstarc;//指向第一条依附于该顶点的边的指针；
}VNode,AdjList[MVNum];//Adjlist表示邻接表类型；

typedef struct//定义邻接表；
{
	AdjList vertices;
	int vexnum, arcnum;//图的当前顶点数和边数；
}ALGraph;

int main()
{

}

int CreateUDG(ALGraph &G)
{
	cin>>G.vexnum>>G.arcnum;
	for(i=0;i<G.vexnum;i++)
	{
		cin>>G.veretices[i].data;
		G.vertices[i].firstarcs=NULL;
	}
	for(k=0;k<G.arcnum,k++)
	{
		cin>>v1>>v2;//输入一条边依附的两个顶点；
		i=LocateVex(G,v1);
		j=LocateVex(C,v2);
		p1=new ArcNode;//生成一个新的边结点*p1;
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;G.vertices[i].firstarc=p1;
		p2=new ArcNode;
		p2->adjvex=i;
		p2->nextarc=G.vertices[j].firstarc;G.vertices[j].firstarc=p2;
	}
return 1;
}

//十字链表的定义；
#define MAX_VERTEX_NUM 20
typedef struct ArcBox{
	int tailvex,headvex;
	struct ArcBox *hlink,*tlink;
	InfoType *info;
}ArcBox;

//普里姆算法
//设置一个辅助数组closedge，记录从U到V-U具有最小权值的各边；
struct{
	VerTexType adjvex;//最小边在U中的那个顶点；
	ArcType lowcost;//最小边上的权值；
}closedge[MVNum];

void MiniSpanTree_Prim(AMGraph G,VerTexType u)
{
	k=LocateVex(G,u);
	for(j=0;j<G.vexnum;j++)
		if(j!=k)
		closedge[j]={u,G.arcs[k][j]};
	closedge[k].lowcost=0;
	for(i=0;i<G.vexnum;i++)
	{
		k=Min(closedge);
		//求出T的下一个结点：第k个顶点，closedge[k]中存有当前最小边；
		u0=closedge[k].adjvex;//u0为当前最小边的一个顶点，u0属于U；
		v0=G.vexs[k];//v0为当前最小边的另一个顶点，v0属于V-U；
		cout<<u0<<v0;//输出当前最小边(u0,v0)；
		closedge[k].lowcost=0;//第k个顶点并入U集；
		for(j=0;j<G.vexnum;j++)
			if(G.arcs[k][j]<closedge[j].lowcost)//新顶点并入U集后重新选择最小边；
				closedge[j]={G.vexs[k],G.arcs[k][j]};
	}
}

//克鲁斯卡尔算法
//1.结构体数组Edge：储存边的信息，包括边的两个顶点信息和权值；
struct{
	VerTexType Head//边的始点；
	VerTexType Tail;//边的终点；
	ArcType lowcost;//边上的权值；
}Edge[arcnum];
//Vexset[i],标志各个顶点所属的连通分量。对于每个顶点vi属于V，在辅助数组中存在一个相应的元素Vexset[i]表示该顶点所在的连通分量；
//初始时Vexset[i]=i；表示各顶点自成一个连通分量；
//辅助数组Vexset[i]的定义；
int Vexset[MVNum];

void MinSpanTree_Kruskal(AMGraph G)
{
	Sort(Edge);//将辅助数组Edge中的元素按权值大小从小到大排序；
	for(i=0;i<G.vexnum;i++)//辅助数组，表示各顶点自成一个连通分量；
		Vexset[i]=i;
	for(i=0;i<G.arcnum;i++)//依次查看数组Edge中的边；
	{
		v1=LocateVex(G,Edge[i].Head);//v1为边始边Head的下标;
		v2=LocateVex(G.Edge[i].Tail);//v2为边的终点Tail的下标；
		vs1=Vexset[v1];//获取边Edge[i]的始边所在的连通分量vs1;
		vs2=Vexset[v2];//获取边Edge[i]的始边所在的连通分量vs2;
		if(vs1!=vs2)//边的两个顶点分属不同的连通分量；
		{
			cout<<Edge[i].Head<<Edge[i].Tail;
			for(j=0;j<G.vexnum;j++)//合并vs1,vs2l两个分量，即两个集合统一编号；
				if(Vexset[j]==vs2)//编号集合为vs2的都改为vs1;
					Vexset[j]=vs1;
		}	
	}
}
		
	