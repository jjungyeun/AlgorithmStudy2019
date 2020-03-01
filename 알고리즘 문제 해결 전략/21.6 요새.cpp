#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N;
int longest;
int x[100], y[100], r[100];

struct TreeNode {
	vector<TreeNode*> children;
};

TreeNode* getTree(int root);
bool isInside(int c1, int c2);
bool isChild(int c1, int c2);
int getHeight(TreeNode* root);
int solve();

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 0;i < N;i++) {
			int tmpX, tmpY, tmpR;
			cin >> tmpX >> tmpY >> tmpR;
			x[i] = tmpX; y[i] = tmpY; r[i] = tmpR;
		}
		cout << solve() << endl;
	}
}

// root번째 node를 루트로 하는 tree를 생성 후 루트 반환
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int i = 0;i < N;i++) {
		if (isChild(i, root))
			ret->children.push_back(getTree(i));
	}
	return ret;
}

// c1이 c2안에 있는지 판단 (c1<c2)
bool isInside(int c1, int c2) {
	if (r[c2] <= r[c1])
		return false;

	int sqrDist = (x[c2] - x[c1]) * (x[c2] - x[c1]) + (y[c2] - y[c1]) * (y[c2] - y[c1]);
	if ((r[c2] - r[c1]) * (r[c2] - r[c1]) > sqrDist)
		return true;
	else
		return false;
}

// c1이 c2의 자식인지 판단 (직접 포함 관계)
bool isChild(int c1, int c2) {
	if (!isInside(c1, c2))
		return false;

	for (int i = 0;i < N;i++) {
		if (i == c1 || i == c2)
			continue;
		if (isInside(c1, i) && isInside(i, c2))
			return false;
	}
	return true;
}

// root 노드를 루트로 하는 트리의 높이 반환
// 해당 트리 내에서 최장 길이가 있을 경우 longest값 수정
int getHeight(TreeNode* root) {

	int len = root->children.size();
	if (len == 0)
		return 0;

	vector<int> heights;
	for (int i = 0;i < len;i++) {
		heights.push_back(getHeight(root->children[i]));
	}

	sort(heights.begin(), heights.end());
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[len - 2] + heights.back());
	return heights.back() + 1;
}

int solve() {
	longest = 0;
	int rootNum = 0;
	for (int i = 0;i < N;i++) {
		rootNum = 0;
		for (int j = 0;j < N;j++) {
			if (i == j)
				continue;
			if (!isInside(j, i)) {
				rootNum = -1;
				break;
			}
		}
		if (rootNum == 0) {
			rootNum = i;
			break;
		}
	}

	TreeNode* root = getTree(rootNum);
	int h = getHeight(root);

	return max(longest, h);
}