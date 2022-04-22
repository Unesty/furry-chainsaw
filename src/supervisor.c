#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <math.h>
#include "shared.h"

// we can add child process signal handlers

// TODO: supervision
// struct Pids {
//     int* gameplay, graphics, sound;
// }*pids;

int main(int argc, char** argv, char** envp) {
    // init shm
    inpname = "/furrychainsaw_input0";
    inpfd = shm_open(inpname, O_CREAT|O_EXCL|O_RDWR, S_IRUSR | S_IWUSR);
    if (inpfd == -1) {
        printf("can't open shm %s\n", inpname);
        //TODO: generate new name
    }
    if (ftruncate(inpfd, 1) == -1) {
        printf("can't truncate shm\n");
    }
    shm = (struct SharedMem*)mmap(0, sizeof(struct SharedMem), PROT_READ|PROT_WRITE, MAP_SHARED, inpfd, 0);
    if (shm == MAP_FAILED) {
        printf("mmap failed\n");
    }
//     pids = (struct Pids*)mmap(0, sizeof(struct Pids), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, inpfd, 0);
    // run gameplay
    if(!fork()) {
        execvpe("src/gameplay", argv, envp);
//         pids.gameplay =
    }
    // run graphics

//         pids.graphics =
    // run sound

//         pids.sound =
    // wait
}
