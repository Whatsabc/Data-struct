#include<iostream>
using namespace std;
typedef int ElemType;
//二叉排序树的二叉链表储存表示；
typedef struct BSNode{
	ElemType data;
	struct BSNode *lchild, *rchild;
}BSNode,*BSTree;
//函数定义开始；
BSTree SearchBST(BSTree T, ElemType key);//二叉排序树的递归查找；
//void InsertBST(BSTree &T, ElemType e);//二叉排序树的插入；
void CreateBST(BSTree &T);//创建二叉排序树；
void PreOrderTraverse(BSTree T);//对二叉排序树进行先序遍历；
void MidOrderTraverse(BSTree T);
void PostOrderTraverse(BSTree T);
//主函数开始；
int main()
{
	BSTree T = NULL;
	CreateBST(T);
	cout << "PreOrderTraverse:";
	PreOrderTraverse(T);
	cout << "MidOrderTraverse:";
	MidOrderTraverse(T);
	cout << "PostOrderTraverse:";
	PostOrderTraverse(T);
	system("pause");
	return 0;
}
//查找当前元素是否在先行列表中存在；
BSTree SearchBST(BSTree T, ElemType key)
{
	if (T == NULL)
		return NULL;
	else if (key > T->data)
		return SearchBST(T->rchild, key);
	else if(key<T->data)
		return SearchBST(T->lchild, key);
	else
		return BSTree();
}

void InsertBST(BSTree & T, ElemType data)
{
	BSTree NewT = new BSNode;
	if (!NewT)
		return;
	NewT->data = data;
	NewT->lchild = NewT->rchild = NULL;
	//空树时，直接作为节点；
	if (T == NULL)
	{
		T = NewT;
		return;
	}
	if (SearchBST(T, data) != NULL)
		return;
	//进行插入，首先要找到要插入位置的父节点；
	BSTree tnode = NULL,troot = T;
	while (troot)
	{
		tnode = troot;
		if (data < troot->data)
			troot = troot->lchild;
		else
			troot = troot->rchild;
	}
	if (data < tnode->data)
		tnode->lchild = NewT;
	else
		tnode->rchild = NewT;
}

void CreateBST(BSTree & T)
{
	int data;
	cin >> data;
	while(data!=10000)
	{
		InsertBST(T, data);
		cin >> data;
	}
}

void PreOrderTraverse(BSTree T)
{
	if (T)
	{
		cout << T->data << " ";
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	cout << endl;
}

void MidOrderTraverse(BSTree T)
{
	if (T)
	{
		MidOrderTraverse(T->lchild);
		cout << T->data << " ";
		MidOrderTraverse(T->rchild);
	}
	cout << endl;
}

void PostOrderTraverse(BSTree T)
{
	if (T)
	{
		MidOrderTraverse(T->lchild);
		cout << T->data << " ";
		MidOrderTraverse(T->rchild);
	}
	cout << endl;
}