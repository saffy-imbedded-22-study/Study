/*
문제 유의사항
- 자신 크기보다 큰 칸 이동 X
- 먹는건 자기보다 작은거만.
- 먹을 수 있는게 많으면 가장 가까운거. 거리 가까울시 1.위 2. 왼쪽
- 자신의 크기와 같은 수 만큼 물고기 먹을때마다 성장.

1. 성장할때마다 CheckMove 함수 통해서 CantMove에 현재 이동 불가능한 지점 1로 채워주기.
2. 먹기 전에 항상 현재 위치에서 모든 지점까지 최단거리 계산 후, 먹을 수 있는 것들중 가장 가까운 칸 찾기.


*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int diry[4] = {-1, 0, 1, 0};	// 방향 설정을 위, 좌 먼저 해줌으로써 문제 조건 해결.
int dirx[4] = {0, -1, 0, 1};

int N;				  // 공간의 크기
int Map[20][20];	  // 맵
int CantMove[20][20]; // 이동 가능 위치 저장
int DAT[20][20];	// 최단거리 저장
struct node
{
	int y, x;
	int dist;
};

void CheckMove(int level)	// 현재 크기 입력받음.
{

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] > level)	// 현재 크기보다 크면
			{
				CantMove[i][j] = 1; // 이동 불가능
			}
			else
			{
				CantMove[i][j] = 0;
			}
		}
	}
}

node CanEat(int level, int nowy, int nowx)	// 현재 크기, 현재 위치 입력.
{
	vector<node> v; // 먹을 수 있는거 저장

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] < level && Map[i][j] > 0) // 내 몸집보다 작으면 먹을 수 있음
			{
				v.push_back({i, j, 0});
			}
		}
	}

	queue<node> q;
	q.push({nowy, nowx});

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			DAT[i][j] = 99999;	// 처음에 21e8로 초기화했는데, 문제 발생
		}
	}
	DAT[nowy][nowx] = 0;	// 시작 위치 0으로 설정

	while (!q.empty())
	{
		node now = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int dy = now.y + diry[dir];
			int dx = now.x + dirx[dir];
			if (dy >= N || dy < 0 || dx >= N || dx < 0)	continue;	// 경계선
			if (CantMove[dy][dx] == 1)	continue;					// 이동할 수 없는 칸
			if (DAT[dy][dx] <= DAT[now.y][now.x] + 1)	continue;	// 이동할 칸이 더 적은 횟수로 갈 수 있으면 안가도 됨
			DAT[dy][dx] = DAT[now.y][now.x] + 1;
			q.push({dy, dx, DAT[dy][dx]});
		}
	}

	node Min = {0, 0, 99999};	
	/*
	21e8 사용할 때 주의점!

	21e8은 기본적으로 double.

	int Max = 21e8 같은 경우 자동으로 21e8을 int로 변환 후 넣어주는데,

	node 를 {int, int, int} 형식으로 만들었을 때,

	{int, int, int} = {0, 0, 21e8} 을 하면 int에 double 넣는것처럼 되어서 오류가 발생!

	vs2022에서는 알아서 변환해주는데, 낮은 버전에서는 안해주니까 주의!!

	백준에 제출했을때도 안됐음.

	21e8을 사용하고 싶으면

	{int, int, int} = {0, 0, int(21e8)}

	또는

	{int, int, int} = {0, 0, 2100000000}

	해주면 사용 가능

	*/
	for (int i = 0; i < v.size(); i++)	// v에 먹을 수 있는 물고기들 정보
	{
		if (Min.dist > DAT[v[i].y][v[i].x])	// 
		{
			v[i].dist = DAT[v[i].y][v[i].x];
			Min = v[i];	
		}
	}
	return Min;	// 가장 가까운 물고기 좌표, 거리 리턴
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	node start = {0, 0, 0};
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 9)
			{
				start = {i, j, 0};
				Map[i][j] = 0;
			}
		}
	}

	int level = 2;	// 크기
	int exp = 0;	// 경험치
	CheckMove(2);	// 크기 2일때 이동 가능 위치 세팅

	node now = start;
	node next = CanEat(2, start.y, start.x);	// 현재 위치에서 가장 가까운 값 찾기
	int ans = 0;
	while (1)
	{
		if (next.dist == 99999)	// 먹을 수 있는게 없으면 종료
		{
			break;
		}

		ans += next.dist;			// 누적 이동 거리
		Map[next.y][next.x] = 0;	// 먹었으면 0 처리
		exp++;
		if (exp == level)	// 현재 크기와 경험치 같아지면 크기 증가
		{
			level++;
			exp = 0;
			CheckMove(level);	// 갈 수 있는 곳 다시 갱신
		}
		now = next;	// 현재 위치 갱신	
		next = CanEat(level, now.y, now.x); // 다음 먹을거 찾기
	}

	cout << ans;

	return 0;
}