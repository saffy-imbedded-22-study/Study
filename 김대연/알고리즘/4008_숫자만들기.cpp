#include <iostream>
#include <cstring>
using namespace std;

int N;
int num[12];
int oper[4];
int Sum, Min_num, Max_num;

int calc(int a, int b, int op) {    //연산
	switch (op) {
	case 0:
		return a + b;
	case 1:
		return a - b;
	case 2:
		return a * b;
	case 3:
		return a / b;
	}
}

void dfs(int a) {
	if (a == N) {
		if (Min_num > Sum) {
			Min_num = Sum;
		}
		if (Max_num < Sum) {
			Max_num = Sum;
		}
		return;
	}

	for (int i = 0;i < 4;i++) {
		if (oper[i] > 0) {  //남은 operator가 1개 이상일 경우 실행
			oper[i]--;
			
			int save_n = Sum;   //계산 전 값 저장

			Sum = calc(Sum, num[a], i);
			
			dfs(a + 1);

			oper[i]++;
			Sum = save_n;       //계산 후 되돌려줌
		}

	}

}

int main()
{
	int T;
	cin >> T;
	for (int t = 1;t <= T;t++) {
		//reset
		memset(num, 0, sizeof(num));
		Min_num = 21e8;
		Max_num = -21e8;

		//input
		cin >> N;
		for (int i = 0;i < 4;i++) {
			cin >> oper[i];
		}
		for (int i = 0;i < N;i++) {
			cin >> num[i];
		}
		Sum = num[0];

		//solve
		dfs(1);

		//output
		cout << '#' << t << ' ' << Max_num - Min_num << '\n';
	}

	return 0;
}

