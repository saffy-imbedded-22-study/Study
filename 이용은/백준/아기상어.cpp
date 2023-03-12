#include <iostream>
#include <queue>
using namespace std;
struct Shark {
	int y, x, level, cnt,dist;
	//level : 현재 크기
	// cnt : 먹은수
	bool operator < (Shark next) const {
		if (dist < next.dist)
			return false;
		if (dist > next.dist)
			return true;
		if (y < next.y)
			return false;
		if (y > next.y)
			return true;
		if (x < next.x)
			return false;
		if (x > next.x)
			return true;
		return false;
	}
};
int N;
int MAP[21][21];
int fish_cnt;//물고기수
int flag;
int sy, sx;
int ans = 0;
Shark baby;

void Flood(Shark Baby) {
	//pq에서 정렬 -> dist, y, x 오름차순 정렬
	priority_queue<Shark>q;
	q.push(Baby);

	int visited[20][20] = { 0, };
	visited[Baby.y][Baby.x] = 1;
	int ydir[] = { -1, 1,0,0 };
	int xdir[] = { 0, 0, -1,1 };

	while (!q.empty()) {
		Shark now = q.top();
		q.pop();
		
		//물고기 먹기
		if (MAP[now.y][now.x] >=1 && now.level > MAP[now.y][now.x]) {
			flag = 1;
			fish_cnt--;
			MAP[now.y][now.x] = 0;
			ans += now.dist-1;
			now.cnt++;
			if (now.cnt == now.level) {
				now.level++;
				now.cnt = 0;
			}
			baby = now;
			break;
		}
		//못먹으면 탐색
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= N || nx >= N || nx < 0 || ny < 0) continue;
			if (visited[ny][nx] !=0) continue;
			if (MAP[ny][nx] > now.level) continue;
			
			visited[ny][nx] = visited[now.y][now.x] +1;
			q.push({ ny,nx,now.level,now.cnt ,visited[ny][nx]});
		}
	}
}

int sol() {
	baby = { sy,sx,2,0,1 };
	while (true) {
		if (fish_cnt == 0)break;//물고기 다먹은 경우
		flag = 0;
		Flood(baby);
		if (flag == 0) break;//못먹은 경우
	}
	return ans;
}

void input() {
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
			int tmp = MAP[y][x];
			if (tmp == 0) continue;
			if (1 <= tmp && tmp <= 6) fish_cnt++;
			else if (tmp == 9) {
				sy = y;
				sx = x;
				MAP[y][x] = 0;//상어 없애기
			}
		}
	}
}

int main() {
	input();
	cout <<sol();
	return 0;
}