#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int M;
int arr[10000];
struct cmp
{
    bool operator()(int left, int right)
    {
        return left > right;
    }
};
int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        memset(arr, 0, sizeof(arr));
        priority_queue<int> small_num;
        priority_queue<int, vector<int>, cmp> big_num;
        cin >> M;
        for (int i = 0; i < M; i++)
        {
            cin >> arr[i];
        }
        int middle_num = arr[0];
        int N = (M + 1) / 2;
        cout << N << '\n';
        cout << middle_num << ' ';
        int ten_space = 1;
        for (int i = 0; i < N - 1; i++)
        {
            int cnt = 0;
            int input[2];
            for (int j = 1; j < 3; j++)
            {
                input[j - 1] = arr[2 * i + j];
                if (middle_num < input[j - 1])
                {
                    cnt++;
                }
            }
            sort(input, input + 2);
            switch (cnt)
            {
            case 0:
                big_num.push(middle_num);
                small_num.push(input[0]);
                small_num.push(input[1]);
                middle_num = small_num.top();
                small_num.pop();
                break;
            case 1:
                small_num.push(input[0]);
                big_num.push(input[1]);
                break;
            case 2:
                small_num.push(middle_num);
                big_num.push(input[0]);
                big_num.push(input[1]);
                middle_num = big_num.top();
                big_num.pop();
                break;
            }
            cout << middle_num << ' ';
            ten_space++;
            if (ten_space == 10)
            {
                cout << '\n';
                ten_space = 0;
            }
        }
        cout << '\n';
    }
    return 0;
}