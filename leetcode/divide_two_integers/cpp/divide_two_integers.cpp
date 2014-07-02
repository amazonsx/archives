#include <iostream>
#define DEBUG
using namespace std;

class Solution {
	public:
        int divide(int divident, int divisor);
};
int Solution::divide( int divident, int divisor) {
}

int main(int argc, char *argv[]) {
    Solution s;
    int a = 200, b = 30;
    cout << a <<"/" << b << "=" <<  s.divide(a, b) << endl;
    a = 122, b = 2;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = 122, b = 0;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = -22, b = 11;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
	return 1;
}
