#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int C, N;
int moveArr[50001];	// 움직임 횟수를 저장하는 배열
vector<int> order;

typedef int KeyType;
struct Node
{
	KeyType key;
	int priority, size;
	Node* left, * right;

	// key를 원소로 하는 노드 생성자
	Node(const KeyType& _key) : key(_key), priority(rand()), size(1),
		left(NULL), right(NULL) {}

	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	void calcSize() {	// 이 노드를 루트로 하는 트리의 원소의 개수
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};
typedef pair<Node*, Node*> NodePair;


// 트리를 원소 key를 기준으로 2개의 서브트리로 나눈다
NodePair split(Node* root, KeyType key) {
	// 빈 트리면 NULL 반환
	if (root == NULL) return NodePair(NULL, NULL);

	// root보다 key가 크면 오른쪽 서브트리에서 자르기
	if (root->key < key) {
		// rs: root의 오른쪽 서브트리를 key를 기준으로 자른 것
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// root보다 key가 작으면 왼쪽 서브트리에서 자르기
	// ls: root의 왼쪽 서브트리를 key를 기준으로 자른 것
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// 트리에 새로운 노드를 삽입
Node* insert(Node* root, Node* node) {
	// 빈 트리인 경우 node자체를 루트로 반환
	if (root == NULL) return node;

	// root보다 node의 우선순위가 높은 경우, 루트를 node로 바꿔준다
	if (root->priority < node->priority) {
		// 기존 트리를 key를 기준으로 나누어 새로운 루트의 왼쪽/오른쪽에 붙여준다
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	// node의 우선순위가 더 낮은 경우
	// node의 원소가 root의 원소보다 작으면, 왼쪽 서브트리에 삽입
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	// node의 원소가 root의 원소보다 크면, 오른쪽 서브트리에 삽입
	else
		root->setRight(insert(root->right, node));
	return root;
}

// a를 루트로하는 트리와 b를 루트로 하는 트리 합치기
Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;

	// 우선순위가 더 높은 애를 루트로 설정
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

// 트리에서 key를 원소로하는 노드 삭제
Node* erase(Node* root, KeyType key) {
	if (root == NULL) return root;

	// root를 지워야하는 경우
	if (root->key == key) {
		// root의 왼쪽/오른쪽 서브트리를 합친 새로운 트리를 반환
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}

	// 루트보다 작을때/클때 각각 왼쪽/오른쪽 서브트리에서 재귀적으로 삭제
	if (root->key > key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

// 트리에서 k번째 노드 찾기
Node* findKelement(Node* root, int k) {
	int leftSize = 0;
	if (root->left != NULL)
		leftSize = root->left->size;
	// 트리의 왼쪽에 있을 때
	if (k <= leftSize)
		return findKelement(root->left, k);
	// 루트일 때
	if (k == leftSize + 1)
		return root;
	// 트리의 오른쪽에 있을 때
	return findKelement(root->right, k - leftSize - 1);
}

void getOriginalArray() {
	// 1~N을 원소로 하는 트리 생성
	Node* numbers = NULL;
	for (int i = 1;i <= N;i++) {
		numbers = insert(numbers, new Node(i));
	}

	// 움직임 횟수를 보고 뒤에서부터 기존수열의 원소를 찾는다
	for (int i = N;i > 0;i--) {
		Node* K = findKelement(numbers, i - moveArr[i]);
		order.push_back(K->key);
		numbers = erase(numbers, K->key);
	}

}

void solve() {
	order.clear();
	getOriginalArray();
	// 수열의 뒤에서부터 찾았으므로 반대로 출력해준다
	for (int i = order.size() - 1;i >= 0;i--) {
		printf("%d ", order[i]);
	}
	printf("\n");
}

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		int tmp;
		for (int i = 1;i <= N;i++) {
			scanf("%d", &tmp);
			moveArr[i] = tmp;
		}
		solve();
	}
}