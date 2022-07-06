#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void    log_wrapper(FILE* file /* rbp - 0x118 */, char* str /* rbp - 0x120 */, __uint64_t u /* rbp - 0x128 */) {
    char*   ptr; // rbp - 0x8

    rbp = 
}

int main(int argc /* rbp-0x94 */, char* argv[] /* rbp - 0xa0 */) {

    __uint64_t  canary; // rbp -0x8
    __uint8_t   bt; // rbp - 0x71
    __uint32_t  dword; // rbp -0x78
    FILE*       file2; // rbp - 0x80
    FILE*       file; // rbp - 0x88

    canary = 0xb5f3c629a160a200;
    bt = 0xff;
    dword = 0xffffffff;

    if (argc != 0x2) {
        printf("Usage: %s filename\n", "/mnt/nfs/homes/frthierr/workspace/OverRide/level08/Ressources/level08");
        exit(1);
    }

    file = fopen("./backups/.log", "w");

    if (file == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    log_wrapper(file, "Starting back up: ", argv[1]);

    file2 = fopen(argv[1], 'r');

    if (file2 == NULL) {
        printf("ERROR: Failed to open %s\n", 'a');
        exit(1);
    }
    

}