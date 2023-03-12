#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, l, r;

int ans; int flag;

struct node {
	int value;
	int num;
};

int country[51][51];

int parent[2501];

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

node pop[2501];

//Find �Լ�
int Find(int now)
{
	if (parent[now] == now)
		return now;

	return parent[now] = Find(parent[now]);
}

//Union �Լ�
void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb)
		return;

	//value = ���� union�� ������, num = ������ ������ ��
	pop[pa].value += pop[pb].value;
	pop[pa].num += pop[pb].num;
	parent[pb] = pa;

}

void move(int y, int x)
{
	for (int i = 0; i < 4; i++)
	{
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

		int value = abs(country[ny][nx] - country[y][x]);

		//value�� ���� �������� ���� ��� union���ش�.
		if (value >= l && value <= r)
		{
			Union(n*y + x, n*ny + nx);
			flag = 1;
		}
	}
}

int main()
{
	cin >> n >> l >> r;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> country[i][j];
			parent[n*i + j] = n * i + j;
			pop[n*i + j] = { country[i][j], 1 };
		}
		
	}

	while (1)
	{
		flag = 0;

		//���Ͽ� �۾�
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				move(i, j);
		}

		//���ճ��� �α� �̵�
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				//pop�� index�� Find(parent[n*i+j])�� ���� : �ش� ������ �θ� ��忡 �����հ� ������ ������ �ֱ� ������
				//parent[n*i+j]�� ����ϵ� ���� �θ� ������ ���� �� �� ��찡 ���� �� �ֱ� ������ find�Լ���
				//�̿��� ���� �θ� ����� �ε������� �����ϵ��� �Ͽ���.
				int new_population = pop[Find(parent[n*i + j])].value / pop[Find(parent[n*i + j])].num;
				country[i][j] = new_population;
			}
		}

		//�ʱ�ȭ
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				parent[n*i + j] = n * i + j;
				pop[n*i + j] = { country[i][j], 1 };
			}
		}
		if (flag)
			ans++;
		else
			break;

	}
	
	cout << ans;

	return 0;
}