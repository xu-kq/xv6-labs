#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int in[2];
    int out[2];
    pipe(in);

    // initialize
    for(int i = 2; i <= 35; ++i) {
        write(in[1], &i, 4);
    }
    close(in[1]);

    int num;
    while(read(in[0], &num, 4) != 0) {
        pipe(out);
        if(fork() == 0) {
            close(in[0]);

            close(out[1]);

            in[0] = out[0];
        }
        else {

            printf("prime %d\n", num);     
            
            int i;
            while(read(in[0], &i, 4) != 0) {
                if(i % num != 0) {
                    write(out[1], &i, 4);
                }
            }

            close(in[0]);

            close(out[0]);
            close(out[1]);

            wait(0);
            exit(0);
        }
    }
    close(in[0]);
    exit(0);
}
