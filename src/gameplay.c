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
#include <linux/kd.h>
#include <stdbool.h>
#include <math.h>
//////////////////////////////////////////////
//// globals

long time = 0;
int sleep_time = 1000;
struct timeval stopt, startt, overallt;
bool quit = false;

//////////////////////////////////////////
// gameplay
enum GOType {
    player,
    enemy,
};
struct GameObject {
    enum GOType type;
    float pos;
    int hp;
};


struct GameObject gos[] = {{player, 0., 100}, {enemy, 10.,0}}; // array of all GameObject

// end gameplay
//////////////////////////////////////////

//////////////////////////////////////////
// communication with other processes
char* input; // will be array with size 1 byte after mmap
char inpfd;
//
//////////////////////////////////////////

//// end globals
//////////////////////////////////////////////

void io_init() {
    input = mmap(0, 1, PROT_READ|PROT_WRITE, MAP_SHARED, inpfd, 0);
}

void gameplay_init() {
    // spawn objects
    
}

void gameplay_loop() {
    while(quit == false) {
        printf("\n%f\n", gos[0].pos);
        usleep(sleep_time);
    }
}

int main() {
    io_init();
    gameplay_loop();
}
