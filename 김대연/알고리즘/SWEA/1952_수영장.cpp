#include <iostream>
#include<cstring>
using namespace std;

int price[4];
int month[12];
int total;
int sum;
void dfs(int k) {
	if (k >= 12) {
		if (sum < total) {	//합계가 1년 이용권보다 싼지 비교
			total = sum;
		}
		return;
	}
	
	if (month[k] == 0) {	//그 달 이용일이 0일이면 다음달로 넘어감
		dfs(k + 1);
	}
	else {
		if (month[k] * price[0] > price[1]) { //일일 이용권과 한달 이용권 중 싼 값 더해줌
			sum += price[1];
			dfs(k + 1);
			sum -= price[1];
		}
		else {
			sum += month[k] * price[0];
			dfs(k + 1);
			sum -= month[k] * price[0];
		}

		sum += price[2];	//3달이용권 이용할 경우
		dfs(k + 3);
		sum -= price[2];

	}
}


int main()
{
	int T;
	cin >> T;

	for (int t = 1;t <= T;t++) {
		//reset
		memset(month, 0, sizeof(month));
		memset(price, 0, sizeof(price));
		sum = 0;

		//input
		for (int i = 0;i < 4;i++) {
			cin >> price[i];
		}
		for (int i = 0;i < 12;i++) {
			cin >> month[i];
		}
		total = price[3];

		//solve

		dfs(0);

		//output
		cout << "#" << t << ' ' << total << '\n';

	}


	return 0;
}

