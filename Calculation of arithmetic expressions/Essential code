#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define true 1
#define false 0
#define OPSETSIZE 7
using namespace std;

typedef int Status;
typedef struct StackChar {		
	char data;
	struct StackChar *next;
}CharStackNode, *LinkCharStack; //定义储存字符栈；

typedef struct StackFloat {		
	double data;
	struct StackFloat *next;
}NumStackNode, *LinkNumStack; //定义储存数字栈；

char OPSET[OPSETSIZE] = { '+' , '-' , '*' , '/' ,'(' , ')' , '#' };
unsigned char Prior[OPSETSIZE][OPSETSIZE] = { // 算符间的优先级表 ，用于算符优先算法的判断；
	//'+' '-' '*' '/' '(' ')' '#' '^' '%'
	/*'+'*/'>','>','<','<','<','>','>',
	/*'-'*/'>','>','<','<','<','>','>',
	/*'*'*/'>','>','>','>','<','>','>',
	/*'/'*/'>','>','>','>','<','>','>',
	/*'('*/'<','<','<','<','<','=',' ',
	/*')'*/'>','>','>','>',' ','>','>',
	/*'#'*/'<','<','<','<','<',' ','=',
};

//全局函数声明开始；
double EvaluateExpression(char* e);//实现算符优先算法的函数；
void CPush(LinkCharStack &s, char c);//使算符c进入算符栈；
void Push(LinkNumStack &s, double f);//使数值f进入数值栈；
char CPop(LinkCharStack &s);//使字符栈的栈顶元素出栈，并返回出栈元素；
double Pop(LinkNumStack &s);//使数值栈的栈顶元素出栈，并返回出栈数字；
double Operate(double a, unsigned char t, double b); //进行运算，a,b为数，t为运算符；
Status In(char Test, char* TestOp);//判断是不是运算符 ，返回是或不是；
char precede(char Aop, char Bop);//判断优先级，返回'>'或'<'或'='；
int ReturnOpOrd(char op, char *TestOp);//判断是哪个运算符；
double GetTop(LinkNumStack &S);//返回数字栈栈元素；
char CGetTop(LinkCharStack &S);//返回字符栈栈顶元素；


int main()//程序主函数开始；
{
	char s[128];//定义一个表达式储存数组；
	cout << "/*请输入算数表达式计算，以#符号结束*/" << "	*[例如9+6*(3+2)/4#]" << endl << endl;
	cout<<"			#目前仅支持四则运算#" << endl;
	while (true)
	{
		cout << "请输入一个算数表达式：";
		cin >> s;
		printf_s("\n计算结果是:%s\b=%lf\n", s, EvaluateExpression(s)); //调用算符优先算法函数；
		cout << endl;
	}
	system("pause");
	return 0;
}

double EvaluateExpression(char* e)//进行运算的主函数；
{
	LinkCharStack OPTR = NULL; // 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈；
	LinkNumStack OPND = NULL; 
	char TempData[20] = {};//定义一个临时数组用来储存数字，注意将该数组置为空；
	double Data, a, b;
	char theta, Popchar;
	int icout = 0;//定义计数器；
	CPush(OPTR, '#');
	while (*e != '#' || OPTR->data != '#')
	{
		if (!In(*e, OPSET)) // 不是运算符则进栈；
		{
			TempData[icout] = *e;//将数字依此输入字符数组；
			e++;
			icout++;//计数器自增，用于加入数组结束标志；
			if (In(*e, OPSET))//如果下一个元素是运算符，进行转化为浮点数操作；
			{
				TempData[icout] = '\0';//加入数组结束标志符号；
				icout = 0;//计数器归零；
				Data = atof(TempData);//字符串转换为浮点数；
				Push(OPND, Data);//将转化的浮点数推入栈中；
				strcpy_s(TempData, "\0");//将推入栈中的数字重置为0；
			}
		}
		else//如果是运算符；
		{
			switch (precede(CGetTop(OPTR), *e))
			{
			case '<': // 栈顶元素优先权低；
				CPush(OPTR, *e);//将此运算符入栈；
				e++;
				break;
			case '=': 
				Popchar = CPop(OPTR); //脱括号丢掉后接收下一字符；
				e++;
				break;
			case '>': // 退栈并将运算结果入栈
				theta = CPop(OPTR);//运算符出栈；
				b = Pop(OPND);//数字出栈；
				a = Pop(OPND);//数字出栈；
				Push(OPND, Operate(a, theta, b));//运算后进入栈顶；
				break;
			}
		}
	}
	return GetTop(OPND);//返回数字最后的的元素，即结果；
}

void CPush(LinkCharStack &s, char c)//使算符c进入算符栈；
{
	LinkCharStack p = new CharStackNode;//开辟一个新空间；
	p->data = c;
	p->next = s;
	s = p;
	cout<<"PUSH NUMBER STACK \""<<c<<"\" IS SUCCESS" << endl;//输出入栈结果；
}

void Push(LinkNumStack &s, double f)//使浮点数进入数值栈；
{
	LinkNumStack p = new NumStackNode;
	p->data = f;
	p->next = s;
	s = p;
	cout << "PUSH CHAR STACK \"" << f << "\" IS SUCCESS" << endl;
}

char CPop(LinkCharStack &s)//使算符栈的栈顶元素出栈；
{
	LinkCharStack q = s;
	char ch;
	ch = q->data;
	s = s->next;
	delete(q);
	cout << "POP CHAR STACK \"" << ch << "\" IS SUCCESS" << endl;
	return ch;
}

double Pop(LinkNumStack &s)//使数值栈的栈顶元素出栈
{
	LinkNumStack q = s;
	double num;
	num = q->data;
	s = s->next;
	delete(q);
	cout<<"POP NUMBER STACK \""<<num<<"\" IS SUCCESS"<<endl;
	return num;
}

double Operate(double a, unsigned char t, double b)//运算函数；
{
	switch (t)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return 0;
	}
}

Status In(char Test, char* TestOp)//判断是不是运算符 ，返回1或者0；
{
	int Find = false;
	for (int i = 0; i<OPSETSIZE; i++)
	{
		if (Test == TestOp[i])
			Find = true;
	}
	return Find;
}

char precede(char Aop, char Bop)//判断优先级，返回字符'>'或'<'或'='；
{
	return Prior[ReturnOpOrd(Aop, OPSET)][ReturnOpOrd(Bop, OPSET)];//对字符串优先级进行计算，返回字符">""<""="来进行后面的操作；
}

int ReturnOpOrd(char op, char *TestOp)//判断是哪个运算符；
{
	for (int i = 0; i< OPSETSIZE; i++)
		if (op == TestOp[i])
			return i;
}

double GetTop(LinkNumStack &S)//返回栈顶的浮点数；
{
	if (S != NULL)
	{
		printf("GET NUMBERTOP IS SUCCESS");
		return S->data;
	}
}

char CGetTop(LinkCharStack &S)//返回栈顶的运算符字符；
{
	if (S != NULL)
	{
		printf("GET CHARTOP IS SUCCESS");
		return S->data;
	}
}
