Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

first try start: 22:13, June 23, 2014
first try end: 9:51, June 23, 2014

Thoughts:
Since we need to flip surrounded Os into Xs,
we may find all Os that shouldn't be changed.
I think this may be easier than finding all the Os that need to be changed.

All Os that shouldn't be changed have a path to Os that located on that edges of the graph.
So we can start with getting all the Os on edges.
And then extend our path from these Os and flag them.  Using a stack or a queue to store all extendable Os.
//I need another two-dimension vector to store these flags.
Actually, just use the original vector can do a in place alogirithm.

I use these flags:
X: means X
O: means O at the beginning, and keep the same at last means O that shoud be changed
#: means O that shouldn't be changed

So all 0 at last will be repaint.

Space Complexity: O(1)
Time Complexity: O(n)
