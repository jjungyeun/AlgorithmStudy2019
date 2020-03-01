#include <iostream>
#include <string>
#include <stack>

using namespace std;

int C;

bool isCorrect(string str) {
	stack<char> s;
	for (int i = 0;i < str.size();i++) {
		char here = str[i];
		if (here == '(' || here == '{' || here == '[')
			s.push(here);
		else if (s.empty())
			return false;
		else if ((here == ')' && s.top() == '(')
			|| (here == '}' && s.top() == '{')
			|| (here == ']' && s.top() == '['))
			s.pop();
		else
			return false;
	}
	if (!s.empty())
		return false;
	return true;
}

int main() {
	cin >> C;
	while (C--) {
		string tmp;
		cin >> tmp;
		if (isCorrect(tmp))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}