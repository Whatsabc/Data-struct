//最小生成树实践；
//克鲁斯卡尔算法  
//在连通网中求出最小生成树  
#include <stdio.h>  
#include <stdlib.h>  
#define MAXEDGE 20  
#define MAXVEX  20  
#define INFINITY 65535  
  
typedef struct {  
    int arc[MAXVEX][MAXVEX];  
    int numVertexes, numEdges;//顶点数，边数  
}MGraph;  
  
typedef struct {  
    int begin;  
    int end;  
    int weight;  
}Edge;   //对边集数组Edge结构的定义  
  
//创建图的邻接矩阵  
void CreateMGraph(MGraph *G) 
{  
    int i, j;  
    G->numEdges=11;  
    G->numVertexes=7;  
    for (i = 0; i < G->numVertexes; i++) 
	{  
        for ( j = 0; j < G->numVertexes; j++) 
		{  
            if (i==j)  
                G->arc[i][j]=0;  
            else  
                G->arc[i][j] = G->arc[j][i] = INFINITY;  
        }  
    }  
    G->arc[0][1]=7;  
    G->arc[0][3]=5;  
    G->arc[1][2]=8;  
    G->arc[1][3]=9;  
    G->arc[1][4]=7;  
    G->arc[2][4]=5;  
    G->arc[3][4]=15;  
    G->arc[3][5]=6;  
    G->arc[4][5]=8;  
    G->arc[4][6]=9;  
    G->arc[5][6]=11;  
    for(i = 0; i < G->numVertexes; i++) 
	{  
        for(j = i; j < G->numVertexes; j++) 
		{  
            G->arc[j][i] =G->arc[i][j];  
        }  
    }  
}  
  
//快速排序的条件  
int cmp(const void* a, const void* b) 
{	
    return (*(Edge*)a).weight - (*(Edge*)b).weight;  
}  
  
//找到根节点  
int Find(int *parent, int f) 
{  
    while ( parent[f] > 0) 
	{  
        f = parent[f];  
    }  
    return f;  
}  
  
// 生成最小生成树  
void MiniSpanTree_Kruskal(MGraph G) 
{  
    int i, j, n, m;  
    int k = 0;  
    int parent[MAXVEX]; //用于寻找根节点的数组  
  
    Edge edges[MAXEDGE]; //定义边集数组,edge的结构为begin,end,weight,均为整型  
  
    // 用来构建边集数组并排序(将邻接矩阵的对角线右边的部分存入边集数组中)  
    for ( i = 0; i < G.numVertexes-1; i++) 
	{  
        for (j = i + 1; j < G.numVertexes; j++) 
		{  
            if (G.arc[i][j] < INFINITY) 
			{  
                edges[k].begin = i; //编号较小的结点为首  
                edges[k].end = j;   //编号较大的结点为尾  
                edges[k].weight = G.arc[i][j];  
                k++;  
            }  
        }  
    }  
  
    //为边集数组Edge排序  
    qsort(edges, G.numEdges, sizeof(Edge), cmp);  
	
    for (i = 0; i < G.numVertexes; i++)  
        parent[i] = 0;  
  
    printf("打印最小生成树：\n");  
    for (i = 0; i < G.numEdges; i++) 
	{  
        n = Find(parent, edges[i].begin);//寻找边edge[i]的“首节点”所在树的树根  
        m = Find(parent, edges[i].end);//寻找边edge[i]的“尾节点”所在树的树根  
  
        //假如n与m不等，说明两个顶点不在一棵树内，因此这条边的加入不会使已经选择的边集产生回路  
        if (n != m) 
		{  
            parent[n] = m;  
            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);  
        }  
    }  
}  
  
int main(void)  
{  
    MGraph G;  
    CreateMGraph(&G);  
    MiniSpanTree_Kruskal(G);  
  
    return 0;  
}  
//普里姆算法；
#include<stdio.h>  
#include<stdlib.h>  
#include<malloc.h>  
#include<string.h>  
#define MAX 100  
#define INF (~(0x1<<31))  
typedef struct Graph {  
    char vexs[MAX];  
    int vexnum;  
    int edgnum;  
    int matrix[MAX][MAX];  
} Graph,*PGraph;  
  
typedef struct EdgeData {  
    char start;  
    char end;  
    int weight;  
} EData;  
  
