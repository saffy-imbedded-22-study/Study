#include <iostream>
#include <vector> 
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

int T, N;

int opr[4] = { 0 };

int number[13] = { 0 };

int ans_min;
int ans_max;

void dfs(int level, int result)
{
	if (level == N)
	{
		ans_min = min(ans_min, result);
		ans_max = max(ans_max, result);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (opr[i] > 0)
		{
			opr[i] --;
			if (i == 0)
				dfs(level + 1, result + number[level]);
			else if (i == 1)
				dfs(level + 1, result - number[level]);
			else if (i == 2)
				dfs(level + 1, result * number[level]);
			else if (i == 3)
				dfs(level + 1, result / number[level]);
			opr[i]++;
		}
	}
}

int main()
{
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		ans_min = 21e8;
		ans_max = -21e8;
		cin >> N;

		for (int i = 0; i < 4; i++)
		{
			cin >> opr[i];
		}

		for (int i = 0; i < N; i++)
			cin >> number[i];

		dfs(1, number[0]);

		cout << "#" << tc << " " << ans_max - ans_min << endl;
	}
	return 0;
}