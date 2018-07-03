#include<iostream>
using namespace std;
typedef struct {
	int Xaxis;
	int Yaxis;
}PosType;

PosType startlocation, endlocation;
int mazelength, mazewidth;//定义数组的长度和宽度；
int maze[10][10];//定义一个数组用于储存迷宫；
int Thewaycounts;//总共的走法数；

typedef struct {
	int order;
	PosType location;//当前的开始和结束的位置；
	int direction;//下一次前进的方面；1 2 3 4分别代表右下左上；
}ElemType;

typedef struct LNode{//链栈的定义；
	ElemType data;
	struct LNode *next;
}LNode,*LNodeLink;

LNodeLink InitStack(LNodeLink &S);
void Push(LNodeLink &S,ElemType *e);
ElemType Pop(LNodeLink &S);
int EmptyStack(LNodeLink &S);//栈的基本操作

int CreateMaze(int maze[][10],int xaxis,int yaxis);////输出创建好的迷宫
void Visit(int i, int j);//递归算法，得到所有路径后打印；
int Print(int maze[][10], int a[], int b[], int c[], int length, int width, int n);
int MazePath(int maze[][10], PosType start, PosType end, int length, int width);//得到迷宫的遍历路径；

LNodeLink InitStack(LNodeLink &S)
{
	S = NULL;
	return S;
}

void Push(LNodeLink &S, ElemType *e)
{
	LNodeLink p = new LNode;
	p->data.direction = e->direction;
	p->data.order = e->order;
	p->data.location.Xaxis = e->location.Xaxis;
	p->data.location.Yaxis = e->location.Yaxis;
	p->next = S;
	S = p;
}

ElemType Pop(LNodeLink &S)
{
	LNodeLink p;
	ElemType q;
	p = S;
	q = S->data;
	S = S->next;
	delete p;
	return q;
}
int EmptyStack(LNodeLink &S)
{
	if (S == NULL)
		return 1;
	else
		return 0;
}

int CreateMaze(int maze[][10], int xaxis, int yaxis)//输出创建好的迷宫
{
	cout << "Please key the number of maze:" << endl;
	int i, j;
	for (i = 1; i <= yaxis; i++)
		for (j = 1; j <= xaxis; j++)
			cin >> maze[i][j];
	for (i = 0; i <= yaxis + 1; i++)//构建迷宫图形（注意包括围墙）
	{
		for (j = 0; j <= xaxis + 1; j++)
		{
			if (i == 0 || i == yaxis + 1 || j == 0 || j == xaxis + 1)//构建围墙；
				cout << "■";
			else if (maze[i][j] == 1)
				cout << "■";
			else
				cout << "  ";
		}
		cout << endl;
	}
	return 1;
}

PosType NextPos(PosType curpos, int n)//计算当前位置的下一个位置；
{
	PosType loc;
	if (n == 1)
	{
		loc.Xaxis = curpos.Xaxis;
		loc.Yaxis = curpos.Yaxis+1;
	}
	if (n == 2)
	{
		loc.Xaxis = curpos.Xaxis+1;
		loc.Yaxis = curpos.Yaxis;
	}
	if (n == 3)
	{
		loc.Xaxis = curpos.Xaxis-1;
		loc.Yaxis = curpos.Yaxis;
	}
	if (n == 4)
	{
		loc.Xaxis = curpos.Xaxis;
		loc.Yaxis = curpos.Yaxis-1;
	}
	return loc;
}

int Print(int maze[][10], int a[],int b[],int c[],int length,int width,int n)
{
	char mazechar[20][20];
	int i, j;
	for (i = 0; i <= width + 1; i++)
	{
		mazechar[0][i] = 0;
		mazechar[length + 1][i] = 0;
	}
	for (i = 1; i <= length ; i++)
	{
		mazechar[i][0] = 0;
		mazechar[i][width + 1] = 0;
	}
	for(i = 1;i <= length;i++)
		for (j = 1; j <= width; j++)
		{
			if (maze[i][j] == 1)
				mazechar[i][j] = 0;
			else
				mazechar[i][j] = 32;
		}
	for (i = n; i >= 1; i--) 
	{ 
		if (i == n)
			mazechar[a[i]][b[i]] = 'S'; 
		else if (i == 1)
			mazechar[a[i]][b[i]] = 'E';         
		else 
			mazechar[a[i]][b[i]] = '*'; 
	}     
	for (i = 0; i<length + 2; i++)
	{
		for (j = 0; j<width + 2; j++)
		{
			if (mazechar[i][j] == 0)
				cout<<"■";         
			else if (mazechar[i][j] == '*')
				cout<<"◇";         
			else 
				cout<<mazechar[i][j]<<mazechar[i][j];
		}
		cout << endl;
	}
	return 1;
}

