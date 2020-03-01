#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;
const int INF = 987654321;

int C;
string num;
int cache[10002];

int difficulty(int begin, int size) {
	string s = num.substr(begin, size);
	int len = s.size();
	int diff = s.at(1) - s.at(0);

	if (diff == 0) {
		for (int i = 2;i < len;i++) {
			if (s.at(i) != s.at(0))
				return 10;
		}
		return 1;
	}

	int diff2 = s.at(2) - s.at(1);
	if (diff == diff2) {
		for (int i = 3;i < len;i++) {
			if (s.at(i) - s.at(i - 1) != diff)
				return 10;
		}
		return ((diff == 1)||(diff == -1) ? 2 : 5);
	}

	if (diff + diff2 == 0) {
		if (len == 4 || len == 5) {
			if (s.at(3) - s.at(2) != diff)
				return 10;
			if (len == 5 && s.at(4) - s.at(3) != diff2)
				return 10;
		}
		return 4;
	}

	return 10;
}

int memorize(int start) {
	if (start == num.size())
		return 0;

	int& ret = cache[start];
	if (ret != -1)
		return ret;

	ret = INF;
	for (int len = 3;len <= 5;len++) {
		if (start + len <= num.size())
			ret = min(ret, difficulty(start, len) + memorize(start + len));
	}

	return ret;
}

int main() {
	cin >> C;
	while (C--) {
		cin >> num;
		memset(cache, -1, sizeof(cache));
		cout << memorize(0) << endl;
	}
	return 0;
}