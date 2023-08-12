#ifndef UNISTD_H
#define UNISTD_H

#include <sys/types.h>


ssize_t write(int fd, const void buf[.count], size_t count);
#endif
