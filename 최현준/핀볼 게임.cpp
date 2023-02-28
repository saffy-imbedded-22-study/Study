#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector> 
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

int T;
int n;

int field[101][101];

struct pinball {
	int y;
	int x;
	int dir;
	int score;
};

struct node {
	int y;
	int x;
};

int ydir[4] = { -1,0,1,0 }; // À§ ¿À¸¥ ¾Æ·¡ ÁÂ
int xdir[4] = { 0,1,0,-1 };
vector<node> warmhole[11];
pinball ball;
int ans;

void play()
{
	int y = ball.y;
	int x = ball.x;
	int dir = ball.dir;
	int score = ball.score;

	while (1)
	{
		//¿Üº®
		if (y + ydir[dir] < 0 || y + ydir[dir] >= n || x + xdir[dir] < 0 || x + xdir[dir] >= n)
		{
			score *= 2;
			score++;
			break;
		}
		//ºó°ø°£ÀÏ ¶§
		else if (field[y + ydir[dir]][x + xdir[dir]] == 0)
		{
			y = y + ydir[dir];
			x = x + xdir[dir];
		}
		//ºí·Ï
		else if (field[y + ydir[dir]][x + xdir[dir]] == 1)
		{
			if (dir == 0 || dir == 1)
			{
				score *= 2;
				score++;
				break;
			}
			else if (dir == 2)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 1;
				score++;
			}
			else if (dir == 3)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 0;
				score++;
			}
		}

		else if (field[y + ydir[dir]][x + xdir[dir]] == 2)
		{
			if (dir == 1 || dir == 2)
			{
				score *= 2;
				score++;
				break;
			}
			else if (dir == 0)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 1;
				score++;
			}
			else if (dir == 3)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 2;
				score++;
			}
		}

		else if (field[y + ydir[dir]][x + xdir[dir]] == 3)
		{
			if (dir == 2 || dir == 3)
			{
				score *= 2;
				score++;
				break;
			}
			else if (dir == 0)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 3;
				score++;
			}
			else if (dir == 1)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 2;
				score++;
			}
		}


		else if (field[y + ydir[dir]][x + xdir[dir]] == 4)
		{
			if (dir == 0 || dir == 3)
			{
				score *= 2;
				score++;
				break;
			}
			else if (dir == 1)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 0;
				score++;
			}
			else if (dir == 2)
			{
				y = y + ydir[dir];
				x = x + xdir[dir];
				dir = 3;
				score++;
			}
		}


		else if (field[y + ydir[dir]][x + xdir[dir]] == 5)
		{
			score *= 2;
			score++;
			break;
		}


		//¿úÈ¦
		else if (field[y + ydir[dir]][x + xdir[dir]] >= 6)
		{
			int ind = field[y + ydir[dir]][x + xdir[dir]];

			if (y + ydir[dir] == warmhole[ind][0].y && x + xdir[dir] == warmhole[ind][0].x)
			{
				y = warmhole[ind][1].y;
				x = warmhole[ind][1].x;
			}

			else if (y + ydir[dir] == warmhole[ind][1].y && x + xdir[dir] == warmhole[ind][1].x)
			{
				y = warmhole[ind][0].y;
				x = warmhole[ind][0].x;
			}
		}



		//Ãâ¹ßÁöÁ¡
		if (y == ball.y && x == ball.x)
			break;


		//ºí·¢È¦
		if (field[y + ydir[dir]][x + xdir[dir]] == -1)
			break;
	}

	ans = max(score, ans);



}


int main()
{
	cin >> T;
	ball.y = 0;
	ball.x = 0;
	ball.dir = 0;
	ball.score = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n;
		ans = -21e8;

		for (int i = 6; i <= 10; i++)
		{
			warmhole[i].clear();
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> field[i][j];
				if (field[i][j] >= 6)
				{
					warmhole[field[i][j]].push_back({ i,j });
				}
			}

		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					if (field[i][j] == 0)
					{
						ball.y = i;
						ball.x = j;
						ball.dir = k;
						ball.score = 0;
						play();
					}
				}
			}
		}



		cout << "#" << tc << " " << ans << endl;

	}


	return 0;
}