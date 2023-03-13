#include <iostream>
#include <cstring>
using namespace std;
/*
1
6 8 3
0 0 1 0 1 0 0 1
0 1 0 0 0 1 1 1
0 1 1 1 0 0 0 0
1 1 1 1 0 0 0 1
0 1 1 0 1 0 0 1
1 0 1 0 1 1 0 1
*/
int D, W, K; //두께 가로 합격기준
int film[15][20];
int origin[15][20];
int MIN;
int injection;

int check() {
    for (int col = 0; col < W; col++) {
        int cnt = 1;
        int tar = film[0][col];
        for (int i = 1; i < D; i++) {
            int now = film[i][col];
            if (tar != now) {
                tar = now;
                cnt = 1;
            }
            else {
                cnt++;
                if (cnt == K) break;
            }

        }
        if (cnt < K) return 0;
    }
    return 1;
}

void inject(int row, int what) {
    for (int i = 0; i < W; i++) {
        film[row][i] = what;
    }
}
void restore(int row) {
    for (int i = 0; i < W; i++) {
        film[row][i] = origin[row][i];
    }
}

void dfs(int level) {
    if (level == D) {
        if (MIN > injection && check() == 1) MIN = injection;
        return;
    }
    if (injection > MIN) return;

    dfs(level + 1);
    for (int i = 0; i < 2; i++) {
        inject(level, i);
        injection++;

        dfs(level + 1);

        restore(level);
        injection--;
    }
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        memset(film, 0, sizeof(film));
        memset(origin, 0, sizeof(origin));
        cin >> D >> W >> K;
        MIN = D;

        for (int i = 0; i < D; i++) {
            for (int j = 0; j < W; j++) {
                cin >> film[i][j];
                origin[i][j] = film[i][j];
            }
        }
        dfs(0);

        cout << "#" << tc << " " << MIN << endl;
    }
    return 0;
}