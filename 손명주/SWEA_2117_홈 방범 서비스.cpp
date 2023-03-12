#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
/*
1
8 3
0 0 0 0 0 1 0 0
0 1 0 1 0 0 0 1
0 0 0 0 0 0 0 0
0 0 0 1 0 1 0 0
0 0 1 1 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 1 0 1 0
1 0 0 0 0 0 0 0
*/
int map[20][20];
int visited[20][20];
int N;
int perhouse;
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
struct node {
    int y;
    int x;
};

int fill(int y, int x) {

    int range = 0;
    int house = 0;
    int max = 0;

    queue<node> q;
    memset(visited, 0, sizeof(visited));
    visited[y][x] = 1;
    if (map[y][x] == 1) house++;
    q.push({y,x});

    while (true) {
        range++;

        int cost = range * range + (range - 1) * (range - 1);
        if (perhouse * house - cost >= 0) {
            if (max < house) max = house;
        }

        int size = q.size();
        if (size == 0) break;

        for (int p = 0; p < size; p++)
        {
            node now = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int ny = now.y + dir[i][0];
                int nx = now.x + dir[i][1];
                if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
                if (visited[ny][nx] == 1) continue;
                visited[ny][nx] = 1;
                if (map[ny][nx] == 1) house++;
                q.push({ ny,nx });
            }

        }

    }
    return max;
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        memset(map, 0, sizeof(map));
        int ans = 0;
        cin >> N >> perhouse;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int res = fill(i, j);
                if (ans < res) ans = res;
            }
        }

        cout << "#" << tc << " " << ans << endl;
    }
    return 0;
}