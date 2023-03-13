#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
/*
1
28 11
8E0B7DD258D4122317E3ADBFEA99
*/
int N;
int nth;
string input;
vector<long long> v;
bool cmp(long long left, long long right) {
    if (left > right) return true;
    if (left < right) return false;
    return false;
}
long long num(string hex) {
    long long res = 0;
    long long pow = 1;
    for (int i = hex.size() - 1; i >= 0; i--) {
        char now = hex[i];
        if ('0' <= now && now <= '9') res += pow * (now - '0');
        else if ('A' <= now && now <= 'F') res += pow * (now - 'A' + 10);
        pow *= 16;
    }
    return res;
}
void make() {
    for (int i = 0; i < N; i++) {
        string password = input.substr(i, N / 4);
        v.push_back({ num(password) });
    }
    sort(v.begin(), v.end(), cmp);
}
int find(int k) {
    int cnt = 1;
    for (int i = 1; i < v.size(); i++) {
        int now = v[i];
        int bef = v[i - 1];
        if (now == bef) continue;;
        cnt++;
        if (cnt == k) return now;
    }
    return v[0];
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> N >> nth;
        cin >> input;
        v.clear();

        input += input.substr(0, N / 4 - 1);
        make();

        cout << "#" << tc << " " << find(nth) << endl;
    }
    return 0;
}