#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int diry[4] = {-1, 1, 0, 0};
int dirx[4] = {0, 0, -1, 1};

int N, M;
int Map[50][50];
int visited[50][50];
struct node
{
	int y, x;
	int limit;
	int maxlimit;
};
node start;
node dest;

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
			visited[i][j] = 21e8;
			if (Map[i][j] == 2)
			{
				start = {i, j, 0};
			}
			else if (Map[i][j] == 3)
			{
				dest = {i, j};
			}
		}
	}

	queue<node> q;
	q.push(start);
	visited[start.y][start.x] = -1;

	while (!q.empty())
	{
		node now = q.front();
		q.pop();

		// if (now.maxlimit > visited[now.y][now.x]) continue;

		if (Map[now.y][now.x] == 0)
		{ // 공중
			for (int i = 0; i < 2; i++)
			{ // 상하 이동만
				int dy = now.y + diry[i];
				int dx = now.x + dirx[i];
				if (dy >= N || dy < 0 || dx >= M || dx < 0)
					continue;
				node next = {dy, dx, now.limit, now.maxlimit};
				next.limit++;
				next.maxlimit = max(next.maxlimit, next.limit);
				if (Map[dy][dx] == 1)
				{
					next.limit = 0;
				}
				if (next.maxlimit >= visited[dy][dx])
					continue;
				visited[dy][dx] = next.maxlimit;
				q.push(next);
			}
		}
		else if (Map[now.y][now.x] == 3)
		{
			continue;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{ // 상하좌우, 좌우 땅 있을때만
				int dy = now.y + diry[i];
				int dx = now.x + dirx[i];
				if (dy >= N || dy < 0 || dx >= M || dx < 0)
					continue;
				node next = {dy, dx, now.limit, now.maxlimit};
				if (i == 2 || i == 3)
				{ // 좌우에 땅 없으면 이동 x
					if (Map[dy][dx] == 0)
						continue;
				}
				else
				{ // 위아래 이동시 limit 추가
					next.limit++;
					next.maxlimit = max(next.maxlimit, next.limit);
				}
				if (Map[dy][dx] == 1)
				{
					next.limit = 0;
				}
				if (next.maxlimit >= visited[dy][dx])
					continue;
				visited[dy][dx] = next.maxlimit;
				q.push(next);
			}
		}
	}

	cout << visited[dest.y][dest.x];

	return 0;
}