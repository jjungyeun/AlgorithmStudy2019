#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> Pair;
typedef priority_queue<Pair, vector<Pair>, greater<Pair>> PQ;
const int INF = 987654321;

int C, V, E, n, m;
vector<vector<Pair>> adj;
vector<int> fire, dist;

// 각 화재 장소에 소방차가 도착하기까지 걸리는 최소시간의 합을 반환
int dijkstraSum() {
	PQ pq;
	dist = vector<int>(V + 1, INF);

	// 모든 소방서에 연결된 0번 정점에서 시작한다
	pq.push(make_pair(0, 0));
	dist[0] = 0;

	while (!pq.empty()) {
		int hereDist = pq.top().first, here = pq.top().second;
		pq.pop();

		// 더 가까운 경로로 온 적이 있으면 패스
		if (hereDist > dist[here])
			continue;

		// 인접한 정점에 더 짧은 시간에 갈 수 있다면 dist갱신 및 큐에 추가
		for (int i = 0;i < adj[here].size();i++) {
			int there = adj[here][i].first;
			int cost = hereDist + adj[here][i].second;

			if (cost < dist[there]) {
				dist[there] = cost;
				pq.push(make_pair(cost, there));
			}
		}
	}

	int ret = 0;
	for (int i = 0;i < fire.size();i++) {
		ret += dist[fire[i]];
	}
	return ret;
}

int main() {
	int a, b, t;
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d %d %d", &V, &E, &n, &m);
		adj = vector<vector<Pair>>(V + 1);
		fire.clear();
		for (int i = 0;i < E;i++) {
			scanf("%d %d %d", &a, &b, &t);
			adj[a].push_back(make_pair(b, t));
			adj[b].push_back(make_pair(a, t));
		}

		// 화재난 집들의 번호 저장
		for (int i = 0;i < n;i++) {
			int tmp;
			scanf("%d", &tmp);
			fire.push_back(tmp);
		}

		// 소방서들의 번호 저장
		// 다익스트라 함수를 한번만 사용하기 위해 새로운 0번 정점 추가
		for (int i = 0;i < m;i++) {
			int tmp;
			scanf("%d", &tmp);
			adj[0].push_back(make_pair(tmp, 0));
		}

		printf("%d\n", dijkstraSum());
	}
}