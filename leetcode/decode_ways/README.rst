A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.


Thoughts:

Now I got two ways to solve this problem.
1.
Intuitively, this problem has some characters in common with Word Break I.
According to the algorithm of Word Break I, 
we may use a stack to store the index in path while traversing the string.
When one path reach its end, we start to pop its points until a furcation is reached.
And we may need a anther stack to store all the furcation index, 
or we can't identify the choices( go forward or go back) when we meet a furcation point.
And when the furcation stack is empty, we can stop our processing.

So this is a iteration method. And I believe its recursion method will be much easier to program.

2.
Much more understandable than the first method.
We may realize that all the furcation are binary. 
So we can use a binary tree to build the furcation path.
In this method, we also need a stack to store the furcation points, or we will lost the furcation info.
When the stack is empty, it means the completion of the tree.
So we can check the count of leaves in the tree.
And this is the result.

3. methematical method
Acctually, use the knowledge of combination mathematics is the easiest algorithm.
We check amount S of couples that may cause a furcation. And the result is 2^S.
Some cases were forgotten here, dont trust thie!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
This can be used as the mathematical model.

