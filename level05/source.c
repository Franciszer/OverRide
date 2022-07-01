#include <stdio.h>
#include <string.h>

void	main(void)
{
	unsigned	var;		/* esp+0x8c */
	char		buf[100];	/* esp+0x28 */

	var = 0;
	fgets(buf, 100, stdin);
	buf[100] = 0;
	for (var = 0; var < strlen(buf); ++var)
		if (buf[var] >= 'A' && buf[var] <= 'Z')	/* caps letters only */
			buf[var] ^= 0x20;					/* to lower caps */
	printf(buf);	/* tiens tiens tiens, ya le printf qui debarque */
	exit(0);
}