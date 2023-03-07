#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;

int N;	// 접수 창구
int M;	// 정비 창구
int ai[10];	// 접수 시간
int bj[10];	// 정비 시간
int K;	// 사람 수
int tk[1000];	// 사람 도착 시간
int A;	// 목표 접수 창구
int B;	// 목표 정비 창구
int DAT_A[1000]; // A창구 이용했는지
int DAT_B[1000]; // B창구 이용했는지


struct node {
	int idx;
	int tk;
	int used;	// 이용했던 창구
	int waiting;	// 기다린 시간

	bool operator < (node next)const {
		if (tk > next.tk)return true;	// 시간순
		if (tk < next.tk)return false;
		if (waiting < next.waiting)return true;	// 기다린 시간 긴사람 먼저
		if (waiting > next.waiting)return false;
		if (used > next.used)return true;	// 접수창고 번호순
		if (used < next.used)return false;
		return idx > next.idx;	// 고객번호 순
	}
};
node A_now[10];	// 접수 창구 이용현황.
node B_now[10]; // 정비 창구
priority_queue<node> pq;	// 접수 창구
priority_queue<node> pq2;	// 정비 창구

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		memset(ai, 0, sizeof(ai));
		memset(bj, 0, sizeof(bj));
		memset(tk, 0, sizeof(tk));
		memset(DAT_A, 0, sizeof(DAT_A));
		memset(DAT_B, 0, sizeof(DAT_B));
		memset(A_now, 0, sizeof(A_now));
		memset(B_now, 0, sizeof(B_now));

		pq = priority_queue<node>();
		pq2 = priority_queue<node>();
		// input
		cin >> N >> M >> K >> A >> B;
		A--;
		B--;
		for (int i = 0; i < N; i++) {
			cin >> ai[i];
		}
		for (int j = 0; j < M; j++) {
			cin >> bj[j];
		}
		for (int k = 0; k < K; k++) {
			cin >> tk[k];
			pq.push({ k,tk[k] });
		}

		// solve
		int now_t = pq.top().tk;	// 시간.


		while (!pq.empty()) {	// 접수 창고 이용
			node now = pq.top();
			pq.pop();

			if (now_t != now.tk) {	// 이용중 시간 갱신.
				int diff = now.tk - now_t;
				for (int i = 0; i < N; i++) {
					if (A_now[i].tk != 0) {
						A_now[i].tk -= diff;
						if (A_now[i].tk <= 0) {	// 사용 종료
							pq2.push({ A_now[i].idx,now.tk + A_now[i].tk,i }); // 번호, 끝난시간, 사용창구
							A_now[i].tk = 0;
						}
					}
				}
			}

			bool flag = false;
			for (int i = 0; i < N; i++) {	// 접수하기
				if (A_now[i].tk != 0) continue;	// 이용중이라면 스킵
				// i번 접수창고 이용
				A_now[i].tk = ai[i];	
				A_now[i].idx = now.idx;
				if (i == A) {
					DAT_A[now.idx] = 1;
				}
				flag = true;
				break;
			}
			now_t = now.tk;
			if (!flag) {	// 꽉차있다면 시간 1추가해서 다시
				now.tk++;
				pq.push(now);
			}

		}

		for (int i = 0; i < N; i++) {
			if (A_now[i].tk != 0) {
				pq2.push({ A_now[i].idx,now_t + A_now[i].tk,i });
			}
		}

		now_t = pq2.top().tk;	// 시간.

		while (!pq2.empty()) {	// 접수 창고 이용
			node now = pq2.top();
			pq2.pop();

			if (now_t != now.tk) {	// 이용중 시간 갱신.
				int diff = now.tk - now_t;
				for (int i = 0; i < M; i++) {
					if (B_now[i].tk != 0) B_now[i].tk -= diff;
					if (B_now[i].tk <= 0) {
						B_now[i].tk = 0;
					}
				}
			}

			bool flag = false;

			for (int i = 0; i < M; i++) {
				if (B_now[i].tk != 0) continue;
				B_now[i].tk = bj[i];
				B_now[i].idx = now.idx;
				if (i == B) {
					DAT_B[now.idx] = 1;
				}
				flag = true;
				break;
			}
			now_t = now.tk;
			if (!flag) {
				now.tk++;
				now.waiting++;
				pq2.push(now);
			}

		}

		int cnt = 0;
		for (int i = 0; i < K; i++) {
			if (DAT_A[i] == 1 && DAT_B[i] == 1)
			{
				cnt += (i + 1);
			}
		}

		// output
		if (cnt == 0)cnt = -1;
		cout << "#" << tc << ' ' << cnt << '\n';

	}



	return 0;
}