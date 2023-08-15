#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LAST    0x1
#define FRONT   0x2
#define FREE    0x4
#define HUGE    0x8

int errno;

union hdr{
    struct {
        unsigned prev_size;
        unsigned this_size; // excluding header
        unsigned cookie;
        unsigned flags;
    };
    struct {
        union hdr *next;
        union hdr *prev;
    };
};

static union hdr free_list = (union hdr){.next = &free_list, .prev = &free_list, };

static union hdr *search_free_list(size_t size){
    union hdr *pos = free_list.next;
    union hdr *smallest = NULL;
    while(pos != &free_list && (smallest != NULL && smallest->this_size != size)){
        if (pos->this_size <= size && pos->this_size < smallest->this_size)
            smallest = pos;
        pos = pos[1].next;
    }
    if(smallest){       // remove from list
        smallest[1].prev = smallest[1].next;
        smallest[1].next[1].prev = smallest[1].prev;
    } else { // smallest == NULL
        // allocate more memory
        union hdr *new_mem = mmap(0, 0x500000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        new_mem->flags = FREE | FRONT;
        new_mem->this_size = 0x500000 -  2 * sizeof(union hdr);
        new_mem[1].prev = &free_list;
        new_mem[1].next = free_list.next;
        free_list.next = new_mem;
        new_mem[1].next[1].prev = new_mem;
        union hdr *trailer = new_mem + new_mem->this_size / sizeof(union hdr) - 1;
        trailer->flags = LAST;
        trailer->prev_size = new_mem->this_size;
        smallest = new_mem;
    }
    if(smallest->this_size > size + 2 * sizeof(union hdr)){
        union hdr *child = smallest + size / sizeof(union hdr);
        child->flags = smallest->flags;
        child->this_size = smallest->this_size - size;
        smallest->flags &= ~LAST;
        smallest->this_size = size;
        child->prev_size = smallest->this_size;
        child[1].prev = smallest[1].prev;
        child[1].next = smallest[1].next;
    }
    return smallest;
}

void *malloc(size_t size){
    if(!size)
        return NULL;
    size = (size + 0xf) & ~0xf;     // round up to multiple of 16
    union hdr *new_mem;
    if(size > 1000000){
        int mmap_size = (size + sizeof(union hdr) + 0xfff) & ~0xfff;
        new_mem = mmap(0, mmap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        new_mem->flags = HUGE;
        new_mem->this_size = mmap_size - sizeof(union hdr);
    } else {
        new_mem = search_free_list(size);
        new_mem->flags &= ~FREE;
    }
    return new_mem + 1;
}

void free(void *ptr){
    if (!ptr)
        return;
    union hdr *hdr = ptr;
    hdr--;
    if(hdr->flags & HUGE){
        munmap(ptr, hdr->this_size + sizeof(union hdr));
    } else{
        hdr->flags &= ~FREE;
        hdr[1].next = free_list.next;
        free_list.next = hdr;
        hdr[1].prev = &free_list;
        hdr[1].next[1].prev = hdr;
    }
}

void *calloc(size_t nmemb, size_t size){
    size_t max_members = ~0ul / size;
    if(nmemb > max_members)
        return NULL;
    void *tmp = malloc(nmemb*size);
    memset(tmp, 0, nmemb*size);
    return tmp;
}
void *realloc(void *ptr, size_t size){
    void *tmp = malloc(size);
    union hdr *hdr = ptr;
    size_t old_size = hdr[-1].this_size;
    size_t min_size = size < old_size ? size : old_size;
    memcpy(tmp, ptr, min_size);
    free(ptr);
    return tmp;
}
void *reallocarray(void *ptr, size_t nmemb, size_t size){
    size_t max_members = ~0ul / size;
    if(nmemb > max_members)
        return NULL;
    return realloc(ptr, nmemb*size);
}
