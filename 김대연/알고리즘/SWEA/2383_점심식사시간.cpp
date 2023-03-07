/*
1. 모든 사람과 계단 사이 거리 구하기.
2. dfs 이용해서 계단 이용 가능한 모든 조합 구하기. (1번 사람- 1번계단, 2번사람- 1번 계단, 3번사람 - 2번 계단, ...)
3. 각 경우에 대해 pq 이용하여 모든 사람이 계단 내려오는데 걸리는 시간 구하기.

*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int N; // 방 한변 길이
int Map[11][11];
int Dist[11][2]; // 계단 2개에 대한 거리
int ans;
int P; // 사람 수

struct node
{ // 사람 정보
    int y, x;
};
vector<node> people;

struct stair
{ // 계단 정보
    int y, x;
    int height;
};
vector<stair> stairs;

struct dfsnode
{
    int stairnum; // 어떤 계단 이용하는지
    int dist;     // 계단까지 남은 거리     -> 0이 아니라면 이동중
    int t;        // 현재 시각
    int walking;  // 계단 남은 수           -> 0이 아니라면 계단 이용중

    bool operator<(dfsnode next) const
    {
        if (t > next.t)
            return true; // 시간 빠른순 정렬 -> 그래야 현재 시간꺼 처리 가능
        if (t < next.t)
            return false;
        if (walking < next.walking)
            return true; // 내림차순 정렬 -> 그래야 내려오던거 내려오고 대기중인 애들 처리가능.
        if (walking > next.walking)
            return false;
        return dist > next.dist; // 거리 가까운 순 처리
    }
};

vector<dfsnode> v;

void CheckDist()
{ // 모든 거리 계산

    for (int i = 0; i < people.size(); i++)
    {
        int y = people[i].y;
        int x = people[i].x;

        for (int j = 0; j < 2; j++)
        {
            int sty = stairs[j].y;
            int stx = stairs[j].x;

            Dist[i][j] = abs(y - sty) + abs(x - stx); // 사람과 계단 거리 계산
        }
    }
}

int solve()
{
    priority_queue<dfsnode> pq;

    for (int i = 0; i < v.size(); i++)
    {
        pq.push(v[i]);
    }

    int num[2] = {0}; // 계단 이용자 수
    int Time = 0;

    while (!pq.empty())
    {
        int timecnt = pq.size();    // 현재 pq에 들은 정보들만큼 실행 후 시간 증가
        Time++;
        if (Time > ans)
        { // 지금까지 구한 값보다 크면 종료
            return 21e8;
        }
        for (int i = 0; i < timecnt; i++)
        {
            dfsnode now = pq.top();
            pq.pop();

            if (now.dist > 0)
            {               // 계단으로 가는중
                now.dist--; // 남은 거리 - 1
                now.t++;
                pq.push(now);
            }
            else if (now.dist == 0)
            {
                int stairnum = now.stairnum; // 어떤 계단 이용할지
                now.t++;

                if (now.walking == 0)
                { // 계단 도착
                    if (num[stairnum] == 3)
                    { // 계단 이용 불가
                        pq.push(now);
                    }
                    else
                    {                    // 계단 이용 가능
                        num[stairnum]++; // 이용자 수 + 1
                        now.walking = stairs[stairnum].height;
                        pq.push(now);
                    }
                }
                else if (now.walking == 1)
                {                    // 계단 다 내려옴
                    num[stairnum]--; // 이용자 수 - 1
                }
                else
                {                  // 계단 내려가는중
                    now.walking--; // 남은 계단 - 1
                    pq.push(now);
                }
            }
        }
    }
    return Time;
}

void dfs(int level)
{ // dfs 이용해서 모든 계단 이용하는 경우의 수
    if (level == P)
    {
        int prob = solve();
        ans = min(ans, prob);
        return;
    }

    for (int i = 0; i < 2; i++)
    {

        v.push_back({i, Dist[level][i]});
        dfs(level + 1);
        v.pop_back();
    }
}

int main()
{
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        // reset
        memset(Map, 0, sizeof(Map));
        memset(Dist, 0, sizeof(Dist));
        people.clear();
        stairs.clear();
        v.clear();
        ans = 21e8;

        // input
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> Map[i][j];

                if (Map[i][j] == 1)
                {
                    people.push_back({i, j}); // 사람 정보 저장
                }
                else if (Map[i][j] != 0)
                {
                    stairs.push_back({i, j, Map[i][j]}); // 계단 정보 저장
                }
            }
        }
        P = people.size();

        // solve

        CheckDist();
        dfs(0);

        // output
        cout << "#" << tc << ' ' << ans << '\n';
    }

    return 0;
}