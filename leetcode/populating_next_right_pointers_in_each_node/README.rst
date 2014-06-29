Given a binary tree
struct TreeLinkNode {
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL


Thoughts:

We can use BFS to read all the nodes in sequence. But this will need a queue which cannot be constant length.

Actually, what we need to do is to read points line after line.
On a particular line, we can link their kids together. 
And so on their kids line, all kids have been conneced, and we can do the same thing previous again in loop.
So we need a pointer to store the start of next line, and a pointer to the node on the current line.
