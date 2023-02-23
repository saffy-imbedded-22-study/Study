#include <iostream>
#include<cstring>
#include <vector>
using namespace std;

struct node {
	int y;
	int x;
	int num;
	int dir;
};

struct XY {
	int y;
	int x;
};

int Map[100][100]; // N 최대 100
node Bugs[1000]; // K 최대 1000
vector<int> overlap[100][100];
vector<XY> exist;
int N, M, K;
int dirx[4] = { 0,0,-1,1 };
int diry[4] = { -1,1,0,0 };

void Move(int i) {
	int dy = Bugs[i].y + diry[Bugs[i].dir - 1];
	int dx = Bugs[i].x + dirx[Bugs[i].dir - 1];

	if (dy == 0 || dy == N - 1 || dx == 0 || dx == N - 1) {
		if (Bugs[i].dir == 1 || Bugs[i].dir == 3) {	//방향 전환
			Bugs[i].dir += 1;
		}
		else {
			Bugs[i].dir -= 1;
		}
		Bugs[i].num /= 2;
	}
	overlap[dy][dx].push_back(i);	//그 칸에 i번째 얘가 있다고 표시.
	exist.push_back({ dy,dx });

	Bugs[i].y = dy;
	Bugs[i].x = dx;
}


int main()
{
	int T;
	cin >> T;

	for (int t = 1;t <= T;t++) {
		//reset
		memset(Bugs, 0, sizeof(Bugs));
		memset(Map, 0, sizeof(Map));


		//input
		cin >> N >> M >> K;
		for (int i = 0;i < K;i++) {
			cin >> Bugs[i].y >> Bugs[i].x >> Bugs[i].num >> Bugs[i].dir;
		}


		//solve

		for (int i = 0;i < M;i++) {
			memset(overlap, 0, sizeof(overlap));
			exist.clear();

			for (int j = 0;j < K;j++) {
				if (Bugs[j].num == 0)continue;
				Move(j);
			}

			for (int z = 0;z < exist.size();z++) {
				int m = exist[z].y;
				int n = exist[z].x;

				if (overlap[m][n].size() > 1) {	//그 칸에 2개 이상 있을경우
					int max = 0, max_idx = 0;
					for (int k = 0;k < overlap[m][n].size();k++) {	//가장 큰 애 찾기.
						if (max < Bugs[overlap[m][n][k]].num) {
							max = Bugs[overlap[m][n][k]].num;
							max_idx = k;
						}
					}
					for (int k = 0;k < overlap[m][n].size();k++) {	//가장 큰애한테 몰아주기.
						if (k == max_idx)continue;
						Bugs[overlap[m][n][max_idx]].num += Bugs[overlap[m][n][k]].num;
						Bugs[overlap[m][n][k]].num = 0;
					}
				}
			}
		}

		int left_bug = 0;
		for (int i = 0;i < K;i++) {
			left_bug += Bugs[i].num;
		}


		//output
		cout << "#" << t << ' ' << left_bug << '\n';
	}
	return 0;
}

