#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int diry[4] = { -1,1,0,0 };	// 상 하 좌 우
int dirx[4] = { 0,0,-1,1 };

struct node {	//좌표, 방향
	int y;
	int x;
	int dir;

	bool operator == (node next) const {
		return (y == next.y) && (x == next.x);
	}
};
int N;				// 한 변의 길이
int Map[100][100];	// 맵
node start;			// 시작 위치
int Max;			// 최대값 저장
vector<node> worm[5];	// 웜홀 정보 저장
int cnt;			// 카운트

node block(node now) {	// 블록 만났을 때 다음 위치 반환
	int block_num = Map[now.y][now.x];
	node next;
	bool flag = false;

	if (now.dir == 0) {	// 현재 방향 : 상
		if (block_num == 2) {
			next.dir = 3;	// 우
		}
		else if (block_num == 3) {
			next.dir = 2;	// 좌
		}
		else {
			next = start;
			flag = true;
		}

	}
	else if (now.dir == 1) {	// 현재 방향 : 하
		if (block_num == 1) {
			next.dir = 3;	// 우
		}
		else if (block_num == 4) {
			next.dir = 2;	// 좌
		}
		else {
			next = start;	// 상
			flag = true;

		}
	}
	else if (now.dir == 2) {	// 현재 방향 : 좌
		if (block_num == 1) {
			next.dir = 0;	// 상
		}
		else if (block_num == 2) {
			next.dir = 1;	// 하
		}
		else {
			next = start;// 우
			flag = true;

		}
	}
	else if (now.dir == 3) {	// 현재 방향 : 우
		if (block_num == 3) {
			next.dir = 1;	// 하
		}
		else if (block_num == 4) {
			next.dir = 0;	// 상
		}
		else {
			next = start;	// 좌
			flag = true;

		}
	}

	if (!flag) {
		next.y = now.y + diry[next.dir];
		next.x = now.x + dirx[next.dir];
	}

	return next;
}




int main() {
	int T;
	cin >> T;

	for (int t = 1;t <= T;t++) {
		//reset
		memset(Map, 0, sizeof(Map));
		Max = 0;
		for (int i = 0;i < 5;i++) {
			worm[i].clear();
		}

		//input
		cin >> N;
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				cin >> Map[i][j];
				if (Map[i][j] > 5 && Map[i][j] < 11) {
					worm[Map[i][j] - 6].push_back({ i,j });
				}
			}
		}

		//solve
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				if (Map[i][j] != 0)continue; // 빈칸일때만 시작가능
				start = { i,j };
				for (int dir = 0;dir < 4;dir++) {	// 4방향 진행
					int dy = i + diry[dir];
					int dx = j + dirx[dir];
					//if (dy >= N || dy < 0 || dx >= N || dx < 0) continue;	// 범위 벗어나면 스킵
					cnt = 0; // cnt 초기화
					node next = { dy,dx,dir };	// 다음 위치에서 시작 (처음 값 확인할때 때문)
					//cout << next.x << ' ' << next.y << ' ' << dir << '\n' << '\n';

					while (1) {
						//cout << next.x << ' ' << next.y << '\n';
						if (next == start) {	// 현재위치로 돌아왔을때
							Max = max(cnt, Max);
							break;
						}

						if (next.y >= N || next.y < 0 || next.x >= N || next.x < 0) {	// 경계선 만날때
							cnt = cnt * 2 + 1;
							Max = max(cnt, Max);
							break;
						}
						else if (Map[next.y][next.x] == -1) {	// 블랙홀 만날때
							Max = max(cnt, Max);
							break;
						}
						else if (Map[next.y][next.x] >= 1 && Map[next.y][next.x] <= 5) {	// 블록 만날때
							next = block(next);
							if (next == start) {
								cnt = cnt * 2 + 1;
								Max = max(cnt, Max);
								break;
							}
							else {
								cnt++;
							}
							continue;
						}
						else if (Map[next.y][next.x] > 5 && Map[next.y][next.x] < 11) {	// 웜홀 만날때
							int wormnum = Map[next.y][next.x] - 6;

							for (int i = 0;i < 2;i++) {	// 값 둘 중 현재 위치와 다른값 찾기
								if (worm[wormnum][i] == next) {	// 현재 위치랑 동일하면 스킵
									continue;
								}
								next.y = worm[wormnum][i].y + diry[next.dir];
								next.x = worm[wormnum][i].x + dirx[next.dir];
								break;
							}
							continue;
						}
						else {	// 빈칸 일때
							next.y = next.y + diry[next.dir];
							next.x = next.x + dirx[next.dir];
							continue;
						}

					}


				}
			}
		}


		//output
		cout << "#" << t << ' ' << Max << '\n';
	}






	return 0;
}