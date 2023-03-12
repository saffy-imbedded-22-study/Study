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
int sharky, sharkx; //����� ���� ��ġ

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

int checked[21][21]; // ĭ�� ���������� Ȯ��
int dist[21][21]; //�Ÿ����� ����ֱ�
int eaty, eatx; // ���� ����� ��ġ
int resulttime; //��� ��
int sharksize; // ����� ũ��
int fishcnt; //�Ծ���ϴ� ����� ��

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

                //���� ����ų� �ڽ��� ũ�⺸�� ū ����� ������ continue
                if (ny < 0 || nx<0 || ny >= N || nx >= N || MAP[ny][nx ]> sharksize) continue;
                if (checked[ny][nx] == 1)continue;

                 dist[ny][nx] = dist[now.y][now.x] + 1;
                 checked[ny][nx] = 1;
                 q.push({ ny,nx });
            }
        }

        int mindist = 21e8;
        int flag = 0;

        // ��Ƹ��� ����Ⱑ �ִ��� �Ǵ�, �� �߿� ���� ������, ���� ��, ���� ������ ��� ã��
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

        //��Ƹ��� �� �ִ� ��� ������ �� ����
        if (flag == 0 || mindist==21e8) {
            return resulttime;
        }

        //����� ��ƸԾ����ϱ� -���ֱ�
        fishcnt--;

        //�Ծ���ϴ� ����⸦ �� ��Ƹ����� ��� ũ��, ��ƸԾ���ϴ� ����� �� �������ֱ�
        if (fishcnt == 0) {
            sharksize++;
            fishcnt = sharksize;
        }

        resulttime += mindist; //�̵��Ÿ� �����ֱ�
        sharky = eaty; // �����ġ ����
        sharkx = eatx; 
        MAP[eaty][eatx] = 0; //�Ծ����ϱ� 0���� �����


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