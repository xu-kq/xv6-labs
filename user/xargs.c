#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    char* cmd[argc];
    for(int i = 0; i < argc - 1; ++i) {
        cmd[i] = argv[i + 1];
    }

    char buf[255];
    int n = read(0, &buf, 255);

    char* p = buf;
    for(int i = 0; i < n; ++i) {
        if(buf[i] != '\n') {
            continue;
        }
        else {
            if(fork() == 0) {
                buf[i] = 0;
                cmd[argc - 1] = p;
                exec(argv[1], cmd);
            }
            else {
                wait(0);
                p = buf + i + 1;
            }

        }
    }
    exit(0);
}
