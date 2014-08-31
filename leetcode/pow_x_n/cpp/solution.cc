#include <iostream>
#define DEBUG
using namespace std;

class Solution {
    public:
        double pow( double x, int n);
};

double Solution::pow( double x, int n) {
    if ( (x == 0) && ( n > 0) ) {
        return 0;
    }
    if ( n == 0) {
        return 1;
    } 
    double res = x;
    int remain = 0;
    int pair = 1;
    int sign = 0;
    if ( n < 0) {
        sign = 1;
        n *= -1;
    }
    while ( (n/2) != 0 ) {
        res *= res;
        cout << res << endl;
        remain += n%2*pair;
        n >>= 1;
        pair <<= 1;
    }
    cout << remain << endl;
    res *= pow(x, remain);
    if ( sign == 1)  res = 1.0/res;
    return res;
}

int main(int argc, char *argv[]) { 
    //int x = 2, n = -9;
    /*
    double x = 8.88023; 
    int n = 3;
    */
    /*
    double x = 34.00515;
    int n = -3;
    */
    double x = -1;
    int n = -2147483648;
    Solution s;
    cout << s.pow(x, n) << endl;
    return 1;
}
