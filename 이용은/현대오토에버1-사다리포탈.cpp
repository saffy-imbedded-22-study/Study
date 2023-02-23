#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
struct Node {
	int y, x;
};
char MAP[11][20];
int N, M;
int flag;//0 포탈 들어가기 전, 1:포탈 들어간 후
int MAN=1;// 몇번째 사람인지, 1~M
vector<Node>v[30];//포탈
int ans[20];//도착위치

void input() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < 2 * M - 1; x++) {
			cin >> MAP[y][x];

			if ('a' <= MAP[y][x] && MAP[y][x] <= 'z') {
				int idx = MAP[y][x] - 'a';
				v[idx].push_back({ y,x});
			}
		}
	}
}

Node potal(int y, int x) {
	int idx = MAP[y][x] - 'a';
	flag = 1;
	if (v[idx][0].x == x) {
		return v[idx][1];
	}
	else {
		return v[idx][0];
	}
		
}

void DFS(int row, int col) {
	//base: N-1
	if (row > N-1) {
		ans[col / 2 + 1] = MAN;
		MAN++;
		return;
	}
	//recursive: | or 알파벳
	if (MAP[row][col] == '|')
		DFS(row + 1, col);
	if('a'<= MAP[row][col] && MAP[row][col]<='z'){
		if (flag == 0) {
			Node next = potal(row, col);
			DFS(next.y, next.x);
		}
		if (flag == 1) {
			flag = 0;
			DFS(row + 1, col);
		}
	}
}

int main() {
	input();

	for (int x = 0; x < 2 * M - 1; x += 2) {
		flag = 0;
		DFS(0, x);//결과를 ans queue에 저장
	}
		
	//output
	for (int x = 1; x <=M; x++) {
		cout << ans[x] << " ";
	}

	return 0;
}