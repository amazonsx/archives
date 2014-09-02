#include <iostream>
#include <string>
#include <sys/time.h>
#include <assert.h>
#include <stack>
#define DEBUG
#define MULTIPLE_SOLUTION
using namespace std;

class Solution{
private:
    void reverseStr(string &s, int begin, int end);
    void reverseWordsS1(string &s);
    void reverseWordsS2(string &s);
public:
    void reverseWords(string &s);
};

void Solution::reverseStr( string &s, int begin, int end ) {
    if ( begin == end ) return;
    for ( int i = 0; i < ((end-begin+1)>>1); i ++) {
        char tmp = s[begin+i];
        s[begin+i] = s[end-i];
        s[end-i] = tmp;
    }
}

void Solution::reverseWordsS1(string &s) {
    if ( s.empty() )    return;
    int cursor = 1, count = 1;
    int begin = 0, end = -1;
    while ( count < (signed)s.size() ) {
        if ( s[cursor] == ' ') {
            if (s[cursor-1] == ' ') s.erase(cursor);
            else {
                end = cursor-1;
                reverseStr(s, begin, end);
                cursor ++;
            }
        } else {
            if ( s[cursor-1] ==  ' ')   begin = cursor;
            cursor ++;
        }
        count ++;
    }
    if ( s[0] == ' ' )  s.erase(0);
    if ( s.empty() )    return;
    // c++11    s.back()
    if ( s[s.size()-1] == ' ' )  s.erase(s.size() - 1);
    reverseStr(s, begin, s.size()-1);
    reverseStr( s, 0, s.size()-1);
}

void Solution::reverseWordsS2(string &s){
	stack<string> ss;
	int size = s.size();
	string word_cur("");

	for(int i = 0; i < size; i ++){
		char &current = s[i];
		if (current == ' '){
			if( word_cur.size()!= 0){
				ss.push(word_cur);
				word_cur.clear();
			}
			continue;
		}
		word_cur += current;
		if( size == (i + 1)){
			ss.push(word_cur);
			word_cur.clear();
		}
	}
	s.clear();
	if(ss.size() != 0){
		word_cur = ss.top();
		ss.pop();
		s += word_cur;
	}

	while(!ss.empty()){
		s += ' ';
		word_cur = ss.top();
		ss.pop();
		s += word_cur;
	}
}
void Solution::reverseWords( string &s) {
    string str1(s); 
    reverseWordsS1(s);
    cout << s << endl;
#ifdef MULTIPLE_SOLUTION
    reverseWordsS2(str1);
    cout << str1 << endl;
    assert( s == str1);
#endif
}


int main(int argc, char *argv[]){
	string str("The sky is blue");
	cout <<"The former str: " << str <<endl;
	Solution s;
	string &str_ref = str;
	s.reverseWords(str_ref);
	cout <<"After reverse:-" << str <<endl;
	return 1;
}

