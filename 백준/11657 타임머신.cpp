#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int u, v, t;
const int INF = 987654321;
int reached[501][501] = { 0, };
vector<int> upper;
vector<vector<pair<int, int>>> adj;

// reached[u][v]: u에서 v로 가는 경로가 존재하는지
// reached 행렬을 계산해주는 함수(BFS)
void canReach() {
	for (int i = 1;i <= N;i++) {
		queue<int> q;
		q.push(i);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (int j = 0;j < adj[here].size();j++) {
				int there = adj[here][j].first;
				if (!reached[i][there]) {
					q.push(there);
					reached[i][there] = 1;
				}
			}
		}
	}
}

// 1번부터 각 정점까지의 최단거리를 계산하여 upper에 저장하는 함수
// 음수 사이클이 있다면 -INF를 반환
int fastest() {
	canReach();
	
	upper = vector<int>(N + 1, INF);
	upper[1] = 0;
	bool updated = false;

	// v번 순회
	for (int v = 0;v < N;v++) {
		updated = false;
		for (int here = 1;here <= N;here++) {
			for (int idx = 0;idx < adj[here].size();idx++) {
				int there = adj[here][idx].first,
					cost = adj[here][idx].second;
				// 상한값보다 작으면 상한값 업데이트
				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}
		// 더이상 업데이트할 게 없으면 종료
		if (!updated)
			break;
	}

	// V번째 순회에도 업데이트되면 음수 사이클이 있는것
	if (updated) {
		for (int here = 1;here <= N;here++) {
			for (int idx = 0;idx < adj[here].size();idx++) {
				int there = adj[here][idx].first,
					cost = adj[here][idx].second;

				if (upper[there] > upper[here] + cost) 
					// 음수 사이클이 있다면, 출발점에서 사이클로 오는 경로가 있으면 -INF 반환
					if (reached[1][here])
						return -INF;
			}
		}
	}
	return 0;
}

int main() {
	cin >> N >> M;
	adj = vector<vector<pair<int, int>>>(N + 1);
	while (M--) {
		cin >> u >> v >> t;
		adj[u].push_back(make_pair(v, t));
	}

	// 음수 사이클이 존재할 때
	if (fastest() == -INF) {
		cout << -1 << endl;
		return 0;
	}

	for (int i = 2;i <= N;i++) {
		// 출발점에서 도달하지 못하면 -1 반환
		if (!reached[1][i])
			cout << -1 << endl;
		else
			cout << upper[i] << endl;
	}
}