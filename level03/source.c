#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void	decrypt(unsigned arg)
{
	unsigned	var;		/* ebp-0x0c */
	char		buf[17];	/* ebp-0x1d */

	var = 20;
	((unsigned *)buf)[0] = 0x757c7d51U;
	((unsigned *)buf)[1] = 0x67667360U;
	((unsigned *)buf)[2] = 0x7b66737eU;
	((unsigned *)buf)[3] = 0x33617c7dU;
	buf[16] = 0;
}

void	test(unsigned in, unsigned b)
{
	unsigned	var;	/* ebp-0xc */

	var = b - in;
	if (var <= 21)
		decrypt(0x80489f0 + var << 2);
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
	test(var, 322424845);
	return (0);
}