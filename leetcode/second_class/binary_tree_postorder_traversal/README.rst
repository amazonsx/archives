Given a binary tree, return the postorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].

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
    last_visited = NULL
    while(p) {
        s.push(p);
        p = p->left;
    }
    while(!s.empty) {
        current = s.top()
        if ((current->left||current->right) == NULL) || (currnet->left==last_visited || current->right == last_visited) {
           s.pop();
           last_visited = current; 
        }
        if (current->right) {
            p = current->right;
            while(p) {
                s.push(p);
                p = p->left;
            }
        }
    }

