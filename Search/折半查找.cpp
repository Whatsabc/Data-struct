#include<iostream>
using namespace std;
typedef int KeyType;
//数据元素的定义；
typedef struct {
	KeyType key;
	char otherinfo;
}ElemType;
//顺序表的定义；
typedef struct {
	ElemType *R;
	int length;
}SSTable, *SSTableLink;

int Search_Bin(SSTable ST, KeyType key);
void Create_Bin(SSTableLink &ST);
//主函数从此开始；
int main()
{
	SSTableLink ST;
	int Key;
	Create_Bin(ST);
	cout << "请输入要查找的KEY值：";
	cin >> Key;
	Search_Bin(*ST, Key);
	system("pause");
	return 0;
}
//折半查找函数；
int Search_Bin(SSTable ST, KeyType key)
{
	int low, high, mid;
	low = 1;
	high = ST.length;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key == ST.R[mid].key)
			return mid;
		else if (key < ST.R[mid].key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}
//构建线性表；
void Create_Bin(SSTableLink &ST)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		ST = new SSTable;
		ST->R[i].key = i;//此处有问题；！！！！！
		ST->length = i + 1;
	}
}