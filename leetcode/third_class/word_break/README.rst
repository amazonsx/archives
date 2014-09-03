Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
For example, given
s = "leetcode",
dict = ["leet", "code"].
Return true because "leetcode" can be segmented as "leet code".


Thoughts:
Basic steps:
recognize the words one by one.
Some words may have the same prefix, so it's necessary to records all of them.
Recursive steps:
    Recognize all the posible words in one step, and do recursive recognization on the following substrings one by one.
Iterative steps:
    Use a stack s.
    Init: push(s, 0) // 0 is the search start of a substring
    
    Recognise all recogonized words which have the same prefix in one step with the start poped from the stack.  
    And push all their successor subscript into the stack.

    return true when subscipt poped from s is equal with the length of the string
    else return false

########################################################
Coner cases:
when there are some redundant words in dict, the performance can be badly affected.
like dict = 'a', 'aaaaaa'
So I use some trick to optimize these ---- remove the redundant words from dict. 

But I think maybe it's the design of the algorithm architecture which led these problem
So I guess this is not the best algorithm.
