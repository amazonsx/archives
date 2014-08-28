#include <iostream>
#define DEBUG
using namespace std;

class Solution {
private:
    int length(const char *s, int offset, int formerLen);
public:
    int lengthOfLastWord(const char *s);
};

int Solution::length(const char *s, int offset, int formerLen) {
    if (!s) return 0;
    int len = 0;
    while ( *(s+offset+len) != ' ' && *(s+offset+len) != '\0') {
        len ++;
    }
    if ( *(s+offset+len) == '\0') {
        if ( len == 0)  return formerLen;
        return len;
    } else {
        if ( len == 0)  return length(s, offset+len+1, formerLen);
        return length(s, offset+len+1, len);
    }
}

int Solution::lengthOfLastWord(const char *s) {
    return length(s, 0, 0);
}

int main(int argc, char *argv[]) {
    //char str[] = "Hello World";
    char str[] = "Today is a nice   day";
    Solution s;
    cout << s.lengthOfLastWord(str) << endl;
	return 1;
}

