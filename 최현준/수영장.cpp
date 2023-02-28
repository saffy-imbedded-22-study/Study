#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

#include <algorithm>
using namespace std;


int dy, mn, three_mn, yr;
int ans;
int schedule[13] = { 0 };

void dfs(int mon, int result)
{
	if (mon > 12)
	{
		if (result < ans)
			ans = result;
		return;
	}

	if (schedule[mon] > 0)
	{
		dfs(mon + 1, result + dy * schedule[mon]);
		dfs(mon + 1, result + mn);
		dfs(mon + 3, result + three_mn);
	}
	else
		dfs(mon + 1, result);

}

int main()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> dy >> mn >> three_mn >> yr;

		ans = yr;

		for (int i = 1; i <= 12; i++)
		{
			cin >> schedule[i];
		}

		dfs(1, 0);

		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}