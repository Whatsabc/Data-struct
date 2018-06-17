#include<iostream>
using namespace std;
#define MAXSIZE 20
typedef int KeyType;

typedef struct {
	KeyType key;
	int otherinfo;
}RedType;
typedef struct SqList{
	RedType r[MAXSIZE + 1];//r[0]闲置用作哨兵单元；
	int length=0;
}SqList,*SqListLink;
int dt[3] = { 5,3,1 };
//函数定义开始；
void InsertSort(SqListLink &L);//直接插入排序；
void BInsertSort(SqListLink &L);//折半插入排序；
void ShellInsert(SqListLink &L, int dk);
void ShellSort(SqListLink &L, int dt[], int t);
void BubbleSort(SqListLink &L);

int main()
{
	SqListLink InsertL = new SqList;
	int i, data;
	for (i = 1; i < 10; i++)
	{	
		cin >> data;
		InsertL->r[i].key = data;
		InsertL->length++;
	}
	SqListLink BInsertL = InsertL;
	SqListLink Shell = InsertL;
	SqListLink Bubble = InsertL;
	InsertSort(InsertL);
	BInsertSort(BInsertL);
	ShellSort(Shell,dt,3);
	for (i = 1; i <= Shell->length; i++)
		cout << Shell->r[i].key << " ";
	cout << endl;
	BubbleSort(Bubble);
	system("pause");
	return 0;
}

void InsertSort(SqListLink &L)
{
	int i, j;
	for (i = 1; i <= L->length; i++)
	{
		L->r[0] = L->r[i];//将带插入的元素保存到首位；
		L->r[i] = L->r[i - 1];
		for (j = i - 1; L->r[0].key < L->r[j].key; j--)
			L->r[j + 1] = L->r[j];
		L->r[j + 1] = L->r[0];
	}
	for (i = 1; i <= L->length; i++)
		cout << L->r[i].key << " ";
	cout << endl;
}

void BInsertSort(SqListLink & L)
{
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
			if (L->r[0].key < L->r[m].key)
				high = m - 1;
			else
				low = m + 1;
		}
		for (j = i - 1; j >= high + 1; j--)
			L->r[j + 1] = L->r[j];
		L->r[high + 1] = L->r[0];
	}
	for (i = 1; i <= L->length; i++)
		cout << L->r[i].key << " ";
	cout << endl;
}

void ShellInsert(SqListLink &L, int dk)
{
	int i, j;
	for(i=dk+1;i<=L->length;i++)
		if (L->r[i].key < L->r[i - dk].key)
		{
			L->r[0] = L->r[i];
			for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk)
				L->r[j + dk] = L->r[j];
			L->r[j + dk] = L->r[0];
		}
}

void ShellSort(SqListLink &L, int dt[], int t)
{
	int k;
	for (k = 0; k < t; k++)
		ShellInsert(L, dt[k]);
}

void BubbleSort(SqListLink & L)
{
	int m, flag, j, i;
	RedType temp;
	m = L->length - 1;
	flag = 1;
	while ((m > 0) && (flag == 1))
	{
		flag = 0;
		for(j=1;j<m;j++)
			if (L->r[j].key > L->r[j + 1].key)
			{
				flag = 1;
				temp = L->r[j];
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = temp;
			}
		m--;
	}
	for (i = 1; i <= L->length; i++)
		cout << L->r[i].key << " ";
	cout << endl;
}
