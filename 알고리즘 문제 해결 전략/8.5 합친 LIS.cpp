#include <stdio.h>
#include <algorithm>

using namespace std;

int C, N, M;
int A[100], B[100];
int cache[101][101];
const long long NEGINF = numeric_limits<long long>::min();

int list(int indexA, int indexB) {
	//printf("<<%d, %d>>\n", indexA, indexB);
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1)
		return ret;

	ret = 2;
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	long long maxElement = max(a, b);

	//printf("a: %d, b: %d -> maxElement: %d\n", a, b, maxElement);

	for (int i = indexA + 1; i < N;i++) {
		if (maxElement < A[i])
			ret = max(ret, list(i, indexB) + 1);
	}

	for (int j = indexB + 1;j < M;j++) {
		if (maxElement < B[j])
			ret = max(ret, list(indexA, j) + 1);
	}

	return ret;
}

int main() {

	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &N, &M);
		for (int i = 0;i < N;i++) {
			scanf("%d", &A[i]);
		}
		for (int i = 0;i < M;i++) {
			scanf("%d", &B[i]);
		}

		memset(cache, -1, sizeof(cache));
		int ans = list(-1, -1) -2;
		printf("%d\n", ans);
	}

	return 0;
}