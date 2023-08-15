.PHONY: all clean

CC := gcc
CFLAGS := -std=gnu17 -nostdlib -Og -g3 -W -Wall -Wshadow -Wstrict-prototypes -Wmissing-prototypes -fno-common -fno-stack-protector
CPPFLAGS := -I. -nostdinc
SRC := startup.c main_test.c string.c unistd.c sys/mman.c stdlib.c
OBJ := $(SRC:.c=.o)
NAME := startup
HDR := $(wildcard *.h sys/*.h)

all: startup

%.o : %.c $(HDR) Makefile
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

startup: $(OBJ) Makefile
	gcc $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f startup *~ *.o

unop_$(NAME): startup.c Makefile
	gcc -I. -std=gnu17 -nostdlib -nostdinc -g3 -W -Wall -Wshadow -Wstrict-prototypes -Wmissing-prototypes -fno-common -o $@ $<

mem_$(NAME): startup.c Makefile
	gcc $(CFLAGS) -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -o $@ $<

und_$(NAME): startup.c Makefile
	gcc $(CFLAGS)  -fsanitize=undefined -o $@ $<