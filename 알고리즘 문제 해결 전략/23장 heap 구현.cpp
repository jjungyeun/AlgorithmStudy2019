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

// key를 원소로 하고 우선순위 priority를 갖는 새로운 노드를 삽입
void push_heap(vector<Node>& h, KeyType key, int priority) {
	// 새 노드를 만들고 힙의 맨 끝에 넣는다
	Node here(key, priority);
	h.push_back(here);

	// 부모의 우선순위가 자신보다 낮아질 때까지,
	// 혹은 루트에 도달할 때까지 올려준다
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

// 힙 h에서 최상위 원소를 꺼내고 반환
Node pop_heap(vector<Node>& h) {
	// 루트에서 원소를 꺼내주고 그 자리를 마지막 원소로 대체한다
	Node ret = h[0];
	h[0] = h[h.size() - 1];
	h.pop_back();

	// 루트부터, 자식들의 우선순위가 자신보다 높으면 더 높은 자식이랑 바꾼다
	int idx = 0;
	while (idx < h.size()) {
		int leftIdx = idx * 2 + 1, rightIdx = leftIdx + 1;

		// leaf node에 도달하면 종료
		if (leftIdx >= heap.size())
			break;

		// 왼쪽/오른쪽 자식 중 나보다 크면서 둘중에 더 큰 노드랑 바꾼다
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