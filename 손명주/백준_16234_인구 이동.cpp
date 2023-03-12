//한글
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N, L, R; //크기, 차이 하한, 상한
int pop[50][50];
int visited[50][50];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
int flag;
struct node {
	int y;
	int x;
};

void run(int y, int x) {
	if (visited[y][x] == 1) return;
	queue<node> q; //탐색용
	vector<node> v; //y, x랑 연합
	q.push({ y,x });
	v.push_back({ y,x });
	visited[y][x] = 1;
	int sum = pop[y][x];
	int cnt = 1;
	while (!q.empty()) {
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited[ny][nx] == 1) continue;
			int diff = abs(pop[now.y][now.x] - pop[ny][nx]);
			if (diff<L || diff>R) continue; //L이 1이상이라 같으면 연합안됨
			visited[ny][nx] = 1;
			q.push({ ny,nx });
			v.push_back({ ny,nx });
			cnt++;
			sum += pop[ny][nx];
		}
	}
	//연합있을 때 flag(하루기준) 증가, 인구수 변화
	if (cnt != 1) {
		flag++;
		for (int i = 0; i < v.size(); i++) {
			pop[v[i].y][v[i].x] = sum / cnt;
		}
	}
}
void move() {
	//하루마다 visited 초기화
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			run(i, j);
		}
	}
}
int main() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> pop[i][j];
		}
	}
	int day = 0;
	while (true) {
		flag = 0;
		move();
		if (flag == 0) break;
		day++;
	}
	cout << day;
	return 0;
}