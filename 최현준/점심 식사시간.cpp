#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

int T; int n; int ans; int len;

int stair[11][11];

struct node {
	int y;
	int x;
};

struct info {
	int y;
	int x;
	int value;
};

struct dista {
	int a;
	int b;
};

dista dist[11];
vector<node> student;
vector<info> down;

// 거리 계산
void calc(int cmp)
{
	if (cmp == pow(2, len))
	{
		return;
	}

	// 계단 길이
	int a = down[0].value;
	int b = down[1].value;

	int avalue[11];
	int bvalue[11];

	int a_index = 0;
	int b_index = 0;

	int result = 0;

	// adist {4,3,2,4,2,7},  bdist {5,4,3,3,3,2}
	for (int i = 0; i < len; i++)
	{
		int temp = (cmp >> len - 1 - i) & 1;
		if (temp)
			bvalue[b_index++] = dist[i].b;
		else
			avalue[a_index++] = dist[i].a;
	}

	sort(avalue, avalue + a_index);
	sort(bvalue, bvalue + b_index);

	if (a_index > 3)
	{
		for (int i = 3; i < a_index; i++)
		{
			if (avalue[i - 3] + a > avalue[i])
				avalue[i] = avalue[i - 3] + a;
		}
	}

	if (b_index > 3)
	{
		for (int i = 3; i < b_index; i++)
		{
			if (bvalue[i - 3] + b > bvalue[i])
				bvalue[i] = bvalue[i - 3] + b;
		}
	}

	if (a_index == 0)
		result = bvalue[b_index - 1] + b + 1;
	else if (b_index == 0)
		result = avalue[a_index - 1] + a + 1;
	else
		result = max(avalue[a_index - 1] + a + 1, bvalue[b_index - 1] + b + 1);

	ans = min(result, ans);

	calc(cmp + 1);
}

int main()
{
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n;

		//초기화
		ans = 21e8;

		student.clear();
		down.clear();

		// 입력 받기
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> stair[i][j];
				if (stair[i][j] == 1)
					student.push_back({ i,j });
				if (stair[i][j] > 1)
					down.push_back({ i,j,stair[i][j] });
			}
		}

		len = student.size();
		// 계단 2개와 학생과의 거리 저장
		int ind = 0;
		for (int j = 0; j < len; j++)
		{
			dist[ind] = { abs(down[0].y - student[j].y) + abs(down[0].x - student[j].x), abs(down[1].y - student[j].y) + abs(down[1].x - student[j].x) };
			ind++;
		}

		calc(0);

		cout << "#" << tc << " " << ans << endl;

	}
	return 0;
}