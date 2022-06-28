#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char    a_user_name[0x44];

int    verify_user_name(char* user_name) {
    puts("verifying username....");
    return strcmp(a_user_name, user_name);
}

int     verify_user_pass(char* user_pass) {
    return strcmp(user_pass, "admin");
}

int main()
{
    int     iseq; // +0x5c
    char    buffer[64]; // +0x1c

    bzero(buffer, 64);

    iseq = 0;

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, 0x100, stdin);
    iseq = verify_user_name(buffer);

    if (!iseq) {
        puts("Enter Password: ");
        fgets(buffer, 0x64, stdin);
        iseq = verify_user_pass(buffer);
    }

    puts("nope, incorrect username...\n");
    return 1;
}