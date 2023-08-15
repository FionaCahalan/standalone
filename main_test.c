#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    char word[] = "Hello World!";
    int len = strlen(word);
    write(STDOUT_FILENO, &word, len);

    char *tester = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (tester != MAP_FAILED){
        *tester = 'a';
        write(STDOUT_FILENO, tester, 1);
    }

    return 5;
}
