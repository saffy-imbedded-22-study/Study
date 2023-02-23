#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

int N;
int input[200001];
int arr[200001];
int DAT_zero[200001];
unordered_map<int, int> um;

/*
	0 개수 = 본인위치까지의 0 개수 + 본인위치부터 본인 입력값과 같은 값 개수
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

	int sum = 0;
	int cnt_zero = 0;

	for (int i = 0;i < N;i++) {
		cin >> input[i];
		sum += input[i];
		arr[i] = sum;			// 지금까지의 합 저장
		DAT_zero[i] = cnt_zero; // 본인 위치 전까지의 0 개수 저장
		if (arr[i] == 0) cnt_zero++;
		
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