#include <iostream>
#include <vector>

using namespace std;

typedef int KeyType;
struct Node
{
	int priority;
	KeyType key;
	Node(KeyType _key, int _priority): key{_key}, priority{_priority} {}
};

vector<Node> heap;

// key�� ���ҷ� �ϰ� �켱���� priority�� ���� ���ο� ��带 ����
void push_heap(vector<Node>& h, KeyType key, int priority) {
	// �� ��带 ����� ���� �� ���� �ִ´�
	Node here(key, priority);
	h.push_back(here);

	// �θ��� �켱������ �ڽź��� ������ ������,
	// Ȥ�� ��Ʈ�� ������ ������ �÷��ش�
	int index = h.size() - 1;
	while (index > 0) {
		int parent = (index - 1) / 2;
		if (h[parent].priority < here.priority) {
			swap(h[index], h[parent]);
			index = parent;
		}
		else break;
	}
}

// �� h���� �ֻ��� ���Ҹ� ������ ��ȯ
Node pop_heap(vector<Node>& h) {
	// ��Ʈ���� ���Ҹ� �����ְ� �� �ڸ��� ������ ���ҷ� ��ü�Ѵ�
	Node ret = h[0];
	h[0] = h[h.size() - 1];
	h.pop_back();

	// ��Ʈ����, �ڽĵ��� �켱������ �ڽź��� ������ �� ���� �ڽ��̶� �ٲ۴�
	int idx = 0;
	while (idx < h.size()) {
		int leftIdx = idx * 2 + 1, rightIdx = leftIdx + 1;

		// leaf node�� �����ϸ� ����
		if (leftIdx >= heap.size())
			break;

		// ����/������ �ڽ� �� ������ ũ�鼭 ���߿� �� ū ���� �ٲ۴�
		int nextIdx = idx;
		if (h[nextIdx].priority < h[leftIdx].priority)
			nextIdx = leftIdx;
		if (rightIdx < h.size() && h[leftIdx].priority < h[rightIdx].priority)
			nextIdx = rightIdx;
		if (nextIdx = idx)
			break;
		swap(h[idx], h[nextIdx]);
		idx = nextIdx;
	}

	return ret;
}

int main() {

}