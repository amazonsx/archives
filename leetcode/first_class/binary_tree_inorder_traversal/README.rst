Given a binary tree, return the inorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?


Thoughts:

Recursion method:
    if (left(current) access preorder(left(current))
    access the current point
    if (right(current) access preorder(right(current))
    return


Iterative method:
    stack s;
    p = current
    while(p) {
        push(s, p)
        p = p->left;
    }
    while (!s.empty()) {
        current = s.pop()
        access current
        p = current
        while(p) {
            push(s, p)
            p = p->left
        }
    }

