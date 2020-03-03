#include <cstdio>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

typedef pair<double,int> weight;
typedef priority_queue<weight, vector<weight>, greater<weight>> PQ;
const double INF = 987654321;

int T, N, M;
vector<vector<pair<int,double>>> adj;
vector<double> dist;

// 0�� �������� �� ���������� �ּ� weight�� ���Ѵ�
double dijkstra() {
	PQ pq;
	dist = vector<double>(N, INF);		// �� ���������� weight�� log���� ����
	pq.push(make_pair(log(1), 0));		// weight�� ���ذ����ϹǷ� 0�� ������ 1�� ����
	dist[0] = log(1);

	while (!pq.empty()) {
		double hereDist = pq.top().first;
		int here = pq.top().second; 
		pq.pop();

		// �� ���� weight�� �湮�� ���� �ִٸ� �н�
		if (dist[here] < hereDist)
			continue;

		// ������ ������ �� �湮�� ���� ������(INF�� �ƴϸ�)
		// �� �ּ� weight�� ����� ��쿡 dist�� �����ϰ� �湮�Ѵ�
		for (int i = 0;i < adj[here].size();i++) {
			int there = adj[here][i].first; double w = adj[here][i].second;
			double cost = log(w) + hereDist;

			if (cost < dist[there]) {
				dist[there] = cost;
				pq.push(make_pair(cost, there));
			}
			
		}
	}

	// ���� ������ ������ dist�� ��ȯ�Ѵ�
	return exp(dist[N - 1]);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);

		int a, b; double c;
		adj = vector<vector<pair<int, double>>>(N);

		for (int i = 0;i < M;i++) {
			scanf("%d %d %lf", &a, &b, &c);
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		}

		printf("%.10lf\n", dijkstra());
	}
}