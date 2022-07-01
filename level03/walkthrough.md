The executable we have access to is highly obfuscated, and hard to disassemble
because of the use of a large jump table that essentially does nothing.

It uses scanf to read a signed integer on the standard input, and feeds it as an
unsigned to a test() function.

The test() function will subtract that number to 322424845, and check if the
resulting number is between 0 and 9, or between 16 and 21. If it is within
range, it sends it to a decrypt() function. If not, it sends a random number to
the decrypt function.

The decrypt() function will store data in a buffer, then xor each byte with the
least significant byte of the number passed to it. It will then compare the
resulting data to the string "Congratulations!" and conveniently open us a
shell.

Our objective is to find what value to pass to decrypt() in order for it to
produce the adequate string and open us a shell. To do that, since the range is
fairly limited, we can try all values from 0 to 21 and visually identify the
right one. This is done via a small C program in the Ressources folder. We can
clearly see that 18 is the right value.
Since 18 must be passed to decrypt(), the value passed to test() must be
322424845 - 18 = 322424827 so that the result can be subtracted to 322424845 to
give us back 18. It's also great that 18 is within the range allowed by test().

We then simply pass that number to the executable via standard input, and cat
the pass in the resulting shell.

$ echo "322424827" > /tmp/in
$ (cat /tmp/in; echo "cat /home/users/level04/.pass") | ./level03
