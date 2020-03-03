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

// 0번 정점부터 각 정점까지의 최소 weight를 구한다
double dijkstra() {
	PQ pq;
	dist = vector<double>(N, INF);		// 각 정점까지의 weight의 log값을 저장
	pq.push(make_pair(log(1), 0));		// weight를 곱해가야하므로 0번 정점은 1로 세팅
	dist[0] = log(1);

	while (!pq.empty()) {
		double hereDist = pq.top().first;
		int here = pq.top().second; 
		pq.pop();

		// 더 작은 weight로 방문한 적이 있다면 패스
		if (dist[here] < hereDist)
			continue;

		// 인접한 정점들 중 방문한 적이 없으며(INF가 아니며)
		// 더 최소 weight를 만드는 경우에 dist를 갱신하고 방문한다
		for (int i = 0;i < adj[here].size();i++) {
			int there = adj[here][i].first; double w = adj[here][i].second;
			double cost = log(w) + hereDist;

			if (cost < dist[there]) {
				dist[there] = cost;
				pq.push(make_pair(cost, there));
			}
			
		}
	}

	// 제일 마지막 정점의 dist를 반환한다
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