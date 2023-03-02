/*
중요한건 최소 전선 길이가 아닌 최대 연결 코어!!!

1. 코어 위치 저장
2. dfs 이용해서 각 코어에 대해 4방향 + 연결 안할때에 대한 경우 조합
3. 우선순위 : 코어 저장 갯수 > 최소 전선 길이

*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

int N;
int Map[12][12];
int cntsum;
int ans;

struct node {
	int y, x;
};

node core[12];

int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

bool checkcore(node now, int dir) {	// 그 방향으로 설치 가능한지 확인
	int y = now.y;
	int x = now.x;

	if (dir == 0) {
		for (int i = 0;i < y;i++) {
			if (Map[i][x] == 1)return false;
		}
	}
	else if (dir == 1) {
		for (int i = y + 1;i < N;i++) {
			if (Map[i][x] == 1)return false;
		}
	}
	else if (dir == 2) {
		for (int j = 0;j < x;j++) {
			if (Map[y][j] == 1)return false;
		}
	}
	else if (dir == 3) {
		for (int j = x + 1;j < N;j++) {
			if (Map[y][j] == 1)return false;
		}
	}
}

int checkline(node now, int dir) {	// 전선 설치 후 길이 리턴
	int y = now.y;
	int x = now.x;

	int cnt = 0;
	if (dir == 0) {
		for (int i = 0;i < y;i++) {
			Map[i][x] = 1;
			cnt++;
		}
	}
	else if (dir == 1) {
		for (int i = y + 1;i < N;i++) {
			Map[i][x] = 1;
			cnt++;
		}
	}
	else if (dir == 2) {
		for (int j = 0;j < x;j++) {
			Map[y][j] = 1;
			cnt++;
		}
	}
	else if (dir == 3) {
		for (int j = x + 1;j < N;j++) {
			Map[y][j] = 1;
			cnt++;
		}
	}
	return cnt;
}

void deleteline(node now, int dir) {	// 설치했던 전선 취소
	int y = now.y;
	int x = now.x;

	if (dir == 0) {
		for (int i = 0;i < y;i++) {
			Map[i][x] = 0;
		}
	}
	else if (dir == 1) {
		for (int i = y + 1;i < N;i++) {
			Map[i][x] = 0;
		}
	}
	else if (dir == 2) {
		for (int j = 0;j < x;j++) {
			Map[y][j] = 0;
		}
	}
	else if (dir == 3) {
		for (int j = x + 1;j < N;j++) {
			Map[y][j] = 0;
		}
	}
}

int corecnt = 0;
int coremax = 0;

void dfs(int level) {
	if (level == N) {
		if (coremax < corecnt) {	// 코어 갯수가 더 크면 정답 갱신
			coremax = corecnt;
			ans = cntsum;	
		}
		else if (coremax == corecnt) {	// 코어 갯수 같으면 더 작은 값 저장
			ans = min(ans, cntsum);
		}
		return;
	}

	int y = core[level].y;
	int x = core[level].x;

	if (y == 0 || y == N - 1 || x == 0 || x == N - 1) {	// 테두리에 있을 경우 길이 0
		corecnt++;
		dfs(level + 1);
		corecnt--;
	}
	else {
		for (int i = 0;i < 4;i++) {	// 4 방향 dfs
			if (checkcore({ y,x }, i)) {
				int cnt = checkline({ y,x }, i);
				cntsum += cnt;
				corecnt++;
				dfs(level + 1);
				corecnt--;
				cntsum -= cnt;
				deleteline({ y,x }, i);
			}

		}
		dfs(level + 1);	// 설치 안하고 다음으로
	}


}


int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		//reset
		memset(Map, 0, sizeof(Map));
		memset(core, 0, sizeof(core));
		cntsum = 0;
		ans = 21e8;
		corecnt = 0;
		coremax = 0;


		//input
		cin >> N;
		int idx = 0;

		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				cin >> Map[i][j];
				if (Map[i][j] == 1) {
					core[idx++] = { i,j };
				}
			}
		}


		//solve
		dfs(0);


		//output
		cout << "#" << tc << ' ' << ans << '\n';
	}



	return 0;
}