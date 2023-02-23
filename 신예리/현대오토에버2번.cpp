#include<iostream>
#include<string>
using namespace std;

string filename[101];
string name;
int key[101] = { -1 };

int compare(string filename) {

    int leng;
    leng = filename[0] - name[0];
    if (leng < 0)leng += 26;

    for (int i = 1; i < filename.length(); i++) {
        int cmpleng = filename[i] - name[i];
        if (cmpleng < 0)cmpleng += 26;
        if (leng != cmpleng) {
            return -1;
        }
    }
    return leng;

}


int main() {

    int n;
    cin >> n;

    cin >> name;

    for (int i = 0; i < n; i++) {
        cin >> filename[i];
    }

    for (int i = 0; i < n; i++) {
        if (name.length() == filename[i].length()) {
            key[i] = compare(filename[i]);
        }
    }

    int minkey = 21e8;
    int keyindex;

    for (int i = 0; i < name.length(); i++) {
        if (key[i] > 0 && minkey > key[i]) {
            minkey = key[i];
            keyindex = i;
        }
    }

    cout << filename[keyindex];

    return 0;
}