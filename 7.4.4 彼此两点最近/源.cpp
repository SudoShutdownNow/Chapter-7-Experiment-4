#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct point {
	int x;
	int y;

	point(int myx, int myy) :x(myx), y(myy) {};

	bool operator< (const point a) const {
		if (a.x != x)
		{
			return a.x > x;
		}
		else
		{
			return a.y > y;
		}
	}

};

typedef struct pointpair {
	point* points[2];
	friend ostream& operator<<(ostream& out, pointpair mypair)
	{
		out << "(" << mypair.points[0]->x << "," << mypair.points[0]->y << ")" << " (" << mypair.points[1]->x << "," << mypair.points[1]->y << ")";
		return out;
	}
};

float calcDist(point p1, point p2)
{
	float deltax = pow((p1.x - p2.x), 2);
	float deltay = pow((p1.y - p2.y), 2);

	return pow((deltax + deltay), 0.5);
}

void testmain()
{
	point point1(1, 1);
	point point2(3, 6);
	cout << calcDist(point1, point2);
}

//vector<pointpair*> findNear(vector<point> points)
void findNear(vector<pointpair*>& pairs, vector<point> points)
{
	//vector<pointpair*> pairs;
	vector<point>::iterator a = points.begin();
	vector<point>::iterator b = points.begin() + 1;

	float minDis = calcDist(*a, *b);
	pointpair* temppair = new pointpair();
	temppair->points[0] = &*a;
	temppair->points[1] = &*b;
	pairs.push_back(temppair);

	for (a = points.begin(); a != points.end()-1; a++)
	{
		for (b = a + 1; b != points.end(); b++)
		{
			if (calcDist(*a, *b) < minDis)
			{
				temppair = new pointpair();
				minDis = calcDist(*a, *b);
				pairs.clear();
				temppair->points[0] = &*a;
				temppair->points[1] = &*b;
				pairs.push_back (temppair);
			}
			else if (calcDist(*a, *b) == minDis && temppair->points[0] != &*a && temppair->points[1] != &*b)
			{
				temppair = new pointpair();
				temppair->points[0] = &*a;
				temppair->points[1] = &*b;
				pairs.push_back (temppair);
			}
		}
	}

	vector<pointpair*>::iterator iter;
	for (iter = pairs.begin(); iter != pairs.end(); iter++)
	{
		cout << **iter << endl;
	}
	cout << endl;
	//return pairs;
	
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

		vector<point> points;
		

		int x, y;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			point mypoint(x, y);
			points.push_back(mypoint);
		}

		sort(points.begin(), points.end());
		vector<pointpair*> res;
		findNear(res,points);
		/*vector<pointpair*>::iterator iter;
		for (iter = res.begin(); iter != res.end(); iter++)
		{
			cout << **iter << endl;
		}
		cout << endl;*/


	}
}

int main()
{
	realmain();
}

/*
4
1 2
0 0
3 6
7 2
3
1 3
3 1
0 0
11
1 2
2 3
3 5
7 5
9 6
9 7
10 8
1 9
9 1
10 11
10 12
0
*/