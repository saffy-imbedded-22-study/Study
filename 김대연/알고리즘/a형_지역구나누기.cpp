#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int N;	// 마을 수
int Map[8][8];	// 연결 맵
int SumAll;	// 모든 사람 수 합
int People[8];	// 사람 수
bool visited[8];	// 방문 체크
int Ans;		// 최소 차이 값
int parent[8];	// 부모 정보

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




void dfs(int now, int level, int sum) {
	vector<int> v;

	for (int i = 0;i < N;i++) {
		if (visited[i] == 0)
			v.push_back(i);
	}
	for (int i = 0;i < v.size();i++) {
		for (int j = i + 1;j < v.size();j++) {
			if (Map[v[i]][v[j]] == 1) {
				Union(v[i], v[j]);
			}
		}
	}

	bool flag = true;
	for (int i = 0;i < v.size();i++) {
		for (int j = i + 1;j < v.size();j++) {
			if (Find(v[i]) != Find(v[j])) {
				flag = false;
				break;
			}
		}
		if (!flag)break;
	}
	if(flag)	Ans = min(Ans, abs(SumAll - sum*2));
	
	for (int i = 0;i < v.size();i++) {
		cout << v[i]+1 << ' ';
	}cout << "flag" << flag << ' ' << abs(SumAll - sum * 2) << '\n';

	for (int i = 0;i < N;i++) {
		parent[i] = i;
	}

	if (level == N-1) {
		return;
	}

	for (int i = 0;i < N;i++) {
		if (Map[now][i] == 0)continue;
		if (visited[i])continue;
		visited[i] = 1;

		dfs(i, level + 1, sum + People[i]);

		visited[i] = 0;
	}



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
		

		//solve
		/*for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				if (Map[i][j] != 0) {
					Union(i, j);
				}
			}
		}*/
		

		visited[0] = 1;
		dfs(0, 0, People[0]);


		//output
		cout << "#" << tc << ' ' << Ans << '\n';
	}



	return 0;
}