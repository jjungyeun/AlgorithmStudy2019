#include <iostream>
#include <queue>

using namespace std;

const int MOD = 20090711;

int C, N, A, B;
priority_queue<int, vector<int>, less<int>> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

// ���� ������
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

// ���ڸ� �ϳ��� n������ �߰��� ������ �ٲ�� �߰����� ���� ��ȯ
int getMedianSum(int n, RNG rng) {
	// �ʱ�ȭ
	int ret = 0;
	maxHeap = priority_queue<int, vector<int>, less<int>>();
	minHeap = priority_queue<int, vector<int>, greater<int>>();
	
	// n�� �ݺ�
	for (int cnt = 1;cnt <= n;cnt++) {
		// maxHeap�� ũ�Ⱑ minHeap�� ���ų� �ϳ� �� Ŀ����
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());

		// minHeap�� top�� maxHeap�� top���� ������ ���� ��ü
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b); minHeap.push(a);
		}
		
		// maxHeap�� top�� �׻� �߰���
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