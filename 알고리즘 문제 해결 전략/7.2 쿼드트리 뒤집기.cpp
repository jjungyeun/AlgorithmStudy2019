#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

// ������ ����� ���ϴ� �Լ�
// (x)xwwwbxwxwbbbwwxxxwwbbbwwwwbb�� ������ (�Ǿ� x����)
// xwwwb�� ���� 5�� ��ȯ����
unsigned long getPatternSize(string tree) {
	unsigned long goal = 0, size = 0;
	for (char c : tree) {
		size++;
		if (c == 'x')
			goal += 4;

		if (goal == 0) {
			return size;
		}
		goal--;
	}
	return -1;
}

// Ʈ���� reverse���ִ� �Լ�
// �� ���� x�� �ƴ϶�� ���� �Ѱ��� �����θ� �̷�����ִٴ°��̹Ƿ� �״�� ��ȯ
// 1 2	=>	3 4
// 3 4		1 2
// ������ ������ ����� ���� �ٲٸ� ��ü�� ���������� �̿�
string reverseTree(string tree) {
	if (tree.at(0) != 'x') {
		return tree;
	}
	string croppedTree(tree.substr(1));

	unsigned int index = 0, size = 0;

	size = getPatternSize(croppedTree);
	string tl = reverseTree(croppedTree.substr(0, size));

	index += size;
	size = getPatternSize(croppedTree.substr(index));
	string tr = reverseTree(croppedTree.substr(index, size));

	index += size;
	size = getPatternSize(croppedTree.substr(index));
	string bl = reverseTree(croppedTree.substr(index, size));

	index += size;
	size = getPatternSize(croppedTree.substr(index));
	string br = reverseTree(croppedTree.substr(index, size));

	return "x" + bl + br + tl + tr;
}

int main() {

	string str;
	//str = "xbwxwbbwb";
	str = "xxwwwbxwxwbbbwwxxxwwbbbwwwwbb";
	
	string res;
	res = reverseTree(str);

	cout << res << endl;

	return 0;
}