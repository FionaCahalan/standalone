struct _FILE{
    int flags;
    int fd;
};

static struct _FILE stds[3] = {
    [STDIN_FILENO] = {.fd = STDIN_FILENO, }, 
    [STDOUT_FILENO] = {.fd = STDOUT_FILENO, },
    [STDERR_FILENO] = {.fd = STDERR_FILENO, },
};

struct _FILE *stdin = stds + STDIN_FILENO;
struct _FILE *stdout = stds + STDOUT_FILENO;
struct _FILE *stderr = stds + STDERR_FILENO;

static int make_mode_num (const char *restrict mode){
    int mode_num = 0;
    switch(mode[0]){
        case 'a':
            mode |= O_CREAT | O_APPEND;
            if(!mode[1]){
                mode |= O_WRONLY;
            } else if(mode[1] == '+'){
                mode |= O_RDWR;
            } else{
                //ERROR
            }
            break;
        case 'r':
            if(!mode[1]){
                mode |= O_RDONLY;
            } else if(mode[1] == '+'){
                mode |= O_RDWR;
            } else{
                //ERROR
            }
            break;
        case 'w'
            mode |= O_CREAT | O_TRUNC;
            if(!mode[1]){
                mode |= O_WRONLY;
            } else if(mode[1] == '+'){
                mode |= O_RDWR;
            } else{
                //ERROR
            }
            break;
    }
    return mode_num;
}

FILE *fopen(const char *restrict pathname, const char *restrict mode){
    int mode_num = make_mode_num(mode);
    struct _FILE *new_file = malloc(sizeof *new_file);
    new_file->fd = open(pathname, mode_num, 0666);
    new_file->flags = mode_num;     //improper use of flags
    return new_file;
}
FILE *fdopen(int fd, const char *mode){

}
FILE *freopen(const char *restrict pathname, const char *restrict mode, FILE *restrict stream){
    int mode_num = make_mode_num(mode);
    if(stream->fd != -1)
        close(stream->fd);
    stream->fd = open(pathname, mode_num, 0666);
    stream->flags = mode_num;       //improper use of flags
    return stream;
}

