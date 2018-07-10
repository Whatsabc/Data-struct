#include<iostream>
#include<string>
#define MAXSIZE 10
using namespace std;

int sumplayersnumber;
int dt[3] = { 5,3,1 };

typedef struct Player {
	int number;
	string name;
	int count = 0;
}Player,*LinkPlayer;

typedef struct SqList {
	Player r[MAXSIZE + 1];
	int length = 0;
}SqList,*SqListLink;

void Counts(LinkPlayer &p);//计数函数；
SqListLink InitSort(LinkPlayer p);//初始化成员结构体；
LinkPlayer InitPlayer();//初始化排序结构体；
void PrintPlayers(LinkPlayer p);//打印成员名单；
void InsertSort(SqListLink &L);//直接插入排序；
void BInsertSort(SqListLink & L);//折半插入排序；
void ShellInsert(SqListLink &L, int dk);
void ShellSort(SqListLink &L, int dt[], int t);//希尔排序；
void PrintList(SqListLink L);//打印排序后的成员名单；

void Counts(LinkPlayer &p)
{
	int playernumber = 10;//每个投票所代表的选手；
	while (playernumber != 0)
	{
		cout << "Please vote for everyone:" << " [1-" << sumplayersnumber << "] as every people" << endl;
		cin >> playernumber;
		int i;
		for (i = 1; i <= playernumber; i++)//依次与所有人比较，如果与某一个人相同，这个人的票数++；
			if (playernumber == p[i].number)
			{
				p[i].count++;
				cout << p[i].name << "'s count is" << p[i].count << endl;
			}
	}
}

LinkPlayer InitPlayer()
{
	cout << "Please key sum player's number:[1-9]";
	cin >> sumplayersnumber;
	LinkPlayer player = new Player[sumplayersnumber+1];
	int i;
	for (i = 1; i <= sumplayersnumber; i++)//位置1开始初始化；
	{
		player[i].number= i;
		cout << "This people's number is:" << i << endl;
		cout << "Please key his name:";
		cin>>player[i].name;
	}
	return player;
}


void PrintPlayers(LinkPlayer p)
{
	int i;
	cout << "NO.	Name	Count" << endl;
	for (i = 1; i <= sumplayersnumber; i++)
	{
		cout << p[i].number << "	";
		cout << p[i].name << "	";
		cout << p[i].count << endl;
	}
}
void PrintList(SqListLink L)
{
	int i;
	cout << "NO.	Name	Count" << endl;
	for (i = 1; i <= L->length; i++)
	{
		cout << L->r[i].number << "	";
		cout << L->r[i].name << "	";
		cout << L->r[i].count << endl;
	}
}

SqListLink InitSort(LinkPlayer p)
{
	int i;
	SqListLink L = new SqList;
	for (i = 1; i <= sumplayersnumber; i++)
	{
		L->r[i] = p[i];
		L->length++;
	}
	return L;
}

void InsertSort(SqListLink &L)
{
	cout << "直接插入排序：" << endl;
	int i, j;
	for (i = 2; i <= L->length; i++)
	{
		if (L->r[i].count < L->r[i - 1].count)//满足条件，需要将r[i]插入到有序子列；
		{
			L->r[0] = L->r[i];//将带插入的元素保存到首位；
			L->r[i] = L->r[i - 1];//依次将元素后移；
			for (j = i - 2; L->r[0].count < L->r[j].count; j--)//从后向前寻找插入位置；
				L->r[j + 1] = L->r[j];//记录逐个后移；
			L->r[j + 1] = L->r[0];//将r[0]还原到r[i]，插入到正确的位置；
		}
	}
	PrintList(L);
	cout << endl;
}

void BInsertSort(SqListLink & L)
{
	cout << "折半插入排序：" << endl;
	int i, j;
	int low, high, m;
	for (i = 1; i <= L->length; i++)
	{
		L->r[0] = L->r[i];
		low = 1;
		high = i - 1;
		while (low < high)
		{
			m = (low + high) / 2;
			if (L->r[0].count < L->r[m].count)
				high = m - 1;
			else
				low = m + 1;
		}
		for (j = i - 1; j >= high + 1; j--)
			L->r[j + 1] = L->r[j];
		L->r[high + 1] = L->r[0];
	}
	PrintList(L);
	cout << endl;
}

void ShellInsert(SqListLink &L, int dk)
{
	int i, j;
	for (i = dk + 1; i <= L->length; i++)
		if (L->r[i].count < L->r[i - dk].count)
		{
			L->r[0] = L->r[i];
			for (j = i - dk; j > 0 && L->r[0].count < L->r[j].count; j -= dk)
				L->r[j + dk] = L->r[j];
			L->r[j + dk] = L->r[0];
		}
}

void ShellSort(SqListLink &L, int dt[], int t)
{
	int k;
	cout << "希尔排序：" << endl;
	for (k = 0; k < t; k++)
		ShellInsert(L, dt[k]);
	PrintList(L);
}

int main()
{
	LinkPlayer p = InitPlayer();
	PrintPlayers(p);
	Counts(p);
	SqListLink L1 = InitSort(p);
	SqListLink L2 = InitSort(p);
	SqListLink L3 = InitSort(p);
	InsertSort(L1);
	BInsertSort(L2);
	ShellSort(L3, dt, 3);
	system("pause");
	return 0;
}