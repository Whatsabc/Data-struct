#include<iostream>
using namespace std;

//队列的结构体定义如下；
typedef struct QNode {
	int data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct Queue{
	QueuePtr front;
	QueuePtr rear;
}Queue,*LinkQueue;
//函数声明开始；
void InitQueue(LinkQueue &Q);//初始化队列；
void EnQueue(LinkQueue &Q,int insertnum);//在队尾加入一个元素；
void DeQueue(LinkQueue &Q, int &e);//删除一个元素；
void GetHead(LinkQueue Q);//取得最后一个元素；

int main()
{
	LinkQueue Q=new Queue;//初始化队列的头节点和尾节点；
	int deletenum,insertnum;
	InitQueue(Q);//队列初始化；
	cout << "请输入进入队列的数字：";
	cin >> insertnum;
	while (insertnum != 0)
	{
		EnQueue(Q,insertnum);
		cout << "请输入进入队列的数字：";
		cin >> insertnum;	
	}
	DeQueue(Q,deletenum);
	GetHead(Q);
	system("pause");
	return 0;
}

void InitQueue(LinkQueue &Q)
{
	Q->front = Q->rear = new QNode;//生成新节点作为头结点，队头和队尾指针指向此节点；
	Q->front->next = NULL;//将头节点的指针域置为空；
}

void EnQueue(LinkQueue &Q,int insertnum)
{
	QueuePtr p = new QNode;
	p->data = insertnum;
	p->next = NULL;
	Q->rear->next = p;//将新节点插入到队尾；
	Q->rear = p;//修改队尾指针值，使其指向最后一个节点；
}

void DeQueue(LinkQueue &Q, int &e)
{
	if (Q->front == Q->rear)
		cout << "Queue is Empty!!";//判断队列是否是空的；
	QueuePtr p = NULL;
	p = Q->front->next;
	e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	delete p;
	cout << "删除成功！"<<endl;
}
void GetHead(LinkQueue Q)
{
	if (Q->front != Q->rear)
		cout << "队列的最后一个数字是：" << Q->front->next->data << endl;
}