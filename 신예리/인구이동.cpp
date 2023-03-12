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
int resultcnt; //����

int ydir[4] = { -1, 1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };
int checked = 1;
vector<yx>vect; //���漱 ������ ��ǥ �־��� ����

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

        sum += MAP[now.y][now.x]; //���漱 ���� ������� �α��� �����ֱ�
        cnt += 1; // ���� ����� ī��Ʈ
        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if (visited[ny][nx] == 1) continue;
            if (abs(MAP[now.y][now.x] - MAP[ny][nx]) >= L && abs(MAP[now.y][now.x] - MAP[ny][nx]) <= R) {
                visited[ny][nx] = 1;
                q.push({ ny,nx });
                vect.push_back({ ny,nx }); //���漱�� ���ȴٸ� ��ǥ �־��ֱ�
            }
        }
    }

    //���漱�� ���� ��ǥ�鿡 ���� MAP���� ���ο� �α����� ����
    for (int i = 0; i < vect.size(); i++) {
        yx now = vect[i];
        MAP[now.y][now.x] = sum / cnt;
    }
    vect.clear();
}

int canopen(int y, int x)
{
    //�ش� ��ǥ���� ���漱�� ���� �� �ִ� ���� �ִ��� �Ǵ�
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

    while (checked == 1) //���̻� �α��̵��� ��찡 ������ üũ
    {
        memset(visited, 0, sizeof(visited));
        resultcnt++;
        checked = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (visited[i][j] == 0 && canopen(i, j) == 1) //���� ���漱�� �������� ���� �α��̵��� ������ ���
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

    cin >> N >> L >> R; //N ��ũ��, �α����� L�̻� R����
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }

    simul();

    cout << resultcnt - 1; //�ѹ��� ������ ī��Ʈ �Ǳ� ������ -1���ֱ�
    return 0;
}