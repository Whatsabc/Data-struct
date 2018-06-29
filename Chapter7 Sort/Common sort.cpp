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
void PrintList(SqListLink L);
//直接插入排序；
void InsertSort(SqListLink &L);
//折半插入排序；
void BInsertSort(SqListLink &L);
//希尔排序；
void ShellInsert(SqListLink &L, int dk);
void ShellSort(SqListLink &L, int dt[], int t);
//冒泡法排序；
void BubbleSort(SqListLink &L);
//快速排序；
int Partition(SqListLink &L, int low, int high);
void QSort(SqListLink &L, int low, int high);
void QuickSort(SqListLink &L);

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
	SqListLink	QuickL = InsertL;
	InsertSort(InsertL);
	BInsertSort(BInsertL);
	ShellSort(Shell,dt,3);
	PrintList(Shell);
	cout << endl;
	BubbleSort(Bubble);
	QuickSort(QuickL);
	cout << endl;
	system("pause");
	return 0;
}

void PrintList(SqListLink L)
{
	int i;
	for (i = 1; i <= L->length; i++)
		cout << L->r[i].key << " ";
}

void InsertSort(SqListLink &L)
{
	int i, j;
	for (i = 2; i <= L->length; i++)
	{
		if (L->r[i].key < L->r[i - 1].key)//满足条件，需要将r[i]插入到有序子列；
		{
			L->r[0] = L->r[i];//将带插入的元素保存到首位；
			L->r[i] = L->r[i - 1];//依次将元素后移；
			for (j = i - 2; L->r[0].key < L->r[j].key; j--)//从后向前寻找插入位置；
				L->r[j + 1] = L->r[j];//记录逐个后移；
			L->r[j + 1] = L->r[0];//将r[0]还原到r[i]，插入到正确的位置；
		}
	}
	PrintList(L);
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
	PrintList(L);
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
	PrintList(L);
	cout << endl;
}
//快速排序；
int Partition(SqListLink & L, int low, int high)
{
	L->r[0] = L->r[low];//用子表的第一个数字用作枢纽记录；
	int pivotekey;//定义枢纽记录关键字；
	pivotekey = L->r[low].key;
	while (low < high)
	{
		while (low < high&&L->r[high].key >= pivotekey)
			high--;
		L->r[low] = L->r[high];//将比枢纽小的记录移动到低端；
		while (low < high&&L->r[low].key <= pivotekey)
			low++;
		L->r[high] = L->r[low];//将比枢纽大的记录移动到高端；
	}
	L->r[low] = L->r[0];//枢纽记录到位；
	return low;//返回枢纽数值；
}

void QSort(SqListLink &L, int low, int high)
{
	int pivotekey;
	if (low < high)
	{
		pivotekey = Partition(L, low, high);//得到枢纽位置；
		QSort(L, low, pivotekey - 1);//对左子树进行递归排序；
		QSort(L, pivotekey + 1, high);//对右子树进行递归排序；
	}
}

void QuickSort(SqListLink &L)
{
	QSort(L, 1, L->length);
	PrintList(L);
}
