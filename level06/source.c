#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

unsigned	auth(char *buf, unsigned serial)
{
	int			len;	/* ebp-0xc */
	unsigned	var;	/* ebp-0x10 */
	int			i;		/* ebp-0x14 */

	buf[strcspn(buf, "\n")] = 0;
	if ((len = strnlen(buf, 32)) <= 5)
		return (1);
	if (ptrace(0, 0, 1, 0) == -1)
	{
		puts("\033[32m.---------------------------.");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m'---------------------------'");
		return (1);
	}
	var = ((int)buf[3] ^ 0x1337) + 0x5eeded;
	i = 0;
	do
	{
		if (buf[i] <= 0x1f)
			return (1);
	} while (i < len);
	return (0);
}

int			main(int ac, char **av)
{
	unsigned	canary;		/* esp+0x4c */
	char		buf[32];	/* esp+0x2c */
	unsigned	serial;		/* esp+0x28 */

	canary = 20;
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