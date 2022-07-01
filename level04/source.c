#include <sys/types.h>
#include <unistd.h>
#include <sys/prctl.h>

int main() {
    pid_t   pid; // +0xac
    char    buffer[0x20]; // +0x20
    char*   ptr1; // +0xa8
    char*   ptr2; // +0x1c

    pid = fork();

    // bzero(buffer, 0x20);

    ptr1 = NULL;
    ptr2 = NULL;

    if (pid == 0) {
        prctl(0, 0);
    }
}