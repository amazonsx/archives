#include <iostream>
#include <string.h>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
public:
    char *strStr( char *haystack, char* needle);
};

char* Solution::strStr(char *haystack, char *needle) {
    if (!haystack || !needle)   return NULL;

    if ((*haystack == '\0') && (*needle == '\0'))
        return haystack;
    if (*haystack == '\0')
        return NULL;

    char *current = haystack; 
    while( *current != '\0') {
        char *nextCurrent = NULL;
        if (*current == *needle) {
            char *cursor = needle;
            for (int i = 0; *cursor != '\0'; 
                    cursor ++, i ++) {
                if (*(current+i) == '\0')
                    return NULL;
                if (*(current+i) != *(cursor))
                    break;
                if ((*cursor == *current) && !nextCurrent && (cursor != needle))
                    nextCurrent = current + i;
            }
            if ((cursor != needle) && (*cursor == '\0'))
                return current;
        }
        if (nextCurrent == NULL) {
            current += 1;
        } else {
            current = nextCurrent;
        }
    }
    if ((*current == '\0') && (*needle == '\0'))
        return current - 1;

    return NULL;
}

int main(int argc, char *argv[]) {
    Solution s;
    struct timeval first;
    struct timeval second;

    char *a = "abcd123ab15123123";
    char *b = "ab15";
    cout << "b -- "<< b << " -- res -- "<< s.strStr(a, b) << endl;

    char *a1 = "\0";
    char *b1 = "\0";
    cout << "b -- "<< b1 << " -- res -- "<< s.strStr(a1, b1) << endl;

    char *a2 = "abcd";
    char *b2 = "\0";
    cout << "b -- "<< b2 << " -- res -- "<< s.strStr(a2, b2) << endl;

    char *a3 = "abcd";
    char *b3 = "cb";
    cout << "b -- "<< b3 << " -- res -- "<< s.strStr(a3, b3) << endl;

    char *a4 = "a";
    char *b4 = "";
    gettimeofday(&first, NULL);
    cout << "b -- "<< b4 << " -- res -- "<< s.strStr(a4, b4) << endl;
    gettimeofday(&second, NULL);
    cout << "time cost ---- "  <<  second.tv_usec - first.tv_usec + (second.tv_sec - first.tv_sec) * 1000000 << endl;

	return 1;
}
