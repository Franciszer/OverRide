#include <stdio.h>

int	main(void)
{
	char	buf[17];

	for (unsigned var = 0; var <= 21; ++var)
	{
		((unsigned *)buf)[0] = 0x757c7d51U;
		((unsigned *)buf)[1] = 0x67667360U;
		((unsigned *)buf)[2] = 0x7b66737eU;
		((unsigned *)buf)[3] = 0x33617c7dU;
		buf[16] = 0;
		for (unsigned i = 0; i < 16; ++i)
			buf[i] ^= var;
		printf("%d > %s\n", var, buf);
	}
	return (0);
}
