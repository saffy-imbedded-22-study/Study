#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int N, M; //세로 가로 크기
int sy, sx; //시작 위치
int T;//시간
int map[50][50];
int visited[50][50];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 }; //상 하 좌 우
struct node {
    int y;
    int x;
};
int out[8][4] = {
    0,0,0,0,
    1,1,1,1,
    1,1,0,0,
    0,0,1,1,
    1,0,0,1,
    0,1,0,1,
    0,1,1,0,
    1,0,1,0
};
int in[8][4] = {
    0,0,0,0,
    1,1,1,1,
    1,1,0,0,
    0,0,1,1,
    0,1,1,0,
    1,0,1,0,
    1,0,0,1,
    0,1,0,1
};

int move(int y, int x) {
    memset(visited, 0, sizeof(visited));
    queue<node> q;
    q.push({ y,x });
    visited[y][x] = 1;
    int time = 1;
    int cnt = 1;

    while (true) {
        int size = q.size();
        if (size == 0 || time == T) return cnt;

        for (int j = 0; j < size; j++)
        {
            node now = q.front();
            q.pop();
            int from = map[now.y][now.x];

            for (int i = 0; i < 4; i++) {
                int ny = now.y + dir[i][0];
                int nx = now.x + dir[i][1];
                if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
                if (visited[ny][nx] == 1) continue;
                int to = map[ny][nx];
                if (out[from][i] == 0 || in[to][i] == 0) continue;
                visited[ny][nx] = 1;
                cnt++;
                q.push({ ny,nx });
            }
        }
        time++;
    }

}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        memset(map, 0, sizeof(map));
        cin >> N >> M >> sy >> sx >> T;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> map[i][j];
            }
        }

        cout << "#" << tc << " " << move(sy, sx) << endl;
        
    }
    return 0;
}