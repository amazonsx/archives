/*
 * This is a realization of "reverse words in a string"
 * Caveat:
 *	boundary condition - input value is empty("")
 */
#include <iostream>
#include <string>
#include <stack>
#define DEBUG
using namespace std;

void normalizeString(string &s);

void normalizeString(string &s){

}

class Solution{
	public:
		void reverseWords(string &s);
};

void Solution::reverseWords(string &s){
	stack<string> ss;
	int size = s.size();
	string word_cur("");

	for(int i = 0; i < size; i ++){
		char &current = s[i];
#ifdef DEBUG
		cout << "read: " << current << endl;
#endif
		if (current == ' '){
			if( word_cur.size()!= 0){
#ifdef DEBUG
				cout << "push: "<< word_cur << endl;
#endif
				string &word_ref = word_cur;
				ss.push(word_ref);
				word_cur.clear();
			}
			continue;
		}
		word_cur += current;
#ifdef DEBUG
		cout << "concatenate: " << word_cur << endl;
#endif
		if( size == (i + 1)){
#ifdef DEBUG
			cout << "push: "<< word_cur << endl;
#endif
			string &word_ref = word_cur;
			ss.push(word_ref);
			word_cur.clear();
		}
	}
	s.clear();
#ifdef DEBUG
	cout << "clear string: "<< s << endl;
	cout << "string size: "<< s.size() << endl;
#endif
	if(ss.size() != 0){
		word_cur = ss.top();
#ifdef DEBUG
		cout << "pop: "<< word_cur << endl;
#endif
		ss.pop();
		s += word_cur;
	}

	while(!ss.empty()){
		s += ' ';
		word_cur = ss.top();
#ifdef DEBUG
		cout << "pop:-"<< word_cur << endl;
#endif
		ss.pop();
		s += word_cur;
	}
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

