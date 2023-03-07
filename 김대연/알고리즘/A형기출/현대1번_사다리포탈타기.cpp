#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N;	// 세로 줄 길이
int M;	// 사람 수

struct node {
	int y, x;

	bool operator == (node next)const {
		return (y == next.y) && (x == next.x);
	}
};

int Map[10][20];
vector<node> portal[26];	// 포탈 저장
int ans[10];				// 정답 저장

node move_portal(node now) {
	int portalnum = Map[now.y][now.x] - 1;	// 포탈 번호

	for (int i = 0;i < 2;i++) {
		if (now == portal[portalnum][i]) {
			continue;
		}
		return portal[portalnum][i];	// 포탈 좌표 리턴
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M*2-1;j++) {		// 입력할때 사람 사이에 . 존재	
			char temp;
			cin >> temp;
			if (temp >= 'a' && temp <= 'z') {	// 포탈이면
				int num = temp - 'a' + 1;		// 포탈 숫자
				Map[i][j] = num;				// 맵에 숫자 표기
				portal[num-1].push_back({ i,j });	// 포탈 좌표 추가
			}
		}
	}

	for (int i = 0;i < M;i++) {
		node now = { 0,2 * i };	// 시작 위치

		while (1) {
			if (Map[now.y][now.x] != 0) {	// 포탈 존재하면
				now = move_portal(now);		// 포탈 탑승
			}
			now.y++;						// 아래로 이동
			if (now.y == N)break;			// 맨 밑이면 탈출
		}
		ans[now.x / 2] = i + 1;				// 현재 위치 저장
	}

	for (int i = 0;i < M;i++) {
		cout << ans[i] << ' ';				
	}
	return 0;
}