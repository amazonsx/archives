Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.


first try: 14:00, June 8, 2014
first fin: 21:19, June 8, 2014


Solutions:
No complex recursion or loop in the implemenation.
Just a bunch of fussy conditions. Maybe a recursion would ease the implementation complexity.
But unfortunately, I choose the iteration implementation method.

Valid conditions I can still remember,
chars can show in the string: digits, +, -, e, ' ', '.'
For digits, no special requirements.
For +/-, valid chars before them: ' ', e or nothing
         valid chars behind them: must a digit
For ' ', should split the string into more than two substrings
For e,  valid chars before it: a valid decimal number or integer, cannot be a 0
        valid chars behind it: +, - and a valid integer
For '.', valid chars before it: all the former chars,
         valid chars behind it: digits > ' '.

There cant be two '.' or two 'e' in the string
