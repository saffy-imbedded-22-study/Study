#include <iostream>
#include <vector>
#include <queue>
#include<cstring>
using namespace std;

struct BC {
    int number;
    int power;
};

struct BC_infor {
    int y;
    int x;
    int c;
    int power;
};

vector<BC> MAP[11][11];
int M, cnt;
int Amove[100];
int Bmove[100];
int Ay, Ax, By, Bx;
int ans;
int ydir[5] = { 0,-1,0,1,0 };
int xdir[5] = { 0,0,1,0,-1 };

void bfs(int number, int y, int x, int c, int power) {
    queue<BC_infor> q;
    q.push({ y,x,0,power });

    int visited[11][11] = { 0 };
    visited[y][x] = 1;

    while (!q.empty()) {
        BC_infor now = q.front();
        q.pop();

        if (now.c == c)
            break;

        for (int i = 1; i < 5; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];
            if (ny < 1 || nx < 1 || ny >= 11 || nx >= 11)
                continue;
            if (visited[ny][nx] == 1)
                continue;
            visited[ny][nx] = 1;
            MAP[ny][nx].push_back({ number,power });
            q.push({ ny,nx,now.c + 1,power });
        }
    }
}

void charge() {

    if (!MAP[Ay][Ax].empty() && !MAP[By][Bx].empty()) {
        int maxcharge = 0;
        //둘 다 BC가 존재할 때
        for (int i = 0; i < MAP[Ay][Ax].size(); i++) {
            for (int j = 0; j < MAP[By][Bx].size(); j++) {
                // 둘이 다른 BC를 사용하는 경우
                if (MAP[Ay][Ax][i].number != MAP[By][Bx][j].number) {
                    if (MAP[Ay][Ax][i].power + MAP[By][Bx][j].power > maxcharge)
                        maxcharge = MAP[Ay][Ax][i].power + MAP[By][Bx][j].power;
                }
                // 둘이 같은 BC를 사용하는 경우
                else if (MAP[Ay][Ax][i].number == MAP[By][Bx][j].number) {
                    if (MAP[Ay][Ax][i].power > maxcharge)
                        maxcharge = MAP[Ay][Ax][i].power;
                }
            }
        }
        ans += maxcharge;
    }
    // A만 가능할 때
    else if (!MAP[Ay][Ax].empty()) {
        int maxcharge = 0;
        for (int i = 0; i < MAP[Ay][Ax].size(); i++) {
            if (MAP[Ay][Ax][i].power > maxcharge)
                maxcharge = MAP[Ay][Ax][i].power;
        }
        ans += maxcharge;
    }
    // B만 가능할 때
    else if (!MAP[By][Bx].empty()) {
        int maxcharge = 0;
        for (int i = 0; i < MAP[By][Bx].size(); i++) {
            if (MAP[By][Bx][i].power > maxcharge)
                maxcharge = MAP[By][Bx][i].power;
        }
        ans += maxcharge;
    }
}

int main()
{
    int test;

    cin >> test;

    for (int te = 1; te <= test; te++)
    {
        memset(MAP, 0, sizeof(MAP));
        ans = 0;
        Ay = 1;
        Ax = 1;
        By = 10;
        Bx = 10;

        cin >> M >> cnt;
        for (int i = 0; i < M; i++)
            cin >> Amove[i];
        for (int i = 0; i < M; i++)
            cin >> Bmove[i];
        for (int i = 0; i < cnt; i++) {
            int x, y, c, power;
            cin >> x >> y >> c >> power;

            MAP[y][x].push_back({ i,power });
            //각 c의 거리만큼 BC의 number와 power 정보 넣어주기
            bfs(i, y, x, c, power);
        }

        // 출발지에서 충전
        charge();

        // A, B 이동하면서 시간마다 확인
        for (int i = 0; i < M; i++) {
            Ay += ydir[Amove[i]];
            Ax += xdir[Amove[i]];
            By += ydir[Bmove[i]];
            Bx += xdir[Bmove[i]];
            charge();
        }

        cout << "#" << te << " " << ans << '\n';
    }

    return 0;
}