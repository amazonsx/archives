#include <iostream>
#include <string>
using namespace std;
class Solution {
	public:
		bool isNumber(const char *s);
};

bool Solution::isNumber(const char *s) {
	if (!s) return false;
	if (s[0] == '\0') return false;
	char current = s[0];
	// substr_count: the count of substrings spilitted by space chars
	// non_e_count: count of chars not e and not digit and not '.'
	// e_count: more than one e char is not valid
	// digits started with a 0 is it valid or not
	// decimals started with a . is it valid or not
	// capital e,E, is it valid or not
	int substr_count = 0, non_e_count = 0, e_count = 0, dot_count = 0;
	int cursor = 0, substr_begin = 0, substr_end = 0, valid_substr = 1, e_loc = 0;
	int dot_loc[2] = {0};
	while (current != '\0') {
		if (current == ' ')	{
			if (valid_substr --)  substr_end = cursor - 1; 
			current = s[++cursor];
			if (current == '\0') break;
			if ((current != ' ')&(current != '\0')) {
				substr_count ++;
				substr_begin = cursor;
				valid_substr = 1;
			}
			if (substr_count > 1) return false;
			continue;
		} else if ((current == '+') || (current == '-')){
			if (cursor > 0) {
				if ((s[cursor-1] != ' ') && (s[cursor-1] != 'e') && (s[cursor-1] != 'E')) return false;
			}
			current = s[++cursor];
			if (current == '\0') return false;
			int expect_digit = cursor;
			if (current == '.')  expect_digit += 1;
		   	if(((s[expect_digit] >= '0') && (s[expect_digit] <= '9'))) continue;
			else return false;
		} else if ((current == 'e')||(current == 'E')) {
			e_count ++;
			if (e_count > 1) return false;
			e_loc = cursor;

			// there must be some integer before char 'e'
			int expect_digit = cursor - 1;
			if (cursor==0) return false;
			if (s[cursor-1] == '.')	expect_digit -= 1;
			if (!((s[expect_digit] > '0') && (s[expect_digit] <= '9')))	return false;
			// there must be a integer after char 'e'
			current = s[++cursor];
			if (current == '\0') return false;
			expect_digit = cursor ;
			if (current == '.' || current == '-'|| current == '+')	expect_digit += 1;
			if (!((s[expect_digit] >= '0') && (s[expect_digit] <= '9') ))	return false;
			continue;
		} else if (current == '.') {
			dot_count ++;
			if (dot_count > 2) return false;
			if ((dot_count == 2) && (e_count == 0)) return false;
			dot_loc[dot_count - 1] = cursor;
			// check if there is a digit number before '.', then we don't care what's behand '.'
			// or there must be a valid char after '.'
			 if ((cursor > 0) && (((s[cursor-1] >= '0') && (s[cursor-1] <='9')) || (s[cursor-1] == '+') || (s[cursor-1] == '-'))) {
				 current = s[++cursor];
				 continue;
			 }

			current = s[++cursor];
			if (current == '\0') return false;
			// after dot, there must be a valid char
			if (!((current <= '9') && (current >= '0')))	return false;
			continue;
		} else if (((current > '9') || (current < '0'))) {
			non_e_count ++;
			return false;
		} else {
			substr_count = 1;
		}
		current = s[++cursor];
	}
	if (substr_count == 0) return false;
	if ((dot_count == 2) && (e_loc > 0) && ((dot_loc[0] >= e_loc) || (dot_loc[1] <= e_loc))) return false;
	if ((dot_count == 1) && (e_loc > 0) && (dot_loc[0] >= e_loc)) return false;
	return true;
}

int main(int argc, char *argv[]) {
	Solution s;
	string a("abcedfg");
	const char *b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = "   1.234  ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 1.234 abcd";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 1.234e123";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 1.23.4e123";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " . . . ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;
	
	a = " .. ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 12e1.23 ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 1.2e1.23 ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 12e1.2e3 ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 12e ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 12e. ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 12e.1 ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 12e12.1 ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 12e12.1 ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 0e12.1 ";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 4e1.e";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 07e.6..033";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 2.e7.";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = ". 1";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = "-1.";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = "-";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;
	
	a = "-e";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = "-.";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = "7-c";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = "-R7";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = "+.8";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = ".1";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;

	a = " 005047e+6";
	b = a.c_str();
	cout << b << endl;
	cout << s.isNumber(b) << endl;
	return 1;
}
