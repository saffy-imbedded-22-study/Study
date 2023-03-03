/*
1. 마을 기준으로 dfs 이용해서 두 팀으로 나누기.
2. 각 팀마다 연결정보를 이용해 union 해주기.
3. 팀원들의 부모가 다 같은지 find 이용해서 확인.
4. 다 같을 경우 각 팀의 합 구해서 차이 최소 찾기.

*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int N;			// 마을 수
int Map[8][8];	// 연결 맵
int SumAll;	// 모든 사람 수 합
int People[8];	// 사람 수
int Ans;		// 최소 차이 값
int parent[8];	// 부모 정보
int team[8];	// 그룹 정보



int Find(int now) {
	if (now == parent[now])
		return now;

	return parent[now] = Find(parent[now]);
}

void Union(int a, int  b) {
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb)return;

	parent[pb] = pa;

}

int solve() {

	for (int i = 0;i < N;i++) {
		parent[i] = i;
	}

	for (int i = 0;i < N;i++) {
		if (team[i] == 0)continue;
		for (int j = i + 1;j < N;j++) {
			if (team[j] == 0)continue;
			if (Map[i][j] == 1) {
				Union(i, j);
			}
		}
	}

	for (int i = 0;i < N;i++) {
		if (team[i] == 1)continue;
		for (int j = i + 1;j < N;j++) {
			if (team[j] == 1)continue;
			if (Map[i][j] == 1) {
				Union(i, j);
			}
		}
	}

	for (int i = 0;i < N;i++) {
		if (team[i] == 0)continue;
		for (int j = i + 1;j < N;j++) {
			if (team[j] == 0)continue;
			if (Find(i) != Find(j))return -1;
		}
	}

	for (int i = 0;i < N;i++) {
		if (team[i] == 1)continue;
		for (int j = i + 1;j < N;j++) {
			if (team[j] == 1)continue;
			if (Find(i) != Find(j))return -1;
		}
	}
	int sum1 = 0;
	for (int i = 0;i < N;i++) {
		if (team[i] == 0)continue;
		sum1 += People[i];
	}

	return abs(sum1 * 2 - SumAll);

}

void dfs(int level) {
	if (level == N) {
		int sol = solve();
		if (sol != -1) {
			Ans = min(Ans, sol);
		}
		return;
	}

	dfs(level + 1);
	team[level] = 1;
	dfs(level + 1);
	team[level] = 0;
}



int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		//reset
		memset(Map, 0, sizeof(Map));
		memset(team, 0, sizeof(team));
		SumAll = 0;
		Ans = 21e8;

		//input
		cin >> N;
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				cin >> Map[i][j];
			}
		}
		for (int i = 0;i < N;i++) {
			cin >> People[i];
			SumAll += People[i];
			parent[i] = i;
		}
	


		//solve

		dfs(0);


		//output
		cout << "#" << tc << ' ' << Ans << '\n';
	}



	return 0;
}