#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

struct yx {
    int y;
    int x;

};

int N, L, R;
int MAP[51][51];
int visited[51][51];
int resultcnt; //정답

int ydir[4] = { -1, 1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };
int checked = 1;
vector<yx>vect; //국경선 열리는 좌표 넣어줄 벡터

void bfs(int y, int x)
{
    queue<yx> q;
    q.push({ y,x });
    vect.push_back({ y,x });
    visited[y][x] = 1;
    int sum = 0;
    int cnt = 0;

    while (!q.empty())
    {
        yx now = q.front();
        q.pop();

        sum += MAP[now.y][now.x]; //국경선 열린 나라들의 인구수 더해주기
        cnt += 1; // 열린 나라수 카운트
        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if (visited[ny][nx] == 1) continue;
            if (abs(MAP[now.y][now.x] - MAP[ny][nx]) >= L && abs(MAP[now.y][now.x] - MAP[ny][nx]) <= R) {
                visited[ny][nx] = 1;
                q.push({ ny,nx });
                vect.push_back({ ny,nx }); //국경선이 열렸다면 좌표 넣어주기
            }
        }
    }

    //국경선이 열린 좌표들에 대한 MAP값을 새로운 인구수로 변경
    for (int i = 0; i < vect.size(); i++) {
        yx now = vect[i];
        MAP[now.y][now.x] = sum / cnt;
    }
    vect.clear();
}

int canopen(int y, int x)
{
    //해당 좌표에서 국경선이 열릴 수 있는 나라가 있는지 판단
    for (int i = 0; i < 4; i++)
    {
        int ny = y + ydir[i];
        int nx = x + xdir[i];
        if (ny >= 0 && nx >= 0 && ny < N && nx < N) {
            if (abs(MAP[y][x] - MAP[ny][nx]) >= L && abs(MAP[y][x] - MAP[ny][nx]) <= R) return 1;
        }
    }
    return 0;
}

void simul()
{

    while (checked == 1) //더이상 인구이동할 경우가 없는지 체크
    {
        memset(visited, 0, sizeof(visited));
        resultcnt++;
        checked = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (visited[i][j] == 0 && canopen(i, j) == 1) //아직 국경선이 열린적이 없고 인구이동이 가능한 경우
                {
                    bfs(i, j);
                    checked = 1;
                }
            }
        }
    }
}


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> L >> R; //N 맵크기, 인구차이 L이상 R이하
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }

    simul();

    cout << resultcnt - 1; //한번은 무조건 카운트 되기 때문에 -1해주기
    return 0;
}