CC=gcc
CFLAGS=-std=c99 \
	-O3 -Wall -Wextra -Wundef -Wfloat-equal -Wpointer-arith \
	-Wcast-align -Wstrict-prototypes -Wno-missing-field-initializers \
	-Warray-bounds -Wwrite-strings -pedantic -fstrict-aliasing \
	-Wshadow -Wswitch-default -Wswitch-enum
LINKS=-lpthread
INCLUDES=-I. -I./src

LIB_OBJS =
LIB_OBJS += build/objs/keyval.o
LIB_OBJS += build/objs/benchmark.o
LIB_OBJS += build/objs/hashtable.o
LIB_OBJS += build/objs/server.o

EXEC=keyval

all: clean $(EXEC)
	@echo ""

$(EXEC): $(LIB_OBJS)
	@$(CC) $(CFLAGS) -o $@ $(LIB_OBJS) $(INCLUDES) $(LINKS)

$(LIB_OBJS): build/objs/%.o: src/%.c
	@echo "cc: $<"
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) $(LINKS) -o $@

clean:
	find . -type f -name '*.o' -delete
