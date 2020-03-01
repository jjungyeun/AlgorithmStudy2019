#include <iostream>
#include <vector>

using namespace std;

int C, N, D, P, T, Q;
vector<vector<int>> roads;

double cache[51][101];
int linked[50][50];

void clearCache() {
	for (int i = 0;i <= N;i++) {
		for (int j = 0;j <= D;j++) {
			cache[i][j] = -1.0;

		}
	}
}

double dunivalHere(int A, int days) {
	//cout << "<" << A << ", " << days << ">" << endl;
	double& ret = cache[A][days];
	if (ret > -0.5) {
		cout << "using cache" << endl;
		return ret;
	}


	int lenRoads = roads[A].size();
	//cout << 1.0 / double(lenRoads) << endl;

	if (days == 0) {
		if (A == Q)
			return 1.0;
		else
			return 0.0;
	}
	if (days == 1) {
		if (linked[A][Q])
			return 1 / double(lenRoads);
		else
			return 0;
	}

	ret = 0;
	for (int i = 0;i < lenRoads;i++) {
		ret += dunivalHere(roads[A][i], days - 1);
	}
	ret /= double(lenRoads);
	return ret;
}

int main() {

	cout << fixed;
	cout.precision(8);

	cin >> C;
	while (C--) {
		cin >> N >> D >> P;
		roads.clear();
		for (int i = 0;i < N;i++) {
			vector<int> tmp;
			for (int j = 0;j < N;j++) {
				int num;
				cin >> num;
				if (num == 1) {
					tmp.push_back(j);
					linked[i][j] = linked[j][i] = 1;
				}
				else
					linked[i][j] = linked[j][i] = 0;
			}
			roads.push_back(tmp);
		}
		cin >> T;
		while (T--) {
			cin >> Q;
			clearCache();
			cout << dunivalHere(P, D) << " ";
		}
		cout << endl;
	}

	return 0;
}


/* 
// 속도 향상 ver

#include <iostream>
#include <vector>

using namespace std;

int C, N, D, P, T, Q;
vector<vector<int>> roads;

double cache[51][101];
int linked[50][50];

void clearCache() {
	for (int i = 0;i <= N;i++) {
		for (int j = 0;j <= D;j++) {
			cache[i][j] = -1.0;

		}
	}
}

double dunivalHere(int here, int days) {
	//cout << "<" << here << ", " << days << ">" << endl;

	if (days == 0)
		return (here == P ? 1.0 : 0.0);

	double& ret = cache[here][days];
	if (ret > -0.5) {
		//cout << "using cache" << endl;
		return ret;
	}

	ret = 0.0;
	for (int i = 0;i < roads[here].size();i++) {
		int there = roads[here][i];
		ret += dunivalHere(there, days - 1) / roads[there].size();
	}
	return ret;
}

int main() {

	cout << fixed;
	cout.precision(8);

	cin >> C;
	while (C--) {
		cin >> N >> D >> P;
		roads.clear();
		clearCache();
		for (int i = 0;i < N;i++) {
			vector<int> tmp;
			for (int j = 0;j < N;j++) {
				int num;
				cin >> num;
				if (num == 1) {
					tmp.push_back(j);
					linked[i][j] = linked[j][i] = 1;
				}
				else
					linked[i][j] = linked[j][i] = 0;
			}
			roads.push_back(tmp);
		}
		cin >> T;
		while (T--) {
			cin >> Q;
			cout << dunivalHere(Q, D) << " ";
		}
		cout << endl;
	}

	return 0;
}
*/