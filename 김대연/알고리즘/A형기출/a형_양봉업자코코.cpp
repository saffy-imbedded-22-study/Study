#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int diry_even[6] = { -1,1,0,1,0,1 };    // 짝수 줄 일때
int dirx_even[6] = { 0,0,1,1,-1,-1 };

int diry_odd[6] = { -1,1,0,-1,0,-1 };   // 홀수 줄 일때
int dirx_odd[6] = { 0,0,1,1,-1,-1 };


int N, M;
int Map[16][16];
int visited[16][16];
int Max_sum = 0;

bool cmp(int left, int right) {
	return left > right;
}

void dfs(int y, int x, int level, int Sum) {
	

	if (level == 3) {
		if (Max_sum < Sum) {    //최대값 찾기
			Max_sum = Sum;
		}

		return;
	}

	for (int i = 0;i < 6;i++) {
		int dy, dx;
		if (x % 2 == 0) {           // 홀수 줄 (x가 0부터 시작)
			dy = y + diry_odd[i];
			dx = x + dirx_odd[i];
		}
		else {
			dy = y + diry_even[i];
			dx = x + dirx_even[i];
		}
		
		if (dy >= N || dy < 0 || dx >= M || dx < 0)continue;
		if (visited[dy][dx] == 1)continue;      // 갔던 곳 또 안가기
		visited[dy][dx] = 1;                    // 방문 체크
		
		dfs(dy, dx, level + 1, Sum + Map[dy][dx]);

		visited[dy][dx] = 0;                    // dfs 끝났으면 초기화 해주기!!
	}
}

void check_round(int y, int x) {    //주변에 3개 있을 경우
	int dy, dx, cnt=0;
	vector<int> round;

	for (int i = 0;i < 6;i++) {
		if (x % 2 == 0) {
			dy = y + diry_odd[i];
			dx = x + dirx_odd[i];
		}
		else {
			dy = y + diry_even[i];
			dx = x + dirx_even[i];
		}
		if (dy >= N || dy < 0 || dx >= M || dx < 0)continue;
		round.push_back(Map[dy][dx]);   // 크기를 벡터에 저장
		cnt++;
	}
	if (cnt < 3)return; // 주변에 3개가 없을 경우 계산 X
	sort(round.begin(), round.end(), cmp); // 내림차순으로 정렬
	int temp = round[0] + round[1] + round[2] + Map[y][x];  // 본인 값 포함해서 큰 순으로 3개 값 계산
	if (Max_sum < temp)
		Max_sum = temp;

}


int main() {
	cin >> N >> M;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			cin >> Map[i][j];
		}
	}

	for (int i = 0;i < N;i++) {         // 맵 전체를 돌면서 dfs 및 주변 값 계산
		for (int j = 0;j < M;j++) { 
			memset(visited, 0, sizeof(visited));
			visited[i][j] = 1;          // 시작 위치 방문 체크
			dfs(i, j, 0, Map[i][j]);    // 합 초기 값을 본인 값으로 시작.
			check_round(i, j);      
		}
	}

	cout << Max_sum;

	return 0;
}