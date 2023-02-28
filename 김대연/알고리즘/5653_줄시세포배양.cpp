#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

int N;	// 세로
int M;	// 가로
int K;	// 배양 시간
int Map[750][750];	// 세포 정보 저장

struct node {
	int y, x;	// 좌표
	int sleep;	// 비활성화
	int alive;	// 생존 남은 일수
	int life;	// 세포 생명력
	int day;	// 며칠차 정보인지.
};
struct cmp {
	bool operator()(node left, node right) {
		if (left.day < right.day)return false;
		if (left.day > right.day)return true;

		return left.life < right.life;
	}
};

priority_queue<node, vector<node>, cmp> pq; // 현재 생존 좌표 저장

void bfs()
{
	int nowT = 0;
	int nowsize = 0;

	while (1) {
		nowsize = pq.size();	// 현재 queue에 있는 개수만큼 진행하고 다음날로
		nowT++;				
		
		for (int i = 0;i < nowsize;i++) {
			node now = pq.top();
			pq.pop();

			if (now.sleep != 0) {
				now.sleep--;
				now.day = nowT;
				pq.push(now);
			}
			else {
				if (now.alive == 0) {
					for (int dir = 0;dir < 4;dir++) {
						int dy = now.y + diry[dir];
						int dx = now.x + dirx[dir];
						
						if (Map[dy][dx] != 0) {
							continue;
						}

						Map[dy][dx] = Map[now.y][now.x];
						pq.push({ dy,dx,Map[dy][dx],0,Map[dy][dx],nowT });
					}
					if (Map[now.y][now.x] != 1) {
						now.alive = Map[now.y][now.x] - 1;
						now.day = nowT;
						pq.push(now);
					}
				}
				else {
					if (now.alive > 1) {
						now.alive--;
						now.day = nowT;
						pq.push(now);
					}
				}
			}

		}
		/*cout << nowT << '\n' << '\n';
		for (int i = 345;i < 365;i++) {
			for (int j = 345;j < 365;j++) {
				if (Map[i][j] != 0)
					cout << Map[i][j] << ' ';
				else
					cout << "  ";
			}cout << '\n';
		}
		cout << '\n';*/


		if (nowT == K)break;
	}
	return;
}





int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++)
	{
		//reset
		memset(Map, 0, sizeof(Map));
		pq = priority_queue<node, vector<node>, cmp>();	// queue 초기화

		//input
		cin >> N >> M >> K;

		for (int i = 350;i < N+350;i++) {
			for (int j = 350;j < M+350;j++) {
				cin >> Map[i][j];
				if (Map[i][j] != 0) {
					pq.push({ i,j,Map[i][j],0,Map[i][j],0 });
				}
			}
		}

		//solve
		bfs();

		

		//output
		cout << "#" << tc << ' ' << pq.size() << '\n';

	}


	return 0;
}