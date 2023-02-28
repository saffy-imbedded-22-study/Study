#include<iostream>
#include<cstring>
using namespace std;
int N;

int oper[4];
int visited[4];
int number[12];
int maxnum;
int minnum;

void dfs(int now, int sum) {

	if (now == N) {
		if (maxnum < sum) {
			maxnum = sum;
		}
		if (minnum > sum) {
			minnum = sum;
		}
		return;
	}


	for (int i = 0; i < 4; i++) {

		if (visited[i] == oper[i])continue;

		int resum = sum;

		if (i == 0) {
			sum += number[now];
		}

		if (i == 1) {
			sum -= number[now];
		}

		if (i == 2) {
			sum *= number[now];
		}

		if (i == 3) {
			sum /= number[now];
		}
		visited[i]++;
		dfs(now + 1, sum);
		visited[i]--;
		sum = resum;

	}

}




int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {
		cin >> N;
		memset(visited, 0, sizeof(visited));
		memset(number, 0, sizeof(number));
		maxnum = -21e8;
		minnum = 21e8;

		for (int i = 0; i < 4; i++) {
			cin >> oper[i];
		}

		for (int i = 0; i < N; i++) {
			cin >> number[i];
		}

		int summ = number[0];
		dfs(1, summ);

		cout << "#" << te << " " << maxnum - minnum << endl;
	}
	return 0;
}