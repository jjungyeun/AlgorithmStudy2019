#include <cstdio>
#include <string>
#include <string.h> // 답안 제출용
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
	if (ret != -1)	// cache에 저장되어있는 경우 바로 반환
		return ret;
	
	// bc - 범위 벗어나는 경우 -> 0
	if (w > W.size() || s > S.size()) {
		ret = 0; return ret;
	}

	// bc - 비교 끝난 경우 -> 1
	if (w == (W.size()) && s == (S.size())) {
		ret = 1; return ret;
	}

	// bc - 글자는 남았는데 패턴은 끝난 경우 -> 0
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

		// wild card 입력
		W.clear();
		cin >> W;

		// 단어 N개 입력받고 패턴과 일치하는지 확인
		cin >> N;
		for (int i = 0;i < N;i++) {
			S.clear();
			cin >> S;
			// cache를 -1로 초기화
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