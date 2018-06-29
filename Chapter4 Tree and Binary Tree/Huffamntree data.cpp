#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)//VS预处理命令，用于忽略_s；可忽略；
using namespace std;

//树的结构体定义开始；
typedef struct {
	int num;
	int weight;
	int parent, lchild, rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;//定义一种可以储存指针的字符类型；

int Weight[100] = {0};//定义一个数组，置空，用于暂时储存权重；

//函数声明开始；
void CreateHuffmanTree(HuffmanTree &HT, int n);//构建一个哈夫曼树；
int CountNum(char ch[]);//进行输入的字符串计数；
void Select(HuffmanTree HT, int n,int &s1,int &s2);//选择一个两个双亲域为0且权值最小的节点，并返回它们在HT中的序号s1和s2;
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n);//构建哈夫曼编码；
void PrintHuffmanCode(HuffmanCode HC,char ch[]);//打印每个字符的哈夫曼编码；

int main()
{
	while(1)
	{
		char Cinstring[100];//储存字符串的数组；
		int Chartypenum;//统计字符串长度；
		int HTNum, i = 0;
		HuffmanTree HT;
		HuffmanCode HC;
		cout << "请输入一串字符：" << endl;
		cin >> Cinstring;
		Chartypenum=CountNum(Cinstring);//返回数值得到字符串长度；
		CreateHuffmanTree(HT, Chartypenum);//构建树；
		CreateHuffmanCode(HT,HC,Chartypenum);//构建哈夫曼树的编码；
		PrintHuffmanCode(HC, Cinstring);//打印每个字母哈夫曼编码；
		while (Cinstring[i] != '\0')//进行全部哈夫曼编码的输出；[需要认真看]
		{
			cout << HC[Cinstring[i] - 'a' + 1];
			i++;
		}
		cout << endl;
		cout << Cinstring<<endl;//将字符串输出；以后改进；
	}
	system("pause");
	return 0;
}

int CountNum(char ch[])
{
	int i, j = 0, Chartypenum=0;
	int Tempweight[27];
	for (i = 1; i < 27; i++)//初始化临时储存权重数组；
	{
		Tempweight[i] = 0;
	}
	while (ch[j] != '\0')//对各个字母进行计数，并储存计数结果；
	{
		if ('a' <= ch[j] <= 'z')
		{
			i = ch[j] - 96;
			Tempweight[i]++;
		}
		j++;
	}
	j = 1;
	for (i = 1; i < 27; i++)//将权重储存起来，并输出每一个字母的权重；
	{
		if (Tempweight[i] != 0)
		{
			Weight[j] = Tempweight[i];//将权重储存在暂时的权重储存数组中；
			Weight[j + 1] = '\0';
			Chartypenum++;
			j++;
			cout << char(i + 96) << ":" << Tempweight[i] << " ";
		}
	}
	cout << endl;
	return Chartypenum;
}

void Select(HuffmanTree HT, int n,int &s1,int &s2)//自己写的总是错的，上网借鉴；
	int i, ti1,ti2;
	HTNode h1, h2;
	ti1 = ti2 = 0;
	h1 = HT[1];
	h1.weight = 999999;
	for (i = 1; i <= n; i++)
	{
		if (HT[i].weight <= h1.weight&&(HT[i].parent==0))
		{
			h1 = HT[i];
			ti1 = i;
		}
	}
	h2 = HT[2];
	h2.weight = 999999;
	for (i = 1; i <= n; i++)
	{
		if ((HT[i].weight <= h2.weight) && (ti1!=i) && (HT[i].parent == 0))
		{
			h2 = HT[i];
			ti2 = i;
		}
	}
	if ((h1.weight == h2.weight)&&(HT[ti1].num > HT[ti2].num))
	{
		int temp;
		temp = ti1;
		ti1 = ti2;
		ti2 = temp;
	}
	s1 = ti1;
	s2 = ti2;
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode & HC, int n)//输出每个字符的HuffmanCode代码，来自课本；
{
	HC = new char* [n + 1];//定义一个储存有指针的数组；
	int start, c, f, i;
	char *cd;//定义一个储存数组cd;
	cd = new char[n];
	cd[n-1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n-1;
		c = i;
		f = HT[i].parent;
		while (f != 0)
		{
			--start;
			if (HT[f].lchild == c)
				cd[start] = '0';
			else
				cd[start] = '1';
			c = f;
			f = HT[f].parent;
		}
		HC[i] = new char[n - start-1];//开辟一个HC空间；
		strcpy(HC[i],&cd[start]);//将每个字母的哈夫曼树储存在一起；
	}
	delete cd;
}

void PrintHuffmanCode(HuffmanCode HC,char ch[])//这段和计数函数差不多，但我写的有些复杂，后续会改；
{
	int i, j = 0;
	int t = 1;
	int Tempweight[27];
	for (i = 1; i < 27; i++)
	{
		Tempweight[i] = 0;
	}
	while (ch[j] != '\0')
	{
		if ('a' <= ch[j] <= 'z')
		{
			i = ch[j] - 96;
			Tempweight[i]++;
		}
		j++;
	}
	for (i = 1; i < 27; i++)
	{
		if (Tempweight[i] != 0)
		{
			cout << char(i + 96) << ":" << HC[t] <<" ";
			t++;
		}
	}
	cout << endl;
}

void CreateHuffmanTree(HuffmanTree & HT, int n)//构建哈夫曼树；
{
	int i, m;
	if (n <= 1)
	{
		cout << "ERROR" << endl;
		return;
	}
	m = n * 2 - 1;
	HT = new HTNode[m + 1];
	for (i = 1; i <= m; i++)
	{
		HT[i].num = i;
		HT[i].parent = 0;
		HT[i].rchild = 0;
		HT[i].lchild = 0;
	}
	for (i = 1; i <= n; i++)
	{
		HT[i].weight = Weight[i];//将临时的权重数组赋值进入哈夫曼树中；
	}
	for (i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; 
		HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	for (i = 1; i <= m; i++)//进行构建好的哈夫曼树的输出；
	{
		cout << HT[i].num << " " << HT[i].weight << " " << HT[i].parent << " " << HT[i].lchild << " " << HT[i].rchild << endl;
	}
}
