#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

string ans;
int N;
string temp[100];

int main() {
	cin >> N;
	cin >> ans;
	int len = ans.length();

	for (int i = 0;i < N;i++) {
		cin >> temp[i];
	}

	sort(temp, temp + N);	// 알파벳 순으로 정렬

	int start_idx = 0;

	for (int i = 0;i < N;i++) {		// 정답과 첫번째 글자가 같은 temp부터 시작
		if (temp[i][0] != ans[0])continue;
		start_idx = i;
		break;
	}

	int ans_idx = -1;

	for (int i = 0;i < N;i++) {
		int idx = (i + start_idx) % N;	// start_idx 부터 start_idx-1까지 순회
		
		if (len != temp[idx].length()) continue;	// 길이 다르면 바로 스킵

		int key = temp[idx][0] - ans[0];		// key값 갱신
		if (key < 0)key += 26;					// 음수일경우 +26

		bool flag = true;

		for (int j = 0;j < len;j++) {
			int check_key = temp[idx][j] - ans[j];
			if (check_key < 0) check_key += 26;	// 모든 글자 차이가 key값과 동일한지 확인
			if (check_key != key) {
				flag = false;
				break;
			}
		}

		if (flag) {
			ans_idx = idx;
			break;
		}
	}

	cout << temp[ans_idx];

	return 0;
}

