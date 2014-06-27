You are given an n x n 2D matrix representing an image.
Rotate the image by 90 degrees (clockwise).
Follow up:
Could you do this in-place?

Thoughts:
Of course, this could be done in-place.
Let's map the matrix onto a coordinate system with it's dimensional subscripts.
Then there will be a leading diagonal and a median line of the matrix
So rotate the matrix by 180 degrees in clockwise can be divided into 2 steps.
Rotate along the leading diagonal and then rotate along the median line.
For point(a, b)
step 1. (b, a)
step 2. (b, n-1-a)




# this is the way to rotate the image by 180 degrees (clockwise)
Then there will be bivariate diagonals: one leading diagonal and one auxiliary diagonal.
So rotate the matrix by 180 degrees in clockwise can be divided into 2 steps.
Rotate along the leading diagonal and then rotate along the auxiliary diagonal.
For point(a, b)
step 1. (b, a)
step 2. (n-1-a, n-1-b)



