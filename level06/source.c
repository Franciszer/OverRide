#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

typedef unsigned int	u32;
typedef unsigned long	u64;

unsigned	auth(char *buf, unsigned serial)
{
	int	len;	/* ebp-0xc */
	u32	var;	/* ebp-0x10 */
	int	i;		/* ebp-0x14 */

	u32	tmp;	/* registres */
	u32	tmp2;	/* registres */

	buf[strcspn(buf, "\n")] = 0;
	if ((len = strnlen(buf, 32)) <= 5)
		return (1);
	if (ptrace(0, 0, 1, 0) == -1)
	{
		puts("\033[32m.---------------------------.");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m'---------------------------'");
		/* fucks up your terminal >:c */
		return (1);
	}
	var = ((int)buf[3] ^ 0x1337) + 0x5eeded;
	for(i = 0; i < len; ++i)
	{
		if (buf[i] < ' ')
			return (1);
		tmp2 = ((int)buf[i] ^ var);
		tmp = (u32)(((u64)tmp2 * (u64)0x88233b2b) >> 32);
		tmp += tmp2;
		tmp /= 0x800;
		tmp *= 0x539;
		var += tmp2 - tmp;
	}
	if (serial == var)
		return (0);
	return (1);
}

int			main(int ac, char **av)
{
	unsigned	canary;		/* esp+0x4c */
	char		buf[32];	/* esp+0x2c */
	unsigned	serial;		/* esp+0x28 */

	canary = 20;	/* valeur differente a chaque execution */
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(buf, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &serial);
	if (auth(buf, serial) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
		return (0);
	}
	if (canary != 20)
		*(int *)0 = 0;	/* __stack_chk_fail, induce crash if overflow */
	return (1);
}
