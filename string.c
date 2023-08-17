#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

size_t strlen(const char *string){
    int i = 0;
    while(string[i]){
        i++;
    }
    return i;
}

void *memcpy(void *restrict dst, const void *restrict src, size_t sz){
    char *restrict d = dst;
    const char *restrict s = src;
    while(sz--)
        *d++ = *s++;
    return dst;
}

void *memmove(void *dst, const void *src, size_t sz){
    char *restrict d = dst;
    const char *restrict s =src;
    if(dst < src){
        while(sz--)
            *d++ = *s++;     
    } else {
        d += sz;
        s += sz;
        while(sz--)
            *--d = *--s;
    }
    return dst;
}

void *memchr(const void *mem, int findme, size_t sz){
    const unsigned char *m = mem;
    while(sz--){
        if((unsigned char)findme == *m)
            return m;
        m++;
    }
    return NULL;
}

int memcmp(const void *one, const void *two, size_t sz){
    while(sz--){
        const unsigned char *o = one++;
        const unsigned char *t = two++;
        int diff = *o - *t;
        if(diff)
            return diff;
    }
    return 0;
}

void *memset(void *dst, int val, size_t count){
    unsigned char *d = dst;
    while(count--)
        *d++ = val;
    return dst;
}

char *strchr(const char *mem, int findme){
    const unsigned char *m = mem;
    while(*m){
        if((unsigned char)findme == *m)
            return m;
        m++;
    }
    return NULL;
}

int strcmp(const char *one, const char *two){
    for(;;){
        const unsigned char *o = one++;
        const unsigned char *t = two++;
        int diff = *o - *t;
        if(diff || !*o)
            return diff;
    }
}

char *strcpy(char *restrict dst, const char *restrict src){
    char *restrict org = dst;
    while(*dst++ = *src++)
        ;
    return org;
}

char *strdup(const char *src){
    return strcpy(malloc(strlen(src) + 1), src);
}

static char *error_msgs[] = {
#include <errno-msgs.h>
};

char *strerror(int e){
    if (e >= sizeof(error_msgs)/sizeof(error_msgs[0]) || !!error_msgs[e])
        return "no idea";
    return error_msgs[e];
}
