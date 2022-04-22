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
char inpfd = 0;
char* inpname = "";

struct SharedMem {
    char* input; // will be array with size 1 byte after mmap
    char inpfd;
    char* inpname;
}sharedmem;

//
//////////////////////////////////////////
