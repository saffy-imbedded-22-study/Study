#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

int N;	// 세로
int M;	// 가로
int R;	// 시작 세로
int C;	// 시작 가로
int L;	// 시간
int Map[50][50];	//맵

int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

vector<int> pipe[8];		

void makedir() {
	for (int i = 1;i < 8;i++) {	
		// 상
		if (i == 1 || i == 2 || i == 4 || i == 7) {
			pipe[i].push_back(0);
		}
		// 하
		if (i == 1 || i == 2 || i == 5 || i == 6) {
			pipe[i].push_back(1);
		}
		// 좌
		if (i == 1 || i == 3 || i == 6 || i == 7) {
			pipe[i].push_back(2);
		}
		// 우
		if (i == 1 || i == 3 || i == 4 || i == 5) {
			pipe[i].push_back(3);
		}
	}
}


int visited[50][50];
int cnt = 0;

bool check_move(int nowdir, int next) {
	if (next == 0) {
		return false;
	}

	if (nowdir == 0) {
		if (next == 1 || next == 2 || next == 5 || next == 6)
			return true;
		else return false;
	}
	else if (nowdir == 1) {
		if (next == 1 || next == 2 || next == 4 || next == 7)
			return true;
		else return false;
	}
	else if (nowdir == 2) {
		if (next == 1 || next == 3 || next == 4 || next == 5)
			return true;
		else return false;
	}
	else if (nowdir == 3) {
		if (next == 1 || next == 3 || next == 6 || next == 7)
			return true;
		else return false;
	}
}


struct node {
	int y, x;
};

void bfs() {
	queue<node> q;
	q.push({ R,C });

	int Time = 0;
	cnt = 1;

	while (!q.empty()) {
		int qsize = q.size();
		
		Time++;
		if (Time == L)break;	// 시간이 다되면 break

		for (int i = 0;i < qsize;i++) {
			node now = q.front();
			q.pop();
			
			int blocknum = Map[now.y][now.x];	// 파이프 번호 확인

			for (int i = 0;i < pipe[blocknum].size();i++) {	
				int nowdir = pipe[blocknum][i];	
				int dy = now.y + diry[nowdir];
				int dx = now.x + dirx[nowdir];
				if (dy >= N || dy < 0 || dx >= M || dx < 0)continue;	// 경계면
				if (visited[dy][dx])continue;							// 방문여부
				if (!check_move(nowdir, Map[dy][dx]))continue;			// 갈 수 있는지 확인

				visited[dy][dx] = 1;
				cnt++;
				q.push({ dy,dx });
			}
		}
	}

}


int main() {
	int T;
	cin >> T;

	makedir();

	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(Map, 0, sizeof(Map));
		memset(visited, 0, sizeof(visited));

		// input
		cin >> N >> M >> R >> C >> L;

		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				cin >> Map[i][j];
			}
		}

		// solve
		visited[R][C] = 1;
		bfs();

		// output
		cout << "#" << tc << ' ' << cnt << '\n';
	}



	return 0;
}