/*
내리막길 : 연료 소모 x
오르막길 : 높이 차 x2
평지 : 연료 1

출발지 (1,1)
조난자 (N,N)
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int N; // 지도 크기
int M; // 터널 수 최대 30

int diry[4] = {-1, 1, 0, 0};
int dirx[4] = {0, 0, -1, 1};

struct turnel
{
    int y, x; // 목적지 위치
    int cost; // 소모 비용
};

struct node
{
    int y, x; // 현재 위치
    int fuel; // 누적 연료 값

    bool operator<(node next) const
    { // 연료 적은순 저장 (PQ)
        return fuel > next.fuel;
    }
};

vector<turnel> turnelMap[31][31]; // 터널 정보 저장
int Map[31][31];                  // 높이 저장
int costMap[31][31];              // 연료 누적 저장

int main()
{

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        // reset
        memset(turnelMap, 0, sizeof(turnelMap)); // 되나??
        memset(Map, 0, sizeof(Map));
        memset(costMap, 0, sizeof(costMap));

        // input
        cin >> N >> M;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> Map[i][j];
            }
        }
        for (int i = 0; i < M; i++)
        {
            int ay, ax, by, bx, c;
            cin >> ay >> ax >> by >> bx >> c;
            turnelMap[ay - 1][ax - 1].push_back({by - 1, bx - 1, c}); // 터널 위치에 목적지 위치, 비용 정보 저장
            turnelMap[by - 1][bx - 1].push_back({ay - 1, ax - 1, c}); // 쌍방향 이동 가능
        }

        // solve

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                costMap[i][j] = 21e8; // 최대값으로 초기화
            }
        }
        priority_queue<node> pq;
        pq.push({0, 0, 0});
        costMap[0][0] = 0;
        int ans = 0;

        while (!pq.empty())
        {
            node now = pq.top();
            pq.pop();
            if (now.y == N - 1 && now.x == N - 1)
            { // 목적지 도착하면 break
                ans = now.fuel;
                break;
            }

            int nowheight = Map[now.y][now.x]; // 현재 높이

            for (int i = 0; i < 4; i++)
            {
                int dy = now.y + diry[i];
                int dx = now.x + dirx[i];
                if (dy >= N || dy < 0 || dx >= N || dx < 0)
                    continue;

                int nextcost; // 이동 비용
                if (nowheight > Map[dy][dx])
                {
                    nextcost = 0;
                }
                else if (nowheight < Map[dy][dx])
                {
                    nextcost = (Map[dy][dx] - nowheight) * 2;
                }
                else
                {
                    nextcost = 1;
                }

                if (costMap[dy][dx] <= now.fuel + nextcost)
                    continue; // 왔던곳일 경우 전보다 비용이 적어야만 진행
                costMap[dy][dx] = now.fuel + nextcost;
                pq.push({dy, dx, costMap[dy][dx]});
            }

            for (int i = 0; i < turnelMap[now.y][now.x].size(); i++)
            { // 터널 이용할 경우
                int dy = turnelMap[now.y][now.x][i].y;
                int dx = turnelMap[now.y][now.x][i].x;
                if (costMap[dy][dx] <= now.fuel + turnelMap[now.y][now.x][i].cost)
                    continue; // 왔던곳일 경우 전보다 비용이 적어야만 진행
                costMap[dy][dx] = now.fuel + turnelMap[now.y][now.x][i].cost;
                pq.push({dy, dx, costMap[dy][dx]});
            }
        }

        // output
        cout << "#" << tc << ' ' << ans << '\n';
    }
    return 0;
}