#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int c, n, s;
vector<int> list;
int cache[101][11];
int sbSum[101], sbSqSum[101];
const int INF = 987654321;

void sortList() {
	sort(list.begin(), list.end());
	sbSum[0] = list[0];
	sbSqSum[0] = list[0] * list[0];

	for (int i = 1;i < n;i++) {
		sbSum[i] = sbSum[i - 1] + list[i];
		sbSqSum[i] = sbSqSum[i - 1] + list[i] * list[i];
	}

	return;
}

int calErr(int start, int len) {
	int sum = sbSum[start + len-1] - sbSum[start-1];
	int sqSum = sbSqSum[start + len - 1] - sbSqSum[start - 1];
	int avg = int(0.5 + (double)sum / len);
	int err = sqSum + avg * avg * len - 2 * avg * sum;
	//printf("((%d, %d)) err: %d\n", start, start + len - 1, err);
	return err;
}

int quantize(int start, int parts) {
	//printf("\n<<%d, %d>>\n", start, parts);
	if (start == n)
		return 0;
	if (parts == 0)
		return INF;

	int& ret = cache[start][parts];
	if (ret != -1)
		return ret;

	ret = INF;
	for (int i = start + 1;i <= n;i++) {
		ret = min(ret, calErr(start, i - start) + quantize(i, parts - 1));
	}

	return ret;
}

int main() {

	scanf("%d", &c);
	while (c--) {
		scanf("%d %d", &n, &s);

		int tmp;
		list.clear();
		for (int i = 0;i < n;i++) {
			scanf("%d", &tmp);
			list.push_back(tmp);
		}

		memset(cache, -1, sizeof(cache));
		sortList();

		int ans = quantize(0, s);
		printf("%d\n", ans);

	}

	return 0;
}