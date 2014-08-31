Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.


NOTE:
1. use the brute force method
2. optimize the brute force method to shorten the search width on the inner loop
3. two pointers, one head and one tail.
   move the pointer which has a smaller value to the middle until meet the other pointer
