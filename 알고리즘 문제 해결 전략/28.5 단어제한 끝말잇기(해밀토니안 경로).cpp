#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int C, n;
vector<string> words, order;
vector<int> seen;
vector<vector<int>> adj;

void getGraph() {
	adj = vector<vector<int>>(n, vector<int>(n, 0));
	for (int i = 0;i < n;i++) {
		char endChar = words[i][words[i].size() - 1];
		for (int j = 0;j < n;j++) {
			if (i != j && endChar == words[j][0]) 
				adj[i][j] = 1;
		}
	}
}

bool isChain(vector<string> list) {
	for (int i = n-1;i > 0;i--) {
		if (list[i][list[i].length() - 1] != list[i - 1][0])
			return false;
	}
	return true;
}

void dfs(int here) {
	seen[here] = 1;
	//cout << "visit " << words[here] << endl;
	for (int i = 0;i < n;i++) {
		if (!seen[i] && adj[here][i]) {
			dfs(i);
		}
	}
	order.push_back(words[here]);
}

vector<string> wordChain() {
	getGraph();
	for (int i = 0;i < n;i++) {
		order.clear();
		seen = vector<int>(n, 0);
		dfs(i);
		if (order.size() == n && isChain(order)) {
			break;
		}

		//// -------´«¹ö±ë----------
		//cout << "fail : ";
		//for (int j = 0;j < order.size();j++) {
		//	cout << order[order.size() - 1 - j] << " ";
		//}
		//cout << endl;
		//// -----------------------
	}
	if (order.size() == n)
		reverse(order.begin(), order.end());
	else
		order = vector<string>();
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
		vector<string> ans = wordChain();
		if (ans.size() == 0)
			cout << "IMPOSSIBLE";
		else {
			for (int i = 0;i < n;i++)
				cout << ans[i] << " ";
		}
		cout << endl;
	}
	return 0;
}