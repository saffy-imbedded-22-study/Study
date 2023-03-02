#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
using namespace std;
int reMax = 0;
int MAP[11][11];
int Result[11][11];
int N, M,C;
int maxRe;
int dy, dx;//최대 일떄 시작좌표
void reset() {
	memset(Result, 0, sizeof(Result));
	maxRe = 0;
	reMax = 0;
}

void input() {
	cin >> N >> M >> C;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
		}
	}
}


void findMax(int now, int st, int ed, int arr[11],int re, int sum) {
	
	if (now == ed - st + 1) {
		reMax = max(reMax, re);
		return;
	}

	findMax(now + 1, st, ed, arr, re,sum);
	if (sum + arr[st + now] <= C) {
		findMax(now + 1, st, ed, arr, re + arr[st + now] * arr[st + now], sum + arr[st + now]);
	}
	
}

void Sliding(int arr[11], int y) {
	int left = 0;
	int right = M - 1;
	
	int sum = 0;
	int result = 0;
	for (int i = left; i < right; i++) {
		sum += arr[i];
		result += arr[i]*arr[i];
	}

	while (right < N) {
		//구간완성
		sum += arr[right];
		result += arr[right] * arr[right];
		int tmp = result;//복구용
		//처리
			//sum이 큰경우 result 바꾸기
		if (sum > C) {
			findMax(0, left, right, MAP[y],0,0);
			result = reMax;
			reMax = 0;
		}
			//최댓값 갱신
		if (maxRe < result) {
			maxRe = result;
			dy = y;
			dx = left;
		}
		Result[y][left] = result;

		//포인터 옮기기
		result = tmp;//복구
		sum -= MAP[y][left];
		result -= MAP[y][left] * MAP[y][left];
		left++;
		right++;
		
	}

}

int main() {
	//freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		for (int y = 0; y < N; y++) {
			Sliding(MAP[y],y);
		}
		

		int maxSecond = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x <= N - M; x++) {
				if (y == dy && x + M - 1 >= dx) continue;
				if (y == dy && x <= dx + M - 1) continue;
				if (y == dy && x == dx) continue;

				if (maxSecond < Result[y][x]) {
					maxSecond = Result[y][x];
				}
			}
		}
		cout << "#" << tc << " " <<maxRe+maxSecond << endl;
	}
	
	return 0;
}