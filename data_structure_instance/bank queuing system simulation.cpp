#include<iostream>
using namespace std;
//系统每次要输入的是1）当前顾客顾客的柜台被服务时间2）当前顾客和下一个顾客到达的间隔时间
int totalworktime;

typedef struct {
	int starttime;
	int endtime;
	int businesstime;
}ElemType;

typedef struct QueueNode {
	ElemType data;
	struct QueueNode *next;
}QueueNode, *QueuePtr;
typedef struct LinkQueue{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

LinkQueue queue[4];//初始化四个队列；
int openorclose = false;
int TotalTime=0;
int Totalpeople=0;

void InitQueue(LinkQueue &Q);
void EnQueue(LinkQueue &Q,ElemType &e);
ElemType DeQueue(LinkQueue &Q);
int IsEmpty(LinkQueue &Q);
int ShortestQueue();//获取最短队列函数；
int QueueLength(LinkQueue &Q);
int TheEmptyOne();
void OutQueue(LinkQueue &Q);
void Queuing();
void InitBank();//初始化银行；

void InitQueue(LinkQueue &Q)        //链队的初始化函数
{
	Q.front = Q.rear = new QueueNode;
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q, ElemType &e)            //链队的进队函数
{
	QueuePtr p = new QueueNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

ElemType DeQueue(LinkQueue &Q)                //链队的出队函数，将判断队是否为空放在主函数中
{
	ElemType e;
	QueuePtr p = new QueueNode;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.front == p)
		Q.rear = Q.front;
	delete p;
	return e;
}

int IsEmpty(LinkQueue &Q)
{
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}

int ShortestQueue()
{
	int i, a[4], temp, minnumber=0;
	for (i = 0; i < 4; i++)
		a[i]=QueueLength(queue[i]);
	temp = a[0];
	for (i = 0; i < 4; i++)
		if (a[i] < temp)
		{
			temp = a[i];
			minnumber = i;
		}
	return minnumber;
}

int QueueLength(LinkQueue &Q)
{
	int count = 0;
	QueuePtr p = Q.front->next; 
	while (p)
	{
		p = p->next;
		count++;
	}
	return count;
}

int TheEmptyOne()
{
	int i,icount=0;
	for (i = 0; i < 4; i++)
	{
		if (IsEmpty(queue[i]) == 1)//如果某个柜台是空的，返回这个柜台的编号；
			return i;
		else
			return -1;
	}
}

void OutQueue(LinkQueue &Q)
{
	if (IsEmpty(Q))
		;
	else
	{
		QueuePtr p;
		p = Q.front->next;
		if (p->data.businesstime == 0)
			DeQueue(Q);
		p->data.businesstime = p->data.businesstime - 1;
		
	}
}

void Queuing()
{
	ElemType newhuman;
	int i;
	for (i = 0; i < 4; i++)
	{
		cout << "请输入初始化状态时四个窗口的人 [进入时间] [出去时间]" << endl;
		cin >> newhuman.starttime >> newhuman.endtime;
		newhuman.businesstime = newhuman.endtime - newhuman.starttime;
		EnQueue(queue[i], newhuman);
	}
	for (i = 1; i < totalworktime; i++)
	{
		int comingtime, lefttime;
		cout << "当前时间是第[" << i << "]分钟" << endl;
		cout << "请输入每个人 [进入时间] [出去时间]：" << endl;
		cin >> comingtime >> lefttime;
		newhuman.starttime = comingtime;
		newhuman.endtime = lefttime;
		newhuman.businesstime = newhuman.endtime - newhuman.starttime;
		OutQueue(queue[0]);
		OutQueue(queue[1]);
		OutQueue(queue[2]);
		OutQueue(queue[3]);
		if (TheEmptyOne()!=-1)
		{
			int location = TheEmptyOne();
			EnQueue(queue[TheEmptyOne()], newhuman);
			TotalTime = TotalTime + newhuman.businesstime;
			Totalpeople++;
			cout << "队列未满，当前客人在第[" << TheEmptyOne()+1 << "]柜台" << endl;
		}
		else if (TheEmptyOne()==-1)
		{
			int location = ShortestQueue();
			EnQueue(queue[(ShortestQueue())], newhuman);//选择人最少的队列；
			TotalTime = TotalTime + newhuman.businesstime;
			Totalpeople++;
			cout << "队列已满，当前客人在第[" << location+1<< "]柜台" << endl;
		}
	}
	openorclose = false;
	cout << "[[[银行已关门]]]" << endl;
	cout << "业务总人数：" <<Totalpeople<<endl;
	cout << "业务总时长：" << TotalTime << endl;
	cout << "每个人业务的平均时间：" << TotalTime / Totalpeople << endl;
}
void InitBank()
{
	int i;
	cout << "请输入营业总时长[min]：";
	cin >> totalworktime;
	for (i = 0; i < 4; i++)
		InitQueue(queue[i]);//初始化
	openorclose = true;
	cout << "[[[队列初始化完成，开始营业]]]" << endl;
	cout << "银行的工作时常为" << totalworktime << "[min]" << endl;
}

int main()
{
	InitBank();//银行开门；
	while (openorclose)
		Queuing();//开始进行队列模拟；
	system("pause");
	return 0;
}
