#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int T;

int n, x;

int ans, tmp, cnt;

int road[21][21];

int main()
{
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n >> x;
		ans = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> road[i][j];
			}
		}

		for (int i = 0; i < n; i++)
		{
			cnt = 1;
			for (int j = 1; j < n; j++)
			{
				if (road[i][j] == road[i][j - 1])
					cnt++;
				else if (road[i][j] - road[i][j - 1] == 1)
				{
					if (cnt >= x)
						cnt = 1;
					else
					{
						cnt = -1;
						break;
					}
				}
				else if (road[i][j - 1] - road[i][j] == 1)
				{
					if (cnt >= 0)
						cnt = 1 - x;
					else
					{
						cnt = -1;
						break;
					}
				}
				else
				{
					cnt = -1;
					break;
				}
			}
			if (cnt >= 0)
				ans++;

		}

		for (int j = 0; j < n; j++)
		{
			cnt = 1;
			for (int i = 1; i < n; i++)
			{
				if (road[i][j] == road[i - 1][j])
					cnt++;
				else if (road[i][j] - road[i - 1][j] == 1)
				{
					if (cnt >= x)
						cnt = 1;
					else
					{
						cnt = -1;
						break;
					}
				}
				else if (road[i - 1][j] - road[i][j] == 1)
				{
					if (cnt >= 0)
						cnt = 1 - x;
					else
					{
						cnt = -1;
						break;
					}
				}
				else
				{
					cnt = -1;
					break;
				}
			}
			if (cnt >= 0)
				ans++;
		}

		cout << "#" << tc << " " << ans << endl;

	}
	return 0;
}