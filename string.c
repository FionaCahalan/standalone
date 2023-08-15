#include <string.h>
#include <sys/types.h>

size_t strlen(const char *string){
    int i = 0;
    while(string[i]){
        i++;
    }
    return i;
}

void *memcpy(void *restrict, const void *restrict, size_t){

}

void *memmove(void *, const void *, size_t){}
void *memchr(const void *, int, size_t){}
int memcmp(const void *, const void *, size_t){}
void *memset(void *, int, size_t){}
char *strchr(const char *, int){}
int strcmp(const char *, const char *){}

char *strcpy(char *restrict dst, const char *restrict src){
    char *restrict org = dst;
    while(*dst++ = *src++)
        ;
    return org;
}

char *strdup(const char *src){
    return strcpy(malloc(strlen(src) + 1), src);
}
char *strerror(int){
    return "no idea";
}