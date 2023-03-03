#include <iostream>
#include <vector>
using namespace std;
struct rot {
	int num, type;
};
int K;
int magnet[4][8];
vector<rot>v;
int isRotate[4] = { 0, };//index: 자석종류 // value : -1반시계, 1시계, 0그대로

void reset() {
	v = vector<rot>();
}


void input() {
	cin >> K;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 8; x++) {
			cin >> magnet[y][x];
		}
	}
	for (int i = 0; i < K; i++) {
		int num, type;
		cin >> num >> type;
		num -= 1;
		v.push_back({ num, type });
	}
	
}
// type -1 >> 반시계(왼쪽) 
// type 1 >> 오른쪽
// type 0 >> 회전 X
// num : magnet번호0~3
void rotate(int num, int type) {
	if (type == 0) return;//그대로
	//시계
	if (type == 1) {
		int tmp = magnet[num][7];
		for (int i = 6; i >= 0; i--) {
			magnet[num][i + 1] = magnet[num][i];
		}
		magnet[num][0] = tmp;
	}
	//반시계
	else if (type == -1) {
		int tmp = magnet[num][0];
		for (int i = 1; i < 8; i++) {
			magnet[num][i - 1] = magnet[num][i];
		}
		magnet[num][7] = tmp;
	}
}

//돌아가는 자석 확인
void check(int num, int type) {
	
	isRotate[num] = type;//무조건 돌아감
	
	//양 옆에도 돌수 있는지 확인하기
	int ntype =type;//방향 전환용
	
	int i = 0;
	//#1양옆에 자석이 없거나
	//#2회전하지 않을때까지 반복
	while (true) {
		i++;//양 옆확인
		int flag = 0;
		
		//회전방향 전환
		if (ntype == 1) ntype = -1;
		else ntype = 1;

		if (num - i >= 0) {//왼쪽 자석확인(범위 넘어가지 않는경우만)
			if (magnet[num - i][2] == magnet[num-i+1][6]) {
				if (isRotate[num - i + 1] != 0) {//오른쪽 자석이 회전하는 경우에만 유효
					flag = 1;
					isRotate[num - i] = ntype;
				}
			}
		}

		if (num + i <= 3) {//오른쪽 자석 확인
			if (magnet[num + i-1][2] == magnet[num+i][6]) {
				if (isRotate[num + i - 1] != 0) {
					flag = 1;
					isRotate[num + i] = ntype;
				}
			}
		}
		//종료조건 -> 회전한 자석이 없는경우
		if (flag == 0) break;
	}

	//자석의 회전방향 모두 정해짐
	//모두 돌리기
	for (int x = 0; x < 4; x++) {
		rotate(x, isRotate[x]);
	}
	
}

void resetR() {
	for (int j = 0; j < 4; j++) {
		isRotate[j] = 0;
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {

		reset();
		input();
		int sizeV = v.size();
		for (int i = 0; i < sizeV; i++) {
			resetR();
			check(v[i].num, v[i].type);
		}

		int result = 0;
		for (int i = 0; i < 4; i++) {
			int tmp = magnet[i][0] << i;
			result += tmp;
		}
		cout << "#" << tc << " " << result << endl;

	}
	return 0;
}