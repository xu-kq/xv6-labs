#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int p[2];
    char buf[255];

    pipe(p);

    if(fork() == 0) {
        read(p[0], buf, 255);
        printf("%d: received %s\n", getpid(), buf);
        
        char msg[] = "pong";
        write(p[1], msg, 255); 
        close(p[1]);
        close(p[0]);
        exit(0);
    } else {
        char msg[] = "ping";
        write(p[1], msg, 255);

        wait(0);
        read(p[0], buf, 255);
        printf("%d: received %s\n", getpid(), buf);
        close(p[0]);
        close(p[1]);
        exit(0);
    }
}
