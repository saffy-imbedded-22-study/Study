#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int visited[20]; // idx: 식재료 종류, value: 선택여부
int path[20];//edge가 증가하는 경우만 선택하기
int MAP[20][20] = { 0, };// 입력 받기
int minDiff = 21e8;
int N;

//비교해서 절댓값 return
int process() {
	int re1 = 0;
	int re2 = 0;
	for (int x = 0; x < N - 1; x++)
	{
		for (int y = x + 1; y < N; y++) {

			if (visited[x] == 0 && visited[y] == 0) {
				re1 += MAP[x][y] + MAP[y][x];
			}
			else if (visited[x] == 1 && visited[y] == 1)
			{
				re2 += MAP[x][y] + MAP[y][x];
			}
		}
	}
	int temp = re1 - re2;
	if (temp < 0)
		return -temp;

	return temp;


}

void DFS(int cnt) {
	//종료조건
	//N/2번 실행시 종료
	if (cnt == N / 2) {
		int result = process();
		if (result < minDiff) {
			minDiff = result;
		}
		return;
	}


	for (int x = 0; x < N; x++) {

		//가지치기 

		if (visited[x] == 1) continue;//중복방지
		if (path[cnt - 1] > x) continue;//증가하는 경우만

		//처리
		visited[x] = 1;
		path[cnt] = x;

		//모든 재료로 다 가보기
		DFS(cnt + 1);

		visited[x] = 0;

	}


}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//reset
		minDiff = 21e8;
		for (int x = 0; x < 20; x++) {
			visited[x] = 0;
		}

		//input
		cin >> N;

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> MAP[y][x];
			}
		}

		DFS(0);
		cout << "#" << tc << " " << minDiff << endl;


	}


	return 0;
}