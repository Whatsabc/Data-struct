/*这个链栈代码有一个栈顶空节点*/
#include<iostream>
using namespace std;

struct StackNode;
typedef int ElemType;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node {
	ElemType data;
	PtrToNode next;
};

Stack InitStack();
int IsEmpty(Stack S);
void Pop(Stack S);
void Push(Stack S, ElemType e);
int Top(Stack S);

int main()
{
	Stack TestStack = new Node;
	int TopNumber;
	TestStack = InitStack();
	Push(TestStack, 2);
	Push(TestStack, 5);
	Push(TestStack, 8);

	TopNumber = Top(TestStack);
	cout << "目前栈顶元素是：" << TopNumber << endl;
	Pop(TestStack);
	TopNumber = Top(TestStack);
	cout << "目前栈顶元素是：" << TopNumber << endl;
	system("pause");
	return 0;
}

int IsEmpty(Stack S)
{
	return S->next == NULL;
}

Stack InitStack()
{

	Stack S = new Node;
	if (S == NULL)
	{
		cout << "创建空栈失败" << endl;
		return NULL;
	}
	S->next = NULL;
	return S;
}

void Push(Stack S, ElemType e)
{
	Stack p = new Node;
	p->data = e;
	p->next = S->next;
	S->next = p;
}

void Pop(Stack S)
{
	if (S == NULL)
	{
		cout << "请先创建栈" << endl;
		return;
	}
	if (!IsEmpty(S))
	{
		Stack p = S->next;
		S->next = S->next->next;
		delete p;
	}
	else
		cout << "栈存在，但是是空栈，弹出栈顶元素错误" << endl;
}

int Top(Stack S)
{
	if (S == NULL)
	{
		cout << "请先创建栈" << endl;
		return NULL;
	}
	if (!IsEmpty(S))
		return S->next->data;
	cout << "栈存在，但是是空栈，输出栈顶元素错误" << endl;
	return 0;
}