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
    access the current point
    if (left(current) || right(current) is NULL return
    if (left(current) access preorder(left(current))
    if (right(current) access preorder(right(current))


Iterative method:
    stack s;
    access the current point
    push(s, right)
    push(s, left)
    while (!s.empty()) {
        point = s.pop()
        access point
        push(s, right)
        push(s, left)
    }

