#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
int visited[16];
int MAP[16][16];
int result = 21e8;
int flag;
void reset() {
	result = 21e8;
	flag = 0;
}
void input() {
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
		}
	}

}

void cal() {
	int tmp0 = 0;
	int tmp1 = 0;

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (visited[i] != visited[j]) continue;

			if (visited[i] == 1) {
				tmp1 += MAP[i][j] + MAP[j][i];
			}
			else {
				tmp0 += MAP[i][j] + MAP[j][i];
			}
		}
	}

	

	if (tmp0 == tmp1) {
		result = 0;
		flag = 1;
		return;
	}

	if (tmp0 < tmp1) {
		result = min(result, tmp1 - tmp0);
	}
	else {
		result = min(result, tmp0 - tmp1);
	}

}

void func(int now, int st) {
	//base
	if (flag == 1)return;
	if (now == N / 2) {
		cal();
		return;
	}

	//recursive
	for (int i = st; i < N; i++) {
		visited[i] = 1;
		func(now + 1, i+1);
		visited[i] = 0;
	}

}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {

		reset();
		input();

		func(0, 0);
		cout << "#" << tc << " " << result << endl;
	}
	return 0;
}