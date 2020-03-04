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

// �� ȭ�� ��ҿ� �ҹ����� �����ϱ���� �ɸ��� �ּҽð��� ���� ��ȯ
int dijkstraSum() {
	PQ pq;
	dist = vector<int>(V + 1, INF);

	// ��� �ҹ漭�� ����� 0�� �������� �����Ѵ�
	pq.push(make_pair(0, 0));
	dist[0] = 0;

	while (!pq.empty()) {
		int hereDist = pq.top().first, here = pq.top().second;
		pq.pop();

		// �� ����� ��η� �� ���� ������ �н�
		if (hereDist > dist[here])
			continue;

		// ������ ������ �� ª�� �ð��� �� �� �ִٸ� dist���� �� ť�� �߰�
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

		// ȭ�糭 ������ ��ȣ ����
		for (int i = 0;i < n;i++) {
			int tmp;
			scanf("%d", &tmp);
			fire.push_back(tmp);
		}

		// �ҹ漭���� ��ȣ ����
		// ���ͽ�Ʈ�� �Լ��� �ѹ��� ����ϱ� ���� ���ο� 0�� ���� �߰�
		for (int i = 0;i < m;i++) {
			int tmp;
			scanf("%d", &tmp);
			adj[0].push_back(make_pair(tmp, 0));
		}

		printf("%d\n", dijkstraSum());
	}
}