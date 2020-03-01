#include <cstdio>
#include <map>

using namespace std;

int C, N;
map<int, int> coords;

// ���ο� �� (x, y)�� �ٸ� ���鿡 ����Ǵ��� �ƴ����� ��ȯ
bool isDominated(int x, int y) {
	// �� ���� �ٷ� ������ ��
	map<int, int>::iterator itr = coords.lower_bound(x);

	// ������ ���� ������ �ٷ� false ��ȯ
	if (itr == coords.end())
		return false;

	// �ٷ� ������ ������ �Ʒ��� ������, ����Ǵ� ��
	return y < itr->second;
}

// ��(x,y)���� ����Ǵ� ���� ����
void removeDominated(int x, int y) {
	// x�� �ٷ� ������ ��
	map<int, int>::iterator itr = coords.lower_bound(x);

	// x�� ���� ù��°�� ������ �� �ִ� ���� �����Ƿ� �ٷ� return
	if (itr == coords.begin())
		return;

	// �������� �̵�
	--itr;

	// �������� �Űܰ��鼭 ����Ǵ� �� �����
	while (true) {
		// ���� �ȵǴ� ���̸� �� ������ ��� ���鵵 ����ȵǹǷ� break
		if (itr->second > y)
			break;

		// �� �̻� ���ʿ� ���� ������ �ش� ������ ����� break
		if (itr == coords.begin()) {
			coords.erase(itr);
			break;
		}
		else { // ���� �� ����� �������� ��ĭ �̵�
			map<int, int>::iterator tmp = itr;
			--tmp;
			coords.erase(itr);
			itr = tmp;
		}
	}
}

int registered(int x, int y) {
	// (x,y)�� �ٸ� ���� ����Ǹ� �׳� coords ������ ����
	if (isDominated(x, y))
		return coords.size();

	// (x,y)�� �����ϴ� ������ ����� (x,y) �ֱ�
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