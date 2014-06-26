#include <iostream>
#include <limits>
#define DEBUG
using namespace std;

class Solution {
	private:
		int isDigit(char &c, int &res, int &i, const char *str, int &has_digit, int flag);
	public:
		int atoi(const char *str);

};

int Solution::isDigit(char &c, int &res, int &i, const char *str, int &has_digit, int flag) {
	if ((c >= 48) && (c <= 57)) {
		int digit = c - 48;
		unsigned int tmp = res * 10 + digit;
		if ( res > (numeric_limits<int>::max()/10))  return -1;
		else if ((res == (numeric_limits<int>::max()/10)) && (digit > 8) && (flag == 1))  return -1;
		else if ((res == (numeric_limits<int>::max()/10)) && (digit > 7) && (flag == -1))  return -1;
		
		if ((tmp > numeric_limits<int>::max())) return -1;
		res = res *10 + digit;
		c = str[++i];
		has_digit = 1;
		return 1;
	}
	return 0;
}

int Solution::atoi(const char *str) {
	if (!str) return 0;
	int res = 0;
	char c = str[0];
	int flag = 1;
	int has_digit = 0;
	int has_flag = 0;
	int i = 0;
	while (c != '\0') {
		int tmp = isDigit(c, res, i, str, has_digit, flag);
		if ( tmp == 1) continue;
		else if ( tmp == -1 )  return (flag==1)?numeric_limits<int>::max():numeric_limits<int>::min();
		if (!has_digit) {
			switch (c) {
				case ' ': {}
				case '\t': {}
				case '\n': {}
				case '\r': {}
				case '\v': {}
				case '\f': {
					c = str[++i];
					continue;
				}
				case '+': {
					if (has_flag) return 0;
					flag = 1;
					c = str[++i];
					tmp = isDigit(c, res, i, str, has_digit, flag);
					if (tmp == 1) continue;
					else if ( tmp == -1 )  return (flag==1)?numeric_limits<int>::max():numeric_limits<int>::min();
					else return 0;
				}
				case '-': {
					if (has_flag) return 0;
					flag = -1;
					c = str[++i];
					tmp = isDigit(c, res, i, str, has_digit, flag);
					if (tmp == 1) continue;
					else if ( tmp == -1 )  return (flag==1)?numeric_limits<int>::max():numeric_limits<int>::min();
					else return 0;
				}
				default : {
					return 0;
				}
			}
		} else break;
	}
	return flag * res;
}

int main(int argc, char *argv[]) {
	Solution s;
	char *str1 = "012312312";
	cout << str1 << endl;
	cout << s.atoi(str1) << endl;
	cout << "--------------" << endl;
	char *str2 = "+01asdfa2312312";
	cout << str2 << endl;
	cout << s.atoi(str2) << endl;
	cout << "--------------" << endl;
	char *str3 = "- 1asdfa2312312";
	cout << str3 << endl;
	cout << s.atoi(str3) << endl;
	cout << "--------------" << endl;
	char *str4 = "abc- 1asdfa2312312";
	cout << str4 << endl;
	cout << s.atoi(str4) << endl;
	cout << "--------------" << endl;
	char *str5 = "\t   12abc- 1asdfa2312312";
	cout << str5 << endl;
	cout << s.atoi(str5) << endl;
	cout << "--------------" << endl;
	char *str6 = "\r   12abc- 1asdfa2312312";
	cout << str6 << endl;
	cout << s.atoi(str6) << endl;
	cout << "--------------" << endl;
	char *str7 = "-2147483647";
	cout << str7 << endl;
	cout << s.atoi(str7) << endl;
	cout << "--------------" << endl;
	char *str8 = "\f   12abc- 1asdfa2312312";
	cout << str8 << endl;
	cout << s.atoi(str8) << endl;
	cout << "--------------" << endl;
	char *str9 = "   10522545459";
	cout << str9 << endl;
	cout << s.atoi(str9) << endl;
	cout << "--------------" << endl;
	char *str0 = "123123123123123123123123123121231231231231231231231231233";
	cout << str0 << endl;
	cout << s.atoi(str0) << endl;
	cout << "--------------" << endl;
	cout << numeric_limits<int>::min() << endl;
	return 1;
}
