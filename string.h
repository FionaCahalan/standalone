#ifndef STRING_H
#define STRING_H

#include <sys/types.h>

size_t strlen(const char *string);
void *memcpy(void *restrict, const void *restrict, size_t);
void *memchr(const void *, int, size_t);
int memcmp(const void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
char *strchr(const char *, int);
int strcmp(const char *, const char *);
char *strcpy(char *restrict, const char *restrict);
char *strdup(const char *);
char *strerror(int);


#endif
