#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N; // 맵 크기
int people; //사람 인원 수
int ans; //답
int maxnum;
int MAP[11][11];

struct yx
{
	int y, x;
};

vector<yx> stairs; //계단 좌표
vector<int> stai; //계단 2개에 대한 경우의 수
vector<yx> peo; //사람 좌표

int simulation(int s)
{
	vector<int> vect; //사람에서 계단까지의 거리 계산

	for (int i = 0; i < people; i++) //계산해서 벡터에 넣기
	{
		if (stai[i] == s)
		{
			vect.push_back(abs(peo[i].x - stairs[s].x) + abs(peo[i].y - stairs[s].y));
		}
	}

	if (vect.size() == 0) //만약 s번째 계단에 온 사람이 없으면 리턴
		return 0;

	int time = 0; //시간계산
	int stairpeo = 0;	//계단에 올라가있는 사람의 수
	int st[3] = { 0 }; //3명만 가능
	int leng = MAP[stairs[s].y][stairs[s].x]; //계단의 길이

	while (1)
	{
		time++;

		for (int i = 0; i < vect.size(); i++) //시간당 사람에서 계단 거리 줄여주기
		{
			vect[i]--;
			if (vect[i] == 0) //만약 계단에 도착했다면 계단에 올라가있는 사람 증가
				stairpeo++;
		}

		if (stairpeo != 0) //계단에 도착한 사람이 있으면
		{
			for (int i = 0; i < 3; i++) 
			{
				if (st[i] == 0) //3명이 다 안찼으면
				{
					st[i] = leng; //계단 길이만큼을 넣어주고
					stairpeo--; // 사람 한명 줄여주기
					if (stairpeo == 0) // 사람이 더이상 없으면 break;
						break;
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (st[i] > 0) {
				st[i]--; //시간당 계단 한칸씩 내려가기
			}
		}

		int checkvect = 1; // 계단에서 사람까지의 거리 다 갔는지 체크
		int checkst = 1; // 계단 다 내려갔는지 체크

		for (int i = 0; i < vect.size(); i++)
		{
			if (vect[i] > 0) //아직 다 계단까지 도착못했으면 
			{
				checkvect = 0;
				break;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (st[i] > 0) //아직 계단에 사람이 있으면
			{
				checkst = 0;
				break;
			}
		}

		if (checkvect == 1 && checkst == 1 && stairpeo == 0) //계단까지,계단에, 사람 모두 없을 경우에 break
			break;
	}
	return time + 1; // 계단에 도착하고 바로 내려가기 시작했기 때문에 +1

}

void dfs(int k) //계단 가능한 경우의 수
{
	if (k == people)
	{

		int stair1 = simulation(0);
		int stair2 = simulation(1);

		//둘 중에 더 큰 시간으로 해줘야함
		maxnum = max(stair1, stair2);

		//최소 값 갱신
		ans = min(maxnum, ans);

		return;
	}

	for (int i = 0; i < 2; i++)
	{
		stai.push_back(i);
		dfs(k + 1);
		stai.pop_back();
	}
}


int main(void)
{
	int test;
	cin >> test;

	for (int te = 1; te <= test; te++)
	{
		cin >> N;
		ans = 21e8;
		maxnum = 0;
		stairs.clear();
		stai.clear();
		peo.clear();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> MAP[i][j];
				if (MAP[i][j] == 1)
				{
					peo.push_back({ i,j }); //사람 좌표
				}
				if (MAP[i][j] >= 2 && MAP[i][j] <= 10)
				{
					stairs.push_back({ i,j }); //계단 좌표
				}
			}
		}

		people = peo.size(); //사람 수
		dfs(0);

		cout << "#" << te << " " << ans << endl;
	}
}