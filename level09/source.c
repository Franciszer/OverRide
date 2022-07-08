#include <stdio.h>
#include <string.h>

typedef unsigned int	u64;

typedef struct	s_msg
{
	u64		msg_size;
	char	name[40];
	char	msg[140];
}				t_msg;


void	secret_backdoor()
{
	char	buf[128]; /* rbp-0x80 */

	fgets(buf, 128, stdin);
	system(buf);
	return ;
}

void	set_username(t_msg *msg)
{

	int		var;		/* rbp-0x04 */
	char	buf[140];	/* rbp-0x90 */

	bzero(buf, 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(buf, 128, stdin);
	strncpy(msg->name, buf, 41);	/* equivalent of below */
	// var = 0;
	// while (var <= 40 && buf[var] != 0)
	// {
	// 	(msg->name)[var] = buf[var];
	// 	++var;
	// }
	printf(">: Welcome, %s", msg->name);
	return ;
}

void	set_msg(t_msg *msg)
{
	char	buf[1024];	/* rbp-0x400 */

	bzero(buf, 1024);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(buf, 1024, stdin);
	strncpy(msg->msg, buf, msg->msg_size);
}

void	handle_msg(void)
{
	t_msg	msg;	/* rbp-0xc0 */

	bzero(msg.name, 40);
	msg.msg_size = 140;
	set_username(&msg);
	set_msg(&msg);
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
