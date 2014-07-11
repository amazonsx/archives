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

Idea 1.(implemented)
Follow the Next Permutation k times from the original sorted integer list.
But this implemantation seems to have a really high time complexity.

Idea 2.(implemented with error on calculating the new first_k, second_k)
Try to guess the probable distribution of the integers in the permutation.
For the given k, we may calculate the m, satisfied (m)! <= k < (m+1)! 
(m accumulates from the rightmost)

Then m is a partition of the permutation
There will be n-m integers located on the left of  m.
If we could choose this n-m integers out. then the left permutation sequence 
is the k/(m!)th permutation.
the right sequencet si the k%(m!)th permuation of the other m integers.
Sounds like the network IP address, divided into subnet addr and addr in subnet.

Then decide each single permutation int the two sequences.
This really saves a lot of time and space.

Idea 3.(implemented)
Actually, in the implementation of Idea 2, 
I realized that the procedure of selecting each single integer 
of two sequences can be merged into one procedure.
For each location, there's a calculation method to determine it uniquely.
For the subsequence undecied, there are n integers.
Then the factorial of n is n!.
The first integer needed to determined can be get in this way:
index = k/n!, index means the index_th smallest integer in the available integer array.
Then n -> n - 1, the preocedure continues.

