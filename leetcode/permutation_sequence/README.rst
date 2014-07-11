The set [1,2,3,…,n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.
Note: Given n will be between 1 and 9 inclusive.


Thoughts:

Idea 1.
Follow the Next Permutation k times from the original sorted integer list.
But this implemantation seems to have a really high time complexity.

Idea 2.
Try to guess the probable distribution of the integers in the permutation.
For the given k, we may calculate the m, satisfied (m)! <= k < (m+1)! 
(m accumulates from the rightmost)

Then m is a partition of the permutation
There will be n-m integers located on the left of  m.
If we could choose this n-m integers out. then the left permutation sequence 
is the k/(m!)th permutation.
the right sequencet si the k%(m!)th permuation of the other m integers.
Sounds like the network IP address, divided into subnet addr and addr in subnet.

We may still using the Next Permutation algorithm to build the left and right permutation.
But this really saves a lot of time and space.
