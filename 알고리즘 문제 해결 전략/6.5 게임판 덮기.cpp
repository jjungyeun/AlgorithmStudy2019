#include <stdio.h>

int H, W;
int pan[20][20] = { 0, };

int dx[] = { 1,1,0,-1,0,1, 1, 0 };
int dy[] = { 0,1,1,1,1,1, 0, 1 };

void printBoard(int board[20][20]) {
	for (int i = 0;i < H;i++) {
		for (int j = 0;j < W;j++) {
			if (board[i][j] == 0)
				printf("O");
			else
				printf("@");
		}
		printf("\n");
	}
	printf("\n");
	return;
}

int fillBlocks(int restW, int board[20][20]) {

	/*printf("rest: %d\n", restW);
	printf("-- board --\n");
	printBoard(board);*/

	if (restW <= 0) {
		//printf("\n<<<<<< SUCCESS >>>>>>\n");
		return 1;
	}

	int ans = 0;
	int firstX, firstY;

	for (int y = 0;y < H;y++) {
		int flag = 0;
		for (int x = 0; x < W;x++) {
			if (board[y][x] == 0) {
				firstX = x;
				firstY = y;
				flag = -1;
				break;
			}
		}
		if (flag == -1)
			break;
	}


	for (int i = 0;i < 4;i++) {
		int tmpY1 = firstY + dy[2 * i];
		int tmpX1 = firstX + dx[2 * i];
		int tmpY2 = firstY + dy[2 * i + 1];
		int tmpX2 = firstX + dx[2 * i + 1];
		if ((tmpY1 < H && tmpY2 < H && tmpX1 < W && tmpX2 >= 0) &&
			board[tmpY1][tmpX1] == 0 && board[tmpY2][tmpX2] == 0) {
			board[firstY][firstX] = board[tmpY1][tmpX1] = board[tmpY2][tmpX2] = 1;
			ans += fillBlocks(restW - 3, board);
			board[firstY][firstX] = board[tmpY1][tmpX1] = board[tmpY2][tmpX2] = 0;
		}
	}

	return ans;
}

int main() {

	int numWhite = 0;

	scanf("%d %d", &H, &W);
	getchar();

	for (int i = 0;i < H;i++) {
		for (int j = 0;j < W;j++) {
			char tmp;
			scanf("%c", &tmp);
			if (tmp == '#')
				pan[i][j] = 1;
			else {
				numWhite++;
				pan[i][j] = 0;
			}

		}
		getchar();
	}

	if (numWhite % 3 != 0)
		printf("0\n");

	else
		printf("%d\n", fillBlocks(numWhite, pan));




	return 0;
}