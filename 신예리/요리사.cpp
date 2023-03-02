#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int table[17][17];
int visited[17];
int N;
int ans;

void dfs(int now, int ja) {

	if (now == N / 2) {
		int Asum = 0;
		int Bsum = 0;
		vector<int>Avect;
		vector<int>Bvect;
		for (int i = 1; i <= N; i++) {
			if (visited[i] == 1) {
				Avect.push_back(i);
			}
			else {
				Bvect.push_back(i);
			}
		}

		for (int i = 0; i < Avect.size() - 1; i++) {
			for (int j = i + 1; j < Avect.size(); j++) {
				Asum += table[Avect[i]][Avect[j]] + table[Avect[j]][Avect[i]];
				Bsum += table[Bvect[i]][Bvect[j]] + table[Bvect[j]][Bvect[i]];
			}
		}

		if (abs(Asum - Bsum) < ans) {
			ans = abs(Asum - Bsum);
		}

		return;
	}

	for (int i = ja; i <= N; i++) {

		if (visited[i] == 1)continue;
		visited[i] = 1;
		dfs(now + 1, i);
		visited[i] = 0;

	}


}

int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {
		memset(table, 0, sizeof(table));
		memset(visited, 0, sizeof(visited));
		ans = 21e8;
		cin >> N;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> table[i][j];
			}
		}


		dfs(0, 1);

		cout << "#" << te << " " << ans << endl;

	}
	return 0;
}