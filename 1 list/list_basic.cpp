#include<iostream>
using namespace std;

struct Node;
typedef struct Node *PtrToNode;
typedef int ElementType, PositionNum;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
	ElementType Element;
	Position Next;
};

List MakeEmpty(List L);//初始化链表，构建空表
int IsEmpty(List L);//判断是否是空链表
void InitList(List L);//后插入法创建链表
void PrintList(List L);//遍历当前链表
void ChangeList(List L);//修改某一结点的数值
void InsertList(List L);//插入节点
List FindPrevious(PositionNum x, List L);//寻找第i-1个节点
void DeleteList(List L);//删除节点

int main()
{
	int IsEmptyNumber = 0;//如果链表是空，置为1，非空，置为0
	List TestList = NULL;//创建测试链表
	//开始测试函数
	TestList = MakeEmpty(TestList);
	IsEmptyNumber = IsEmpty(TestList);
	cout << "	此时标志位是" << IsEmptyNumber << "[1是空，0是非空]" << endl;
	InitList(TestList);
	PrintList(TestList);
	cout << endl;
	ChangeList(TestList);
	PrintList(TestList);
	cout << endl;
	InsertList(TestList);
	PrintList(TestList);
	cout << endl;
	DeleteList(TestList);
	PrintList(TestList);
	cout << endl;
	IsEmptyNumber = IsEmpty(TestList);
	cout << "	此时标志位是" << IsEmptyNumber << "[1是空，0是非空]" << endl;

	system("pause");
	return 0;
}

List MakeEmpty(List L)
{
	L = new Node;
	L->Element = -1;
	L->Next = NULL;
	cout << "初始化链表成功，链表第一个节点置为-1" << endl;
	return L;
}

int IsEmpty(List L)
{
	return L->Next == NULL;
}

void InitList(List L)
{
	int ListNumber, icout;
	List q = new Node;
	cout << "请输入要创建的链表节点数目：";
	cin >> ListNumber;
	q->Next = NULL;
	q = L;
	for (icout = 1; icout <= ListNumber; icout++)
	{
		List p = new Node;
		cout << "请输入第" << icout << "个节点数值：";
		cin >> p->Element;
		p->Next = NULL;
		q->Next = p;
		q = p;
	}
}

void PrintList(List L)
{
	List p = L->Next;
	cout << "链表遍历开始：" << endl;
	while (p != NULL)//遍历链表；
	{
		cout << p->Element << endl;
		p = p->Next;
	}
	cout << "----遍历结束----" << endl;
}

void ChangeList(List L)
{
	int changeNumber, icout = 1;
	cout << "请输入要修改第几个节点：";
	cin >> changeNumber;
	L = FindPrevious(changeNumber, L);
	L = L->Next;//指向i-节点的下一个节点，即i节点
	cout << "请输入要修改的新的节点的值：";
	cin >> L->Element;
	cout << "----修改完毕----" << endl;
}

void InsertList(List L)
{
	int InsertListNum;
	List p = new Node;
	cout << "请输入要插入的节点位置[插入到该节点前面]：";
	cin >> InsertListNum;
	L = FindPrevious(InsertListNum, L);
	cout << "请输入要插入的数值：";
	cin >> p->Element;
	p->Next = L->Next;
	L->Next = p;
}


List FindPrevious(PositionNum x, List L)
{
	int  icout = 1;
	while (L->Next != NULL && icout < x)
	{
		L = L->Next;
		icout++;
	}
	return L;
}

void DeleteList(List L)
{
	int DeleteListNum;
	List p = L->Next;
	cout << "请输入要删除第几个节点：";
	cin >>  DeleteListNum;
	L = FindPrevious(DeleteListNum, L);
	L->Next = p->Next;
	delete p;
}
