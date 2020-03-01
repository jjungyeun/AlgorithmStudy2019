#include <iostream>
#include <queue>

using namespace std;

const int MOD = 20090711;

int C, N, A, B;
priority_queue<int, vector<int>, less<int>> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

// 난수 생성기
struct RNG
{
	int seed, a, b;
	RNG(int _a, int _b): a{_a}, b{_b}, seed{1983} {}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a + b)) % MOD;
		return ret;
	}
};

// 숫자를 하나씩 n개까지 추가할 때마다 바뀌는 중간값의 합을 반환
int getMedianSum(int n, RNG rng) {
	// 초기화
	int ret = 0;
	maxHeap = priority_queue<int, vector<int>, less<int>>();
	minHeap = priority_queue<int, vector<int>, greater<int>>();
	
	// n번 반복
	for (int cnt = 1;cnt <= n;cnt++) {
		// maxHeap의 크기가 minHeap와 같거나 하나 더 커야함
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());

		// minHeap의 top이 maxHeap의 top보다 작으면 둘이 교체
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b); minHeap.push(a);
		}
		
		// maxHeap의 top이 항상 중간값
		ret = (ret + maxHeap.top()) % MOD;
	}
	return ret;
}


int main() {
	cin >> C;
	while (C--) {
		cin >> N >> A >> B;
		cout << getMedianSum(N, RNG(A, B)) << endl;
	}
}