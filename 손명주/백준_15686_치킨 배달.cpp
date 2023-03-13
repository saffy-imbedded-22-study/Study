#include <iostream>
#include <vector>
using namespace std;

int N, M;
struct node {
    int y;
    int x;
};
vector<node> chick;
vector<node> house;
int dist[15][100]; //치킨집 - 집 거리 저장
int chosen[15];
int ans;

//저는 거리를 따로 저장안하면 같은 걸 여러번 계산한다고 생각돼서 이렇게 했네요
void calcdist() {
    for (int i = 0; i < chick.size(); i++) {
        for (int j = 0; j < house.size(); j++) {
            int d = 0;
            d += abs(chick[i].y - house[j].y);
            d += abs(chick[i].x - house[j].x);
            dist[i][j] = d;
        }
    }
}
int chickdist() {
    int sum = 0;
    for (int i = 0; i < house.size(); i++) {
        int near = 99999;
        for (int j = 0; j < chick.size(); j++) {
            if (chosen[j] == 0) continue;
            if (near > dist[j][i]) near = dist[j][i];
        }
        sum += near;
    }
    return sum;
}
void pick(int lev, int ind) {
    if (lev == M) {
        int res = chickdist();
        if (ans > res) ans = res;
        return;
    }
    for (int i = ind; i < chick.size(); i++) {
        if (chosen[i] == 1) continue;
        chosen[i] = 1;
        pick(lev + 1, i + 1);
        chosen[i] = 0;
    }
}
int main() {
    cin >> N >> M;
    ans = 9999999;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            if (a == 1) house.push_back({ i,j });
            else if (a == 2) chick.push_back({ i,j });
        }
    }
    calcdist();
    pick(0,0);

    cout << ans;
    return 0;
}