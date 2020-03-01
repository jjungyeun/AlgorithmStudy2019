#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int C, n;
vector<string> words, order;
vector<int> inDegree, outDegree;
vector<vector<int>> adj;
vector<string> graph[26][26];

void getGraph() {
	for (int i = 0;i < 26;i++)
		for (int j = 0;j < 26;j++)
			graph[i][j].clear();
	inDegree = outDegree = vector<int>(26, 0);
	adj = vector<vector<int>>(26, vector<int>(26, 0));

	for (int i = 0;i < n;i++) {
		int a = words[i][0] - 'a';
		int b = words[i][words[i].length() - 1] - 'a';
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outDegree[a]++; inDegree[b]++;
	}
}

void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0;there < adj.size();there++) {
		while (adj[here][there]>0) {
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}

vector<int> getEulerTrainOrCircuit() {
	vector<int> circuit;
	for (int i = 0;i < 26;i++) {
		if (outDegree[i] == inDegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	for (int i = 0;i < 26;i++) {
		if (outDegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	return circuit;
}

bool checkEuler() {
	int start = 0, end = 0;
	for (int i = 0;i < 26;i++) {
		int degree = outDegree[i] - inDegree[i];
		if (degree < -1 || degree > 1)
			return false;
		if (degree == 1)
			start++;
		if (degree == -1)
			end++;
	}
	return (start == 1 && end == 1) || (start == 0 && end == 0);
}

string wordChain() {
	getGraph();
	if (!checkEuler())
		return "IMPOSSIBLE";

	vector<int> circuit = getEulerTrainOrCircuit();

	if(circuit.size() != words.size() + 1)
		return "IMPOSSIBLE";
	reverse(circuit.begin(), circuit.end());

	string ans;
	for (int i = 1;i < circuit.size();i++) {
		int a = circuit[i - 1], b = circuit[i];
		if (ans.size()) 
			ans += " ";
		ans += graph[a][b].back();
		graph[a][b].pop_back();
	}

	return ans;
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
		string ans = wordChain();
		cout << ans << endl;
	}
	return 0;
}