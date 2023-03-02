#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

#include <algorithm>
using namespace std;

int T;

int recipe;

int table[17][17];

int ans;

int visited[17] = { 0 };

void dfs(int cnt, int st)
{

	if (cnt == recipe / 2)
	{
		int a = 0;
		int b = 0;

		for (int i = 0; i < recipe; i++)
		{
			for (int j = 0; j < recipe; j++)
			{
				if (visited[i] && visited[j])
					a += table[i][j];
				else if (!visited[i] && !visited[j])
					b += table[i][j];
			}
		}

		int tmp = abs(a - b);

		ans = min(ans, tmp);

		return;
	}


	for (int i = st; st < recipe; st++)
	{
		visited[st] = 1;
		dfs(cnt + 1, st + 1);
		visited[st] = 0;
	}



}

int main()
{
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> recipe;
		ans = 21e8;
		for (int i = 0; i < recipe; i++)
		{
			for (int j = 0; j < recipe; j++)
			{
				cin >> table[i][j];
			}
		}


		dfs(0, 0);

		cout << "#" << tc << " " << ans << endl;

	}

	return 0;
}