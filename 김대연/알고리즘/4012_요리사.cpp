#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int Map[16][16];
int N, min_cook = 21e8;
vector<int> cookA;

bool visited[16];

/*
DFS 이용해서 vector에 저장.

구현 못한거 : 겹치는 경우 제외하기.
ex) A 1 2 3  B 4 5 6 // A 4 5 6  B 1 2 3
*/

int solve_cook(vector<int> A)
{ // 조합 합
    int Sum = 0;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = i + 1; j < A.size(); j++)
        {

            Sum += Map[A[i]][A[j]];
            Sum += Map[A[j]][A[i]];
        }
    }
    return Sum;
}

void dfs(int level, int next)
{
    if (level == N / 2)
    {
        vector<int> cookB;
        for (int i = 0; i < N; i++)
        { // A 원소 제외 B 구성
            if (find(cookA.begin(), cookA.end(), i) == cookA.end())
            {
                cookB.push_back(i);
            }
        }
        int Sum = abs(solve_cook(cookA) - solve_cook(cookB));
        if (Sum < min_cook)
        {
            min_cook = Sum;
        }

        return;
    }

    for (int i = next; i < N; i++)
    { // 다음번에 고를 때 골랐던 수보다 더 큰 수 뽑기
        cookA.push_back(i);

        dfs(level + 1, i + 1);

        cookA.pop_back();
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
        cookA.clear();
        min_cook = 21e8;

        // input
        cin >> N;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> Map[i][j];
            }
        }

        // solve
        dfs(0, 0);

        // output
        cout << "#" << t << ' ' << min_cook << '\n';
    }
}