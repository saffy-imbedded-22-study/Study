#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
 
int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };
 
int N;  // 도시 크기
int M;  // 지불 가능 비용
int Map[20][20]; // 지도 저장
int Max; // 최대값
 
struct node {
    int y, x;
};
 
int bfs(node start) {
    queue<node> qnow;
    qnow.push(start);
 
    int visited[20][20] = { 0 };
    visited[start.y][start.x] = 1;
 
    int cnt = 0;
    if (Map[start.y][start.x] == 1)cnt++;   // 시작점 확인
 
    int cnt_best=1; // 최소 1개의 집 존재

    for (int k = 2;k <= N+1;k++) {  // N이 짝수일때 N+1까지 봐야 모든칸 확인 가능
        int len = qnow.size();  // 현재 존재하는 qnow 크기만큼만 반복 후 k 증가
 
        for (int n = 0; n < len;n++) {
            node now = qnow.front();
            qnow.pop();
 
            for (int i = 0;i < 4;i++) {
                int dy = now.y + diry[i];
                int dx = now.x + dirx[i];
                if (dy >= N || dy < 0 || dx >= N || dx < 0)continue;
                if (visited[dy][dx])continue;
                visited[dy][dx] = 1;
                if (Map[dy][dx] == 1)cnt++;
                qnow.push({ dy,dx });
 
            }
        }
        int cost = k * k + (k - 1) * (k - 1);   
        if (cnt * M >= cost)    // cost보다 클 경우 cnt_best 갱신
        {
            cnt_best = cnt; // cost는 항상 증가하기에 대소비교 필요X
        }
    }
 
    return cnt_best;
}
 
 
 
int main() {
    int T;
    cin >> T;
 
    for (int t = 1;t <= T;t++) {
        //reset
        memset(Map, 0, sizeof(Map));
        Max = 0;
 
        //input
        cin >> N >> M;
        for (int i = 0;i < N;i++) {
            for (int j = 0;j < N;j++) {
                cin >> Map[i][j];
            }
        }
 
        //solve
         
        for (int i = 0;i < N;i++) {
            for (int j = 0;j < N;j++) {
                node now = { i,j };
                Max = max(Max, bfs(now));   // 모든 칸에 대해 BFS
            }
        }
 
        //output
        cout << "#" << t << ' ' << Max << '\n';
    }
 
    return 0;
}