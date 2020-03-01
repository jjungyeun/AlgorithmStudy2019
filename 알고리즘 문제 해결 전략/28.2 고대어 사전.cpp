#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int C, n;
vector<string> words;
vector<vector<int>> adj;
vector<int> visited;
vector<int> order;

void makeGraph() {
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	for (int i = 0;i < n - 1;i++) {
		int len = min(words[i].length(), words[i + 1].length());
		for (int j = 0;j < len;j++) {
			if (words[i][j] != words[i + 1][j]) {
				int a = words[i][j] - 'a';
				int b = words[i + 1][j] - 'a';
				adj[a][b] = 1;
				//cout << "<" << words[i][j] << ", " << words[i + 1][j] << ">" << endl;
				break;
			}
		}
	}
	return;
}

void dfs(int crnt) {
	//cout << "visit " << crnt << endl;
	visited[crnt] = 1;
	for (int i = 0;i < 26;i++) {
		if (!visited[i] && adj[crnt][i]) {
			dfs(i);
		}
	}
	order.push_back(crnt);
}

vector<int> topologySort() {
	int m = adj.size();
	visited = vector<int>(m, 0);
	order.clear();


	for (int i = 0;i < m;i++) {
		if (!visited[i])
			dfs(i);
	}
	reverse(order.begin(), order.end());

	for (int i = 0;i < m;i++) {
		for (int j = i+1;j < m;j++) {
			if (adj[order[j]][order[i]])
				return vector<int>();
		}
	}
	return order;
}

int main() {

	cin >> C;
	while (C--) {
		cin >> n;
		words.clear();
		for (int i = 0;i < n;i++) {
			string tmp;
			cin >> tmp;
			words.push_back(tmp);
		}

		makeGraph();
		vector<int> ans = topologySort();
		if (ans.size() == 0)
			cout << "INVALID HYPOTHESIS";
		else
			for (int i = 0;i < ans.size();i++) {
				char apbt = ans[i] + 'a';
				cout << apbt;
			}
		cout << endl;
	}

	return 0;
}