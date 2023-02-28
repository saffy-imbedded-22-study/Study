#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

struct micro {
	int y, x, cnt, dir;
};

int N, M, K;

int MAP[100][100];
int ydir[] = { 0,-1,1,0,0 };
int xdir[] = { 0,0,0,-1,1 };
vector<micro>v;

int changedir(int dir) {

	if (dir % 2 == 1) {
		return dir + 1;
	}
	else {
		return dir - 1;
	}

}




void simul() {

	while (M--) {
		//이동
		for (int i = 0; i < v.size(); i++) {
			micro now = v[i];
			MAP[now.y][now.x]--;
			int ny = now.y + ydir[now.dir];
			int nx = now.x + xdir[now.dir];

			if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
				now.cnt = now.cnt / 2;
				now.dir = changedir(now.dir);
			}

			if (now.cnt == 0) {
				v.erase(v.begin() + i);
				i--;
			}
			else {
				MAP[ny][nx]++;
				v[i].cnt = now.cnt;
				v[i].y = ny;
				v[i].x = nx;
				v[i].dir = now.dir;
			}

		}

		//합치기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j] > 1) {
					int sum = 0;
					int maxcnt = 0;
					int maxdir = 0;
					for (int k = 0; k < v.size(); k++) {
						if (v[k].y == i && v[k].x == j) {
							sum += v[k].cnt;
							if (v[k].cnt > maxcnt) {
								maxcnt = v[k].cnt;
								maxdir = v[k].dir;
							}
							v.erase(v.begin() + k);
							k--;
						}

					}
					v.push_back({ i,j,sum,maxdir });
					MAP[i][j] = 1;
				}

			}
		}


	}


}





int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {
		memset(MAP, 0, sizeof(MAP));
		v.clear();
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++) {
			int y, x, cnt, dir;
			cin >> y >> x >> cnt >> dir;
			v.push_back({ y,x,cnt,dir });
			MAP[y][x]++;
		}

		simul();

		int minumber = 0;

		for (int i = 0; i < v.size(); i++) {
			minumber += v[i].cnt;
		}

		cout << "#" << te << " " << minumber << endl;
	}
	return 0;
}