#include <iostream>
#define DEBUG
using namespace std;

class Solution {
    private:
        bool isMatchRecursive( const char *s, const char *p);
        bool isMatchIterative( const char *s, const char *p);
	public:
        bool isMatch( const char *s, const char *p);
};

//recursive method
bool Solution::isMatchRecursive( const char *s, const char *p) {
    if ((s == NULL) && (p == NULL))  return true;   
    else if (s == NULL) return false;
    else if (p == NULL) return false;
    if ((*s == '\0') && (*p == '\0'))  return true;
    else if ( *p == '\0') return false;
    else if ( *s == '\0') {
        int index = 1;
        int start_flag = 0;
        while ( p[index] == '*')  {
            start_flag = 1;
            index++;
        }
        if ((start_flag == 1) && (p[index] == '\0')) return true;
        else if (start_flag == 0) return false;
        else return isMatchRecursive(s, p+index);
    }

    char current_p = p[0];
    int s_next = 0, p_next = 1;
    while (p[p_next] == '*')  p_next ++;
    if (p_next == 1) {
        if (current_p == '.'){
            //return isMatchRecursive(s, p+p_next) || isMatchRecursive( s+1, p+p_next);
            return isMatchRecursive( s+1, p+p_next);
        } else if (current_p == s[s_next]){
            return isMatchRecursive( s+1, p+p_next);
        } else return false;
    } else {
        char next_p = p[p_next];
        if (current_p == '.') {
            bool flag = false;
            flag |= isMatchRecursive( s, p+p_next);
            if (flag) return true;
            flag |= isMatchRecursive( s+1, p);
            if (flag) return true;
            flag |= isMatchRecursive( s+1, p+p_next);
            return flag;
        } else if ( current_p == s[s_next]) {
            if ( next_p == s[s_next]){
                bool flag1 = isMatchRecursive( s, p+p_next);
                bool flag2 = isMatchRecursive( s + 1, p);
                return flag1||flag2;
            } else  {
                char current_s = s[s_next];
                char next_s = s[s_next +1];
                int flag = isMatchRecursive( s+1, p);
                int i = 1;
                while (next_s == current_s) {
                    if (flag) return flag;
                    flag |= isMatchRecursive(s+i, p+p_next);
                    i++;
                    current_s = next_s;
                    next_s = s[s_next+i];
                }
                flag |= isMatchRecursive(s, p+p_next);
                return flag;
            }
        } else {
            return isMatchRecursive( s, p+p_next);
        }
    }
}

//iterative method
bool Solution::isMatchIterative( const char *s, const char *p) {
    return true;    
}


//recursive method
bool Solution::isMatch( const char *s, const char *p) {
    // recursive
    return isMatchRecursive(s, p);
}

int main(int argc, char *argv[]) {
    Solution s;
    // case 1
    char *a1 = "aa";
    char *b1 = "a*";
    cout << a1 << "    " << b1 << "   expected " << true << endl;
    cout << s.isMatch(a1, b1) << endl;

    char *a2 = "aa";
    char *b2 = "aa";
    cout << a2 << "    " << b2 << "   expected " << true << endl;
    cout << s.isMatch(a2, b2) << endl;

    char *a3 = "aaa";
    char *b3 = "aaaa";
    cout << a3 << "    " << b3 << "   expected " << false << endl;
    cout << s.isMatch(a3, b3) << endl;

    char *a4 = "aaa";
    char *b4 = ".*";
    cout << a4 << "    " << b4 << "   expected " << true << endl;
    cout << s.isMatch(a4, b4) << endl;
    
    char *a5 = "aba";
    char *b5 = ".*";
    cout << a5 << "    " << b5 << "   expected " << true << endl;
    cout << s.isMatch(a5, b5) << endl;

    char *a6 = "aab";
    char *b6 = "c*a*b";
    cout << a6 << "    " << b6 << "   expected " << true << endl;
    cout << s.isMatch(a6, b6) << endl;

    char *a7 = "aa";
    char *b7 = "a*";
    cout << a7 << "    " << b7 << "   expected " << true << endl;
    cout << s.isMatch(a7, b7) << endl;

    char *a8 = "aaa";
    char *b8 = "b*a*c*a";
    cout << a8 << "    " << b8 << "   expected " << true << endl;
    cout << s.isMatch(a8, b8) << endl;

    char *a9 = "bbbba";
    char *b9 = ".*a*a";
    cout << a9 << "    " << b9 << "   expected " << true << endl;
    cout << s.isMatch(a9, b9) << endl;

    char *a10 = "ab";
    char *b10 = ".*..";
    cout << a10 << "    " << b10 << "   expected " << true << endl;
    cout << s.isMatch(a10, b10) << endl;

    char *a11 = "";
    char *b11 = "c*c*";
    cout << a11 << "    " << b11 << "   expected " << true << endl;
    cout << s.isMatch(a11, b11) << endl;

    char *a12 = "bbbaccbbbaababbac";
    char *b12 = ".b*b*.*...*.*c*.";
    cout << a12 << "    " << b12 << "   expected " << true << endl;
    cout << s.isMatch(a12, b12) << endl;
    
    char *a13 = "a";
    char *b13 = ".*..a";
    cout << a13 << "    " << b13 << "   expected " << false << endl;
    cout << s.isMatch(a13, b13) << endl;
	return 1;
}
