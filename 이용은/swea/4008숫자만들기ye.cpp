#include <iostream>
#include <algorithm>
using namespace std;
int N;
int Result;
int MAP[12];//입력받은 수
int minS, maxS;
int oper[4];

void DFS(int now) {
    //기저

    if (now == N) {
        //최대, 최소값 갱신
        // 
        //minS : 이전 결과 값 중  최솟값, Result: 현재 연산결과
        minS = min(minS, Result);
        maxS = max(maxS, Result);

        return;
    }


    for (int i = 0; i < 4; i++) {
        //가지치기
        if (oper[i] == 0) continue;//연산자 다 사용한 경우 skip

        int temp = Result; // 복구용
        //처리: Result에 연산결과 저장
        if (i == 0) {
            Result = Result + MAP[now];
        }
        else if (i == 1) {
            Result -= MAP[now];
        }
        else if (i == 2) {
            Result *= MAP[now];
        }
        else {
            Result = Result / MAP[now];
        }

        oper[i]--;//사용횟수차감
        DFS(now + 1);//기본구조
        //복구
        oper[i]++;

        Result = temp;

    }

}

int main() {

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        //reset
        minS = 21e8;
        maxS = -21e8;
        Result = 0;

        //input
        cin >> N;
        for (int x = 0; x < 4; x++) {
            cin >> oper[x];
        }
        for (int x = 0; x < N; x++) {
            cin >> MAP[x];
        }

        //solve
        Result = MAP[0];// 입력받은 맨처음 수를 result로 초기화
        DFS(1);

        //output
        //DFS 에서 구한 maxS 와 minS 출력
        cout << "#" << tc << " " << maxS - minS << endl;

    }


    return 0;
}