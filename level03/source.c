#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void	decrypt()
{

}

void	test(unsigned in, unsigned b)
{
	unsigned	var;	/* ebp-0xc */

	var = b - in;
	if (var <= 21)
	{

		*(char *)(0x80489f0 + var * 4);
	}

}

int	main(void)
{
	unsigned	var;

	srand(time(0));
	puts("***********************************");
	puts("*		level03		**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &var);
	test(var, 322424845);
	return (0);
}