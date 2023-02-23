#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
struct Node {
    int y, x;
    bool gongsa;
};
int N, K;
int MAP[10][10];
vector<Node>v;
int maxPath;
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
int visited[10][10];

int input() {
    int Max = 0;
    cin >> N >> K;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> MAP[y][x];
            Max = max(Max, MAP[y][x]);
        }
    }
    return Max;
}

void findSt(int H) {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (MAP[y][x] == H) {
                v.push_back({ y,x,false });
            }
        }
    }
}

void DFS(Node now, int result) {

    //recursive
    for (int i = 0; i < 4; i++) {
        int ny = now.y + ydir[i];
        int nx = now.x + xdir[i];
        int gong = now.gongsa;
        int tmp = MAP[ny][nx];

        if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;
        if (visited[ny][nx] != 0) continue;
        if (gong && MAP[ny][nx] >= MAP[now.y][now.x]) continue;
        if (!gong && MAP[ny][nx] >= MAP[now.y][now.x]) {
            //공사 안했으면 K만큼 현재보다 1만큼만 작게 만들기!
            if (K + MAP[now.y][now.x] > MAP[ny][nx]) {
                gong = true;
                MAP[ny][nx] = MAP[now.y][now.x] - 1;
            }
            else {
                //공사를 했는데 안되는 경우는 버리기
                continue;
            }
        }

        Node next = { ny,nx,gong };
        maxPath = max(maxPath, result + 1);
        visited[ny][nx] = 1;
        DFS(next, result + 1);
        visited[ny][nx] = 0;
        MAP[ny][nx] = tmp;

    }
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        maxPath = 0;

        v = vector<Node>();
        int H = input();
        findSt(H);//시작위치 v에 저장

        int size = v.size();
        for (int i = 0; i < size; i++) {
            visited[v[i].y][v[i].x] = 1;
            DFS(v[i], 1);//DFS하면서 maxPath갱신
            visited[v[i].y][v[i].x] = 0;
        }
        cout << "#" << tc << " " << maxPath << endl;
    }

    return 0;
}