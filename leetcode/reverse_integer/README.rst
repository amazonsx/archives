Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321


Have you thought about this?
Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!
If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.
Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?
Throw an exception? Good, but what if throwing an exception is not an option? You would then have to re-design the function (ie, add an extra parameter).

first try: 7:56 June 9th, 2014
first fin: 10:24 June 9th, 2014


Solutions:
The basic idea of this problem is to tranverse the original integer from high bit to low bit.
 
But there are something detailed, disgusting.
What if the reversing of the integer overflows?
So I had to use a unsigned integer to load the reversed integer.
And then I had to transform the unsigned integer to the result which is unsigned.
A cast using "(int)" is not ok from unsinged to signed in cpp.

So I cast them, reading bit by bit mannually.

