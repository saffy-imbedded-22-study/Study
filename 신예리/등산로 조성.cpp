#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int MAP[9][9];
int visited[9][9];
int N, K;

struct yx {
	int y;
	int x;
};

vector<yx>v;

int ydir[4] = {-1,1,0,0};
int xdir[4] = {0,0,-1,1};

int ans;

void dfs(int y, int x, int cnt, int cutnum) {

	if (ans < cnt) {
		ans = cnt;
	}

	for (int i = 0; i < 4; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];


		if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
		if (visited[ny][nx] == 1)continue;

		if (MAP[ny][nx] >= MAP[y][x]) {
			if (cutnum == 0) {

				for (int cut = 1; cut <= K; cut++) {
					int orheight = MAP[ny][nx];
					int cutheight = MAP[ny][nx] - cut;

					if (cutheight < MAP[y][x]) {
						MAP[ny][nx] = cutheight;
						visited[ny][nx] = 1;
						dfs(ny, nx, cnt+ 1, cutnum + 1);
						MAP[ny][nx] = orheight;
						visited[ny][nx] = 0;
					}
				}

			}
		}
		else {
			visited[ny][nx] = 1;
			dfs(ny, nx, cnt + 1, cutnum);
			visited[ny][nx] = 0;
		}

	}

}



int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {

		memset(MAP, 0, sizeof(MAP));
		memset(visited, 0, sizeof(visited));
		ans = -21e8;

		cin >> N >> K;

		int maxtop = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
				if (maxtop < MAP[i][j]) {
					maxtop = MAP[i][j];
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j] == maxtop && visited[i][j] != 1) {
					visited[i][j] = 1;
					dfs(i, j, 1, 0);
					visited[i][j] = 0;
				}
			}
		}

		cout <<"#"<<te <<" "<< ans<<endl;

	}
	return 0;
}