static int get_position(Graph g,char ch)  
{  
    int i;  
    for(i=0; i<g.vexnum; i++)  
        if(g.vexs[i]==ch)  
            return i;  
    return -1;  
}  
  
Graph* create_graph()  
{  
    char vexs[]= {'A','B','C','D','E','F','G'};  
    int matrix[][7]=  
    {  
        {0,12,INF,INF,INF,16,14},  
        {12,0,10,INF,INF,7,INF},  
        {INF,10,0,3,5,6,INF},  
        {INF,INF,3,0,4,INF,INF},  
        {INF,INF,5,4,0,INF,8},  
        {16,7,6,INF,2,0,9},  
        {14,INF,INF,INF,8,9,0}  
    };  
    int vlen=sizeof(vexs)/sizeof(vexs[0]);  
    int i,j;  
    Graph *pG;  
    if((pG=(Graph*)malloc(sizeof(Graph)))==NULL)  
        return NULL;  
    memset(pG,0,sizeof(pG));  
    pG->vexnum=vlen;  
    for(i=0; i<pG->vexnum; i++)  
        pG->vexs[i]=vexs[i];  
    for(i=0; i<pG->vexnum; i++)  
        for(j=0; j<pG->vexnum; j++)  
            pG->matrix[i][j]=matrix[i][j];  
    for(i=0; i<pG->vexnum; i++)  
    {  
        for(j=0; j<pG->vexnum; j++)  
        {  
            if(i!=j&&pG->matrix[i][j]!=INF)  
                pG->edgnum++;  
        }  
    }  
    pG->edgnum/=2;  
    return pG;  
}  
  
void print_graph(Graph G)  
{  
    int i,j;  
    printf("Matrix Graph: \n");  
    for(i=0; i<G.vexnum; i++)  
    {  
        for(j=0; j<G.vexnum; j++)  
            printf("%10d ",G.matrix[i][j]);  
        printf("\n");  
    }  
}  
  
EData* get_edges(Graph G)  
{  
    EData *edges;  
    edges=(EData*)malloc(G.edgnum*sizeof(EData));  
    int i,j;  
    int index=0;  
    for(i=0; i<G.vexnum; i++)  
    {  
        for(j=i+1; j<G.vexnum; j++)  
        {  
            if(G.matrix[i][j]!=INF)  
            {  
                edges[index].start=G.vexs[i];  
                edges[index].end=G.vexs[j];  
                edges[index].weight=G.matrix[i][j];  
                index++;  
            }  
        }  
    }  
    return edges;  
}  
  
void prim(Graph G,int start)  
{  
    int min,i,j,k,m,n,sum;  
    int index=0;  
    char prim[MAX];  
    int weight[MAX];  
  
    prim[index++]=G.vexs[start];  
  
    for(i=0; i<G.vexnum; i++)  
        weight[i]=G.matrix[start][i];  
    weight[start]=0;  
  
    for(i=0; i<G.vexnum; i++)  
    {  
       //i用来控制循环的次数，每次加入一个结点，但是因为start已经加入，所以当i为start是跳过  
        if(start==i)  
            continue;  
        j=0;  
        k=0;  
        min=INF;  
        for(k=0; k<G.vexnum; k++)  
        {  
            if(weight[k]&&weight[k]<min)  
            {  
                min=weight[k];  
                j=k;  
            }  
        }  
        sum+=min;  
        prim[index++]=G.vexs[j];  
        weight[j]=0;  
        for(k=0; k<G.vexnum; k++)  
        {  
            if(weight[k]&&G.matrix[j][k]<weight[k])  
                weight[k]=G.matrix[j][k];  
        }  
    }  
    // 计算最小生成树的权值  
    sum = 0;  
    for (i = 1; i < index; i++)  
    {  
        min = INF;  
        // 获取prims[i]在G中的位置  
        n = get_position(G, prim[i]);  
        // 在vexs[0...i]中，找出到j的权值最小的顶点。  
        for (j = 0; j < i; j++)  
        {  
            m = get_position(G, prim[j]);  
            if (G.matrix[m][n]<min)  
                min = G.matrix[m][n];  
        }  
        sum += min;  
    }  
    printf("PRIM(%c)=%d: ", G.vexs[start], sum);  
    for (i = 0; i < index; i++)  
        printf("%c ", prim[i]);  
    printf("\n");  
}  
  
int main()  
{  
    Graph *pG;  
    pG=create_graph();  
    print_graph(*pG);  
    prim(*pG,0);  
} 