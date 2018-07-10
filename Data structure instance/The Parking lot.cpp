#include <iostream>
#include <string>
using namespace std;

int parkmaxsize;
int singlemoney;
char choice; 
//定义车辆的信息数据类型，包括车牌号和进去时间 
typedef struct {     
	string num;
	int cometime;
	int lefttime;
}ElemType;
//定义顺序栈的数据类型
typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

typedef struct QNode {
	ElemType point;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
//函数定义开始；
void InitStack(SqStack &s);
void Push1(SqStack &s, ElemType e, LinkQueue &q);
void Push2(SqStack &s, ElemType e);
ElemType Pop(SqStack &s);//；两个栈的出栈函数；
void InitQueue(LinkQueue &q);
void EnQueue(LinkQueue &q, ElemType e);
ElemType DeQueue(LinkQueue &q);
ElemType Get(SqStack s);
void PrintQueue(SqStack &s);

void InitStack(SqStack &s)//顺序栈的初始化函数
{
	s.base = new ElemType[parkmaxsize];
	if (!s.base)
	{
		cout << "栈申请空间失败，程序结束!" << endl;
		exit(0);
	}
	s.top = s.base;
	s.stacksize = parkmaxsize;
}

void InitQueue(LinkQueue &q)        //链队的初始化函数
{
	q.front = q.rear = new QNode;
	q.front->next = NULL;
}

void EnQueue(LinkQueue &q, ElemType e)            //链队的进队函数
{
	QueuePtr p = new QNode;
	p->point = e;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
}

void Push1(SqStack &s, ElemType e, LinkQueue &q)
{
	if (s.top - s.base == s.stacksize)//如果栈满了，进入队列；
		EnQueue(q, e);
	else
		*s.top++ = e;
}

void Push2(SqStack &s, ElemType e)
{
	*s.top++ = e;
}

ElemType Pop(SqStack &s)            //两个栈的出栈函数
{
	ElemType e;
	e = *--s.top;
	return e;
}


ElemType DeQueue(LinkQueue &q)                //链队的出队函数，将判断队是否为空放在主函数中
{
	ElemType e;
	QueuePtr p = new QNode;
	p = q.front->next;
	e = p->point;
	q.front->next = p->next;
	if (q.front == p)
		q.rear = q.front;
	delete p;
	return e;
}

ElemType Get(SqStack s)            //测试函数，检测栈中元素是否正确的进出
{
	return *(s.top - 1);
}

void PrintQueue(SqStack &s)
{
	SqStack p = s;
	ElemType e;
	while (p.top > p.base)
	{
		e= *(p.base++);
		cout << e.num << endl;
	}
}

int main()
{
	int nowcarnumber;
	cout << "		-------停车场管理系统-------"<<endl;
	cout << "请输入停车场容量：";
	cin >> parkmaxsize;
	cout << "输入每小时停车费：";
	cin >> singlemoney;
	int start,finishtime;
	LinkQueue q;//链队的定义和初始化
	InitQueue(q);
	SqStack s1,s2;
	InitStack(s1);
	InitStack(s2);
	ElemType e, t1;
	string name;
	cout << "请输入车库中原有车的车牌号 入库时间,输入-1 -1结束" << endl;
	while (e.num != "-1"&&e.cometime!=-1)
	{
		cin >> e.num >> start;//记录进去的时间
		e.cometime = start;
		if (e.num != "-1"&&e.cometime != -1)
			Push1(s1, e, q);
	}
	nowcarnumber = s1.top - s1.base;
	if (nowcarnumber == parkmaxsize)
		cout << "停车场已满，只能停" << parkmaxsize << "辆车,多余的车辆进入便道!" << endl;
	while (1)
	{
		cout << "停车场里的车是：" << endl;
		PrintQueue(s1);
		cout << "车辆进去[A] 车辆出去[L]" << endl;
		cout << "请输入你的选择:";
		cin >> choice;
		if (choice == 'L')
		{

			cout << "请输入要出车的车牌号 出库时间:";
			cin >> name;
			cin >> finishtime;
			t1 = Pop(s1);
			if (t1.num == name)//判断栈顶是否是要出的车辆
			{
				double summoney;//计算停车费用
				summoney = (finishtime - t1.cometime)*singlemoney;
				cout << "停车费用为:" << summoney << "元" << endl;
				cout << "车辆出去成功！" << endl;
				//测试位置，检测是否出车成功
				if (q.front == q.rear)//判断便道上是否有车
					cout << "停车场有多余空间进车." << endl;//没有车则停车场产生空位
				else
				{
					Push2(s1, DeQueue(q));//便道上有车则向停车场内补齐
					cout << "停车场没有空位!" << endl;
				}//测试位置，出车成功后检测便道上的车是否进入停车场
			}
			else
			{
				while (t1.num != name && s1.base != s1.top)            //顶上元素不是想要的元素，则将出栈元素储存在栈二中
				{
					Push2(s2, t1);
					t1 = Pop(s1);
				}
				int summoney;
				summoney = (finishtime - t1.cometime)*singlemoney;
				cout << "停车费用为:" << summoney << "元" << endl;
				cout << "车辆出去成功！" << endl;
				//寻找到则出车成功

				while (s2.top != s2.base)            //将栈二内的元素放回到栈一中
				{
					Push1(s1, Pop(s2), q);
				}//测试位置，判断栈二中元素是否全都放回栈一中
				if (q.front == q.rear)//出车成功后判断便道上是否有车
					cout << "停车场有多余空间进车." << endl;    //没车则停车场产生空位
				else
				{
					Push2(s1, DeQueue(q));                //有车则向停车场中补齐
					cout << "停车场没有空位!" << endl;
				}
			}
			//测试位置，检测便道上的车是否进入停车场中
		}
		else if (choice == 'A')
		{
			cout << "请输入要出车的车牌号 入库时间:";
			ElemType newcar;
			cin >> newcar.num;
			cin >> newcar.cometime;
			if (q.front != q.rear)
			{
				cout << "停车场内部已满，停在临时过道上." << endl;
				EnQueue(q, newcar);
			}
			else
			{
				if (s1.top - s1.base != s1.stacksize)
				{
					Push1(s1, newcar, q);
					cout << "您的车已成功停在停车场." << endl;
				}
				else
				{
					cout << "停车场内部已满，停在临时过道上." << endl;
					EnQueue(q, newcar);
				}
			}
		}
		else
			exit(0);
	}
	return 0;
}