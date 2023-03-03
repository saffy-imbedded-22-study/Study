#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int N;	// 맵 크기
int K;	// 공사 가능 깊이
int Map[8][8];	// 맵

int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

struct node {
	int y, x;
};

int best_cnt = 0;	// 최대 이동수
bool visited[8][8];

void dfs(node now, int now_height, int cnt, bool cut) {	// 현재위치, 현재높이, 이동수, 컷 실행여부
	best_cnt = max(cnt, best_cnt);
	
	for (int i = 0;i < 4;i++) {
		int dy = now.y + diry[i];
		int dx = now.x + dirx[i];
		if (dy >= N || dy < 0 || dx >= N || dx < 0)continue;	// 경계면 스킵
		if (Map[dy][dx] >= now_height) continue;				// 높이 같거나 높으면 스킵
		if (visited[dy][dx])continue;							// 방문 했었으면 스킵

		visited[dy][dx] = 1;

		dfs({ dy,dx }, Map[dy][dx], cnt + 1, cut);

		visited[dy][dx] = 0;

	}

	if (cut) {					// 진행 도중 높이 잘랐으면 실행 x
		return;
	}

	for (int k = 1;k <= K;k++) {		// 1~k만큼 높이 잘라보기
		for (int i = 0;i < 4;i++) {
			int dy = now.y + diry[i];
			int dx = now.x + dirx[i];
			if (dy >= N || dy < 0 || dx >= N || dx < 0)continue;	// 위와 동일
			if (Map[dy][dx] - k >= now_height) continue;
			if (visited[dy][dx])continue;

			visited[dy][dx] = 1;

			dfs({ dy,dx }, Map[dy][dx] - k, cnt + 1, 1);		// 현재 높이를 줄여서 dfs

			visited[dy][dx] = 0;

		}
	}
	

}



int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(Map, 0, sizeof(Map));
		best_cnt = 0;

		// input
		cin >> N >> K;
		int Max_height = 0;
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				cin >> Map[i][j];
				Max_height = max(Max_height, Map[i][j]);	// 최대높이 찾기
			}
		}

		// solve
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				if (Map[i][j] == Max_height) {	// 최대높이에서 시작
					visited[i][j] = 1;			// 시작 위치 1 중요 !!! 여기서 틀렸었음.
					dfs({ i,j }, Max_height, 1, 0);
					visited[i][j] = 0;

				}
			}
		}

		

		// output
		cout << "#" << tc << ' ' << best_cnt << '\n';
	}



	return 0;
}