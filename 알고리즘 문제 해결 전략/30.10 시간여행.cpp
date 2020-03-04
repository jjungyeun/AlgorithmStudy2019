#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int C, G, W;
const int INF = 987654321;
int reached[100][100];
vector<int> upper;
vector<vector<pair<int,int>>> adj, adjRev;

// reached[u][v]: u���� v�� ���� ��ΰ� �����ϴ���
// reached ����� ������ִ� �Լ�(BFS)
void canReach() {
	memset(reached, 0, sizeof(reached));
	for (int i = 0;i < G;i++) {
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

int goToAndromeda(vector<vector<pair<int, int>>> a) {
	upper = vector<int>(G, INF);
	upper[0] = 0;

	// V-1�� ��ȸ
	for (int v = 0;v < G-1;v++) {
		// �� ������ ������ ��ȸ�ϸ� upper ��ȭ
		for (int here = 0; here < G;here++) {
			for (int idx = 0;idx < a[here].size();idx++) {
				int there = a[here][idx].first, cost = a[here][idx].second;

				// ���Ѱ����� �� �۾����� ������Ʈ
				if (upper[there] > upper[here] + cost) 
					upper[there] = upper[here] + cost;
				
			}
		}
	}

	// V��° ��ȸ
	// �������� ���� ��ο� ���� ����Ŭ�� ������ -INF ��ȯ
	for (int here = 0;here < G;here++) {
		for (int i = 0;i < a[here].size();i++) {
			int there = a[here][i].first, cost = a[here][i].second;
			// ���� ����Ŭ�� ���� ��
			if (upper[there] > upper[here] + cost)
				// ���� ����Ŭ�� �����ϴ� ��ΰ� �ִٸ� -INF ��ȯ
				if (reached[0][here] && reached[here][1])
					return -INF;
		}
	}
	
	return upper[1];
}

int main() {
	int a, b, d;
	cin >> C;
	while (C--) {
		cin >> G >> W;
		adj = adjRev = vector<vector<pair<int, int>>>(G);
		while (W--) {
			cin >> a >> b >> d;
			adj[a].push_back(make_pair(b, d));
			adjRev[a].push_back(make_pair(b, -d));
		}
		canReach();
		if (!reached[0][1]) {
			cout << "UNREACHABLE" << endl;
			continue;
		}
		int ans = goToAndromeda(adj);
		if (ans == -INF)
			cout << "INFINITY ";
		else
			cout << ans << " ";

		ans = goToAndromeda(adjRev);
		if (ans == -INF)
			cout << "INFINITY" << endl;
		else
			cout << -ans << endl;
	}
}