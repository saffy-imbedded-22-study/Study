#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int N;	// 벌통 크기
int M;	// 선택 개수
int C;	// 최대 양
int Map[10][10]; // 맵

vector<int> v;		// 조합 구할때 사용
bool visited[5];	// 조합 구할때 사용

struct node {
	int sum;	// 제곱 합
	int y, x;	// 좌표

	bool operator < (node next) const {
		return sum > next.sum;
	}
};

node DAT[100];	
int Maxsum = 0;
void dfs(int level, int nowsum, int multisum);

int find_biggest(int y, int x) {	// 범위 안에서 최대값 찾기
	v.clear();
	Maxsum = 0;
	for (int j = x;j < x + M;j++) {
		v.push_back(Map[y][j]);
	}
	sort(v.begin(), v.end());		// 내림차순 정렬, 안해도 될듯

	dfs(0, 0, 0);					// dfs 이용해서 모든 조합에서 가능한 값 찾기

	return Maxsum;					// 제곱합 중 제일 큰 값 리턴
}


void dfs(int level, int nowsum, int multisum) {	// 진행횟수, 합, 제곱합
	if (nowsum > C) return;			// 합이 C 넘어가면 리턴

	Maxsum = max(Maxsum, multisum);	// 제곱합이 최대인지 확인

	if (level == M) {				// 조합이 M개가 되면 리턴
		return;
	}
	
	for (int i = 0;i < M;i++) {
		if (visited[i])continue;	
		visited[i] = 1;		
		dfs(level + 1, nowsum + v[i], multisum + v[i] * v[i]);
		visited[i] = 0;
	}

}




int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(Map, 0, sizeof(Map));
		memset(DAT, 0, sizeof(DAT));

		// input
		cin >> N >> M >> C;
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				cin >> Map[i][j];
			}
		}

		// solve
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N - M + 1;j++) {
				DAT[i * N + j] = { find_biggest(i,j),i,j };	// 최대제곱합과 좌표 저장
			}
		}

		sort(DAT, DAT + N * N);	// 제곱합 내림차순으로 정렬
		
		node Large_one = DAT[0];	// 맨 앞은 무조건 들어감.
		node Large_two;
		
		for (int i = 1;i < N * N;i++) {	// 나머지 중에 안겹치는거 찾기
			bool flag = true;

			if (DAT[i].y == Large_one.y) {		// y좌표 같을때 x좌표 겹치는지 확인. 좀더 간단히?
				for (int j = 0;j < M;j++) {
					int dx = DAT[i].x + j;
					if ((dx >= Large_one.x) && (dx <= Large_one.x + M - 1)) {
						flag = false;
						break;
					}
				}
			}
			if (!flag)continue;

			Large_two = DAT[i];
			break;
		}
		
		
		int ans = Large_one.sum + Large_two.sum;



		// output
		cout << "#" << tc << ' ' << ans << '\n';
	}



	return 0;
}