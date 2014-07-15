Word Ladder II Total Accepted: 

Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:
1. Only one letter can be changed at a time
2. Each intermediate word must exist in the dictionary

For example,
Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
Return
[
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
]
Note:
    All words have the same length.
    All words contain only lowercase alphabetic characters.

g++ -o test -std=c++0x  -ggdb -Wall word_ladder_ii.cpp

Solution:

Idea 1.
We use a graph to represent the relationship of the words.
If they have a single char difference, then draw a edge to connect these nodes.
We use a adjecent list to describe the graph.
Space Complexity: O(VE)

And then, there's a list to store all the pathes have been accessed 
before reaching the final word.
Space Complexity: O(VE)

But leetcode gave a fallback ---- Memory Limit Execeed.

Idea 2.
Optimization by optimization !!!!





