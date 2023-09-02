#ifndef STDIO_H
#define STDIO_H

#include <sys/types.h>

typedef struct _FILE FILE;
struct _FILE *stdin;
struct _FILE *stdout;
struct _FILE *stderr; 

int fclose(FILE *stream);
FILE *fopen(const char *restrict pathname, const char *restrict mode);
FILE *fdopen(int fd, const char *mode);
FILE *freopen(const char *restrict pathname, const char *restrict mode,
        FILE *restrict stream);
size_t fread(void *restrict ptr, size_t size, size_t nmemb,FILE *restrict stream);
size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream);

#endif