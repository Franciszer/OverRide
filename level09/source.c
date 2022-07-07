#include <stdio.h>
#include <string.h>

typedef unsigned int	u32;
typedef unsigned int	u64;

void	secret_backdoor()
{
	char	buf[128]; /* rbp-0x80 */

	fgets(buf, 128, stdin);
	system(buf);
	return ;
}

void	set_username(char *argbuf)
{
	char	buf[128];	/* rbp-0x90 */
	char	*arg;		/* rbp-0x98 */

	arg = argbuf;
	bzero(buf, 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(buf, 128, stdin);
	strncpy(arg + 140, buf, 40);
	printf(">: Welcome, %s", arg + 140);
	return ;
}

void	set_msg(char *argbuf)
{
	char	buf[1024];	/* rbp-0x400 */
	char	*arg;		/* rbp-0x408 */

	arg = argbuf;
	bzero(buf, 1024);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(buf, 1024, stdin);
	strncpy(arg, buf, *(long *)(arg + 180)); /* accede a var de handle_msg */
}

void	handle_msg(void)
{
	u64		var;		/* rbp-0x0c */
	char	buf[180];	/* rbp-0xc0 */

	bzero(buf + 140, 40);
	var = 140;
	set_username(buf);
	set_msg(buf);
	puts(">: Msg sent!");
	return ;
}

int		main(void)
{
	puts("--------------------------------------------\n"
		"|   ~Welcome to l33t-m$n ~    v1337        |\n"
		"--------------------------------------------\n");
	handle_msg();
	return (0);
}

