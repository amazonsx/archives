Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

click to show clarification.

Clarification:
    What constitutes a word?
        A sequence of non-space characters constitutes a word.
    Could the input string contain leading or trailing spaces?
        Yes. However, your reversed string should not contain leading or trailing spaces.
    How about multiple spaces between two words?
        Reduce them to a single space in the reversed string.

second try on September 2nd, 2014 from 8:43 to 9:40. 

Solution:
1. Reverse each characters of words in the string. 
   And then reverse each characters of the string.

2. Use a stack to save all the words have been visited and pop them back.
   So the orders of words are reversed.

Attention:
Each solution contains the procedure that filters duplicate 0s.
This procedure can be combined with the first step of each solution to save traversal time.
