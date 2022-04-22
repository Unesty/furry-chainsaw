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

int gameplay_pid, graphics_pid, sound_pid;

int main() {

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
    input = mmap(0, 1, PROT_READ|PROT_WRITE, MAP_SHARED, inpfd, 0);
    if (input == MAP_FAILED) {
        printf("mmap failed\n");
    }
    // run gameplay
//     gameplay_pid =
    // run graphics
//     graphics_pid =
    // run sound
//     sound_pid =
    // wait
}
