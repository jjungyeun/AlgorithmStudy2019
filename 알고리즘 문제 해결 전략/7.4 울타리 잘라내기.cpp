#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<int> h;

int findMaxBoard(int left, int right) {
	printf("(%d, %d)\n", left, right);
	if (left == right)
		return h.at(left);

	int mid = (left + right) / 2 + 1;	// 오른쪽의 시작점
	printf("mid: %d\n", mid);
	int maxArea = max(findMaxBoard(left, mid - 1), findMaxBoard(mid, right));

	int l = mid - 1, r = mid;
	int height = min(h.at(l), h.at(r));
	maxArea = max(maxArea, height * 2);

	if (right - left == 1)
		return maxArea;

	while (l > left || r < right) {
		if (l > left && (r == right || h.at(l - 1) > h.at(r + 1))) {
			l--;
			height = min(height, h.at(l));
			printf("<< go left (%d, %d)\n", l, r);
		}
		else {
			r++;
			height = min(height, h.at(r));
			printf(">> go right (%d, %d)\n", l, r);
		}
		int cand = height * (r - l + 1);
		maxArea = max(maxArea, cand);
	}
	printf("maxArea: %d\n", maxArea);
	return maxArea;
}

int main() {
	scanf("%d", &N);
	for (int i = 0;i < N;i++) {
		int tmp;
		scanf("%d", &tmp);
		h.push_back(tmp);
	}

	int ans = findMaxBoard(0, N - 1);
	printf("%d\n", ans);

	return 0;
}