#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, l, r;

int ans; int flag;

struct node {
	int value;
	int num;
};

int country[51][51];

int parent[2501];

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

node pop[2501];

//Find 함수
int Find(int now)
{
	if (parent[now] == now)
		return now;

	return parent[now] = Find(parent[now]);
}

//Union 함수
void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb)
		return;

	//value = 같은 union의 누적합, num = 연합의 국가의 수
	pop[pa].value += pop[pb].value;
	pop[pa].num += pop[pb].num;
	parent[pb] = pa;

}

void move(int y, int x)
{
	for (int i = 0; i < 4; i++)
	{
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

		int value = abs(country[ny][nx] - country[y][x]);

		//value의 값이 범위내에 있을 경우 union해준다.
		if (value >= l && value <= r)
		{
			Union(n*y + x, n*ny + nx);
			flag = 1;
		}
	}
}

int main()
{
	cin >> n >> l >> r;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> country[i][j];
			parent[n*i + j] = n * i + j;
			pop[n*i + j] = { country[i][j], 1 };
		}
		
	}

	while (1)
	{
		flag = 0;

		//유니온 작업
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				move(i, j);
		}

		//연합끼리 인구 이동
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				//pop의 index가 Find(parent[n*i+j])인 이유 : 해당 연합의 부모 노드에 누적합과 국가의 개수가 있기 때문에
				//parent[n*i+j]를 사용하되 최종 부모 노드까지 연결 안 된 경우가 있을 수 있기 때문에 find함수를
				//이용해 최종 부모 노드의 인덱스까지 도달하도록 하였다.
				int new_population = pop[Find(parent[n*i + j])].value / pop[Find(parent[n*i + j])].num;
				country[i][j] = new_population;
			}
		}

		//초기화
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				parent[n*i + j] = n * i + j;
				pop[n*i + j] = { country[i][j], 1 };
			}
		}
		if (flag)
			ans++;
		else
			break;

	}
	
	cout << ans;

	return 0;
}