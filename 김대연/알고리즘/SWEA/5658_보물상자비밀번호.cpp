#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

int N;	// 16진수 숫자
int K;	// k번째 큰 수 출력
string number;
vector<string> nums;

int makenumber(string temp) {

	int len = temp.length();
	int num = 0;

	for (int i = 0;i < temp.length();i++) {	
		char k = temp[i];	
		int n;
		if (k >= '0' && k <= '9') {
			n = temp[i] - '0';
		}
		else {
			n = temp[i] - 'A'+ 10;	// 영어일 경우 10~15
		}

		num += pow(16, --len) * n;	
		
	}
	return num;
}

int main() {
	int T;
	cin >> T;
	
	for (int t = 1;t <= T;t++) {
		//reset
		nums.clear();

		//input
		cin >> N >> K >> number;


		//solve
		int cut = N / 4;	// 잘라지는 숫자 길이

		for (int i = 0;i < cut;i++) {
			for (int j = 0;j < 4;j++) {

				string temp;
				for (int k = 0;k < cut;k++) {
					int idx = (cut * j + k + i) % N;
					temp += number[idx];
				}
				if (find(nums.begin(), nums.end(), temp) == nums.end()) {	// 중복되면 안넣음
					nums.push_back(temp);
				}
			}
		}

		sort(nums.begin(), nums.end());	// 오름차순 정렬 후 뒤에서부터 제거
		
		for (int i = 0;i < K-1;i++) {	// k-1개 만큼 제거
			nums.pop_back();
		}
		string ans = nums.back();	// k 번째 16진수

		cout << "#" << t << ' ' << makenumber(ans) << '\n';
	}


	return 0;
}