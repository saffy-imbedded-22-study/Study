#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
/*
1
4
-1000 0 3 5
1000 0 2 3
0 1000 1 7
0 -1000 0 9
*/
struct atom {
    int y;
    int x;
    int dir;
    int e;
    int alive;
};
int N;
int direct[4][2] = { -1,0,1,0,0,-1,0,1 };//상 하 좌 우
int map[4001][4001];
int energy;
int cnt;
vector<atom> v;

void move() {
    for (int i = 0; i < v.size(); i++) {
        atom now = v[i];
        
        if (now.alive == 0) continue;

        map[now.y][now.x]--;
        int ny = now.y + direct[now.dir][0];
        int nx = now.x + direct[now.dir][1];

        if (ny < 0 || nx < 0 || ny >= 4001 || nx >= 4001) {
            v[i].alive = 0;
            cnt--;
            continue;
        }

        v[i].y = ny;
        v[i].x = nx;
        map[ny][nx]++;
    }
}
void explode() {
    for (int i = 0; i < v.size(); i++) {
        atom now = v[i];
        if (now.alive == 0) continue;
        if (map[now.y][now.x] == 1) continue;

        // 2개이상 있을 때
        for (int j = i; j < v.size(); j++) {
            atom next = v[j];
            if (next.alive == 0) continue;
            if (now.y == next.y && now.x == next.x) {
                energy += next.e;
                v[j].alive = 0;
                cnt--;
            }
        }

        map[now.y][now.x] = 0;
    }
}
void run() {
    while (cnt > 1) {
        move();
        explode();
    }
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        memset(map, 0, sizeof(map));
        v.clear();
        energy = 0;
        cnt = 0;

        cin >> N;
        for (int i = 0; i < N; i++) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            int y = (1000 - b) * 2;
            int x = (a + 1000) * 2;

            v.push_back({ y,x,c,d,1 });
            cnt++;
            map[y][x]++;
        }
        run();
        cout << "#" << tc << " " << energy << endl;
    }
    return 0;
}