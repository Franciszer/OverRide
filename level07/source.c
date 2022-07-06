#include <stdio.h>

typedef unsigned int	u32;
typedef unsigned char	u8;

u32	store_number(char *buf)
{
	return (0);
}

u32	read_number(char *buf)
{
	return (0);
}

int	main(int ac, char **argv, char **argenv)
{
	u32		canary;		/* esp+0x1cc */
	char	cmd[20];	/* esp+0x1b8 */
	u32		var;		/* esp+0x1b4 */
						u8	pad[300];
	char	buf[100];	/* esp+0x024 */

	canary = 20;
	var = 0;
	bzero(cmd, 20);
	bzero(buf, 100);
	for (char **av = argv; *av; ++av)
		bzero(*av, strlen(*av));
	for (char **env = argenv; *env; ++env)
		bzero(*env, strlen(*env));
	puts(
	"----------------------------------------------------\n"
	"  Welcome to wil's crappy number storage service!   \n"
	"----------------------------------------------------\n"
	" Commands:                                          \n"
	"    store - store a number into the data storage    \n"
	"    read  - read a number from the data storage     \n"
	"    quit  - exit the program                        \n"
	"----------------------------------------------------\n"
	"   wil has reserved some storage :>                 \n"
	"----------------------------------------------------\n\n");
	for (;;)
	{
		printf("Input command: ");
		fgets(cmd + 4, 20, stdin);
		cmd[strlen(cmd) - 1] = 0;
		if (strncpy(cmd, "store", 5) == 0)
			var = store_number(buf);
		if (strncpy(cmd, "read", 4) == 0)
			var = read_number(buf);
		if (strncpy(cmd, "quit", 4) == 0)
			break ;
		if (var == 0)
			printf(" Completed %s command successfully\n", cmd);
		else
			printf(" Failed to do %s command\n", cmd);
	}
	if (canary != 20)
		*(int *)0 = 0;	/* __stack_chk_fail, induce crash if canary smashed */
	return (0);
}