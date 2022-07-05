#include <stdio.h>

typedef unsigned int	u32;
typedef unsigned char	u8;

int	main(int ac, char **argv, char **argenv)
{
	u32		canary;		/* esp+0x1cc */
	char	buf2[24];	/* esp+0x1b4 */
						u8	pad[300];
	char	buf[100];	/* esp+0x024 */
						u8	pad[8];
	char	**av;		/* esp+0x01c */
	char	**env;		/* esp+0x018 */

	av = argv;
	env = argenv;
	canary = 20;
	bzero(buf2, 24);
	bzero(buf, 100);
	do
	{

	} while (*av);


	if (canary != 20)
		*(int *)0 = 0;	/* __stack_chk_fail, induce crash if canary smashed */
	return (0);
}