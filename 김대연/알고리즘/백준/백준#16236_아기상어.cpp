/*


*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int diry[4] = {-1, 0, 1, 0};
int dirx[4] = {0, -1, 0, 1};

int N;				  // 공간의 크기
int Map[20][20];	  // 맵
int CantMove[20][20]; // 이동 가능 위치 저장
int DAT[20][20];
struct node
{
	int y, x;
	int dist;
};

void CheckMove(int level)
{

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] > level)
			{
				CantMove[i][j] = 1; // 이동 불가능
			}
			else
			{
				CantMove[i][j] = 0;
			}
		}
	}
}

node CanEat(int level, int nowy, int nowx)
{
	vector<node> v; // 먹을 수 있는거 저장

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] < level && Map[i][j] > 0)
			{
				v.push_back({i, j, 0});
			}
		}
	}

	queue<node> q;
	q.push({nowy, nowx});

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			DAT[i][j] = 99999;
		}
	}
	DAT[nowy][nowx] = 0;

	while (!q.empty())
	{
		node now = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int dy = now.y + diry[dir];
			int dx = now.x + dirx[dir];
			if (dy >= N || dy < 0 || dx >= N || dx < 0)
				continue;
			if (CantMove[dy][dx] == 1)
				continue;
			if (DAT[dy][dx] <= DAT[now.y][now.x] + 1)
				continue;
			DAT[dy][dx] = DAT[now.y][now.x] + 1;
			q.push({dy, dx, DAT[dy][dx]});
		}
	}

	node Min = {0, 0, 99999};
	for (int i = 0; i < v.size(); i++)
	{
		if (Min.dist > DAT[v[i].y][v[i].x])
		{
			v[i].dist = DAT[v[i].y][v[i].x];
			Min = v[i];
		}
	}
	return Min;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	node start = {0, 0, 0};
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 9)
			{
				start = {i, j, 0};
				Map[i][j] = 0;
			}
		}
	}

	int level = 2;
	int exp = 0;
	CheckMove(2);
	node now = start;
	node next = CanEat(2, start.y, start.x);
	int ans = 0;
	while (1)
	{
		if (next.dist == 99999)
		{
			break;
		}

		ans += next.dist;
		Map[next.y][next.x] = 0;
		exp++;
		if (exp == level)
		{
			level++;
			exp = 0;
			CheckMove(level);
		}
		now = next;
		next = CanEat(level, now.y, now.x);
	}

	cout << ans;

	return 0;
}