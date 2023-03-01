#include <iostream>
#include<cmath>
#include<cstring>
using namespace std;

int MAProw[21][21]; // 가로체크 맵
int MAPcol[21][21]; // 세로체크 맵
int N, X; // 한변의 길이, 경사로의 길이
int ans; // 건설 가능한 수

void simul(int MAP[21][21]) {

	for (int i = 0; i < N; i++) {
		int check = 1; //활주로 건설 가능 체크
		int connect[21] = { 0 }; // 겹치는 활주로 안만들도록
		for (int j = 0; j < N-1; j++) {
			if (MAP[i][j] == MAP[i][j + 1])continue;
			
			int h = MAP[i][j] - MAP[i][j + 1];

			if (abs(h) > 1) {
				check = 0;
				break;
			}
			
			if (h == 1) { //내리막길
				for (int k = j + 1; k < j + 1 + X; k++) {
					if (k >= N || (MAP[i][j + 1] != MAP[i][k]) || connect[k] == 1) {
						check = 0;
						break;
					}
					else {
						connect[k] = 1;
					}
				}
			}
			else if (h == -1) { //오르막길
				for (int k = j; k > j - X; k--) {
					if (k < 0 || MAP[i][j] != MAP[i][k] || connect[k] == 1) {
						check = 0;
						break;
					}
					else {
						connect[k] = 1;
					}
				}
			}
		}
		if (check == 1) {
			ans++;
		}
	}
}



int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {
		ans = 0;
		memset(MAProw, 0, sizeof(MAProw));
		memset(MAProw, 0, sizeof(MAPcol));
		cin >> N >> X;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAProw[i][j];
				MAPcol[j][i] = MAProw[i][j];
			}
		}

		simul(MAProw);
		simul(MAPcol);

		cout << "#" << te << " " << ans << endl;
	}

}