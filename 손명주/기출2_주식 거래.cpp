#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
1
300 60
3 8
135 120 111 144 170 170 171 173 169
156 150 144 144 144 150 150 150 147
195 180 165 150 141 172 185 190 159
*/
int ms;
int ma;
int N, L;
int hist[15][15];
int sum;
struct stock {
    int n;
    int price;
    int rise;
};
bool cmp(stock left, stock right) {
    if (left.rise > right.rise) return true;
    if (left.rise < right.rise) return false;
    if (left.price < right.price) return true;
    if (left.price > right.price) return false;
    return false;
}
void buy(int month) {
    vector<stock> v;

    for (int i = 0; i < N; i++) {
        int now = hist[i][month];
        int next = hist[i][month + 1];
        if (next - now <= 0) continue;
        v.push_back({ i,now,next - now });
    }

    sort(v.begin(), v.end(), cmp);
    int plus = 0;

    for (int i = 0; i < v.size(); i++) {
        int num = ms / v[i].price;
        if (num <= 0) continue;
        ms -= num * v[i].price;
        sum += num * v[i].rise;
        plus += num * (v[i].price + v[i].rise);
    }
    ms += plus;
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> ms >> ma;
        cin >> N >> L;
        sum = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < L + 1; j++) {
                cin >> hist[i][j];
            }
        }

        for (int m = 0; m < L + 1; m++) {
            if (m > 0) ms += ma;
            if (m < L) buy(m);
        }

        cout << "#" << tc << " " << sum << endl;
    }

    return 0;
}