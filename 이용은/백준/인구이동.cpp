#include <iostream>
#include <unordered_map>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
struct Node {
	int y, x;
};
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
int N, L, R;
int MAP[50][50];
int day;
int flag;
int connected[50][50];
vector<Node>v[1300];

void input() {
	cin >> N >> L >> R;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
		}
	}
}

void flood() {
	queue<Node>q;
	int Union = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (connected[y][x] != 0) continue;
			q.push({ y,x });//연합이 없는 모든 점에 한번씩 확인하기
			
			while (!q.empty()) {
				Node now = q.front();
				q.pop();
				for (int i = 0; i < 4; i++) {
					int ny = now.y + ydir[i];
					int nx = now.x + xdir[i];
					if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;
					if (connected[ny][nx] != 0)continue;
					int diff = MAP[now.y][now.x] - MAP[ny][nx];
					if (diff < 0) diff = -diff;
					if (L <= diff && diff <= R) {
						flag = 1;
						if (connected[now.y][now.x] == 0) {
							Union++;
							connected[now.y][now.x] = Union;
							connected[ny][nx] = Union;
						}
						else {
							connected[ny][nx] = connected[now.y][now.x];
						}
						q.push({ ny,nx });
					}
				}
			}
		}
	}
	//후처리
	unordered_map<int, int>um;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (connected[y][x] != 0) {
				um[connected[y][x]] += MAP[y][x];
				v[connected[y][x]].push_back({y,x});
			}
		}
	}
	for (int i = 1; i <= Union; i++) {
		int size = v[i].size();
		for (int j = 0; j < size; j++) {
			Node now = v[i][j];
			MAP[now.y][now.x] = um[i] / size;
		}
		v[i] = vector<Node>();
	}
	memset(connected, 0, sizeof(connected));
}

int sol() {
	while (true) {
		flag = 0;
		flood();
		if (flag == 0) break;
		day++;
	}
	return day;
}

int main() {
	input();
	cout << sol();
	return 0;
}
