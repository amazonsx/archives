#include <iostream>
#include <assert.h>
#include <limits>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
	public:
        int divide(int dividend, int divisor);
};
int Solution::divide( int dividend, int divisor) {
    if ( divisor == 0)  return numeric_limits<int>::infinity();
    long long dividendl = dividend;
    long long divisorl = divisor; 
    int res = 0;
    int sign = 0;
    if ( dividendl < 0) {
        dividendl = abs(dividendl);
        sign ++;
    }
    if ( divisorl < 0) {
        divisorl = abs(divisorl);
        sign ++;
    }
    if ( dividendl < divisorl ) return 0;
    if ( dividendl == divisorl) {
        if (sign == 1)  return -1;
        return 1;
    }
    int count = 0;
    while ( divisorl <= (dividendl>>1) ) {
        divisorl <<= 1;
        count ++;
    }
    while ( count >= 0) {
        if ( divisorl <= dividendl) {
            dividendl -= divisorl;
            res += (1 << count);
        }
        divisorl >>= 1;
        count --;
    }
    if ( sign == 1) res = -res;
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    int a = 200, b = 30;
    cout << a <<"/" << b << "=" <<  s.divide(a, b) << endl;
    a = 1, b = 1;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = 122, b = 2;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = 10, b = 3;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = 122, b = 0;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = -22, b = 11;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = -1010369383, b = -2147483648;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
    a = -2147483648, b = 1;
    cout << a <<"/" << b << "="  <<  s.divide(a, b) << endl;
	return 1;
}
