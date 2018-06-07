//迪杰斯特拉算法的实现
//假设用带权的邻接矩阵arcs来表示带权有向图G，G.arcs[i][j]表示弧<vi,vj>上的权值。若<vi,vj>不存在，置其值为无穷大，源点为v0;
//一维数组S[i]：记录从源点v0到终点vi是否已被确定为最短路径长度，true表示确定，false表示不确定；
//一维数组path[i]记录从v0到终点vi的当前最短路径长度上vi的直接前驱序号。其初值为：如果从v0到vi有弧，则path[i]为v0;否则为-1；
//一维数组D[i]：记录从源点v0到终点vi的当前最短路径长度。其初值为：如果从v0到vi有弧，则D[i]为弧上的权值；否则为无穷；
void ShorttestPath_DIJ(AMGraph G,int v0)
{
	n=G.vexnum;
	for(v=0;v<n;v++)
	{
		S[v]=false;
		D[v]=G.arcs[v0][v];
		if(D[v]<MaxInt)
			Path[v]=v0;
		else
			Path[v]=-1;
		S[v]=true;
		D[v0]=0;
		for(i=1;i<n;i++)
		{
			min=MaxInt;
			for(w=0;w<n;w++)
				if(!S[w]&&D[w]<min)
				{
					v=w;
					min=D[w];
				}
				
		