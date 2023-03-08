#include <iostream>
#include <vector> 
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

struct micro {
	int y;
	int x;
	int num;
	int dir;
};

struct semicro {
	int num;
	int dir;
	int ind;
};

int T;
int N, M, K;
int ans;
int ydir[5] = { 0,-1,1,0,0 };
int xdir[5] = { 0,0,0,-1,1 };

vector<micro> field[1001];

vector<semicro> cell[101][101];

int main()
{
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M >> K;

		ans = 0;

		for (int i = 0; i < K; i++)
		{
			field[i].clear();
		}

		for (int i = 0; i < K; i++)
		{
			int Y, X, NUM, DIR;
			cin >> Y >> X >> NUM >> DIR;

			field[i].push_back({ Y,X,NUM,DIR });
		}

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < 101; j++)
			{
				for (int k = 0; k < 101; k++)
					cell[j][k].clear();
			}

			int y, x, num, dir;
			for (int j = 0; j < K; j++)
			{
				y = field[j][0].y;
				x = field[j][0].x;
				num = field[j][0].num;
				dir = field[j][0].dir;


				y = y + ydir[dir];
				x = x + xdir[dir];

				if (y == 0 || y == N - 1 || x == 0 || x == N - 1)
				{
					num /= 2;
					if (dir == 1)
						dir = 2;
					else if (dir == 2)
						dir = 1;
					else if (dir == 3)
						dir = 4;
					else if (dir == 4)
						dir = 3;
				}

				cell[y][x].push_back({ num,dir,j });

				field[j][0].y = y;
				field[j][0].x = x;
				field[j][0].num = num;
				field[j][0].dir = dir;
			}

			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < N; k++)
				{
					if (cell[j][k].size() <= 1) continue;


					int standard = cell[j][k][0].num;
					int main_dir = cell[j][k][0].dir;
					int main_ind = cell[j][k][0].ind;
					int sum = standard;

					for (int p = 1; p < cell[j][k].size(); p++)
					{
						int num = cell[j][k][p].num;
						int dir = cell[j][k][p].dir;
						int ind = cell[j][k][p].ind;

						if (num > standard)
						{
							field[main_ind][0].dir = 0;
							field[main_ind][0].num = 0;
							standard = cell[j][k][p].num;
							main_dir = dir;
							main_ind = ind;
						}
						else
						{
							field[ind][0].dir = 0;
							field[ind][0].num = 0;
						}
						sum += num;

					}
					field[main_ind][0].num = sum;
					field[main_ind][0].dir = main_dir;
				}
			}
		}

		for (int i = 0; i < K; i++)
		{
			ans += field[i][0].num;
		}

		cout << "#" << tc << " " << ans << endl;


	}
	return 0;
}