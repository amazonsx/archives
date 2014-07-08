Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie,a <= b <= c)
The solution set must not contain duplicate triplets.

For example, given array S = {-1 0 1 2 -1 -4},
A solution set is:
(-1, 0, 1)
(-1, -1, 2)


Thoughts:
Corner cases:
a value has duplicate values in the num array: 
This may lead to the duplication in the final result vector.

a array has more than 3 zeros:
This may lead to the forgotten of (0 0 0 ) in the final result vector.

a array has exaclty 3 zeros:
This may lead a duplication of ( 0 0 0 ) in the final result vector.
