#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int N;
int map[20][20];
int visit[20][20];
int dir[4][2] = { -1,0,0,-1,0,1,1,0 }; //순서 상 좌 우 하 만으로 안돼서 pq로 바궜음
int t; //시간
int Y, X, ATE, SIZE = 2; //상어 상태

struct node {
	int y;
	int x;
	int d; //상어로부터 거리
};
struct cmp {
	bool operator()(node left, node right) {
		if (left.d > right.d) return true;
		if (left.d < right.d) return false;
		if (left.y > right.y) return true;
		if (left.y < right.y) return false;
		if (left.x > right.x) return true;
		if (left.x < right.x) return false;
		return false;
	}
};
void move() {
	priority_queue<node, vector<node>,cmp> q;
	q.push({ Y,X,0 });
	visit[Y][X] = 1;

	while (!q.empty()) {
		node now = q.top();
		q.pop();

		//먹을 수 있는 경우
		if (map[now.y][now.x] > 0 && map[now.y][now.x] < SIZE) {
			map[now.y][now.x] = 0;
			ATE++;
			t += now.d;
			Y = now.y; X = now.x;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visit[ny][nx] >= 1) continue;
			if (map[ny][nx] > SIZE) continue;
			visit[ny][nx] = 1;
			q.push({ ny,nx,now.d + 1 });
		}
	}
}
void run() {
	while (true) {
		int now = t;
		//한번 움직일 때마다 visit 리셋
		memset(visit, 0, sizeof(visit));
		move();
		if (ATE == SIZE) {
			SIZE++;
			ATE = 0;
		}
		//시간이 안지남 == 먹을게 없음
		if (t == now) break;
	}
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				Y = i;
				X = j;
				map[i][j] = 0;
			}
		}
	}
	run();
	cout << t;
	return 0;
}