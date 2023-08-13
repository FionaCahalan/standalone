#include <string.h>
#include <sys/types.h>

size_t strlen(const char *string){
    int i = 0;
    while(string[i]){
        i++;
    }
    return i;
}