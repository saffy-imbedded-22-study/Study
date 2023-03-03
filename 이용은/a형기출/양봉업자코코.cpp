#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int H, W;
int visited[20][20];
int MAP[20][20];
int maxF = 0;
int ydir0[] = { -1, 1, 0, 0 ,-1,-1 };
int ydir1[] = { -1,1,0,0,1,1 };
int xdir[] = { 0,0, -1, 1 ,-1,1 };



void DFS(int nowY, int nowX, int cnt, int re) {
	//종료
	if (cnt == 4) {
		//최댓값 갱신
		maxF = max(maxF, re);
		return;
	}

	for (int i = 0; i < 6; i++) {
		int ny, nx;
		nx = nowX + xdir[i];
		if (nowX % 2 == 0) {
			ny = nowY + ydir0[i];
		}
		else {
			ny = nowY + ydir1[i];
		}
		

		if (ny >= H || ny < 0 || nx >= W || nx < 0) continue;
		if (visited[ny][nx] == 1) continue;


		if (visited[ny][nx] == 2) {//시작위치에 다시 방문한 경우
			//카운트 안올리고 다음 위치로 이동시키기!
				DFS(ny, nx, cnt, re);
				continue;
		}


		visited[ny][nx] = 1;
		DFS(ny, nx, cnt + 1, re + MAP[ny][nx]);
		visited[ny][nx] = 0;


	}


}

int main() {

	cin >> H >> W;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			cin >> MAP[y][x];
		}
	}

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			visited[y][x] = 2;// 시작위치임을 명시해 주기
			DFS(y, x, 1, MAP[y][x]);
			visited[y][x] = 0;
		}
	}

	cout << maxF;


	return 0;
}