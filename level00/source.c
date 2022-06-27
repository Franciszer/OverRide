int main()
{
    int password;
    int local[3];

    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &password);

    if (password == 0x149c)
    {
        puts("\nAuthenticated!");
        system("/bin/sh");
    }
    else
    {
        puts("\nInvalid Password!");
    }

    return 0;
}