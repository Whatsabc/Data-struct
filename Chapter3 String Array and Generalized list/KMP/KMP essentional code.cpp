//邻接表的生成；
#include<stdio.h>
using namespace std;
#define MVNum 100//最大顶点数；

typedef struct ArcNode//边结点；
{
	int adjvex;//该边所指向顶点的位置;
	struct ArcNode *nextarc;//指向下一条边的指针；
	OtherInfo info;//和边相关的信息；
}ArcNode;

typedef struct VNode//顶点信息；
{
	VerTexType data;
	ArcNode *firstarc;//执行第一条依附该顶点的指针；
}VNode,AdjList[MVNum];//表示邻接表类型；

typedef struct
{
	AdjList vertices;//定义邻接表；
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
		cin>>v1>>v2;
		i=LocateVex(G,v1);
		j=LocateVex(C,v2);
		p1=new ArcNode;
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;G.vertices[i].firstarc=p1;
		p2=new ArcNode;
		p2->adjvex=i;
		p2->nextarc=G.vertices[j].firstarc;G.vertices[j].firstarc=p2;
		//将节点插入顶点的边表头部；
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
struct{
	VerTexType adjvex;
	ArcType lowcost;
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
		u0=closedge[k].adjvex;
		v0=G.vexs[k];
		cout<<u0<<v0;
		closedge[k].lowcost=0;
		