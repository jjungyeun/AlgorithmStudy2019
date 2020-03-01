#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N;

// 정수 배열 arr를 start부터 길이 end까지 잘라서 반환
vector<int> slice(vector<int> arr, int start, int end) {
	return vector<int>(arr.begin() + start, arr.begin() + end);
}

// 트리의 전위순회와 중위순회 순서가 주어졌을 때, 후위순회를 출력하는 함수
void printPostOrder(vector<int> preOrder, vector<int> inOrder) {
	// base case

	int len = preOrder.size();
	if (len == 0)
		return;

	int root = preOrder[0];
	int lenL = find(inOrder.begin(), inOrder.end(), root) - inOrder.begin();
	vector<int> subPre1 = slice(preOrder, 1, 1 + lenL), subPre2 = slice(preOrder, 1 + lenL, len);
	vector<int> subIn1 = slice(inOrder, 0, lenL), subIn2 = slice(inOrder, lenL + 1, len);

	printPostOrder(subPre1, subIn1); printPostOrder(subPre2, subIn2);

	cout << root << " ";
}

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		vector<int> preOrder, inOrder;
		for (int i = 0;i < N;i++) {
			int tmp;
			cin >> tmp;
			preOrder.push_back(tmp);
		}
		for (int i = 0;i < N;i++) {
			int tmp;
			cin >> tmp;
			inOrder.push_back(tmp);
		}

		printPostOrder(preOrder, inOrder);
	}

}