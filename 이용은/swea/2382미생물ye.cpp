#include <iostream>
#include <queue>
using namespace std;

int N, M, K;

struct Node {
    int y, x; //위치
    int num; // 미생물 수
    int dir; //이동방향
};

struct used {
    int name;
    int num, dir;
};


int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        //reset

        queue<Node>q[1001];// idx:군집종류1~K


        //input
        cin >> N >> M >> K;
        for (int i = 1; i <= K; i++) {
            int y, x, num, dir;
            cin >> y >> x >> num >> dir;
            q[i].push({ y,x,num,dir });

        }


        //solve
        int day = 0;

        //방향배열
        int ydir[] = { 0,-1,1,0,0 };// 1 2 3 4
        int xdir[] = { 0, 0,0,-1,1 };// 상하좌우

        while (day < M) {
            day++;

            //visited
            //nynx로 이동하는 미생물 중 최대값의 이름/미생물 수/ 방향 저장
            used v[101][101] = { {0,0,0}, }; 
            int cnt[101][101] = { 0, };// 미생물의 총 수 count

            //각 미생물 군집 처리하기
            for (int i = 1; i <= K; i++) {
                if (q[i].empty()) continue;

                Node now = q[i].front();
                q[i].pop();
                int idx = now.dir;
                //다음 정보
                int ny = now.y + ydir[idx];
                int nx = now.x + xdir[idx];
                int nnum = now.num;
                int ndir = now.dir;


                //경계에 만나는경우
                if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) {
                    //미생물 수 반으로 줄이기
                    nnum = now.num / 2;
                    if (nnum == 0) continue;
                    //미생물 방향 반대로 만들기
                    if (now.dir % 2 == 0) ndir = now.dir - 1;
                    else ndir = now.dir + 1;
                    q[i].push({ ny,nx,nnum,ndir });
                    continue;//약품으로 모이는 경우는 없음>> skip
                }
                //0이면 군집 없애기



                //이전에 방문한 미생물이 있는경우
                if (cnt[ny][nx] != 0) {
                    used preBac = v[ny][nx];
                    //이전 군집 제거 (하나로 합치기 위해)
                    q[preBac.name].pop();
                    v[ny][nx].name = i;//현재 미생물에 합치기 때문에, 이름 갱신해주기

                    //현재가 더 크다면
                    if (preBac.num < now.num) {
                        //v 갱신(최댓값 갱신)
                        v[ny][nx].num = now.num;
                        v[ny][nx].dir = now.dir;
                    }
                    //이전값이 더 크다면
                    else {
                        //방향갱신
                        ndir = preBac.dir;
                    }



                }
                else {
                    //처음 방문하는 경우, 현재 정보로 초기화
                    v[ny][nx] = { i, now.num, now.dir };
                }

                //처리
                cnt[ny][nx] += nnum;//cnt 값: ny nx로 도착한 미생물의 총수


                q[i].push({ ny,nx, cnt[ny][nx],ndir });

            }



        }
        //M일차 종료 >> q에는 살아남은 미생물의 정보만 남아있음.

        //output
        int Sum = 0;
        for (int i = 1; i <= K; i++) {
            if (q[i].empty())continue;//죽은 미생물 skip
            Sum += q[i].front().num;

        }

        cout << "#" << tc << " " << Sum << endl;



    }


    return 0;
}