Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
For example,
Given n = 3, there are a total of 5 unique BST's.


first try start: 16:43, June 23rd, 2014
first try end: 19:26 June 234d, 2014


Solution:
Obviously, if we use the recursion technique, it'll be easier to think.
And to faster the algorithm, we should use mermorize technique or unpack the recursion.
So for recursion, there should be a recursion formula and exit entry.

recursion formula:
  Input: available leaves count n, root of current subtree
  Output: the maximum number of distinguished trees TN
  TN(n) = Sum(TN(i)*TN(j), (i + j = n-1, 0<=i<=n-1)) 
