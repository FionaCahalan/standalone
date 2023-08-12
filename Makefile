.PHONY: all clean

CFLAGS := -nostdlib -Og -g3 -W -Wall -Wshadow -Wstrict-prototypes -Wmissing-prototypes -fno-common
CPPFLAGS := -I. -nostdinc
SRC := startup.c main_test.c
OBJ := $(SRC:.c=.o)
NAME := startup

all: startup

%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

startup: $(OBJ) Makefile
	gcc $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f startup *~ *.o

unop_$(NAME): startup.c Makefile
	gcc -I. -nostdlib -nostdinc -g3 -W -Wall -Wshadow -Wstrict-prototypes -Wmissing-prototypes -fno-common -o $@ $<

mem_$(NAME): startup.c Makefile
	gcc $(CFLAGS) -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -o $@ $<

und_$(NAME): startup.c Makefile
	gcc $(CFLAGS)  -fsanitize=undefined -o $@ $<