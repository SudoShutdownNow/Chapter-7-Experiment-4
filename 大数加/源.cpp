#include <iostream>
using namespace std;
#define MAX 200
#define NUMMAX 100
#pragma warning(disable : 4996)

char*& add(char* a, char* b)
{
	char* res = new char[MAX];

	char* pa = a + strlen(a) - 1;//右对齐
	char* pb = b + strlen(b) - 1;
	char* pr = res;
	bool up = false;//进位标识

	while (pa != NULL || pb != NULL)
	{
		if (up == true)
		{
			*pr = '1'-'0';
			up = false;
		}
		else
		{
			*pr = '0' - '0';
		}
		
		if (pa != NULL && pb != NULL)
		{
			*pr += *pa + *pb - '0';
		}
		else if (pa != NULL && pb == NULL)
		{
			*pr += *pa;
		}
		else if (pb != NULL && pa == NULL)
		{
			*pr += *pb;
		}
		
		if (*pr > '9')
		{
			*pr -= 10;
			up = true;
		}

		if (pa == a || pa == NULL)
		{
			pa = NULL;
		}
		else
		{
			pa--;
		}
		
		if (pb == b || pb == NULL)
		{
			pb = NULL;
		}
		else
		{
			pb--;
		}
		
		pr++;
		
	}
	*pr = '\0';

	if (up == true)
	{
		strcat(res, "1");
		up = false;
	}
	res = strrev(res);
	
	return res;
}

void testmain()
{
	char* a = new char[MAX];
	char* b = new char[MAX];

	strcpy(a, "123456");
	strcpy(b, "654321");
	char* res = add(a, b);
	cout << res;
}

int main()
{
	static char numbers[NUMMAX][MAX];
	
	char* temp = new char[MAX];
	int i = 0;

	while (1)
	{
		int n;
		cin >> n;

		if (n == 0)
		{
			break;
		}

		for (int i = 1; i <= n; i++)
		{
			cin >> temp;
			strcpy(numbers[i-1], temp);
		}

		char* res = new char[MAX];
		strcpy(res, numbers[0]);
		for (int j = 1; j < n; j++)
		{
			res = add(res, numbers[j]);
		}
		cout << res << endl;

	}
	
	
}

/*
5
123456789
6287999980
5645645654654
5
79
0
*/