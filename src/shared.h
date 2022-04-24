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
enum Inputs {
    inp_none,
    inp_right,
    inp_left,
};
struct SharedMem {
//////////////////////////////////////////
// gameplay




struct GameObject gos[2]; // array of all GameObject

// end gameplay
//////////////////////////////////////////

//////////////////////////////////////////
// communication with other processes


    enum Inputs input;

    bool run;

    struct Pids pids;
//
//////////////////////////////////////////
}*shm;

char inpfd;
char* inpname;
