#include<iostream>
using namespace std;
typedef int ElemType;
//二叉排序树的二叉链表储存表示；
typedef struct BSNode {
	ElemType data;
	struct BSNode *lchild, *rchild;
}BSNode, *BSTree;
//函数定义开始；
BSTree SearchBST(BSTree T, ElemType key);//二叉排序树的递归查找；
void InsertBST(BSTree &T, ElemType e);//二叉排序树的插入；
void CreateBST(BSTree &T);//创建二叉排序树；
void PreOrderTraverse(BSTree T);//对二叉排序树进行先序遍历；
void MidOrderTraverse(BSTree T);//对二叉树进行中序遍历；
void PostOrderTraverse(BSTree T);//对二叉树进行后序遍历；
BSTree SearchMin(BSTree T);//二叉树找到最小值；
BSTree SearchMax(BSTree T);//二叉树找到最大值；
void DeleteBSTNode(BSTree &T, ElemType data);//删除节点代码；
//主函数开始；
int main()
{
	BSTree T = NULL;
	int data;
	CreateBST(T);
	cout << "PreOrderTraverse:";
	PreOrderTraverse(T);
	cout << endl;
	cout << "MidOrderTraverse:";
	MidOrderTraverse(T);
	cout << endl;
	cout << "PostOrderTraverse:";
	PostOrderTraverse(T);
	cout << endl;
	cout << "请输入要删除的数：";
	cin >> data;
	DeleteBSTNode(T, data);
	cout << "MidOrderTraverse:";
	MidOrderTraverse(T);
	cout << endl;
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
	else if (key<T->data)
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
	BSTree tnode = NULL, troot = T;
	while (troot)
	{
		tnode = troot;//这句非多余，记录下前一个节点，后续进行遍历；
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
	while (data != 10000)
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
}

void MidOrderTraverse(BSTree T)
{
	if (T)
	{
		MidOrderTraverse(T->lchild);
		cout << T->data << " ";
		MidOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BSTree T)
{
	if (T)
	{
		MidOrderTraverse(T->lchild);
		cout << T->data << " ";
		MidOrderTraverse(T->rchild);
	}
}

BSTree SearchMin(BSTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->lchild == NULL)
		return T;
	else//递归寻找左孩子，直到左孩子为空；
		return SearchMin(T->lchild);
}

BSTree SearchMax(BSTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->rchild == NULL)
		return T;
	else//递归寻找右孩子，直到右孩子为空；
		return SearchMax(T->rchild);
}
//二叉排序树的删除
//1.只有一个节点：如果要删除的节点A只有一个子节点，就直接将A的子节点连到A的父节点，并将A删除；
//2.如果A有两个子节点，我们就以该节点右子树的最小节点取代A；
void DeleteBSTNode(BSTree &T, ElemType data)
{
	BSTree p = T, parent = NULL, s = NULL;
	if (!p)//如果p是空，返回；
		return;
	else if (p->data == data)//如果要删除的是根节点；
	{
		if (!p->lchild && !p->rchild)//是一个叶子节点；
			T = NULL;
		else if (!p->rchild&&p->lchild)//只有左节点；
			T = p->lchild;
		else if (!p->lchild&&p->rchild)//只有右节点；
			T = p->rchild;
		else//两个节点都存在；
		{
			s = p->rchild;
			if (!s->lchild)//p的右子树s没有左子树；
				s->lchild = p->lchild;
			else//p的右子树s有左子树；
			{
				while (s->lchild)//在左子树找到最小的节点；
				{
					parent = s;//记录下这个最小的节点；
					s = s->lchild;
				}
				parent->lchild = s->rchild;
				s->lchild = p->lchild;
				s->rchild = p->rchild;
			}
			T = s;
		}
		free(p);
	}
	else if (data > p->data) //向右找
		DeleteBSTNode((p->rchild), data);
	else if (data < p->data) //向左找
		DeleteBSTNode((p->lchild), data);
}