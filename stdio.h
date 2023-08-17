#ifndef STDIO_H
#define STDIO_H

typedef struct _FILE FILE;
struct _FILE *stdin;
struct _FILE *stdout;
struct _FILE *stderr; 

FILE *fopen(const char *restrict pathname, const char *restrict mode);
FILE *fdopen(int fd, const char *mode);
FILE *freopen(const char *restrict pathname, const char *restrict mode,
        FILE *restrict stream);

#endif