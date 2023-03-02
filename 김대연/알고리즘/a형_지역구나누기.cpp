#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int N;	// 마을 수
int Map[8][8];	// 연결 맵
int SumAll;	// 모든 사람 수 합
int People[8];	// 사람 수
int Ans;		// 최소 차이 값
int parent[8];	// 부모 정보
int Line;		// 연결 선 수

struct node {
	int from;
	int to;
};
vector<node> line;

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

int solve(vector<node>& v1, vector<node>& v2) {
	for (int i = 0;i < N;i++) {
		parent[i] = i;
	}
	int DAT1[8] = { 0 };
	int DAT2[8] = { 0 };

	for (int i = 0;i < v1.size();i++) {
		int from = v1[i].from;
		int to = v1[i].to;
		Union(from, to);
		DAT1[from] = 1;
		DAT1[to] = 1;
	}

	for (int i = 0;i < v2.size();i++) {
		int from = v2[i].from;
		int to = v2[i].to;
		if (DAT1[from] == 1 || DAT1[to] == 1)continue;
		Union(from, to);
		DAT2[from] = 1;
		DAT2[to] = 1;
	}

	for (int i = 0;i < 8;i++) {
		if (DAT1[i] == 1)continue;
		for (int j = i+1;j < 8;j++) {
			if (DAT1[j] == 1)continue;
			if (Find(i) != Find(j))return -1;
		}
	}

	int sum1 = 0;
	for (int i = 0;i < 8;i++) {
		if (DAT1[i] == 1) {
			sum1 += People[i];
		}
	}

	int sum2 = 0;
	for (int i = 0;i < 8;i++) {
		if (DAT1[i] == 0) {
			sum2 += People[i];
		}
	}

	return abs(sum1 - sum2);
}



vector<node> v;
vector<node> v2;

void dfs(int level) {
	if (level == Line) {
		// 계산.
		int nowans = solve(v, v2);
		if (nowans != -1) {
			Ans = min(nowans, Ans);
		}
		return;
	}

	v.push_back(line[level]);

	dfs(level + 1);
	
	v.pop_back();

	v2.push_back(line[level]);

	dfs(level + 1);

	v2.pop_back();

}



int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		//reset
		memset(Map, 0, sizeof(Map));
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
		for (int i = 0;i < N;i++) {
			for (int j = i;j < N;j++) {
				if (Map[i][j] == 1) {
					line.push_back({ i,j });
				}
			}
		}
		Line = line.size();

		//solve
		dfs(0);



		//output
		cout << "#" << tc << ' ' << Ans << '\n';
	}



	return 0;
}