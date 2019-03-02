/*这个链栈代码没有栈顶空节点*/
#include<iostream>
using namespace std;

typedef int ElemType;
typedef struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

typedef struct Node {
	ElemType data;
	PtrToNode next;
};

Stack InitStack();

int IsEmpty(Stack S);
void Pop(Stack &S);
void Push(Stack &S,ElemType e);
int Top(Stack S);

int main()
{
	int TopNumber;
	Stack TestStack = InitStack();
	cout << "当前标志位是" << IsEmpty(TestStack) << " 【1是空，0是非空】" << endl;
	Push(TestStack, 5);
	Push(TestStack, 2);
	Push(TestStack, 3);
	cout << "当前标志位是" << IsEmpty(TestStack) << " 【1是空，0是非空】" << endl;

	TopNumber = Top(TestStack);
	cout << "目前栈顶元素是：" << TopNumber << endl;
	Pop(TestStack);
	TopNumber = Top(TestStack);
	cout << "目前栈顶元素是：" << TopNumber << endl;
	system("pause");
	return 0;
}

Stack InitStack()
{
	Stack S = new Node;
	S = NULL;
	return S;
}

int IsEmpty(Stack S)
{
	return S == NULL;
}

void Push(Stack &S, ElemType e)
{
	Stack p = new Node;
	p->data = e;
	p->next = S;
	S = p;
}

void Pop(Stack &S)
{
	if (!IsEmpty(S))
	{
		Stack p = S;
		S = S->next;
		delete p;
	}
	else if (S == NULL)
		cout << "空栈，弹出栈顶元素失败" << endl;
}

int Top(Stack S)
{
	if (!IsEmpty(S))
		return S->data;
	else
		cout << "空栈，获取栈顶元素失败" << endl;
}
