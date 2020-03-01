#include <stdio.h>

int c, n, m;

int cnt;
int areFriend[10][10] = { 0, };
bool taken[10] = { false, };

void clearBuffer() {
	cnt = 0;
	for (int i = 0;i < 10;i++) {
		taken[i] = false;
		for (int j = 0;j < 10;j++) {
			areFriend[i][j] = 0;
		}
	}
}

void findPartner(int pair) {
	if (pair == n / 2) {
		cnt++;
		return;
	}

	int firstStd = -1;
	for (int i = 0;i < n;i++) {
		if (!taken[i]) {
			firstStd = i; break;
		}
	}

	for (int i = firstStd + 1;i < n;i++) {
		if (!taken[i] && areFriend[i][firstStd]) {
			taken[firstStd] = taken[i] = true;
			findPartner(pair + 1);
			taken[firstStd] = taken[i] = false;
		}
	}
	return;
}

int main() {

	scanf("%d", &c);

	while (c--)
	{
		clearBuffer();
		scanf("%d %d", &n, &m);
		for (int i = 0;i < m;i++) {
			int n1, n2;
			scanf("%d %d", &n1, &n2);
			areFriend[n1][n2] = 1;
			areFriend[n2][n1] = 1;
		}

		findPartner(0);

		printf("%d\n", cnt);

	}
	

	return 0;
}