#include <unistd.h>
#include <sys/types.h>

#include "/usr/include/asm/unistd_64.h"

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
    return ret_value;
}