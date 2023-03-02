#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int N;
string target;
string File[100];
string targetList[50];

void input() {
	cin >> N;
	cin >> target;
	for (int x = 0; x < N; x++) {
		cin >> File[x];
	}
}

void makeList(string target) {
	targetList[0] = target;
	int len = target.length();
	for (int x = 'a'; x < 'z'; x++) {
		int key = x - 'a' + 1;
		string tmp="";
		
		for (int i = 0; i < len; i++) {
			char let = 'A'+((target[i] - 'A' + key) % 26);
			tmp += let;
		}
		targetList[key] = tmp;
	}
}

string solv() {
	int keyMin = 26;
	int Len =target.length();
	for (int x = 0; x < N; x++) {
		if (Len != File[x].length()) continue;

		for (int key = 1; key < 26; key++)
			if (targetList[key] == File[x])
				keyMin = min(keyMin, key);
	}
	return targetList[keyMin];
}

int main() {
	input();
	makeList(target);//key값에 따른 파일명 모두 저장
	cout << solv();
	return 0;
}