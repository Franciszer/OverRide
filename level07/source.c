#include <stdio.h>

typedef unsigned int	u32;
typedef unsigned char	u8;

/* ########################################################################## */

void	clear_stdin(void)
{
	char	c;

	while ((c = getchar()) != (char)0xff)
		if (c == '\n')
			break ;
	return ;
}

u32		get_unum(void)
{
	u32	var;

	fflush(stdout);
	scanf("%u", &var);
	clear_stdin();
	return (var);
}

/* ########################################################################## */

u32		store_number(u32 *buf)
{
	u32	num;	/* ebp-0x10 */
	u32	id;		/* ebp-0x0c */

	num = 0;
	id = 0;
	printf(" Number: ");
	num = get_unum();
	printf(" Index: ");
	id = get_unum();
	if (id % 3 == 0 || (num >> 24) != 0xb7)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	buf[id] = num;
	return (0);
}

u32		read_number(u32 *buf)
{
	u32	id;		/* ebp-0x0c */

	printf(" Index: ");
	id = get_unum();
	printf(" Number at data[%u] is %u\n", id, buf[id]);
	return (0);
}

/* ########################################################################## */

int		main(int ac, char **argv, char **argenv)
{
	u32		canary;		/* esp+0x1cc */
	char	cmd[20];	/* esp+0x1b8 */
	u32		var;		/* esp+0x1b4 */
	u8		buf[400];	/* esp+0x024 */

	canary = 20;	/* pseudo random value */
	var = 0;
	bzero(cmd, 20);
	bzero(buf, 400);
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
		fgets(cmd, 20, stdin);
		cmd[strlen(cmd) - 1] = 0;
		if (strncmp(cmd, "store", 5) == 0)
			var = store_number(buf);
		if (strncmp(cmd, "read", 4) == 0)
			var = read_number(buf);
		if (strncmp(cmd, "quit", 4) == 0)
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
