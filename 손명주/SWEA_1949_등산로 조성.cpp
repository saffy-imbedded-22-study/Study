#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
/*
1
4 4
8 3 9 5
4 6 8 5
8 1 5 1
4 9 5 5
*/
struct node {
    int y;
    int x;
};
int N;
int K; //√÷¥Î ±Ì¿Ã
int map[10][10];
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
int go;
int ans;
int cut;
int visited[10][10];
vector<node> top;

void run(int y, int x) {
    if (go > ans) ans = go;

    for (int i = 0; i < 4; i++) {
        int ny = y + ydir[i];
        int nx = x + xdir[i];
        if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
        if (visited[ny][nx] == 1) continue;
        if (map[ny][nx] >= map[y][x])
        {
            if (cut == 0 && map[ny][nx] < map[y][x] + K) {
                cut++;
                go++;
                int temp = map[ny][nx];
                map[ny][nx] = map[y][x] - 1;
                visited[ny][nx] = 1;

                run(ny, nx);

                cut--;
                go--;
                map[ny][nx] = temp;
                visited[ny][nx] = 0;
            }
        }
        else
        {
            go++;
            visited[ny][nx] = 1;
            run(ny, nx);
            go--;
            visited[ny][nx] = 0;
        }
    }
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        memset(map, 0, sizeof(map));
        cin >> N >> K;

        int max = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
                if (max < map[i][j]) {
                    max = map[i][j];
                    top.clear();
                    top.push_back({ i,j });
                }
                else if (max == map[i][j]) {
                    top.push_back({ i,j });
                }
            }
        }
        ans = 0;
        for (int i = 0; i < top.size(); i++) {
            memset(visited, 0, sizeof(visited));
            go = 1;
            cut = 0;
            visited[top[i].y][top[i].x] = 1;
            run(top[i].y, top[i].x);
        }
        cout << "#" << tc << " " << ans << endl;
    }
    return 0;
}