#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

struct cell {
    int y;
    int x;
    int rest;
    int life;
};
struct cmp {
    bool operator()(cell left, cell right) {
        if (left.life < right.life) return true;
        if (left.life > right.life) return false;
        return false;
    }
};
int visited[1000][1000];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
int N, M;//초기 세로 가로
int TimeLimit;
int Time;
int cnt;
priority_queue<cell, vector<cell>, cmp> pq;
vector<cell> v;

void hour() {
    int size = v.size();
    for (int i = size - 1; i >= 0; i--) {
        v[i].rest++;
        cell a = v[i];

        if (a.rest == a.life + 2) pq.push(a);
        if (a.rest == a.life * 2 + 1) {
            v.erase(v.begin() + i);
            cnt--;
        }
    }
}
void grow() {
    while (!pq.empty()) {
        cell now = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dir[i][0];
            int nx = now.x + dir[i][1];
            if (visited[ny][nx] >= 1) continue;
            visited[ny][nx] = now.life;
            v.push_back({ ny,nx,1,now.life });
            cnt++;
        }
    }
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        memset(visited, 0, sizeof(visited));
        v.clear();
        Time = 0;
        cnt = 0;

        cin >> N >> M >> TimeLimit;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int life;
                cin >> life;
                if (life != 0) {
                    int y = 500 + i;
                    int x = 500 + j;
                    visited[y][x] = life;
                    v.push_back({ y,x,1,life });
                    cnt++;
                }
            }
        }
        while (Time <= TimeLimit) {
            if (Time != 0) hour();
            grow();
            Time++;
        }
        cout << "#" << tc << " " << cnt << endl;
    }
    return 0;
}