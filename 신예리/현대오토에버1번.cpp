#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

struct yx {
    int py;
    int px;
};

vector<yx>v[30];

string MAP[12];
int N, M;
int leng;
int score[11];

void simul(int num, int peoy, int peox) {

    while (1) {

        if (peoy == N) {
            score[peox] = num;
            break;
        }

        peoy += 1;

        if (MAP[peoy][peox] >= 'a' && MAP[peoy][peox] <= 'z') {
            for (int i = 0; i < 2; i++) {
                yx now = v[MAP[peoy][peox] - 'a'][i];
                if (now.py != peoy || now.px != peox) {
                    peoy = now.py;
                    peox = now.px;
                    break;
                }
            }
        }
    }
}


int main() {

    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        cin >> MAP[i];
    }

    leng = MAP[1].length();

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < leng; j++) {
            if (MAP[i][j] >= 'a' && MAP[i][j] <= 'z') {
                v[MAP[i][j] - 'a'].push_back({ i,j });
            }
        }
    }

    int num = 1;
    for (int i = 0; i < leng; i += 2) {
        simul(num, 0, i);
        num++;
    }

    for (int i = 0; i < leng; i += 2) {
        cout << score[i] << " ";
    }
    return 0;
}