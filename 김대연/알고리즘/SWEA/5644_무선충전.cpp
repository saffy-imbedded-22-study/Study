#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int dirx[5] = {0, 0, 1, 0, -1};
int diry[5] = {0, -1, 0, 1, 0};

/*
1. Flood_fill 이용해서 맵에 BC(넘버, 파워) 입력.
2. 0~M까지의 시간동안 이동하면서 현재 위치에서 최대 충전값 찾기.

*/
struct BC
{
    int num;    //넘버 부여.
    int power;  

    bool operator==(BC next)    //BC끼리 비교할 때 넘버가 같으면 같은 BC
    {
        if (num == next.num)
        {
            return true;
        }
        else
            return false;
    }
};

vector<BC> Map[12][12];
int M, A;
int Move_A[101];
int Move_B[101];

void fill_dfs(int level, int y, int x, int C, BC P)
{ // dfs 이용해서 맵에 BC 체크
    if (level == C)
    {
        return;
    }

    for (int i = 1; i < 5; i++)
    {
        int dy = y + diry[i];
        int dx = x + dirx[i];
        if (dy > 10 || dy < 1 || dx > 10 || dx < 1)
            continue;
        if (find(Map[dy][dx].begin(), Map[dy][dx].end(), P) == Map[dy][dx].end())   //그 칸에 P가 없으면 추가
        {
            Map[dy][dx].push_back(P);
        }

        fill_dfs(level + 1, dy, dx, C, P);
    }
}

int main()
{

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        // reset
        memset(Map, 0, sizeof(Map));
        memset(Move_A, 0, sizeof(Move_A));
        memset(Move_B, 0, sizeof(Move_B));

        // input
        cin >> M >> A;
        for (int i = 0; i < M; i++)
        {
            cin >> Move_A[i];
        }
        for (int i = 0; i < M; i++)
        {
            cin >> Move_B[i];
        }
        for (int i = 0; i < A; i++)
        {
            int dy, dx, C, P;
            cin >> dx >> dy >> C >> P;
            BC Energy = {i, P};
            Map[dy][dx].push_back(Energy);
            fill_dfs(0, dy, dx, C, Energy);
        }

        // solve
        int ay = 1, ax = 1;     // A 시작위치
        int by = 10, bx = 10;   // B 시작위치
        int full_sum = 0;

        for (int m = 0; m <= M; m++)    //M번만큼 이동
        {
            int now_best = 0;
            if (Map[ay][ax].empty())    //A 현재 위치에서 맵에 BC가 있는지 확인.
            { // B만 충전 가능할때
                for (int j = 0; j < Map[by][bx].size(); j++)    //현재 위치에 존재하는 BC중 Power가 제일 큰 거 찾기.
                {                                               // 정렬해서 제일 큰거 뽑을까 했는데 모든 칸 정렬이 이득일까 고민.
                    if (now_best < Map[by][bx][j].power)
                    {
                        now_best = Map[by][bx][j].power;
                    }
                }
            }
            else if (Map[by][bx].empty())
            { // A만 충전 가능할때
                for (int i = 0; i < Map[ay][ax].size(); i++)
                {
                    if (now_best < Map[ay][ax][i].power)
                    {
                        now_best = Map[ay][ax][i].power;
                    }
                }
            }
            else    //둘 다 안 비어있을때
            {
                for (int i = 0; i < Map[ay][ax].size(); i++)
                {
                    for (int j = 0; j < Map[by][bx].size(); j++)
                    {
                        int now_sum = 0;    // 현재 조합에서의 크기
                        if (Map[ay][ax][i].num == Map[by][bx][j].num) // 둘이 같은거 충전할때 (넘버가 같음)
                        { 
                            now_sum = Map[ay][ax][i].power; // 둘이 반반 나눠써야하기때문에 파워만큼 더해줌.
                        }
                        else
                        {
                            now_sum += Map[ay][ax][i].power;   //각각 파워만큼 더해줌.
                            now_sum += Map[by][bx][j].power;
                        }
                        if (now_sum > now_best) //현재 위치에서 가능한 조합 중 최대값 찾기
                        {
                            now_best = now_sum;
                        }
                    }
                }
            }

            full_sum += now_best;   //이번 턴에 충전 가능 최대값 더해줌.

            if (m == M) // 시간 다됐으면 break
                break;
            // 다음 위치로 이동
            ay = ay + diry[Move_A[m]];
            ax = ax + dirx[Move_A[m]];
            by = by + diry[Move_B[m]];
            bx = bx + dirx[Move_B[m]];
        }

        // output
        cout << "#" << t << ' ' << full_sum << '\n';
    }

    return 0;
}