L'executable va lire un maximum de 32 octets dans un buffer, avant de scanf un
entier non signe de 32 bits. Il appelle ensuite une fonction auth() avec en
parametres le buffer et l'entier, et si auth() renvoie 0, ouvre un shell.

Auth() va verifier si la chaine de caracteres contenue dans le buffer fait au
moins 6 octets, puis verifie si l'executable n'est pas ouvert en debug (pas de
gdb ou ltrace), et si la chaine ne contiens pas de caracteres non affichables.
Une variable est initialisee, puis, pour chaque caractere de la chaine, une
serie de calculs est faite, et le resultat est ajoute a la variable. A la fin,
si aucun des 3 tests n'echoue et si la variable est egale a l'entier passe en
parametre, auth() retourne 0, sinon 1.

Notre objectif est de trouver une combinaison de chaine + entier (que l'on
appelleras serial) qui fasse que auth retourne 1. Pour se faire, apres
desassemblage du binaire sans ghidra parce qu'on aime souffrir, on copie colle
le code de auth() pour l'executer independemment de l'executable, et observer
son resultat.

On cree un programme C qui va faire les calculs de auth, puis afficher le
resultat. Ensuite, on choisis une chaine de caracteres, on la lui passe, et on
peux recuperer le serial qui correspond:

	(sur la machine hote)
	$ gcc level06/Ressources/auth.c
	$ ./a.out "je bats francois au ping"

Pour cette chaine, le serial est 6246345.
Notre chaine d'attaque seras donc cette chaine, un \n, puis le serial qu'on
viens de trouver:

	$ echo -en "je bats francois au ping\n6246345\n" > /tmp/in
	$ (cat /tmp/in; echo "cat /home/users/level07/.pass") | ./level06
