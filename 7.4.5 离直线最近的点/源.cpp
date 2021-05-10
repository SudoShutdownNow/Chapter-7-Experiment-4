#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct line {
	double A, B, C;

	line(int x1, int y1, int x2, int y2)
	{
		A = y2 - y1;
		B = x1 - x2;
		C = (x2 * y1) - (x1 * y2);
	}
};

typedef struct point {
	int x;
	int y;

	point(int myx, int myy) :x(myx), y(myy) {};
};

double calcDis(line myline, point mypoint)
{
	int x = mypoint.x;
	int y = mypoint.y;
	return pow(pow((x * myline.A + y * myline.B + myline.C), 2) / (pow(myline.A, 2) + pow(myline.B, 2)), 0.5);
}

void findNear(line myline, vector<point>& res, vector<point> points)
{
	vector<point>::iterator iter = points.begin();
	int min = calcDis(myline,*iter);
	res.push_back(*iter);

	for (iter = points.begin(); iter != points.end(); iter++)
	{
		if (calcDis(myline, *iter) < min)
		{
			res.clear();
			res.push_back(*iter);
			min = calcDis(myline, *iter);
		}
		else if (calcDis(myline, *iter) == min && iter != points.begin())
		{
			res.push_back(*iter);
		}
	}
}


void testmain()
{
	line myline(0, 0, 1, 1);
	point mypoint(5, 6);
	cout << calcDis(myline, mypoint);
}

void realmain()
{
	while (1)
	{
		int n;
		cin >> n;
		if (n == 0)
		{
			break;
		}

		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		line myline(x1, y1, x2, y2);

		vector<point> points;
		int x, y;
		point* temp;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			temp = new point(x, y);
			points.push_back(*temp);
		}

		vector<point> res;
		findNear(myline, res, points);

		vector<point>::iterator iter;
		for (iter = res.begin(); iter != res.end(); iter++)
		{
			cout << iter->x << " " << iter->y << " " << endl;
		}
	}
	
}

int main()
{
	realmain();
}

/*
4
1 2 3 4
3 8
10 10
7 2
900 1
0
*/