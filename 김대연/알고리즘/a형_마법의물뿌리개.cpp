#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int N;
int tree[100];
int DAT[100];
int max_height;

int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(tree, 0, sizeof(tree));
		memset(DAT, 0, sizeof(DAT));
		max_height = 0;
		// input
		cin >> N;
		for (int i = 0;i < N;i++) {
			cin >> tree[i];
			max_height = max(tree[i], max_height);
		}

		// solve
		int sum = 0;
		int cnt = 0;
		for (int i = 0;i < N;i++) {
			int dat = max_height - tree[i];
			if (dat % 2 == 1) cnt++;	// 홀수 개수

			sum += dat;	// 차이 합
		}
		int ans = sum / 3 * 2;	// 1,2를 한세트로 생각. 최소 이만큼이 필요
		if (sum / 3 < cnt) ans += (cnt - sum / 3) * 2 - 1;	// 홀수 개수가 세트 수 보다 클 경우 -> 1이 더 필요할 경우
		else ans += sum % 3;	// 1이나 2가 한개 부족한 경우

		// output
		cout << "#" << tc << ' ' << ans << '\n';
	}



	return 0;
}