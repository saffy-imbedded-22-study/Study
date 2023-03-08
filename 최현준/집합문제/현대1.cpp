#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector> 
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

int n, m;

char ladder[11][11];

struct node {
	int y;
	int x;
};

int path[11];
vector<node> portal[256];

int main()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2 * m - 1; j++)
		{
			char a;
			if (j % 2 == 0)
			{
				cin >> ladder[i][j / 2];
				if (ladder[i][j / 2] >= 'a' && ladder[i][j / 2] <= 'z')
				{
					portal[ladder[i][j / 2]].push_back({ i,j / 2 });
				}
			}

			else
				cin >> a;

		}
	}


	for (int i = 0; i < m; i++)
	{
		int y = 0;
		int x = i;
		while (1)
		{
			if (y >= n)
			{
				path[x] = i + 1;
				break;
			}
			if (ladder[y][x] == '|')
				y++;
			else if (ladder[y][x] >= 'a' && ladder[y][x] <= 'z')
			{
				if (y == portal[ladder[y][x]][0].y && x == portal[ladder[y][x]][0].x)
				{
					int tmp_y = portal[ladder[y][x]][1].y + 1;
					int tmp_x = portal[ladder[y][x]][1].x;
					y = tmp_y;
					x = tmp_x;
				}
				else if (y == portal[ladder[y][x]][1].y && x == portal[ladder[y][x]][1].x)
				{
					int tmp_y = portal[ladder[y][x]][0].y + 1;
					int tmp_x = portal[ladder[y][x]][0].x;
					y = tmp_y;
					x = tmp_x;

				}
			}
		}
	}

	for (int i = 0; i < m; i++)
		cout << path[i] << " ";

	return 0;
}