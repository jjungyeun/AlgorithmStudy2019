#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

int T, N;
// first: 입력 순서, second: 높이
map<int, int> heights;
map<int, int> tmpMap;

void printMap(map<int, int> m) {
	map<int, int>::iterator itr = m.begin();
	while (itr != m.end()) {
		printf("%d ", itr++->second);
	}
	printf("\n");
}

// 현재 map에서 가장 긴 오름차순 수열의 길이를 반환
int getAsc(map<int,int> m) {
	int len = 1, ret = 1;
	map<int, int>::iterator itr = m.begin();
	int pre = itr->second;
	while (1) {
		itr++;
		if (itr == m.end())
			break;

		if (itr->second > pre) 
			len++;
		else {
			ret = max(ret, len);
			len = 1;
		}
		pre = itr->second;
	}
	return max(ret,len);
}

int getHighest() {
	int ret = 1;
	for (int i = 1;i < N-1;i++) {
		tmpMap.clear();
		tmpMap = map<int, int>(heights.begin(), heights.end());
		for (int j = i;j < N-1;j++) {
			tmpMap.erase(j);
			ret = max(ret, getAsc(tmpMap));
			printMap(tmpMap);
		}
	}
	return ret;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		int tmp;
		heights.clear();
		for (int i = 0;i < N;i++) {
			scanf("%d", &tmp);
			heights[i] = tmp;
		}
		printf("%d\n",getHighest());
	}
}