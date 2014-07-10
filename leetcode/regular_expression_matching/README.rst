Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a")  false
isMatch("aa","aa") true
isMatch("aaa","aa") false
isMatch("aa", "a*") true
isMatch("aa", ".*") true
isMatch("ab", ".*") true
isMatch("aab", "c*a*b") true

Thoughts:
Intuitively, there is a recursive method to solve this problem.
After the recognition of some preceding chars, 
then the subproblem is to recognize the following substring.
So the prototype of the recursive method can be,
isMatch( str_to_be_recognized, regular_exp)

The key in every cases is to list all the composition of the next head of s and p
