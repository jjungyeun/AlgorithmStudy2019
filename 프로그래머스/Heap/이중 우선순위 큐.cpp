#include <string>
#include <vector>
#include <map>

#include <iostream>

using namespace std;

map<int, int> heap;


void insert(int x) {
	// ���� heap�� ����ִ� ���ڸ� ī��Ʈ ����
	if (heap.count(x) == 1) {
		heap[x]++;
	}
	else
		heap[x] = 1;

	//cout << "insert " << x << "(" << heap[x] << ")" << endl;
}

void popMax() {
	// heap ��������� ���� ����
	if (heap.size() == 0)
		return;

	// ���� ���� ���� pop
	map<int, int>::iterator itr = heap.end();
	itr--;
	if (itr->second == 1)
		heap.erase(itr);
	else // ���� ���ڰ� �������� ������ �ٿ���
		itr->second--;

	// cout << "pop(max) " << itr->first << endl;
}

void popMin() {
	// heap ��������� ���� ����
	if (heap.size() == 0)
		return;

	// ���� ���� ���� pop
	map<int, int>::iterator itr = heap.begin();
	if (itr->second == 1)
		heap.erase(itr);
	else // ���� ���ڰ� �������� ������ �ٿ���
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

	// heap ��������� [0,0] ��ȯ
	if (heap.size() == 0)
		answer = vector<int>{ 0,0 };
	else {
		// �ִ밪 �� �ּҰ� ��ȯ
		map<int, int>::iterator itr = heap.end(); itr--;
		answer.push_back(itr->first);
		itr = heap.begin();
		answer.push_back(itr->first);
	}


	return answer;
}