#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void	decrypt(unsigned arg)
{
	unsigned	canary;		/* ebp-0x0c */
	char		buf[17];	/* ebp-0x1d */

	canary = 20;
	((unsigned *)buf)[0] = 0x757c7d51U;
	((unsigned *)buf)[1] = 0x67667360U;
	((unsigned *)buf)[2] = 0x7b66737eU;
	((unsigned *)buf)[3] = 0x33617c7dU;
	buf[16] = 0;
	for (unsigned i = 0; i < 16; ++i)
		buf[i] ^= (unsigned char)arg;
	if (strncmp(buf, "Congratulations!", 17) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
	if (canary != 20)
		*(int *)0 = 0;	/* __stack_chk_fail, induce crash if overflow */
	return ;
}

void	test(unsigned in)
{
	unsigned	tmp;	/* ebp-0xc */

	tmp = 322424845 - in;
	if (tmp <= 9 || (tmp >= 16 && tmp <= 21))
		decrypt(tmp);
	else
		decrypt(rand());
	return ;
}

int	main(void)
{
	unsigned	var;	/* ebp-0xc */

	srand(time(0));
	puts("***********************************");
	puts("*		level03		**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &var);
	test(var);
	return (0);
}
