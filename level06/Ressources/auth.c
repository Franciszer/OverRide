#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int	u32;
typedef unsigned long	u64;

void	err_quit(char *msg)
{
	puts(msg);
	exit(1);
}

int		main(int ac, char **av)
{
	char	*buf;
	int		len;
	u32		var;
	int		i;
	u32		tmp;
	u32		tmp2;

	if (ac < 2)
		err_quit("Need an arg !");
	buf = av[1];
	if ((len = strnlen(buf, 32)) <= 5)
		err_quit("Arg too short, need to be at least 6 bytes !");
	var = ((int)buf[3] ^ 0x1337) + 0x5eeded;
	i = 0;
	do
	{
		if (buf[i] < ' ')
			err_quit("Only printable characters allowed");
		tmp2 = ((int)buf[i] ^ var);
		tmp = (u32)(((u64)tmp2 * (u64)0x88233b2b) >> 32);
		tmp += tmp2;
		tmp /= 0x800;
		tmp *= 0x539;
		var += tmp2 - tmp;
		++i;
	} while (i < len);
	printf("Serial: %d\n", var);
	return (0);
}
