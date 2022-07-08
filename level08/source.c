#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void    log_wrapper(FILE* file /* rbp - 0x118 */, char* str /* rbp - 0x120 */, __uint64_t u /* rbp - 0x128 */) {
    char*   ptr; // rbp - 0x8

    rbp = 
}

int main(int argc /* rbp-0x94 */, char* argv[] /* rbp - 0xa0 */) {

    char        buff[0xff] = "./backups/";
    __uint32_t  fd; // rbp -0x78
    FILE*       infile; // rbp - 0x80
    FILE*       backupfile; // rbp - 0x88

    *buff = 0xff;
    fd = 0xffffffff;

    if (argc != 0x2) {
        printf("Usage: %s filename\n", "/mnt/nfs/homes/frthierr/workspace/OverRide/level08/Ressources/level08");
        exit(1);
    }

    backupfile = fopen("./backups/.log", "w");

    if (backupfile == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    log_wrapper(backupfile, "Starting back up: ", argv[1]);

    infile = fopen(argv[1], 'r');

    if (infile == NULL) {
        printf("ERROR: Failed to open %s\n", 'a');
        exit(1);
    }

    strcat(buff, argv[1]);

    fd = open(buff, 0xc1);

    if (fd == 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups", "/tt/a");
        exit(1);
    }

    while (1) {
        *(buff + 1) = fgetc(infile);
        if (*(buff + 1) == -1) return -1;
        write(fd, *(buff + 1), 1);
    }
    log_wrapper(backupfile, "Finished back up ", argv[1]);
    fclose(backupfile);
    close(fd);
    return 0;
}