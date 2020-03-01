#include <cstdio>
#include <iostream>
#include <string.h>

using namespace std;

int c, n;
int cache[101][101];
const int MOD = 10000000;

int poly(int rest, int pre) {
	if (rest == 0)
		return 1;

	int& ret = cache[rest][pre];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 1;i <= rest; i++) {
		int state = i + pre - 1;
		if (pre == 0)
			state = 1;
		ret = (ret + state * poly(rest - i, i)) % MOD;
	}
	return ret;
}

int main() {
	cin >> c;

	while (c--) {
		cin >> n;
		memset(cache, -1, sizeof(cache));
		cout << poly(n, 0) << endl;
	}

	return 0;
}