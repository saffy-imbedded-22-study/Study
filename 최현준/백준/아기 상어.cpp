#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n; int ans; int level; int kill_count; int done;

struct node {
	int y;
	int x;
	int time;
	bool operator<(node next) const {
		if (y < next.y) return false;
		if (y > next.y) return true;
		if (x < next.x) return false;
		if (x > next.x) return true;
		return false;
	}
};

node shark;

//상좌하우 순 (위에있는 물고기 -> 왼쪽 물고기 순)
int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

int ocean[21][21];

void move(int y, int x, int time)
{
	queue<node>q;
	priority_queue<node>ans_q;
	q.push({ y,x,time});

	int visited[21][21] = { 0, };
	visited[y][x] = 1;

	while (!q.empty())
	{
		node now = q.front();
		q.pop();
		
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int ntime = now.time + 1;
			
			if (ntime > ans && !ans_q.empty())
			{
				node target = ans_q.top();
				kill_count--;
				if (kill_count == 0)
				{
					level++;
					kill_count = level;
				}
				ocean[target.y][target.x] = 0;
				shark.y = target.y;
				shark.x = target.x;
				done = 1;
				return;
			}

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (ocean[ny][nx] > level) continue;
			if (visited[ny][nx]) continue;

			visited[ny][nx] = 1;

			if (ocean[ny][nx] > 0 && ocean[ny][nx] < level)
			{
				ans = ntime;
				ans_q.push({ ny, nx, ntime });
			}

			q.push({ ny,nx, ntime});
		}
	}
}

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> ocean[i][j];
			if (ocean[i][j] == 9)
			{
				shark = { i,j,0};
				ocean[i][j] = 0;
			}
		}
	}

	ans = 0;
	level = 2;
	kill_count = level;
	done = 1;

	while (done)
	{
		done = 0;
		move(shark.y, shark.x, ans);
	}

	cout << ans;

	return 0;
}