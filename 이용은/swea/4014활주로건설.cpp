#include <iostream>
using namespace std;
int ans;
int N, X;
int MAP[20][20];
int MAPx[20][20];
int visited[20];
void reset() {
    ans = 0;
}
void resetV() {
    for (int x = 0; x < 20; x++) {
        visited[x] = 0;
    }
}

void input() {
    cin >> N >> X;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> MAP[y][x];
            MAPx[x][y] = MAP[y][x];//전치행렬 만들기
        }
    }
}
//경사로 설치 가능한지 확인
// left : type ==0
// right: type == 1
//idx: 시작 index, end :종료 idx, arr: 확인할 행(또는열)
bool check(int idx, int type,int end, int arr[20]) {
    int tmp = arr[idx];//시작인덱스 저장
    if (type == 1) {//오른쪽 확인
        if (end >= N) return false;//1.범위 초과시 거짓
        for (int x = idx; x <= end; x++) {
            if (arr[x] != tmp) return false;//2.높이 다르면 거짓
            if (visited[x] == 1)return false;//3. 겹치는 경우 거짓
            visited[x] = 1;//겹치지 않게 방문처리
        }
    }
    else {//왼쪽확인
        if (end < 0) return false;
        for (int x = idx; x >= end; x--) {
            if (arr[x] != tmp) return false;
            if (visited[x] == 1)return false;
            visited[x] = 1;
        }
        
    }
    //문제 없으면 
    return true;

}

void sol(int arr[20]) {
    int flag = 0;
    for (int i = 0; i < N-1; i++) {
        if (arr[i] == arr[i + 1]) continue;//#1.앞뒤 같은경우
        else if (arr[i] - arr[i + 1] == 1) {//#2. 앞>뒤 인경우 ->오른쪽 확인
            if (!check(i+1, 1,i+X, arr)) {
                flag = 1;
                break;
            }
        }
        else if (arr[i] - arr[i + 1] == -1) {
            if (!check(i, 0,i-X+1, arr)) {//#3. 앞<뒤 인경우 ->왼쪽 확인
                flag = 1;
                break;
            }
        }
        else {//#4. 앞뒤 높이차이가 1이 아닌경우 ->건설불가
            flag = 1;
            break;
        }
    }

    if (flag == 0)ans++;
}


int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        reset();
        input();
        for (int i = 0; i < N; i++) {
            resetV();//visited초기화
            sol(MAP[i]);//행 확인
            resetV();//visited초기화
            sol(MAPx[i]);//열 확인
        }



        cout << "#" << tc << " " << ans << endl;
    }

    return 0;
}