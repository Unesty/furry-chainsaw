#include <stdbool.h>

enum GOType {
    player,
    enemy,
};
struct GameObject {
    enum GOType type;
    float pos;
    int hp;
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

    bool quit;
//
//////////////////////////////////////////
}*shm;

char inpfd;
char* inpname;
