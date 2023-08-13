/*
Reference: https://www.reddit.com/r/C_Programming/comments/se3kgi/hello_world_without_libc/
*/
#include "/usr/include/asm/unistd_64.h"

int main(int argc, char *argv[]);

_Noreturn void _exit(int code){
    asm("syscall"
        :
        : "a" (__NR_exit_group),
          "D" (code)
        );
        __builtin_unreachable();
}

int _start(int argc, char *argv[]){
    int main_ret = main(argc, argv);
    _exit(main_ret);
}