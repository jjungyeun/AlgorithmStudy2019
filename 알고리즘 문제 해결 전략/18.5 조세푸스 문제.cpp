#include <iostream>

using namespace std;

struct ListNode {
	int element;
	ListNode* prev;
	ListNode* next;
};

int C, N, K;
ListNode nodes[1001];

void deleteNode(ListNode* node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

int main() {

	cin >> C;
	while (C--) {
		cin >> N >> K;
		for (int i = 1;i <= N;i++) {
			nodes[i] = ListNode();
			nodes[i].element = i;
		}
		for (int i = 1;i < N;i++)
			nodes[i].next = &nodes[i + 1];
		for (int i = 2;i <= N;i++)
			nodes[i].prev = &nodes[i - 1];
		nodes[1].prev = &nodes[N];
		nodes[N].next = &nodes[1];

		// 1번 자살
		ListNode* ptr = &nodes[1];
		deleteNode(ptr);

		for (int i = 0;i < N - 3;i++) {
			for (int j = 0;j < K;j++) {
				ptr = ptr->next;
			}
			deleteNode(ptr);
		}

		int alive1 = ptr->prev->element;
		int alive2 = ptr->next->element;

		if (alive1 < alive2)
			cout << alive1 << " " << alive2 << endl;
		else
			cout << alive2 << " " << alive1 << endl;

	}

	return 0;
}



// // Queue를 이용한 풀이
//#include <iostream>
//#include <queue>
//
//using namespace std;
//
//int C, N, K;
//
//int main() {
//
//	cin >> C;
//	while (C--) {
//		cin >> N >> K;
//		queue<int> alive;
//		for (int i = 1;i <= N;i++)
//			alive.push(i);
//
//		while (alive.size() != 2) {
//			alive.pop();
//			int k = (K-1) % alive.size();
//			for (int i = 0;i < k;i++) {
//				int tmp = alive.front();
//				alive.pop();
//				alive.push(tmp);
//			}
//		}
//
//		int a = alive.front(), b = alive.back();
//		if (a < b)
//			cout << a << " " << b << endl;
//		else
//			cout << b << " " << a << endl;
//
//	}
//
//	return 0;
//}