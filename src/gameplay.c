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
#include "shared.h"

long time = 0;
int sleep_time = 1;
struct timeval stopt, startt, overallt;
bool quit = false;



//// end globals
//////////////////////////////////////////////

/**
 * Cross-platform sleep function for C
 * @param int milliseconds
 */
void sleep_ms(int milliseconds)
{
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
}

void io_init() {

    input = mmap(0, 1, PROT_READ|PROT_WRITE, MAP_SHARED, inpfd, 0);

}

void gameplay_init() {
    // spawn objects
    
}

void gameplay_loop() {
    while(quit == false) {
        printf("\n%f\n", gos[0].pos);
        sleep_ms(sleep_time);
    }
}

int main() {
    io_init();
    gameplay_loop();
}

