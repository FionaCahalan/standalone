#ifndef FCNTL_H
#define FCNTL_H
#define STDIO_ERROR     0x00000001
#define STDIO_EOF       0x00000002

#define O_ACCMODE       00000003
#define O_RDONLY        00000000
#define O_WRONLY        00000001
#define O_RDWR          00000002
#ifndef O_CREAT
#define O_CREAT         00000100        /* not fcntl */
#endif
#ifndef O_TRUNC
#define O_TRUNC         00001000        /* not fcntl */
#endif
#ifndef O_APPEND
#define O_APPEND        00002000
#endif
int open(const char *path_name, int flags, int mode);

#endif