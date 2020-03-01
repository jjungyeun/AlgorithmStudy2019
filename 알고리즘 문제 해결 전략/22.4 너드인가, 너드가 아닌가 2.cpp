#include <cstdio>
#include <map>

using namespace std;

int C, N;
map<int, int> coords;

// 새로운 점 (x, y)가 다른 점들에 지배되는지 아닌지를 반환
bool isDominated(int x, int y) {
	// 이 점의 바로 오른쪽 점
	map<int, int>::iterator itr = coords.lower_bound(x);

	// 오른쪽 점이 없으면 바로 false 반환
	if (itr == coords.end())
		return false;

	// 바로 오른쪽 점보다 아래에 있으면, 지배되는 것
	return y < itr->second;
}

// 점(x,y)에게 지배되는 점들 삭제
void removeDominated(int x, int y) {
	// x의 바로 오른쪽 점
	map<int, int>::iterator itr = coords.lower_bound(x);

	// x가 제일 첫번째면 지배할 수 있는 점이 없으므로 바로 return
	if (itr == coords.begin())
		return;

	// 왼쪽으로 이동
	--itr;

	// 왼쪽으로 옮겨가면서 지배되는 점 지우기
	while (true) {
		// 지배 안되는 점이면 그 왼쪽의 모든 점들도 지배안되므로 break
		if (itr->second > y)
			break;

		// 더 이상 왼쪽에 점이 없으면 해당 점까지 지우고 break
		if (itr == coords.begin()) {
			coords.erase(itr);
			break;
		}
		else { // 현재 점 지우고 왼쪽으로 한칸 이동
			map<int, int>::iterator tmp = itr;
			--tmp;
			coords.erase(itr);
			itr = tmp;
		}
	}
}

int registered(int x, int y) {
	// (x,y)가 다른 점에 지배되면 그냥 coords 사이즈 리턴
	if (isDominated(x, y))
		return coords.size();

	// (x,y)가 지배하는 점들을 지우고 (x,y) 넣기
	removeDominated(x, y);
	coords[x] = y;

	return coords.size();
}

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		int sum = 0;
		coords.clear();
		for (int i = 0;i < N;i++) {
			int p, q;
			scanf("%d %d", &p, &q);
			sum += registered(p, q);
		}
		printf("%d\n", sum);
	}
}