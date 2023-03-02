#include <iostream>
#include <algorithm>
using namespace std;

int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {

		int day, month, threemonth, year;
		cin >> day >> month >> threemonth >> year;

		int planarr[16] = { 0 };
		for (int i = 4; i < 16; i++) {
			cin >> planarr[i];
		}
		int minmoney[16] = { 0 };

		for (int i = 4; i < 16; i++) {
			minmoney[i] = min({ minmoney[i - 1] + planarr[i] * day, minmoney[i - 1] + month, minmoney[i - 3] + threemonth });
		}

		if (minmoney[15] > year) {
			cout << "#" << te << " " << year << endl;
		}
		else {
			cout << "#" << te << " " << minmoney[15] << endl;
		}
	}
	return 0;
}