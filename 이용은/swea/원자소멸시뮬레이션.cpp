#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct Atom {
	int x, y, dir, K;
};
struct Collision {
	int i, j, dist;//
};
vector<Atom>v;
int N;
int totalE;
int visited[1000];
vector<Collision>col;;//충돌할 가능성 있는 원자 쌍 저장
//거리의 최솟값 정렬
// isAlive를 1로 바꾸어주기
//거리가 같은 경우 여러개 원자가 충돌 할 수 있음

bool cmp(Collision left, Collision right) {
	if (left.dist < right.dist)
		return true;
	if (left.dist > right.dist)
		return false;
	return false;

}


void reset() {
	totalE = 0;
	v = vector<Atom>();
	col = vector<Collision>();
	memset(visited, 0, sizeof(visited));
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, dir, K;
		cin >> x >> y >> dir >> K;
		v.push_back({ x,y,dir,K });
	}
}

int getDist(int x1, int x2) {
	if (x1 - x2 < 0) return x2 - x1;
	return x1 - x2;
}

bool dircheck(int dir1, int dir2) {
	if (dir1 % 2 == 0) dir1 += 1;
	else dir1 -= 1;

	if (dir1 == dir2)return true;
	return false;

}

void findcol() {

	for (int i = 0; i < N; i++) {
		Atom atom1 = v[i];
		for (int j = i + 1; j < N; j++) {
			Atom atom2 = v[j];
			//#1 두개의 방향이 같으면 >> 만날수 없음
			if (atom1.dir == atom2.dir) continue;

			//#2 두개의 방향 반대면 >> 같은 행/열에 있는지 check
			else if (dircheck(atom1.dir, atom2.dir)) {
				if (atom1.dir == 0) {//상이면
					if (atom1.x == atom2.x && atom1.y < atom2.y) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist });
					}
				}
				else if (atom1.dir == 1) {//하이면
					if (atom1.x == atom2.x && atom1.y > atom2.y) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist });
					}
				}
				else if (atom1.dir == 2) {//같은 행에 있는지 확인
					if (atom1.y == atom2.y && atom1.x > atom2.x) {
						int dist = getDist(atom1.x, atom2.x);
						col.push_back({ i,j,dist });
					}
				}
				else if (atom1.dir == 3) {//같은 행에 있는지 확인
					if (atom1.y == atom2.y && atom1.x < atom2.x) {
						int dist = getDist(atom1.x, atom2.x);
						col.push_back({ i,j,dist });
					}
				}

			}

			//방향 수직인 경우
			else {
				if (atom1.x - atom2.x == 0) continue;
				//기울기가 1 인 경우
				if ((atom1.y - atom2.y) == (atom1.x - atom2.x))
				{
					if (atom1.x > atom2.x) {
						Atom tmp = atom1;
						atom1 = atom2;
						atom2 = tmp;
					}

					if ((atom1.dir == 3 && atom2.dir == 1)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}
					if ((atom1.dir == 0 && atom2.dir == 2)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}

				}

				//기울기가 -1인경우
				else if ((atom1.y - atom2.y) == -(atom1.x - atom2.x)) {
					if (atom1.x > atom2.x) {
						Atom tmp = atom1;
						atom1 = atom2;
						atom2 = tmp;
					}
					if ((atom1.dir == 3 && atom2.dir == 0)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}
					else if ((atom1.dir == 1 && atom2.dir == 2)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}

					
				}

			}

			atom1 = v[i];//atom1 복구
		}
	}
}

void Colcheck() {

	int colsize = col.size();
	if (colsize == 0) {
		return;
	}

	sort(col.begin(), col.end(), cmp);//dist 오름차순

	for (int x = 0; x < colsize; x++) {
		Collision now = col[x];
		int A = now.i;
		int B = now.j;
		if (visited[B] != 0 && visited[A] != 0) continue;

		else if (visited[B] == 0 && visited[A] == now.dist) {
			visited[B] = now.dist;
			totalE += v[B].K;
		}
		else if (visited[A] == 0 && visited[B] == now.dist) {
			visited[A] = now.dist;
			totalE += v[A].K;
		}

		//처음충돌
		else if (visited[A] == 0 && visited[B] == 0) {
			visited[A] = now.dist;
			visited[B] = now.dist;
			totalE += v[A].K;
			totalE += v[B].K;
		}

	}
}

int main() {

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		findcol();
		Colcheck();
		cout << "#" << tc << " " << totalE << endl;
	}

	return 0;
}