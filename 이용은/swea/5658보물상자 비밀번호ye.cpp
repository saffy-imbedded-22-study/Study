#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int N, K;
vector<string>v;
bool cmp(string left, string right) {
	if (left > right)
		return true;
	if (left < right)
		return false;
	return false;
}

string input() {
	cin >> N >> K;
	string tmp;
	cin >> tmp;
	string re = tmp + tmp;
	return re;
}

int sdf(char ch) {
	
	if ('0' <= ch && ch <= '9') {
		return  ch - '0';
	}
	else return ch - 'A' + 10;
}

int stToin(string str) {
	int result =0;
	int t = 0;
	int Len = N / 4;

	for (int i = Len - 1; i >= 0; i--) {
		int tmp = sdf(str[t]);
		result +=tmp << 4*i;
		t++;
	}
	return result;
}

void parsing(string str) {
	int Len = N / 4;
	for (int x = 0; x < N; x++) {
		string tmp = str.substr(x, Len);
		int size = v.size();
		int flag = 0;
		for (int i = 0; i < size; i++) {
			if (v[i] == tmp) {
				flag = 1;
				break;
			}
		}
		if(flag==0)
			v.push_back(tmp);
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		v = vector<string>();
		string str = input(); //inputx2
		parsing(str);
		sort(v.begin(), v.end(), cmp);
		
		cout <<"#" << tc<<" " << stToin(v[K - 1]) << endl;
	}
	return 0;
}