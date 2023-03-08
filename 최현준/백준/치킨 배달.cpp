#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int n; int m; int chicken_len; int house_len; int ans = 21e8;

int city[51][51];
int dist[101];
int visited[14] = { 0 };

struct node {
	int y;
	int x;
};

vector<node> house;
vector<node> chicken;

void dfs(int start, int cnt)
{
	if (cnt == m)
	{
		int result = 0;
		for (int i = 0; i < house_len; i++)
		{
			result += dist[i];
		}
		ans = min(ans, result);
		return;
	}

	for (int i = start; i < chicken_len; i++)
	{
		if (visited[i]) continue;

		visited[i] = 1;

		int temp[101];

		node target = chicken[i];

		for (int j = 0; j < house_len; j++)
		{
			node home = house[j];

			int result = abs(target.y - home.y) + abs(target.x - home.x);

			temp[j] = dist[j];
			dist[j] = min(result, dist[j]);
		}
		dfs(i, cnt + 1);
		for (int j = 0; j < house_len; j++)
			dist[j] = temp[j];
		visited[i] = 0;
	}

}

int main()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> city[i][j];
			if (city[i][j] == 1)
				house.push_back({ i,j });
			if (city[i][j] == 2)
				chicken.push_back({ i,j });
		}
	}
	house_len = house.size();
	chicken_len = chicken.size();


	for(int i = 0; i<101; i++)
		dist[i] = 21e8;

	dfs(0, 0);

	cout << ans;


	return 0;
}