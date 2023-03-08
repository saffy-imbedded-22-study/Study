#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

struct yx {
	int y;
	int x;
};

int MAP[51][51];
int N, M;

vector<yx>home;
vector<yx>store;
vector<yx>selectstore;

int mindist;
int visited[14];

void minresult() {

	int ans = 0;
	for (int i = 0; i < home.size(); i++) {
		int result = 21e8;
		for (int j = 0; j < selectstore.size(); j++) {
			int dist = abs(home[i].y - selectstore[j].y) + abs(home[i].x - selectstore[j].x);
			result = min(result, dist);
		}
		ans += result;
	}
	mindist = min(mindist, ans);

}



void dfs(int now, int ja) {

	if (now == M) {
		minresult();
		return;
	}

	for (int i = ja; i < store.size(); i++) {

		if (visited[i] == 1)continue;

		selectstore.push_back({ store[i].y,store[i].x });
		visited[i] = 1;
		dfs(now + 1, i);
		selectstore.pop_back();
		visited[i] = 0;

	}

}



int main() {

	cin >> N >> M;

	mindist = 21e8;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				home.push_back({ i,j });
			}
			else if (MAP[i][j] == 2) {
				store.push_back({ i,j });
			}
		}
	}

	dfs(0, 0);

	cout << mindist << endl;

	return 0;
}