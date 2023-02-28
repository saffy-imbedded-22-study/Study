/*
너무 더럽게품.
bit 연산으로 풀이 가능!!
*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

int K;
int Map[4][8];
int pointer[4];

struct node {
	int num;
	int dir;
};

queue<node> q;

bool checksame(int left, int right) {
	int leftp = (pointer[left] + 2) % 8;
	int rightp = (pointer[right] + 6) % 8;

	if (Map[left][leftp] != Map[right][rightp]) {
		return true;
	}
	else
		return false;
}


int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(Map, 0, sizeof(Map));
		memset(pointer, 0, sizeof(pointer));

		// input
		cin >> K;

		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 8;j++) {
				cin >> Map[i][j];
			}
		}

		for (int i = 0;i < K;i++) {
			int a, b;
			cin >> a >> b;
			q.push({ a-1,b });
		}

		// solve



		while (!q.empty()) {
			node now = q.front();
			q.pop();

			queue<node> nowq;
			int DAT[4] = { 0 };
			DAT[now.num] = 1;
			
			
			if (now.num > 0) {
				if (checksame(now.num - 1, now.num)) {
					nowq.push({ now.num - 1,now.dir * (-1) });
					DAT[now.num - 1] = 1;
				}
			}
			if (now.num < 3) {
				if (checksame(now.num, now.num + 1)) {
					nowq.push({ now.num + 1,now.dir * (-1) });
					DAT[now.num + 1] = 1;
				}
			}

			if (now.dir == 1) {
				pointer[now.num] = (pointer[now.num] + 7) % 8;
			}
			else {
				pointer[now.num] = (pointer[now.num] + 1) % 8;
			}


			while (!nowq.empty()) {
				node next = nowq.front();
				nowq.pop();

				if (next.num > 0) {
					if (DAT[next.num - 1] != 1) {
						if (checksame(next.num - 1, next.num)) {
							nowq.push({ next.num - 1,next.dir * (-1) });
							DAT[next.num - 1] = 1;
						}
					}	
				}
				if (next.num < 3) {
					if (DAT[next.num + 1] != 1) {
						if (checksame(next.num, next.num + 1)) {
							nowq.push({ next.num + 1,next.dir * (-1) });
							DAT[next.num + 1] = 1;
						}
					}
				}

				if (next.dir == 1) {
					pointer[next.num] = (pointer[next.num] + 7) % 8;
				}
				else {
					pointer[next.num] = (pointer[next.num] + 1) % 8;
				}

			}
		}
		int ans = 0;
		for (int i = 0;i < 4;i++) {
			if (Map[i][pointer[i]] == 1) {
				ans += pow(2, i);
			}
		}

		// output
		cout << "#" << tc << ' ' << ans << '\n';

	}



	return 0;
}