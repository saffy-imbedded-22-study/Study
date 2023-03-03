#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int N, M;
int Map[50][50];

struct node {
	int y, x;
};
node Start;
node End;





int main() {
	cin >> N >> M;

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 2) {
				Start = { i,j };
			}
			else if (Map[i][j] == 3) {
				End = { i,j };
			}
		}
	}




	return 0;
}