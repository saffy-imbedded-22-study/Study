#include<iostream>
#include<algorithm>
using namespace std;

int N;	// 일 수
int Ti[20];	// 상담 시간
int Pi[20];	// 상담 비용
int ans;	// 최대 이익

void dfs(int day, int price) {
	if (day > N) {
		return;
	}
	else {
		ans = max(ans, price);
		if (day == N) return;
	}

	
	ans = max(ans, price);
	// 상담 할시
	dfs(day + Ti[day+1], price + Pi[day+1]);

	// 상담 안할시
	dfs(day + 1, price);

}


int main() {
	cin >> N;
	for (int i = 1;i <= N;i++) {
		cin >> Ti[i] >> Pi[i];
	}
	dfs(0, 0);

	cout << ans;

	return 0;
}