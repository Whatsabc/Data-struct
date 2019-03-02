#include<iostream>
#include<string>
using namespace std;

/* P为模式串，下标从0开始 */
void GetNext(string P, int next[])
{
	int p_len = P.size();
	int i = 0;   //P的下标
	int j = -1;
	next[0] = -1;

	while (i < p_len)
	{
		if (j == -1 || P[i] == P[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
	for (i = 0; i < p_len; i++)
		cout << next[i] << " ";
	cout << endl;
}

/* 在S中找到P第一次出现的位置 */
int KMP(string S, string P, int next[])
{
	cout << "GetNext is :";
	GetNext(P, next);

	int i = 0;  //S的下标
	int j = 0;  //P的下标
	int s_len = S.size();
	int p_len = P.size();

	while (i < s_len && j < p_len)
	{
		if (j == -1 || S[i] == P[j])  //P的第一个字符不匹配或S[i] == P[j]
		{
			i++;
			j++;
		}
		else
			j = next[j];  //当前字符匹配失败，进行跳转
	}

	if (j == p_len)  //匹配成功
		return i - j;
	return -1;
}

void GetNextTval(string P, int nexttval[])
{
	int i = 0;
	int j = -1;
	nexttval[0] = -1;
	int p_len = P.size();
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
	for (i = 0; i < p_len; i++)
		cout << nexttval[i] << " ";
	cout << endl;
}

int main()
{
	void GetNext(string P, int next[]);
	int KMP(string S, string P, int next[]);
	void GetNextTval(string S, int nexttval[]);
	int next[100] = { 0 };
	int nexttval[100] = { 0 };
	cout << "[bbc abcdab abcdabcdabde]" << "-----" << "[abcabaa]" << endl;
	cout << KMP("bbc abcdab abcdabcdabde", "abcabaa", next) << endl; //15//abcdabd
	cout << "GetNextTval is :";
	GetNextTval("abcabaa", nexttval);
	system("pause");
	return 0;
}