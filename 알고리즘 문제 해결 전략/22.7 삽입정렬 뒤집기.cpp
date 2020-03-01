#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int C, N;
int moveArr[50001];	// ������ Ƚ���� �����ϴ� �迭
vector<int> order;

typedef int KeyType;
struct Node
{
	KeyType key;
	int priority, size;
	Node* left, * right;

	// key�� ���ҷ� �ϴ� ��� ������
	Node(const KeyType& _key) : key(_key), priority(rand()), size(1),
		left(NULL), right(NULL) {}

	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	void calcSize() {	// �� ��带 ��Ʈ�� �ϴ� Ʈ���� ������ ����
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};
typedef pair<Node*, Node*> NodePair;


// Ʈ���� ���� key�� �������� 2���� ����Ʈ���� ������
NodePair split(Node* root, KeyType key) {
	// �� Ʈ���� NULL ��ȯ
	if (root == NULL) return NodePair(NULL, NULL);

	// root���� key�� ũ�� ������ ����Ʈ������ �ڸ���
	if (root->key < key) {
		// rs: root�� ������ ����Ʈ���� key�� �������� �ڸ� ��
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// root���� key�� ������ ���� ����Ʈ������ �ڸ���
	// ls: root�� ���� ����Ʈ���� key�� �������� �ڸ� ��
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// Ʈ���� ���ο� ��带 ����
Node* insert(Node* root, Node* node) {
	// �� Ʈ���� ��� node��ü�� ��Ʈ�� ��ȯ
	if (root == NULL) return node;

	// root���� node�� �켱������ ���� ���, ��Ʈ�� node�� �ٲ��ش�
	if (root->priority < node->priority) {
		// ���� Ʈ���� key�� �������� ������ ���ο� ��Ʈ�� ����/�����ʿ� �ٿ��ش�
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	// node�� �켱������ �� ���� ���
	// node�� ���Ұ� root�� ���Һ��� ������, ���� ����Ʈ���� ����
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	// node�� ���Ұ� root�� ���Һ��� ũ��, ������ ����Ʈ���� ����
	else
		root->setRight(insert(root->right, node));
	return root;
}

// a�� ��Ʈ���ϴ� Ʈ���� b�� ��Ʈ�� �ϴ� Ʈ�� ��ġ��
Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;

	// �켱������ �� ���� �ָ� ��Ʈ�� ����
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

// Ʈ������ key�� ���ҷ��ϴ� ��� ����
Node* erase(Node* root, KeyType key) {
	if (root == NULL) return root;

	// root�� �������ϴ� ���
	if (root->key == key) {
		// root�� ����/������ ����Ʈ���� ��ģ ���ο� Ʈ���� ��ȯ
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}

	// ��Ʈ���� ������/Ŭ�� ���� ����/������ ����Ʈ������ ��������� ����
	if (root->key > key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

// Ʈ������ k��° ��� ã��
Node* findKelement(Node* root, int k) {
	int leftSize = 0;
	if (root->left != NULL)
		leftSize = root->left->size;
	// Ʈ���� ���ʿ� ���� ��
	if (k <= leftSize)
		return findKelement(root->left, k);
	// ��Ʈ�� ��
	if (k == leftSize + 1)
		return root;
	// Ʈ���� �����ʿ� ���� ��
	return findKelement(root->right, k - leftSize - 1);
}

void getOriginalArray() {
	// 1~N�� ���ҷ� �ϴ� Ʈ�� ����
	Node* numbers = NULL;
	for (int i = 1;i <= N;i++) {
		numbers = insert(numbers, new Node(i));
	}

	// ������ Ƚ���� ���� �ڿ������� ���������� ���Ҹ� ã�´�
	for (int i = N;i > 0;i--) {
		Node* K = findKelement(numbers, i - moveArr[i]);
		order.push_back(K->key);
		numbers = erase(numbers, K->key);
	}

}

void solve() {
	order.clear();
	getOriginalArray();
	// ������ �ڿ������� ã�����Ƿ� �ݴ�� ������ش�
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