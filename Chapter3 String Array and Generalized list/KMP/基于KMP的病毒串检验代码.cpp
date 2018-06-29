#include<iostream>
#include<string.h>
#define YES 1
#define NO -1
using namespace std;

void GetNext(char VirusChar[], int next[]);//进行GetNext数组的求值；
int KMP(char VirusChar[], char HumanChar[], int next[]);//进行KMP算法的主要操作；
//void GetNextTval(char S[], int nexttval[]);

int main()
{
	cout << "		[基于字符串模式匹配算法的病毒感染检验问题程序]" << endl;
	cout << "请输入要检测的病毒DNA序列与人体DNA序列：(输入0 0程序结束)" << endl;
	int icount, i, j;//定义基本变量；
	while (true)
	{
		int  ERRORCOUNT = 0;//定义错误计数器；
		int next[100] = { 0 };//定义next数组；
		int nexttval[100] = { 0 };
		char VirusChar[100], Temp[100],HumanChar[20];//定义两个输入字符串，和中间字符串；
		cin>>VirusChar;
		cin>>HumanChar;
		if ((strlen(VirusChar) == 1) && (strlen(HumanChar) == 1) && (VirusChar[0] == '0') && (HumanChar[0] == '0'))
		{
			cout << "程序已经退出！" << endl;
			break;
		}
		else
		{
			int VirusLength;
			VirusLength = strlen(VirusChar);
			for (icount = VirusLength, j = 0; icount < VirusLength; j++)//将字符串扩展为原来的两倍；
			{
				VirusChar[icount] = VirusChar[j];
				icount++;
			}
			VirusChar[icount] = '\0';
			icount = 0;
			for (i = 0; i < VirusLength; i++)//将病毒字符串进行滚动操作；
			{
				for (j = 0; j < VirusLength; j++)
					Temp[j] = VirusChar[i + j];
				Temp[VirusLength] = '\0';
				if (KMP(HumanChar,Temp , next) == YES)//如果返回
				{
					cout << "YES" << endl;
					break;
				}
				else if(KMP(HumanChar, Temp, next) == NO)
				{
					ERRORCOUNT++;//开始错误计数，只有当错误数目等于字符串长度时候，才认为匹配失败；
					if (ERRORCOUNT == VirusLength)
					  cout << "NO" << endl;
				}
			}
		}
	}
	system("pause");
	return 0;
}

/* P为模式串，下标从0开始 */
void GetNext(char VirusChar[], int next[])//得到GetNext函数；
{
	int p_len = strlen(VirusChar);
	int i = 0;   //P的下标
	int j = -1;
	next[0] = -1;

	while (i < p_len)
	{
		if (j == -1 || VirusChar[i] == VirusChar[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

/* 在S中找到P第一次出现的位置 */
int KMP(char VirusChar[], char HumanChar[], int next[])//KMP主算法；
{
	GetNext(HumanChar, next);//开始求得next数组；

	int i = 0;  //S的下标
	int j = 0;  //P的下标
	int VCLength = strlen(VirusChar);
	int HMLength = strlen(HumanChar);

	while (i < VCLength && j < HMLength)
	{
		if (j == -1 || VirusChar[i] == HumanChar[j])  //P的第一个字符不匹配或S[i] == P[j]
		{
			i++;
			j++;
		}
		else
			j = next[j];  //当前字符匹配失败，进行跳转
	}

	if (j == HMLength)  //匹配成功
		return YES;//位置是i - j;
	else
		return NO;
}
/*
void GetNextTval(char P[], int nexttval[])//得到GetNextTval函数；
{
	int i = 0;
	int j = -1;
	nexttval[0] = -1;
	int p_len = strlen(P);
	while (i < p_len)
	{
		if (j == -1 || P[i] == P[j])
		{
			i++;
			j++;
			if (P[i] != P[j])
				nexttval[i] = j;
			else
				nexttval[i] = nexttval[j];
		}
		else
			j = nexttval[j];
	}
}
*/
