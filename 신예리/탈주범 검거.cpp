#include <iostream>
#include <queue>
#include<cstring>
using namespace std;

int N, M, R, C, L;//N:ºº∑Œ M:∞°∑Œ R:∏«»¶∂—≤± y, C:∏«»¶∂—≤± x, L: ≈ª√‚»ƒ º“ø‰Ω√∞£
int MAP[51][51];
int visited[51][51];
int cnt;

struct yx {
	int y;
	int x;
};

int ydir[4] = { -1,0,0,1 }; // ªÛ¡¬øÏ«œ
int xdir[4] = { 0,-1,1,0 };

int yxdir[7][4] = {
	{1,1,1,1},
	{1,0,0,1},
	{0,1,1,0},
	{1,0,1,0},
	{0,0,1,1},
	{0,1,0,1},
	{1,1,0,0}
};

void bfs(int y, int x) {

	queue<yx>q;
	q.push({ y,x });
	visited[y][x] = 1;

	while (!q.empty()) {
		yx now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			if (yxdir[MAP[now.y][now.x] - 1][i] == 1) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
				if (MAP[ny][nx] == 0)continue;
				if (visited[ny][nx] != 0)continue;
				

				if (yxdir[MAP[ny][nx] - 1][3-i] == 1) {
					visited[ny][nx] = visited[now.y][now.x] + 1;
					q.push({ ny,nx });
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j] > 0 && visited[i][j] <= L) {
				cnt++;
			}
		}
	}
}

int main() {

	int test;
	cin >> test;
	for (int te = 1; te <= test; te++) {
		memset(MAP, 0, sizeof(MAP));
		memset(visited, 0, sizeof(visited));

		cnt = 0;
		cin >> N >> M >> R >> C >> L;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> MAP[i][j];
			}
		}

		bfs(R, C);

		cout << "#"<< te << " "<<cnt << endl;
	}

	return 0;
}
