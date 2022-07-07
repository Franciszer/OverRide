#include <stdio.h>
#include <stdlib.h>

typedef unsigned int	u32;
typedef unsigned long	u64;

void	err_quit(char *msg)
{
	puts(msg);
	exit(1);
}

int		main(int ac, char **av)
{
	u32	id;
	u32	tmp;

	if (ac < 2)
		err_quit("Need an arg !");
	id = (u32)atol(av[1]);
	tmp = (u32)(((u64)id * (u64)0xaaaaaaab) >> 33);
	tmp *= 3;
	printf("n: %u  tr: %u\n", id, tmp);
	printf("equal %u\n", id % 3 == 0);
	return (0);
}
