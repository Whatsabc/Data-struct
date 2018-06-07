//邻接表的建立和十字链表的定义；
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