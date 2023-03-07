#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int N;	// 종목	수
int L;	// 기간
int Ms;	// 초기 돈
int Ma;	// 매달 돈
int Map[15][16];	// 매 월 금액
int DAT[15][15];	// 차액
int Buy[15];		// 구매 수량
int NowMs;			// 지금 돈
int BestBuy[15];	// 최종 구매 수량
int Bestcost;		// 최고이득
int cost;			// 현재 이득

void dfs(int month, int money) {

	bool buyflag = false;
	//if (month == 5)cout << money << ' ' << cost << '\n';
	for (int i = 0;i < N;i++) {
		if (Map[i][month] > money) continue;
		if (DAT[i][month] <= 0)continue;

		Buy[i]++;
		buyflag = true;
		cost += DAT[i][month];
		dfs(month, money - Map[i][month]);
		Buy[i]--;
		cost -= DAT[i][month];
	}
	if (!buyflag) {	//살수있는게 없으면 끝
		if (Bestcost < cost) {
			Bestcost = cost;
			for (int i = 0;i < N;i++) {
				BestBuy[i] = Buy[i];
			}
			NowMs = money;
		}
	}

}


int main() {
	int T;
	cin >> T;
	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(Map, 0, sizeof(Map));
		memset(DAT, 0, sizeof(DAT));

		// input
		cin >> Ms >> Ma;
		cin >> N >> L;

		for (int i = 0;i < N;i++) {
			for (int j = 0;j < L + 1;j++) {
				cin >> Map[i][j];
			}
		}
		// solve
		for (int i = 0;i < N;i++)
		{
			for (int j = 0;j < L;j++) {
				DAT[i][j] = Map[i][j + 1] - Map[i][j];
			}
		}


		NowMs = Ms;

		for (int i = 0;i < L;i++) {

			Bestcost = 0;
			dfs(i, NowMs);
			//cout << NowMs << '\n';

			for (int j = 0;j < N;j++) {			// 산거 다음달에 판매
				NowMs += Map[j][i + 1] * BestBuy[j];
				BestBuy[j] = 0;
			}

			NowMs += Ma;	// 월급 추가


		}
		NowMs = NowMs - Ma * L - Ms;

		// output
		cout << "#" << tc << ' ' << NowMs << '\n';
	}



	return 0;
}