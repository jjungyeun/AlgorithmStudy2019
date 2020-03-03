#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Task {
	int reqT; int workT;
	Task(int rT, int wT) :
		reqT{ rT }, workT{ wT } {}
};
struct cmp {
	bool operator()(Task a, Task b) {
		return a.workT > b.workT;
	}
};

priority_queue<Task, vector<Task>, cmp> pq;

int solution(vector<vector<int>> jobs) {
	int answer = 0;
	int time = 0;

	// 작업을 요청 순서대로 정렬
	sort(jobs.begin(), jobs.end());

	vector<vector<int>>::iterator itr = jobs.begin();
	while (1) {
		// 현재 시간에 따라 작업 추가
		while (itr != jobs.end() && time >= itr->at(0)) {
			pq.push(Task(itr->at(0), itr->at(1)));
			itr++;
		}

		// 현재 실행할 수 있는 작업이 없을 때
		if (pq.empty() && itr != jobs.end()) {
			time = itr->at(0);
		}

		// 작업 실행
		if (!pq.empty()) {
			Task task = pq.top(); pq.pop();
			time += task.workT;
			answer += (time - task.reqT);
		}

		// 작업 모두 끝내면 종료
		if (itr == jobs.end() && pq.empty())
			break;

	}

	return answer / jobs.size();
}