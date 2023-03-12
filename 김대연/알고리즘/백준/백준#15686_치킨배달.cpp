#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N;	// 맵 크기
int M;	// 선택할 치킨집

int Map[60][60];	// 맵
struct node {
	int y, x;
};

node home[110];	// 집 위치 저장
node chicken[20];	// 치킨집 위치 저장
int home_num;	// 집 개수
int chicken_num;	// 치킨집 개수
int path[20];	// 선택한거 저장
int ans;	// 정답(최소거리)

void init() {
	ans = 21e8;

	cin >> N >> M;

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 1) {
				home[home_num++] = { i,j };
			}
			else if (Map[i][j] == 2) {
				chicken[chicken_num++] = { i,j };
			}
		}
	}

}

int solve() {	// 각 집에서 가장 가까운 치킨집까지의 거리 구하기

	int sum = 0;
	for (int i = 0;i < home_num;i++) {
		int minlen = 21e8;
		node now = home[i];

		for (int j = 0;j < M;j++) {
			node nowchicken = chicken[path[j]];
			int len = abs(now.y - nowchicken.y) + abs(now.x - nowchicken.x);
			minlen = min(minlen, len);
		}
		sum += minlen;
	}
	return sum;
}

void dfs(int level, int next) {	// 치킨집 중 M개 뽑기
	if (level == M) {	// M개 뽑았으면 거리 계산해주기!
		int len = solve();
		ans = min(ans, len);
		return;
	}

	for (int i = next;i <= chicken_num-(M-level);i++)	// 중복되지 않게 뽑기.
	//	범위를 저렇게 한건 예를들어 총 3개를 뽑아야 할때 1개 뽑았으면 그 뒤에 2개가 남아있어야하기 때문!
	{
		path[level] = i;
		dfs(level + 1, i + 1);
		path[level] = 0;
	}

}

int main() {
	
	init();

	dfs(0, 0);
	
	cout << ans;


	return 0;
}