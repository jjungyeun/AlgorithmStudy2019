#include <cstdio>
#include <string>
#include <string.h> // ��� �����
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int C, N;
string W, S;
vector<string> ans;

int cache[101][101] = { 0, };

int wildCard(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1)	// cache�� ����Ǿ��ִ� ��� �ٷ� ��ȯ
		return ret;
	
	// bc - ���� ����� ��� -> 0
	if (w > W.size() || s > S.size()) {
		ret = 0; return ret;
	}

	// bc - �� ���� ��� -> 1
	if (w == (W.size()) && s == (S.size())) {
		ret = 1; return ret;
	}

	// bc - ���ڴ� ���Ҵµ� ������ ���� ��� -> 0
	if (w == W.size()) {
		ret = 0; return ret;
	}

	char key = W.at(w);
	if (key != '*') {
		if (s == S.size())
			ret = 0;
		else if (key == '?' || S.at(s) == key)
			ret = wildCard(w + 1, s + 1);
	}
	else
		ret = wildCard(w + 1, s) || wildCard(w, s + 1);

	if (ret == -1)
		ret = 0;

	return ret;
}

int main() {

	cin >> C;

	while (C--) {
		ans.clear();

		// wild card �Է�
		W.clear();
		cin >> W;

		// �ܾ� N�� �Է¹ް� ���ϰ� ��ġ�ϴ��� Ȯ��
		cin >> N;
		for (int i = 0;i < N;i++) {
			S.clear();
			cin >> S;
			// cache�� -1�� �ʱ�ȭ
			memset(cache, -1, sizeof(cache));
			
			if (wildCard(0, 0))
				ans.push_back(S);
		}

		sort(ans.begin(), ans.end());
		for (int i = 0;i < ans.size();i++) {
			cout << ans[i] << endl;
		}


	}
	

	return 0;
}