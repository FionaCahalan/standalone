#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    char word[] = "Hello World!";
    int len = strlen(&word);
    write(STDOUT_FILENO, &word, len);
    return 5;
}