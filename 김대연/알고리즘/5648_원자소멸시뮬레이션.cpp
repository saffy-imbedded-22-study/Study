#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

int diry[4] = { 1,-1,0,0 };
int dirx[4] = { 0,0,-1,1 };

int N;	// 원자 수

int ans;	// 정답

struct node {
	int x, y;	// 좌표
	int dir;	// 방향
};
node atoms[1010];
int DAT[1010];	// 에너지 저장

struct colli {
	int a, b;	//원자 번호
	float T;		//충돌 시간
};

struct cmp {
	bool operator()(colli left, colli right)const {
		return left.T > right.T;
	}
};

float collision(node a, node b) {	// 충돌까지 걸린 시간

	// x 좌표 동일
	if (a.x == b.x) {
		if (a.dir + b.dir == 1) {
			if (a.dir == 0) {
				if (b.y - a.y >= 0) return float(b.y - a.y) / 2;
			}
			else {
				if (a.y - b.y >= 0) return float(a.y - b.y) / 2;
			}
		}
	}
	else if (a.y == b.y)	// y좌표 동일
	{
		if (a.dir + b.dir == 5) {
			if (a.dir == 2) {
				if (a.x - b.x >= 0) return float(a.x - b.x) / 2;
			}
			else {
				if (b.x - a.x >= 0) return float(b.x - a.x) / 2;
			}
		}
	}	// 진행하다 충돌
	else if (abs(a.x - b.x) == abs(a.y - b.y)) {
		int dist = abs(a.x - b.x);
		int ay = a.y + diry[a.dir] * dist;
		int ax = a.x + dirx[a.dir] * dist;
		int by = b.y + diry[b.dir] * dist;
		int bx = b.x + dirx[b.dir] * dist;

		if ((ay == by) && (ax == bx)) return dist;
	}
	return -1;
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1;tc <= T;tc++) {
		// reset
		memset(DAT, 0, sizeof(DAT));
		memset(atoms, 0, sizeof(atoms));
		ans = 0;

		// input
		cin >> N;
		for (int i = 0;i < N;i++) {
			int x, y, dir, energy;
			cin >> x >> y >> dir >> energy;
			atoms[i] = { x,y,dir };
			DAT[i] = energy;
		}

		// solve

		priority_queue<colli, vector<colli>, cmp> pq;

		for (int i = 0;i < N;i++) {
			for (int j = i + 1;j < N;j++) {
	
				float col_time = collision(atoms[i], atoms[j]);	//두 원자의 충돌 여부 확인
				if (col_time == -1)continue;
				pq.push({ i,j,col_time });	// 충돌 가능한거 다 pq에 넣기
			}
		}
		
		float nowT = -1;
		vector<int> v;	// 이번 시간동안 소멸되는 것들


		while (!pq.empty()) {
			colli now = pq.top();	// 충돌 시간 짧은거부터 꺼내기
			pq.pop();

			if (nowT != now.T) {	// 시간이 넘어가면 vector에 있던 원소들 소멸.
				for (int i = 0;i < v.size();i++) {
					if (DAT[v[i]] == 0)continue;
					ans += DAT[v[i]];
					DAT[v[i]] = 0;
				}
				v.clear();
				nowT = now.T;		// 시간 갱신
			}

			if (DAT[now.a] == 0 || DAT[now.b] == 0)continue;	//이미 소멸했으면 스킵.

			v.push_back(now.a);	// 소멸 시킬거 넣어주기
			v.push_back(now.b);

		}
		for (int i = 0;i < v.size();i++) {	// 마지막에도 더해주기
			if (DAT[v[i]] == 0)continue;
			ans += DAT[v[i]];
			DAT[v[i]] = 0;
		}


		// output
		cout << "#" << tc << ' ' << ans << '\n';
	}



	return 0;
}