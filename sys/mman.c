#include <sys/mman.h>
#include "/usr/include/asm/unistd_64.h"

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset){
    long ret;
    register long r10 __asm__("r10") = flags;
	register long r8 __asm__("r8") = fd;
	register long r9 __asm__("r9") = offset;
    asm("syscall"
        : "=a" (ret)
        : "a"(__NR_mmap), "D" (addr), "S" (len), "d" (prot), "r" (r10), "r" (r8), "r" (r9)
        : "rcx", "r11", "memory"
    );
    return (void*)ret;
}

int munmap(void *addr, size_t len){
    long ret;
    asm("syscall"
        : "=a" (ret)
        : "a"(__NR_munmap), "D" (addr), "S" (len)
        : "rcx", "r11", "memory"
    );
    return ret;
}
