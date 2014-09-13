Given n non-negative integers representing the histogram's bar height 
where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

For example,
Given height = [2,1,5,6,2,3],
return 10.


Solution:

Idea 1.
For every element, search the elements around it to count its continuous nodes.
This will be a n^2 time complexity algorithm is the worst cases.
Too slow

Idea 2.
To abbreviate the time overhead,
I thought we could use the left and right elements' continuous count to calculate 
the current one.
current = left + right + 1.
Actually, this is not compeletely right because,
in some cases, a higher left or right element may block the way of the current element to a further element.


Idea 3.
Follow the idea 2, we use the left and right continuous element to calculate the current one.
But when it's blocked, we give it a check, and if it can be continueing, we go on.
And the difference between Idea 3 and 1 is that , 1 finds the continuous by jumps in 1 interval,
while 3 finds the continuous by jumps in serveral intervals decided by a former continuous element.
