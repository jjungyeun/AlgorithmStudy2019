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

// reached[u][v]: u���� v�� ���� ��ΰ� �����ϴ���
// reached ����� ������ִ� �Լ�(BFS)
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

// 1������ �� ���������� �ִܰŸ��� ����Ͽ� upper�� �����ϴ� �Լ�
// ���� ����Ŭ�� �ִٸ� -INF�� ��ȯ
int fastest() {
	canReach();
	
	upper = vector<int>(N + 1, INF);
	upper[1] = 0;
	bool updated = false;

	// v�� ��ȸ
	for (int v = 0;v < N;v++) {
		updated = false;
		for (int here = 1;here <= N;here++) {
			for (int idx = 0;idx < adj[here].size();idx++) {
				int there = adj[here][idx].first,
					cost = adj[here][idx].second;
				// ���Ѱ����� ������ ���Ѱ� ������Ʈ
				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}
		// ���̻� ������Ʈ�� �� ������ ����
		if (!updated)
			break;
	}

	// V��° ��ȸ���� ������Ʈ�Ǹ� ���� ����Ŭ�� �ִ°�
	if (updated) {
		for (int here = 1;here <= N;here++) {
			for (int idx = 0;idx < adj[here].size();idx++) {
				int there = adj[here][idx].first,
					cost = adj[here][idx].second;

				if (upper[there] > upper[here] + cost) 
					// ���� ����Ŭ�� �ִٸ�, ��������� ����Ŭ�� ���� ��ΰ� ������ -INF ��ȯ
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

	// ���� ����Ŭ�� ������ ��
	if (fastest() == -INF) {
		cout << -1 << endl;
		return 0;
	}

	for (int i = 2;i <= N;i++) {
		// ��������� �������� ���ϸ� -1 ��ȯ
		if (!reached[1][i])
			cout << -1 << endl;
		else
			cout << upper[i] << endl;
	}
}