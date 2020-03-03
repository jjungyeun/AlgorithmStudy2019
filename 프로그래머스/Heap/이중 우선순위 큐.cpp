#include <string>
#include <vector>
#include <map>

#include <iostream>

using namespace std;

map<int, int> heap;


void insert(int x) {
	// 현재 heap에 들어있는 숫자면 카운트 증가
	if (heap.count(x) == 1) {
		heap[x]++;
	}
	else
		heap[x] = 1;

	//cout << "insert " << x << "(" << heap[x] << ")" << endl;
}

void popMax() {
	// heap 비어있으면 연산 무시
	if (heap.size() == 0)
		return;

	// 가장 뒤의 숫자 pop
	map<int, int>::iterator itr = heap.end();
	itr--;
	if (itr->second == 1)
		heap.erase(itr);
	else // 같은 숫자가 여러개면 개수만 줄여줌
		itr->second--;

	// cout << "pop(max) " << itr->first << endl;
}

void popMin() {
	// heap 비어있으면 연산 무시
	if (heap.size() == 0)
		return;

	// 가장 앞의 숫자 pop
	map<int, int>::iterator itr = heap.begin();
	if (itr->second == 1)
		heap.erase(itr);
	else // 같은 숫자가 여러개면 개수만 줄여줌
		itr->second--;

	//cout << "pop(min) " << itr->first << endl;
}

vector<int> solution(vector<string> operations) {
	vector<int> answer;

	for (int i = 0;i < operations.size();i++) {
		string cmd = operations[i];
		if (cmd[0] == 'I')
			insert(stoi(cmd.substr(2)));
		else if (cmd[2] == '1')
			popMax();
		else
			popMin();
	}

	// heap 비어있으면 [0,0] 반환
	if (heap.size() == 0)
		answer = vector<int>{ 0,0 };
	else {
		// 최대값 및 최소값 반환
		map<int, int>::iterator itr = heap.end(); itr--;
		answer.push_back(itr->first);
		itr = heap.begin();
		answer.push_back(itr->first);
	}


	return answer;
}