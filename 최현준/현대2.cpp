#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector> 
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;
int n;

string s[101];

int cal(char a, char b)
{

	if (a > b)
		return a - b;
	if (a < b)
		return	a + 26 - b;
	return 0;

}
int main()
{
	cin >> n;

	string target;
	cin >> target;

	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}


	int key = 21e8;
	string ans;

	for (int i = 0; i < n; i++)
	{

		int flag = 0;
		if (s[i].length() != target.length()) continue;
		int standard = cal(s[i][0], target[0]);
		for (int j = 1; j < s[i].size(); j++)
		{
			if (standard != cal(s[i][j], target[j]))
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			key = min(key, standard);
			if (key == standard)
				ans = s[i];
		}
	}

	cout << ans;

	return 0;
}