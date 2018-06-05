#include <iostream>
using namespace std;

typedef struct LNode//定义书的结构体；
{
	char BookISBN[13];
	char BookName[20];
	double BookPrice;
	LNode *next;
}LNode, *LinkList;
//表的创建和输出，表的修改，最贵图书的查找，新书入库，旧书出库；

int main()
{
	void InitList(LinkList &L);//链表的创建和入库；
	void PrintList(LinkList L);//链表的输出；
	void ChangeList(LinkList &L);//链表的修改；
	void DeleteList(LinkList &L);//链表的删除；
	void SearchList(LinkList L);//最贵图书的查找；
	void SortList(LinkList &L, int n);//排序图书；
	void PrintMenu();
	PrintMenu();
	LinkList Head = NULL;
	while (1)//菜单的设计；
	{
		int choice;
		cout << endl;
		cout << "请输入你的选择：";
		cin >> choice;
		switch (choice)
		{
		case(1):InitList(Head); break;
		case(2):ChangeList(Head); break;
		case(3):DeleteList(Head); break;
		case(4):SearchList(Head); break;
		case(5):PrintList(Head); break;
		default:cout << "请重新输入" << endl; 
		break;
		}
	}
	system("pause");
	return 0;
}

void PrintMenu()//目录的建立；
{
	cout << "					    ---菜单---" << endl;
	cout << "					1.图书信息表的创建和入库" << endl;
	cout << "					2.图书信息表图书的修改" << endl;
	cout << "					3.书信息表图书的出库" << endl;
	cout << "					4.图书信息表最贵图书的查找" << endl;
	cout << "					5.图书信息表图书列表的输出" << endl;
	cout << endl;
}

void InitList(LinkList &L)
{
	int i, n;
	L = new LNode;
	LinkList q = NULL;
	cout << "输入你要插入的图书的数目：";
	cin >> n;
	L->next = NULL;
	q = L;
	for (i = 0; i<n; i++)//定位在要插入元素的前一个数据；
	{
		LinkList p;
		p = new LNode;
		cout << "请输入书的ISBN号码/书名/价格：" << endl;
		cin >> p->BookISBN;
		cin >> p->BookName;
		cin >> p->BookPrice;
		p->next = NULL;
		q->next = p;
		q = p;
	}
}

void PrintList(LinkList L)
{
	LinkList p = NULL;
	p = L->next;
	cout << "ISBN	" << "	书名	" << "	价格" << endl;
	while (p != NULL)//遍历链表；
	{
		cout << p->BookISBN << "  " << p->BookName << "  " << p->BookPrice << endl;
		p = p->next;
	}
	cout << endl;
}

void DeleteList(LinkList &L)
{
	int BookNumber;
	cout << "请输入你要删除第几本书：";
	cin >> BookNumber;
	int j = 0;
	LinkList p = NULL, q = NULL;
	p = L;
	while ((p->next) && (j<BookNumber - 1))//用于定位要删除的元素；
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || (j>BookNumber - 1))
		cout << "输入的数字有误" << endl;
	q = p->next;
	p->next = q->next;
	delete q;
	cout << "删除成功!" << endl;
}

void SearchList(LinkList L)
{
	LinkList p = NULL;
	p = L->next;
	LinkList MAXPRICE = NULL;//定义两个指针用来比较大小；
	LinkList NEXTPRICE = NULL;
	MAXPRICE = p;
	while (p != NULL)
	{
		if ((p->BookPrice) > (MAXPRICE->BookPrice))
			MAXPRICE = p;//如果下一个数据大于前一个，将地址付给新的指针；
		p = p->next;
	}
	cout << "这本书是：" << endl;
	cout << "ISBN  " << "  书名  " << "  价格" << endl;
	cout << MAXPRICE->BookISBN << "  " << MAXPRICE->BookName << "  " << MAXPRICE->BookPrice << endl;
}

void ChangeList(LinkList &L)
{
	LinkList p = NULL;
	LinkList q = NULL;
	p = L;
	int j = 0;
	int BookNumber;
	cout << "请输入你要修改第几本书：";
	cin >> BookNumber;
	while (p && (j<BookNumber - 1))//定位要修改的元素，并将其指针赋给新的指针；
	{
		p = p->next;
		++j;
		q = p->next;
	}
	if (!p || j>BookNumber - 1)
	{
		cout << "修改错误";
	}
	cout << "请输入书的ISBN号码/书名/价格" << endl;
	cin >> q->BookISBN;//修改指针所指的元素的值；
	cin >> q->BookName;
	cin >> q->BookPrice;
	cout << "修改完毕！" << endl;
}
