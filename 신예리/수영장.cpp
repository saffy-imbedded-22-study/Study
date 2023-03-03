#include<iostream>
#include<algorithm>
using namespace std;

int month[13];
int sum;
int cost[4];//1일, 1달, 3달, 1년
int mincost;

void dfs(int now, int plancost) {

	if (now >= 12) {
		mincost = min(mincost, plancost);
		return;
	}

	for (int i = 0; i < 3; i++) {

		if (i == 0) {
			plancost += month[now] * cost[i];
			dfs(now + 1, plancost);
			plancost -= month[now] * cost[i];
		}
		if (i == 1) {
			plancost += cost[i];
			dfs(now + 1, plancost);
			plancost -= cost[i];
		}
		if (i == 2) {
			plancost += cost[i];
			dfs(now + 3, plancost);
			plancost -= cost[i];
		}

	}
}



int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {
		mincost = 21e8;

		for (int i = 0; i < 4; i++) {
			cin >> cost[i];
		}

		for (int i = 0; i < 12; i++) {
			cin >> month[i];
		}

		dfs(0, 0);

		if (cost[3] < mincost) {
			cout << "#" << te << " " << cost[3] << endl;
		}
		else cout << "#" << te << " " << mincost << endl;
	}
	return 0;
}


//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//int main() {
//
//	int test;
//	cin >> test;
//
//	for (int te = 1; te <= test; te++) {
//
//		int day, month, threemonth, year;
//		cin >> day >> month >> threemonth >> year;
//
//		int planarr[16] = { 0 };
//		for (int i = 4; i < 16; i++) {
//			cin >> planarr[i];
//		}
//		int minmoney[16] = { 0 };
//
//		for (int i = 4; i < 16; i++) {
//			minmoney[i] = min({ minmoney[i - 1] + planarr[i] * day, minmoney[i - 1] + month, minmoney[i - 3] + threemonth });
//		}
//
//		if (minmoney[15] > year) {
//			cout << "#" << te << " " << year << endl;
//		}
//		else {
//			cout << "#" << te << " " << minmoney[15] << endl;
//		}
//	}
//	return 0;
//}