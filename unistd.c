#include <unistd.h>
#include <sys/types.h>
#include "/usr/include/asm/unistd_64.h"
#include <errno.h>

ssize_t write(int fd, const void *buf, size_t count){
    long ret_value;
    asm("syscall"
        : "=a" (ret_value)
        : "a" (__NR_write),
          "D" (fd),
          "S" (buf),
          "d" (count)
        : "rcx",
          "r11",
          "memory"
        );
    if((unsigned long)ret_value > ~0xffful){
        errno = -ret_value;
        return -1;
    }
    return ret_value;
}

ssize_t read(int fd, void *buf, size_t count){
    long ret_value;
    asm("syscall"
        : "=a" (ret_value)
        : "a" (__NR_read),
          "D" (fd),
          "S" (buf),
          "d" (count)
        : "rcx",
          "r11",
          "memory"
        );
    if((unsigned long)ret_value > ~0xffful){
        errno = -ret_value;
        return -1;
    }
    return ret_value;
}

int close(int fd){
    int ret_value;
    asm("syscall"
        : "=a" (ret_value)
        : "a" (__NR_close),
          "D" (fd)
        : "rcx",
          "r11",
          "memory"
        );
    if((unsigned long)ret_value > ~0xffful){
        errno = -ret_value;
        return -1;
    }
    return ret_value;
}

int open(const char *path_name, int flags, int mode){
    long ret_value;
    asm("syscall"
        : "=a" (ret_value)
        : "a" (__NR_open),
          "D" (path_name),
          "S" (flags),
          "d" (mode)
        : "rcx",
          "r11",
          "memory"
        );
    if((unsigned long)ret_value > ~0xffful){
        errno = -ret_value;
        return -1;
    }
    return ret_value;
}
