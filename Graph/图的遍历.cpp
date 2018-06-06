//深度优先搜索遍历连通图
bool visted[MVNum];
void DFS(Graph G,int v)
{
	cout<<v;
	visted[v]=ture;//将标志数组置为true;
	for(w=FirstAdjVex(G,v),w>=0;w=NextAdjVex(G,v,w))//依次检查所有邻接点，FirstAdjVex表示第一个邻接点；
	{
		if(!visted[w]);
			DFS(G,w);
	}
}
//深度优先搜索非连通图；
void DFSTraverse(Graph G)
{
	for(v=0;v<G.vexnum;v++)
	{
		visted[v]=false;
	}
	for(v=0;v<G.vexnum;v++)
	{
		if(!visted[v])
			DFS(G,v);
	}
}
