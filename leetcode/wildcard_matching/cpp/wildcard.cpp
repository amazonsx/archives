/*
 * The problem require us to match a string A and a specified wildcard string B.
 * There are some conditions that the two strings obviously cannot match with each other,
 * like 1. only one of them is NULL
 *		2. A is shorter than B, and B doesn't have enough wildcards to fullfill the length
 *	    3. in a tranversing, char in A is not equal to char in B, which is not * or ?
 * The basic idea is to tranverse both A and B. 
 *	In the tranversing, if the tranversing char in A is equal to char in B(can be ?), return true
 *
 * What if the tranversing char in B is a '*'. Sadly, it's complicated to handle this.
 * In my solution, I use the recursion technique. 
 * When the tranversing char in B is a '*', I did a recursion to the substring of A and B. 
 *
 * There is a iteration to choose the first non-asterisk char after '*', 
 * and then find the same char in A from the tranversing char.
 * Do a recursion to the substrings started by these two chars.
 * If the result of the recursion is true, we can get it quickly.
 * If its result is false, we may have to iterate many char elements, though I have do a some optimization.
 * So there can be many iterations in iterations if the final result is false. And we cannot affort to wait the computing procedure
 * But in fact, many of the iterations are repeated.
 *  
 * This is a good news, as we can record the old result to use in the future loop.
 * In a loop, the length of the B substring keeps the same, 
 * and we tranverse the substring of A forward to check whether they are match
 * This pair of substring may be accessed later by another loop.
 * So a map<int, map<int,int>> is added to the recursion function to record data. We use map for its O(1) access time.
 * This is used to optimize the false computing procedure.
 * So all values and keys in the map are associated with the false search. 
 *
 * map<int, map<int,int>>: 
 *  its key means the length of the wildcard substring in a recursion, which is unique
 *  its value is a map<int, int> which could has two keys: 0 and 1.
 *		key 0 flags if its the first round to read the stored result.
 *			The reason that we differentiate whether it's the first time to read this result
 *			is that in the first round there is still a chance that this recursion return true.
 *		key 1 means that its value will be the max length of substring of A that the substring of B has checked.
 *			It means all substrings of A after the substring, flagged by this value, are not matched with the substring of B.
 * 
 *
 */
#include <iostream>
#include <string>
#include <map>
#define DEBUG
using namespace std;

class Solution {
	public:
	   	bool isMatch(const char *s, const char *p);
};

bool isMatchRecursion(const char *s, const char *p, map<int, map<int, int>> &n_match_map, int former_slen){
	if ((s == NULL) && (p == NULL))	return true; 
	if ((s == NULL) || (p == NULL))	return false; 
	// s length
	int s_len = 0;
	// p length
	int p_len = 0;
	// record the count of asterisk in p 
	// that will appear in the following procedure.
	// decreace by 1 when a asterisk has been read
	int asterisk_count = 0;
	int questionmask_count = 0;
	int i = 0, j = 0;
	while (s[i++]!='\0') s_len ++;
	i = 0;
	while (p[i]!='\0') {
		if (p[i] == '*') asterisk_count ++;
		if (p[i] == '?') questionmask_count ++;
		p_len ++; i++;
	}
#ifdef DEBUG
	cout << s_len << " " << p_len <<endl;
#endif
    int len_flag = 0;
	i = 0;
	if (s_len < p_len) {
		if (s_len < (p_len - asterisk_count)) {
			if ( n_match_map.find(p_len) ==  n_match_map.end()) {
				n_match_map[p_len][1] = s_len;
				n_match_map[p_len][0] = former_slen;
			}
			return false;
		}
		int count = 0;
		for (int k = s_len - 1; k >= 0; k -- ) {
			if (p[k] != '*'	) count ++;
			if ((count >= s_len) && (p[k] == '*')) break;
		}
		
	} else if (s_len == p_len) {
		len_flag = 1;
	} else {
		len_flag = 2;
		if (!asterisk_count) {
			if ( n_match_map.find(p_len) ==  n_match_map.end()) {
				n_match_map[p_len][1] = s_len;
				n_match_map[p_len][0] = former_slen;
			}
		   	return false;
		}
	}
	char a='\0', b= '\0';
	while (i != s_len) {
		a = s[i];
		b = p[j];
		if ((a == b) || (b == '?')) {
			if (b=='?')	questionmask_count --;
			i ++; j ++;
			continue;
		} else if (b != '*') {
			if ( n_match_map.find(p_len) ==  n_match_map.end()) {
				n_match_map[p_len][1] = s_len;
				n_match_map[p_len][0] = former_slen;
			}
			return false;
		}
		// check b == * condition
		++j;
		if ((--asterisk_count) == (p_len - j - questionmask_count))	{
			n_match_map[p_len][0] = s_len;
			return true;
		}
		for (; j != p_len; j ++) {
			if (p[j] == '*') {
				asterisk_count --; continue;
			}
			for (; i != s_len; i++) {
				if (((s_len-i) < (p_len-j))
						&&(asterisk_count < (p_len - j - s_len + i))) {
					if ( n_match_map.find(p_len) ==  n_match_map.end()) {
						n_match_map[p_len][1] = s_len;
						n_match_map[p_len][0] = former_slen;
					}
					return false;
				}

#ifdef DEBUG
					cout << "s+i: " << s+i << endl;
					cout << "s+j: " << p+j << endl;
#endif
				if ((s[i] == p[j])||(p[j] == '?')){
					if ((n_match_map.find(p_len - j - 1) != n_match_map.end()) 
							&& (n_match_map[p_len-j-1][0] > s_len)
							&& (n_match_map[p_len-j-1][1] != 0)) {
						if ( n_match_map.find(p_len) ==  n_match_map.end()) {
							n_match_map[p_len][1] = s_len;
							n_match_map[p_len][0] = former_slen;
						}
						return false;
					}
				   	if (isMatchRecursion(s+i+1, p+j+1, n_match_map, s_len)) {
						n_match_map[p_len][0] = 0;
						n_match_map[p_len][1] = 0;
						return true; 
					}
				}
			}
			break;
		}
		if ( n_match_map.find(p_len) ==  n_match_map.end()) {
			n_match_map[p_len][1] = s_len;
		   	n_match_map[p_len][0] = former_slen;
		}
		return false;
	}
	n_match_map[p_len][0] = 0;
	n_match_map[p_len][1] = 0;

	return true;
}
bool Solution::isMatch(const char *s, const char *p) {
	map<int, map<int, int> > n_match_map;
	map<int, map<int, int> > &ref = n_match_map;
	return isMatchRecursion(s, p, ref, 0);
}
int main(int argc, char *argv[]){
	//string a("abbbaaaaaaaabbbabaaabbabbbaabaabbbbaabaabbabaabbabbaabbbaabaabbabaabaabbbbaabbbaabaaababbbbabaaababbaaa");
	//string b("ab**b*bb*ab**ab***b*abaa**b*a*aaa**bba*aa*a*abb*a*a");
	//string a("a");
	//string b("aa");
	string a("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb");
	string b("**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb");
	//string a("aaacdgswer");
	//string b("*a*?s*r");
	cout << a.size() << " " << b.size() << endl;
	Solution s;
	cout << "res: " << s.isMatch(a.c_str(), b.c_str()) << endl;
	return 1;
}
