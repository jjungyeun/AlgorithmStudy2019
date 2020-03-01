#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

// 패턴의 사이즈를 구하는 함수
// (x)xwwwbxwxwbbbwwxxxwwbbbwwwwbb를 넣으면 (맨앞 x제외)
// xwwwb의 길이 5를 반환해줌
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

// 트리를 reverse해주는 함수
// 맨 앞이 x가 아니라는 것은 한가지 색으로만 이루어져있다는것이므로 그대로 반환
// 1 2	=>	3 4
// 3 4		1 2
// 각각의 패턴을 뒤집어서 순서 바꾸면 전체가 뒤집어짐을 이용
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