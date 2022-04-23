#include <stdbool.h>

enum GOType {
    player,
    enemy,
    interactive,
};
struct GameObject {
    enum GOType type;
    float pos;
    bool hidden;
    char model[30];
};
struct Pids {
    int gameplay, graphics, sound;
};
struct SharedMem {
//////////////////////////////////////////
// gameplay




struct GameObject gos[2]; // array of all GameObject

// end gameplay
//////////////////////////////////////////

//////////////////////////////////////////
// communication with other processes


    char* input; // will be array with size 1 byte after mmap

    bool run;

    struct Pids pids;
//
//////////////////////////////////////////
}*shm;

char inpfd;
char* inpname;
