Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
You should pack your words in a greedy approach;  that is, pack as many words as you can in each line. 
Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. 
If the number of spaces on a line do not divide evenly between words, 
the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.
Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

There are some cornor cases not listed yet. Find them.

first try start : 15:26, June 25, 2014
first try end : 15:26, June 25, 2014

Thoughts:
I think this can be implenmented with dynamic programming technique or greedy algorithm technique.

1. Greedy algorithm
strategy: 
caculate all the length of the input strings and sort them by their length in desending order.
Then we always try to pick the longest available string to pad the remaining part of a line.
The longest available string means that this string could be inserted into a line whose construction hasn't been finished.
After inserting all the words, the algorithm provides a optimal result.
proof by contradiction:
Assume that this is not good enough. 
Then we have a better plan, may be not a optimal one, but it provides a less consume of lines.
It must be something like, we switch some words or word pairs and there's some place for us to insert some words and decrease the line usage.
The only way to get new spaces is to use the long 
TO be continued...

presudo code:
    sort(word_list) 
    used_word_count = 0
    vector v;
    while(used_word_count < word_list.size()) {
        create a line l; 
        int length = 0; 
        for ( word in word_list) {
            if ( word is ok)     
               length += word.size(); 
               insert word into l;
            else break;
        } 
        v.push(l);
    }
    return v;
         

ERROR INFO
input a b c d e, 3
error,
actually, i have 
abc"
de "
but the leetcode have
a b
c d
e
