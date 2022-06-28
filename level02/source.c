#include <stdio.h>
#include <string.h>

void	main(void)
{
	FILE	*file;		/* rbp-0x8 */
	int		ret;		/* rbp-0xc */
	char	user[100];	/* rbp-0x70 */
	char	pass[48];	/* rbp-0xa0 */
	char	pass_in[112];	/* rbp-0x110 */

	bzero(user, 100);
	bzero(pass, 41);
	bzero(pass_in, 100);

	if ((file = fopen("/home/users/level03/.pass", "r")) == 0)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	ret = fread(pass, 1, 41, file);
	pass[strcspn(pass, "\n")] = 0;
	if (ret != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}
	fclose(file);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(user, 100, stdin);
	user[strcspn(user, "\n")] = 0;
	printf("--[ Password: ");
	fgets(pass_in, 100, stdin);
	pass_in[strcspn(pass_in, "\n")] = 0;
	puts("*****************************************");
	if (strncmp(pass, pass_in, 41) == 0)
	{
		printf("Greetings, %s!\n", user);
		system("/bin/sh");
		return (0);
	}
	printf(user);	/* TIENS TIENS TIENS */
	puts(" does not have access!");
	exit(1);
}
