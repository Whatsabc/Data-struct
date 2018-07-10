#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define HASHSIZE 5
#define NULLKEY -10000
typedef struct {
	int telephonenumber;
	string username;
	string address;
}KeyType;

typedef struct HashTable{
	KeyType key[HASHSIZE];
	int count;//记录当前元素的个数
}HashTable;

void InitHashTable(HashTable &h);
int Hash(int key);//散列函数
int InsertHash(HashTable &h, KeyType key);//插入哈希表；
int SearchHash(HashTable h);//搜索哈希表；
void PrintHash(HashTable h);
void WriteFile(HashTable &h);

int main()
{
	HashTable hashtable;
	KeyType tempkey;
	int usernumber, searchtelephonenumber, i, hash;
	InitHashTable(hashtable);//初始化散列表；
	PrintHash(hashtable);//打印初始化后的散列表；
	cout << "Please enter the number of people you want to enter:";
	cin >> usernumber;
	for (i = 0; i < usernumber; i++)
	{
		cout << "Please key telephone name address:" << endl;
		cin >> tempkey.telephonenumber;
		cin >> tempkey.username;
		cin >> tempkey.address;
		hash=InsertHash(hashtable, tempkey);
		cout << "Hash number is:";
		cout << hash << endl;
	}
	PrintHash(hashtable);//打印构建好的散列表；
	WriteFile(hashtable);//写入到文件；
	SearchHash(hashtable);//开始查找函数；
	system("pause");
	return 0;
}

void InitHashTable(HashTable &h)
{
	int i;
	for (i = 0; i < HASHSIZE; i++)
	{
		h.key[i].telephonenumber = NULLKEY;
	}
	cout << "InitHashTable is success" << endl;
}

int Hash(int key)
{
	return key % HASHSIZE;
}

int InsertHash(HashTable &h, KeyType key)
{
	int addr = Hash(key.telephonenumber);           //求散列地址
	while (h.key[addr].telephonenumber != NULLKEY) //如果不为空，则冲突
	{
		addr = (addr + 1) % HASHSIZE;         //开放地址法的线性探测
	}
	h.key[addr].telephonenumber = key.telephonenumber;             //直到有空位后插入关键字
	h.key[addr].username = key.username;
	h.key[addr].address = key.address;
	return addr;
}

int SearchHash(HashTable h)
{
	while (1)
	{
		int searchtelephonenumber;
		cout << "Please key the telephone that you will search:";
		cin >> searchtelephonenumber;
		int addr = Hash(searchtelephonenumber); //求散列地址
		while (h.key[addr].telephonenumber != searchtelephonenumber) //如果不为空，则冲突
		{
			addr = (addr + 1) % HASHSIZE;     //开放地址法的线性探测
			if (h.key[addr].telephonenumber == NULLKEY || addr == Hash(searchtelephonenumber))
			{
				//如果循环回原点
				cout << "查找失败" << searchtelephonenumber << "不在Hash表中" << endl;
				return -1;
			}
		}
		cout << "His telephone	name	address is:" << endl;
		cout << h.key[addr].telephonenumber << "	" << h.key[addr].username << "		" << h.key[addr].address << endl;
	}
	return 1;
}

void WriteFile(HashTable &h)
{
	ofstream examplefile("E:\\Information file.txt");
	if (examplefile.is_open())
	{
		int i;
		examplefile << "------The personal information list-----" << endl;
		examplefile << "[Telephone]    [Username]    [Address]" << endl;
		for (i = 0; i < HASHSIZE; i++)
		{
			examplefile << h.key[i].telephonenumber << "	";
			examplefile << h.key[i].username << "		";
			examplefile << h.key[i].address << endl;
		}
		examplefile.close();
	}
	cout << "[Information is in E:\\Information file]" << endl;
}

void PrintHash(HashTable h)
{
	int i;
	cout << "此时哈希表的内容是：" << endl;
	for (i = 0; i < HASHSIZE; i++)
	{
		cout << h.key[i].telephonenumber << "		";
		cout << h.key[i].username << "		";
		cout << h.key[i].address << endl;
	}
}