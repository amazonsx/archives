Given a roman numeral, convert it to an integer.
Input is guaranteed to be within the range from 1 to 3999.

Thoughts:
Just to cover all the cases
Roman numeral rule:
Just 7 chars: I（1）、V（5）、X（10）、L（50）、C（100）、D（500）和M（1000)


Identify integers while traversing the roman string from left to right.
For the current char, read its next char
if current > next,  and current and next are in the same bound(separated in every 10),
Then do a add operation
if current = next, Then do a add operation
if current < next, Then do a minus operation



