#include <iostream>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
private:
    int calMaxDigit(int &x, int &expected);
public:
    bool isPalindrome(int x);
};

int Solution::calMaxDigit(int &x, int &expected) {
    unsigned int tmp = 1;
    int places = 1;
    bool flag = true;
    while (tmp <= x) {
        if ((tmp*10/tmp) != 10) {  
            flag = false;
            break;
        }
        tmp *= 10;
        places ++;
    }
    if (flag) {
        tmp /= 10;
        places --;
    } else {
        int count = 0;
        while (tmp != 1) {
            tmp /= 10;
            count ++;
        }
        while ( count > 0) {
            tmp *= 10;
            count --;
        }
    }
    if (expected == 0){
        expected = places;
    } else {
        if (expected > places) {
            return 0;
        }
    }
    int res = 1;
    flag = true;
    while ( tmp*res <= x) {
        if (tmp*(res+1) < tmp) {
            flag = false;
            break;
        }
        res ++;
    }
    if (flag)   res --;
    x -= tmp*res;
    return res;
}

bool Solution::isPalindrome(int x) { 
    int expected = 0;
    while ( x != 0 ) { 
        cout << x << endl;
        int right = x%10;
        int left = calMaxDigit(x, expected);
        cout << left << "   " << right << endl;
        if (left != right)  return false;
        x /= 10;
        expected -= 2;
    }
    return true;
}

int main(int argc, char *argv[]) {
    //int x = 1230321;
    //int x = 1874994781;
    //int x = 10000021;
    int x = 1000110001;
    Solution s;
    timeval first, second;
    gettimeofday( &first, NULL);
    cout << s.isPalindrome(x) << endl;
    gettimeofday( &second, NULL);
    cout << 1000000* (second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
	return 1;
}
