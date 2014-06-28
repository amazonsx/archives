Word Ladder II Total Accepted: 

Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:
1. Only one letter can be changed at a time
2. Each intermediate word must exist in the dictionary

For example,
Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5
Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.

g++ -o test -std=c++0x  -ggdb -Wall word_ladder_ii.cpp


Thouths:

I always want to solve it with graph shortest path algorithms.
But it seems that BFS is good enough to handle this.
