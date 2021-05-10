#include <iostream>
#include <string>
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
			*pr = '1' - '0';
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

char*& subtract(char* a, char* b)
{
	char* res = new char[MAX];

	char* pa = a + strlen(a) - 1;//右对齐
	char* pb = b + strlen(b) - 1;
	char* pr = res;
	bool borrow = false;//借位标识
	bool nagetive = false;//负数标识

	char* tempa = a;
	char* tempb = b;
	while (1)//比大小
	{
		if (strlen(a) < strlen(b))
		{
			char* temp = pa;
			pa = pb;
			pb = temp;
			temp = a;
			a = b;
			b = temp;
			nagetive = true;
		}

		else if (strlen(a) == strlen(b))
		{
			if (strcmp(a, b) == 0)
			{
				strcpy (res, "0");
				return res;
			}
			
			if (*tempa < *tempb)
			{
				char* temp = pa;
				pa = pb;
				pb = temp;
				temp = a;
				a = b;
				b = temp;
				nagetive = true;
				break;
			}
			else if (*tempa == *tempb)
			{
				tempa++;
				tempb++;
			}
			else
			{
				break;
			}
		}

		else
		{
			break;
		}
	}
	

	while (pa != NULL || pb != NULL)
	{
		if (borrow == true)
		{
			*pr = '0' - '1';
			borrow = false;
		}
		else
		{
			*pr = '0' - '0';
		}

		if (pa != NULL && pb != NULL)
		{
			*pr += *pa - *pb + '0';
		}
		else if (pa != NULL && pb == NULL)
		{
			*pr += *pa;
		}
		else if (pb != NULL && pa == NULL)
		{
			*pr += *pb;
		}

		if (*pr < '0')
		{
			*pr += 10;
			borrow = true;
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

	if (*(pr - 1) == '0')
	{
		*(pr - 1) = '\0';
	}
	else
	{
		*pr = '\0';
	}
	

	if (nagetive == true)
	{
		strcat(res, "-");
		//borrow = false;
	}
	res = strrev(res);

	return res;
}

char*& parse(char* a, char* b)//分解数字
{
	char* res = new char[MAX];
	bool negative[2];
	if (*a == '-')
	{
		negative[0] = true;
		a++;
	}
	else
	{
		negative[0] = false;
	}

	if (*b == '-')
	{
		negative[1] = true;
		b++;
	}
	else
	{
		negative[1] = false;
	}

	if (negative[0] == negative[1])//同正或同负
	{

		if (negative[0] == false)
		{
			res = add(a, b);
		}
		else
		{
			strcpy(res, "-");
			strcat(res, add(a, b));
		}
	}
	else
	{
		if (negative[0] == false && negative[1] == true)//一正一负
		{
			res = subtract(a, b);
		}
		else if (negative[0] == true && negative[1] == false)//一负一正
		{
			res = subtract(a, b);
			if (*res == '-')
			{
				res++;
			}
			else
			{
				char* temp = new char[MAX];
				sprintf(temp, "-%s", res);
				res = temp;
			}
		}
	}

	return res;
}



void testmain()
{
	char* a = new char[MAX];
	char* b = new char[MAX];

	cin >> a;
	cin >> b;
	char* res = parse (a, b);
	cout << res;
}


void parsemain()
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
			strcpy(numbers[i - 1], temp);
		}

		char* res = new char[MAX];
		strcpy(res, numbers[0]);
		for (int j = 1; j < n; j++)
		{
			res = parse(res, numbers[j]);
		}
		cout << res << endl;

	}
}

int main()
{
	parsemain();
}

/*
2
123123123123123123
-2
2
43242342342342
-1234567654321
0
*/