#include <iostream>
#include <algorithm>
using namespace std;

int Schedule[12];//idx : month -1 , 값: 이용계획
int Charge[4]; // 요금
int minCost;// 최솟값 갱신용
int Sum; //연산결과 저장용

//visited 필요없음

void DFS(int now) {
    //기저
    if (now >= 12) {
        //12월 초과하면 최솟값 갱신
        minCost = min(minCost, Sum);
        return;
    }

    for (int x = 0; x < 3; x++) {
        //가지치기

        //이전 최솟값 이상경우 skip
        if (Sum >= minCost) continue;


        //처리
        //일일 이용원
        if (x == 0) {
            Sum += Schedule[now] * Charge[x];
            DFS(now + 1);
            Sum -= Schedule[now] * Charge[x];
        }
        //월간
        if (x == 1) {
            Sum += Charge[x];
            DFS(now + 1);
            Sum -= Charge[x];
        }
        //3달
        if (x == 2) {
            Sum += Charge[x];
            DFS(now + 3);
            Sum -= Charge[x];
        }


    }


}


int main() {

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        //reset
        Sum = 0;
        //input
        for (int x = 0; x < 4; x++)
            cin >> Charge[x];

        for (int x = 0; x < 12; x++)
            cin >> Schedule[x];

        minCost = Charge[3]; //연간이용권 가격으로 초기화

        DFS(0);

        //DFS로 갱신된 최솟값 출력
        cout << "#" << tc << " " << minCost << endl;

    }

    return 0;
}