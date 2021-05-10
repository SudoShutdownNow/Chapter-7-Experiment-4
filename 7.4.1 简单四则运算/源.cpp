#include <iostream>
#include <stack>
#include <iomanip>

using namespace std;
#pragma warning (disable : 4996)

void parse(char* express, stack<double> &numbers, stack<char> &symbols)//处理乘除并将所有数字和符号压入栈中
{
	char* p = express;
	while (*p != '\0')
	{
		char temp[10];
		char* t = temp;

		while (*p >= '0' && *p <= '9' && *p != '\0' || *p == '.')
		{
			*t = *p;
			t++;
			p++;
		}

		*t = '\0';
		double ntemp;
		sscanf(temp, "%lf", &ntemp);
		numbers.push(ntemp);

		//make judge on the top of symbol stack

		if (!symbols.empty())
		{
			if (symbols.top() == '*')
			{
				double a, b, res;
				a = numbers.top();
				numbers.pop();
				b = numbers.top();
				numbers.pop();

				res = a * b;
				numbers.push(res);
				symbols.pop();
			}

			else if (symbols.top() == '/')
			{
				double a, b, res;
				a = numbers.top();
				numbers.pop();
				b = numbers.top();
				numbers.pop();

				if (a == 0)
				{
					char* e = new char[10];
					strcpy(e, "DivByZero");
					throw(e);
					return;
				}
				res = b / a;
				numbers.push(res);
				symbols.pop();
			}
		}
		
		
		if (*p == '\0')
		{
			return;
		}
		symbols.push(*p);
		p++;
	}
}//

void add(stack<double>& numbers, stack<char>& symbols)//把仅含有加法的栈进行运算
{
	while (!symbols.empty())
	{
		double a, b, res;
		a = numbers.top();
		numbers.pop();
		b = numbers.top();
		numbers.pop();
		if (symbols.top() == '+')
		{
			res = a + b;
			numbers.push(res);
			symbols.pop();
		}
		else if (symbols.top() == '-')
		{
			res = b - a;
			numbers.push(res);
			symbols.pop();
		}
	}
}

int main()
{
	stack<double> numbers;
	stack<char> symbols;

	char express[100];
	while (cin >> express)//输入表达式
	{
		try
		{
			parse(express, numbers, symbols);
			add(numbers, symbols);
		}
		catch (char* e)
		{
			cout << e << endl;
			continue;
		}


		cout << scientific << numbers.top() << endl;
		system("pause");
		numbers.pop();

	}
	


}

//1+2-3*4+5/6