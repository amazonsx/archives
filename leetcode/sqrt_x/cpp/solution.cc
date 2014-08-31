#include <iostream>
#include <assert.h>
#define DEBUG
using namespace std;

class Solution {
private:
    int binaryTest(int x);
    int newtonRecursive(int x);
public:
    int sqrt(int x);
};

int Solution::binaryTest(int x) {
    long long i = 0;
    long long j = x/2 + 1;
    // can not keep i == j, because what??????
    while ( i <= j) {
        long long mid = (i + j)/2;
        long long sq = mid * mid;
        if ( sq == x)   return mid;
        if ( sq < x) i = mid + 1;
        else    j = mid - 1;
    }
    // choose the j, because j is the smaller value
    return j;
}

int Solution::newtonRecursive(int x) {
    double last = 0;
    double current = 1;
    while ( current != last ) {
        last = current;
        current = (last + x/last )/2;
        if ( current*current == x)  break;
    }
    // if just return current, it's a double type square root 
    return (int)current;
}

int Solution::sqrt(int x) {
    int a = binaryTest(x);
    int b = newtonRecursive(x);
    cout << a << endl;
    cout << b << endl;
    assert(a == b);
    return a;
    
}

int main(int argc, char *argv[]) {
    int x = 2;
    Solution s;
    cout << s.sqrt(x) << endl;
	return 1;
}
