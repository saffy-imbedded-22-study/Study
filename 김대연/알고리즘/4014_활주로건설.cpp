#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int N;	// 한 변 크기
int X;	// 경사로 길이
int Map[21][21]; // 지형 정보
int ans;		// 건설 가능 개수

struct node {
	int height;	// 높이
	int cnt;	// 개수
};

bool checkbuild(vector<int>& v) {

	int cnt = 1;

	vector<node> vh;	// 높이와 연속된 개수 저장
	// ex 3 3 2 2 1 2 이면 (3,2), (2,2), (1,1), (2,1) 저장

	for (int i = 0;i < N - 1;i++) {
		if (v[i] == v[i + 1]) {
			cnt++;	// 같으면 cnt+
		}
		else {
			if (abs(v[i] - v[i + 1]) == 1) {
				vh.push_back({ v[i],cnt });	//높이 정보와 개수.
				cnt = 1;
			}
			else {
				return false;
			}
		}
	}
	vh.push_back({ v[N - 1], cnt });	// 마지막 정보 입력

	

	for (int i = 0;i < vh.size()-1;i++) {
		if (vh[i].height > vh[i + 1].height) {	// 앞 뒤 중 큰 값 찾아서
			if (vh[i + 1].cnt < X) {	// 작은 수의 개수가 X개가 되는지 확인
				return false;
			}
			else {
				vh[i + 1].cnt -= X;		// 있다면 건설 후 X개만큼 제거.
			}
				
		}
		else {
			if (vh[i].cnt < X)
				return false;
			else
				vh[i].cnt -= X;
		}
	}

	ans++;	
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(Map, 0, sizeof(Map));
		ans = 0;

		// input
		cin >> N >> X;
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				cin >> Map[i][j];
			}
		}

		// solve
		for (int i = 0;i < N;i++) {
			vector<int> v;

			for (int j = 0;j < N;j++) {
				v.push_back(Map[i][j]);
			}
			checkbuild(v);
		}

		for (int j = 0;j < N;j++) {
			vector<int> v;

			for (int i = 0;i < N;i++) {
				v.push_back(Map[i][j]);
			}
			checkbuild(v);
		}


		// output
		cout << "#" << tc << ' ' << ans << '\n';
	}



	return 0;
}