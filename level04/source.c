#include <sys/types.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/ptrace.h>

typedef unsigned int uint;

int	main(void)
{
	pid_t	pid;			//	+0xac
	uint	val;			//	+0xa8
	uint	val2;			//	+0xa4
	uint	val3;			//	+0xa0
	char	buffer[0x20];	//	+0x20
	uint	w_status;		//	+0x1c

	pid = fork();

	bzero(buffer, 0x20);

	val = 0;
	w_status = 0;

	if (pid == 0)
	{
		prctl(PR_SET_PDEATHSIG, 1);
		ptrace(0, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buffer);
	}
	while (true)
	{
		wait(&w_status);
		if (WIFEXITED(w_status) || WIFEXITED((w_status + 1) / 2))
		{
			puts("child is exiting...");
			break;
		}
		else if (ptrace(0x3, pid, 0x2c, 0) == 0xb)
		{
			puts("no exec() for you");
			kill(pid, SIGKILL);
			break;
		}
	}
	return (0);
}
