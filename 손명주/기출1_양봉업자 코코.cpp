#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
/*
3 5
30 41 15 5 37
12 18 44 19 45
16 7 9 42 5
*/
int N, M;
int bee[15][15];
int visited[15][15];

int ydir[2][6] = {
    -1,1,0,0,-1,-1, // 0 2 3  1 4 5
    -1,1,0,0,1,1    // 1 2 3  0 4 5
};
int xdir[6] = { 0,0,-1,1,-1,1 };

int sum;
int local;

int tri(int y, int x) {
    int round[6];
    for (int i = 0; i < 6; i++) {
        int ny = y + ydir[x % 2][i];
        int nx = x + xdir[i];
        if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
            round[i] = 0;
            continue;
        }
        round[i] = bee[ny][nx];
    }
    int tri1, tri2;
    if (x % 2 == 0) {
        tri1 = round[0] + round[2] + round[3];
        tri2 = round[1] + round[4] + round[5];
    }
    else {
        tri1 = round[1] + round[2] + round[3];
        tri2 = round[0] + round[4] + round[5];
    }
    return bee[y][x] + max(tri1, tri2);
}
void run(int y, int x, int level) {
    if (level == 3) {
        if (local < sum) local = sum;
        return;
    }

    for (int i = 0; i < 6; i++) {
        int ny = y + ydir[x % 2][i];
        int nx = x + xdir[i];
        if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
        if (visited[ny][nx] == 1) continue;
        sum += bee[ny][nx];
        visited[ny][nx] = 1;
        run(ny, nx, level + 1);
        visited[ny][nx] = 0;
        sum -= bee[ny][nx];
    }
}
int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> bee[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            memset(visited, 0, sizeof(visited));
            sum = bee[i][j];
            visited[i][j] = 1;
            local = tri(i, j);

            run(i, j, 0);

            int temp = local;
            if (ans < temp)
                ans = temp;
        }
    }
    cout << ans;
    return 0;
}