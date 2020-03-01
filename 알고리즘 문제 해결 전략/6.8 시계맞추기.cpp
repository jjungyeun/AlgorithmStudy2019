#include <stdio.h>
#include <algorithm>

using namespace std;

const int INF = 987654321;
// 각 스위치를 눌렀을 때 반응하는 시계의 번호
// 17은 빈칸(의미없음)
const int switchType[10][5] = {
	{0,1,2,17,17}, {3,7,9,11,17}, {4,10,14,15,17}, {0,4,5,6,7},
	{6,7,8,10,12}, {0,2,14,15,17},{3,14,15,17,17},{4,5,7,14,15},
	{1,2,3,4,5},{3,4,5,9,13}
};

int clockDirection[16+1] = { 0, };

bool isAll12() {
	for (int i = 0;i < 16;i++) {
		if (clockDirection[i] != 12)
			return false;
	}
	return true;
}

// switchNum: 누른 스위치 번호
void clockChange(int switchNum) {
		for (int i = 0;i < 5;i++) {
			int clockNum = switchType[switchNum][i];
			if (clockNum == 17)
				continue;
			if (clockDirection[clockNum] == 12)
				clockDirection[clockNum] = 0;
			clockDirection[clockNum] += 3;
		}
	/*printf("---CLOCK---\n");
	for (int i = 0;i < 16;i++) {
		printf("%2d ", clockDirection[i]);
	}
	printf("\n");*/

	return;
}

int clickSwitch(int switchNum) {

	if (switchNum == 10) {
		return isAll12() ? 0 : INF;
	}

	int ans = INF;
	for (int i = 0;i < 4;i++) {
		ans = min(ans, i + clickSwitch(switchNum + 1));
		clockChange(switchNum);
	}

	return ans;


	/*int ans = INF;
	for (int i = 0;i < 10;i++) {
		clickNum[i]++;
		if (clickNum[i] >= 4)
			continue;
		printf("click switch %d =>\n",i);
		clockChange(i,1);

		printf("---CLOCK---\n");
		for (int i = 0;i < 16;i++) {
			printf("%2d ", clockDirection[i]);
		}
		printf("\n");

		int cand = clickSwitch(clickCnt+1);
		clockChange(i, -1);
		ans = min(ans, cand);
		clickNum[i]--;
	}

	if (ans == INF)
		return -1;
	return ans;*/
}


int main() {

	for (int i = 0;i < 16;i++) {
		scanf("%d", &clockDirection[i]);
	}

	int ans = clickSwitch(0);
	if (ans == INF)
		ans = -1;
	printf("%d\n", ans);

	return 0;
}