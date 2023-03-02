#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Pinball {
	int y, x, dir, score;
};
struct Wormhole {
	int y, x;
};
int MAP[110][110];
int N;
int maxScore;
vector<Wormhole>v[11];
int ydir[] = { -1, 1, 0,0 };
int xdir[] = { 0,0,-1,1 };


void reset() {
	maxScore = -21e8;
	for (int x = 0; x < 110; x++) {
		for (int y = 0; y < 110; y++) {
			MAP[y][x] = 5;
		}
	}
	for (int i = 6; i <= 10; i++) {
		while (!v[i].empty()) {
			v[i].pop_back();
		}
	}
}
void input() {
	cin >> N;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> MAP[y][x];
			//웜홀 좌표 저장
			if (6 <= MAP[y][x] && MAP[y][x] <= 10)
				v[MAP[y][x]].push_back({ y,x });
		}
	}
}
//바뀐 방향을 return
int meetBlock(int dir, int block) {
	int ndir;
	int flag = 0;//1:경사면, 0:수직면 
	//dir: 0 1 2 3
	//		 상하좌우
	if (block == 1) {
		if (dir == 1) { //하 >>우 
			flag = 1;
			ndir = 3;
		}
		else if (dir == 2) { // 좌 >>상
			flag = 1;
			ndir = 0;
		}
	}
	else if (block == 2) {
		if (dir == 0) {//상 >> 우
			flag = 1;
			ndir = 3;
		}
		else if (dir == 2) {//좌 >> 하
			flag = 1;
			ndir = 1;
		}
	}
	else if (block == 3) {
		if(dir == 0){//상>>좌
			flag = 1;
			ndir = 2;
		}
		else if(dir == 3){//우>>하
			flag = 1;
			ndir = 1;
		}
	}
	else if(block ==4) {
		if (dir == 1) {//하 >> 좌
			flag = 1;
			ndir = 2;
		}
		else if(dir == 3){//우 >> 상
			flag = 1;
			ndir = 0;
		}
	}
	//수직면이면 방향반대
	if (flag == 0) {
		if (dir % 2 == 0) ndir = dir + 1;
		else ndir = dir - 1;
	}

	return ndir;

}

void gotoWormhole(int idx, int* p1, int* p2) {
	if (v[idx][0].y == *p1 && v[idx][0].x == *p2) {
		*p1 = v[idx][1].y;
		*p2 = v[idx][1].x;
	}
	else {
		*p1 = v[idx][0].y;
		*p2 = v[idx][0].x;
	}
}

//반환: 해당 위치, 시작방향에서 얻은 점수
int solv(int y, int x, int dir) {
	Pinball now = { y,x,dir,0 };

	while (true) {

		//#1. 이동한 맵이 0인경우 : 좌표만 갱신
		int ny = now.y + ydir[now.dir];
		int nx = now.x + xdir[now.dir];
		int ndir = now.dir;
		int nscore = now.score;
		//#2. 종료조건 : 블랙홀 만나는 경우, score반환
		if (MAP[ny][nx] == -1) {
			return now.score;
		}
		//#3.벽만나는 경우 :  방향 반대 + score증가
		if (MAP[ny][nx] == 5) {
			if (now.dir % 2 == 0) ndir =now.dir+ 1;
			else ndir =now.dir- 1;
			nscore++;
		}
		//#4.블록만남: 바뀐 방향 리턴받음+ 스코어 증가
		if (1 <= MAP[ny][nx]&& MAP[ny][nx] <= 4) {
			ndir = meetBlock(now.dir, MAP[ny][nx]);
			nscore++;
		}
		//#5.웜홀만나는 경우
		if (6 <= MAP[ny][nx] && MAP[ny][nx] <= 10) {
			gotoWormhole(MAP[ny][nx], &ny,&nx);
		}
		//다음좌표로 이동시키기
		now = { ny,nx,ndir,nscore };
	}

}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (MAP[y][x] != 0) continue;

				MAP[y][x] = -1;//시작위치 블랙홀 취급
				for (int i = 0; i < 4; i++) {
					int tmp =solv(y, x, i);
					maxScore = max(maxScore, tmp);
				}
				MAP[y][x] = 0;//복구
			}
		}
		cout << "#" << tc << " " << maxScore << endl;
	}

	return 0;
}