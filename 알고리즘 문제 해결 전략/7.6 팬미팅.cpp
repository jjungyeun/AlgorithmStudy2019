#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// a += b * (10^k)
void addTo(vector<int>& a, vector<int>& b, int k) {
	int s = max(b.size() + k, a.size());
	for (int i = 0;i < s - k;i++) {
		int sum = a.at(i+k) + b.at(i);
		a.at(i) = sum;
	}
	return;
}
// a -= b; (´Ü, a>=b)
void subFrom(vector<int>& a, vector<int>& b) {
	int s = max(a.size(), b.size());
	a.resize(s, 0);
	b.resize(s, 0);
	for (int i = 0;i <s;i++) {
		int sub = a.at(i) - b.at(i);
		a.at(i) = sub;
	}
	return;
}

vector<int> multiply(vector<int> a, vector<int> b) {

	vector<int> res;
	res.resize(a.size() + b.size() - 1, 0);

	for (int i = 0;i < a.size();i++) {
		for (int j = 0;j < b.size();j++) {
			res.at(i + j) += a.at(i) * b.at(j);
		}
	}
	return res;
}

vector<int> karatsuba(vector<int> a, vector<int> b) {
	int len_a = a.size(), len_b = b.size();

	if (len_a < len_b)
		return karatsuba(b, a);

	if (len_a == 0 || len_b == 0)
		return vector<int>();

	if (len_a < 50) {
		return multiply(a, b);
	}

	cout << "len_a: " << len_a << ", len_b: " << len_b << endl;
	
	int half = len_a / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(),half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());


	vector<int> z0 = karatsuba(a0, b0);
	vector<int> z2 = karatsuba(a1, b1);
	
	addTo(a0, a1, 0); addTo(b0, b1, 0);
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0); subFrom(z1, z2);

	vector<int> ans;
	addTo(ans, z0, 0);
	addTo(ans, z1, half);
	addTo(ans, z2, 2 * half);

	return ans;
}

int main() {

	/*string N("00001");
	string M("0000011110");*/
	string N("10101000111010");
	string M("11000001000100000010001000010110000000");

	vector<int> a(N.size());
	vector<int> b(M.size());
	for (int i = 0;i < N.size();i++) {
		a.at(i) = N.at(i) - '0';
	}
	for (int i = 0;i < M.size();i++) {
		b.at(M.size()-i-1) = M.at(i) - '0';
	}

	vector<int> ans = karatsuba(a, b);


	int hugs = 0;
	for (int i = N.size()-1;i < M.size();i++) {
		cout << ans.at(i) << " ";
		if (ans.at(i) == 0)
			hugs++;
	}

	cout << endl << hugs << endl;

	return 0;
}