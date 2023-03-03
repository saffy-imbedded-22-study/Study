#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

int N;
int input[200001];		// 입력 정보
int arr[200001];		// 누적 합
int DAT_zero[200001];	// 현재까지 0 개수
unordered_map<int, int> um;

/*
	규칙만 찾으면 간단!

	입력을 없던일로 하는거기 때문에 그 전까지는 영향X, 본인 위치 이후부터 영향.

	0 개수 = 본인위치 전까지의 0 개수 + 본인위치부터 본인 입력값과 같은 값 개수
				DAT_zero 이용				arr 이용

	
	ex) 입력값 0 -1 1 0 1
		누적합 0 -1 0 0 1

		1초 : 0 + 3
		2초 : 1 + 1
		3초 : 1 + 1
		4초 : 2 + 1
		5초 : 3 + 1
*/

int main() {
	cin >> N;

	int sum = 0;		// 합
	int cnt_zero = 0;	// 0 카운트

	for (int i = 0;i < N;i++) {
		cin >> input[i];
		sum += input[i];
		arr[i] = sum;			// 지금까지의 합 저장
		DAT_zero[i] = cnt_zero; // 본인 위치 전까지의 0 개수 저장
		if (arr[i] == 0) cnt_zero++;	// 입력해주고 카운트+
		
		if (um.find(arr[i]) != um.end()) {	// map에 갯수 count
			um[arr[i]]++;
		}
		else {
			um.insert({ arr[i],1 });
		}
	}

	int Max = 0;

	for (int i = 0;i < N;i++) {
		//본인 전까지의 0 개수 + 본인 위치부터 본인 입력값의 개수
		int count_zero = DAT_zero[i] + um[input[i]];

		Max = max(Max, count_zero);
			
		um[arr[i]]--;	// 본인 위치 숫자 개수 1 감소 (그래야 뒤에서 또 호출했을때 카운트 안됨)
	}

	cout << Max;

	return 0;
}