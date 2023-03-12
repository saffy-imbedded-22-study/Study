#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

struct yx {
    int y;
    int x;
};

int MAP[21][21];
int N;
int sharky, sharkx; //상어의 현재 위치

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

int checked[21][21]; // 칸을 지나갔는지 확인
int dist[21][21]; //거리정보 담아주기
int eaty, eatx; // 먹을 물고기 위치
int resulttime; //결과 값
int sharksize; // 상어의 크기
int fishcnt; //먹어야하는 물고기 수

int simul() {
  
    while (1) {

        memset(dist, 0, sizeof(dist));
        memset(checked, 0, sizeof(checked));
        
        queue <yx> q;
        q.push({ sharky,sharkx });
        checked[sharky][sharkx] = 1;

        while (!q.empty()) {
            yx now = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int ny = now.y + ydir[i];
                int nx = now.x + xdir[i];

                //맵을 벗어나거나 자신의 크기보다 큰 물고기 있으면 continue
                if (ny < 0 || nx<0 || ny >= N || nx >= N || MAP[ny][nx ]> sharksize) continue;
                if (checked[ny][nx] == 1)continue;

                 dist[ny][nx] = dist[now.y][now.x] + 1;
                 checked[ny][nx] = 1;
                 q.push({ ny,nx });
            }
        }

        int mindist = 21e8;
        int flag = 0;

        // 잡아먹을 물고기가 있는지 판단, 그 중에 가장 가깝고, 가장 위, 가장 왼쪽인 경우 찾기
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (MAP[i][j] > 0 && MAP[i][j] < sharksize) {
                    flag = 1;
                    if (dist[i][j] > 0 && dist[i][j] < mindist) {
                        mindist = dist[i][j];
                        eaty = i;
                        eatx = j;
                    }
                }
            }
        }

        //잡아먹을 수 있는 경우 없으면 값 리턴
        if (flag == 0 || mindist==21e8) {
            return resulttime;
        }

        //물고기 잡아먹었으니까 -해주기
        fishcnt--;

        //먹어야하는 물고기를 다 잡아먹으면 상어 크기, 잡아먹어야하는 물고기 수 변경해주기
        if (fishcnt == 0) {
            sharksize++;
            fishcnt = sharksize;
        }

        resulttime += mindist; //이동거리 더해주기
        sharky = eaty; // 상어위치 변경
        sharkx = eatx; 
        MAP[eaty][eatx] = 0; //먹었으니까 0으로 만들기


    }
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);


    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 9) {
                sharky = i;
                sharkx = j;
                MAP[i][j] = 0;
            }
        }
    }

    sharksize = 2;
    fishcnt = 2;

    int restime = simul();

    cout << restime << '\n';

    return 0;
}