void Visit(int i, int j)
{
	int u, k;
	maze[i][j] = 2;
	if (i == endlocation.Xaxis&&j == endlocation.Yaxis)
	{
		for (u = 0; u < mazelength + 2; u++)
		{
			for (k = 0; k < mazewidth + 2; k++)
			{
				if (maze[u][k] == 0)//如果这个地方是空的；
					cout << "  ";
				else if (maze[u][k] == 2)//如果这个地方
					cout << "◇";
				else
					cout << "■";
			}
			cout << endl;
		}
		Thewaycounts++;
	}
	if (maze[i][j + 1] == 0)
		Visit(i, j + 1);
	if (maze[i + 1][j] == 0)
		Visit(i + 1, j);
	if (maze[i][j - 1] == 0)
		Visit(i, j - 1);
	if (maze[i - 1][j] == 0)
		Visit(i - 1, j);
	maze[i][j] = 0;
}

int MazePath(int maze[][10], PosType start, PosType end, int length, int width)
{
	int visit[10][10];//定义标记数组；
	int m, n;
	ElemType e;
	for (m = 0; m < 10; m++)
		for (n = 0; n < 10; n++)
			visit[m][n] = 0;
	LNodeLink S;
	S = InitStack(S);
	PosType curpos = start;
	int curstep = 1;
	do{
		if (!visit[curpos.Xaxis][curpos.Yaxis] && !maze[curpos.Xaxis][curpos.Yaxis])//如果标记数组为0而且迷宫可通过；
		{
			visit[curpos.Xaxis][curpos.Yaxis] = 1;
			e.order = curstep;
			e.location.Xaxis = curpos.Xaxis;
			e.location.Yaxis = curpos.Yaxis;
			e.direction = 1;
			Push(S, &e);
			if (curpos.Xaxis == endlocation.Xaxis &&curpos.Yaxis == endlocation.Yaxis)//如果到达终点；
			{
				LNodeLink p;
				int a[100], b[100], c[100];
				for (p = S, m = 1; p != NULL; p = p->next, m++)
				{
					a[m] = p->data.location.Xaxis;
					b[m] = p->data.location.Yaxis;
					c[m] = p->data.direction;
				}
				for (m = m - 1, n = 1; m > 0; m--, n++)
				{
					cout << a[m] << "," << b[m] << "," << c[m];
					if (n % 4 == 0)//当一行有四个元素的时候换行；
						cout << endl;
				}
				cout << endl;
				Print(maze, a, b, c, length, width, n - 1);//打印每一种情况；
				return 1;
			}
			curpos = NextPos(curpos, 1);
			curstep++;
		}
		else
			if (!EmptyStack(S))
			{
				e = Pop(S);
				while (e.direction == 4 && !EmptyStack(S))//如果这个点四路都不通；
				{
					visit[e.location.Xaxis][e.location.Yaxis] = 2;
					e = Pop(S);//出栈；
				}
				if (e.direction < 4)
				{
					e.direction++;
					Push(S, &e);
					curpos = NextPos(e.location, e.direction);
				}
			}
	} while (!EmptyStack);//当运行结束后栈还是空，输出无法得到路径；
	{
		cout << "Unreachable" << endl;
	}
	return 0;
}

int main()
{
	int i, j;
	Thewaycounts = 0;
	cout << "Please key LENGTH and WIDTH:";
	cin >> mazelength >> mazewidth;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			maze[i][j] = 1;
	CreateMaze(maze, mazelength, mazewidth);//开始构建迷宫；
	cout << "Please key the START x axis y axis:";
	cin >> startlocation.Xaxis >> startlocation.Yaxis;
	cout << "Please key the END x axis y axis:";
	cin >> endlocation.Xaxis >> endlocation.Yaxis;
	MazePath(maze, startlocation, endlocation, mazelength, mazewidth);
	cout << "All maze:" << endl;
	Visit(startlocation.Xaxis, startlocation.Yaxis);
	cout << endl;
	cout<<"The count is:"<<Thewaycounts; 
	system("pause");
	return 0;
}