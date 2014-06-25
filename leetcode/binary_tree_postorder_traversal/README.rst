Given a binary tree, return the preorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?


Thoughts:

Recursion method:
    if (left(current) access preorder(left(current))
    if (right(current) access preorder(right(current))
    access the current point
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
        p = current
        while(p) {
            push(s, p)
            p = p->left
        }
        access current
    }

