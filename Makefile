CC = gcc
CFLAGS = -g -std=c99
SOFLAGS = -shared
LINKFLAGS = -L./logging/obj
LIBS = logging/obj/liblogging.a -pthread

EXAMPLE_FILES = main.c module.c
EXAMPLE_SRC = $(EXAMPLE_FILES:%.c=example/%.c)
EXAMPLE_OBJ = $(EXAMPLE_FILES:%.c=obj/%.o)
EXAMPLE_EXE = obj/main
EXAMPLE_INCLUDE = -I./logging/include

example/%.c: example/%.h

obj/%.o: example/%.c
	$(CC) $(CFLAGS) $(EXAMPLE_INCLUDE) -c -o $@ $^

$(EXAMPLE_EXE): $(EXAMPLE_OBJ)
	make -C ./logging all
	$(CC) $(CFLAGS) $(LINKFLAGS) -o $@ $^ $(LIBS) 

all: $(EXAMPLE_EXE)

clean:
	make -C ./logging clean
	rm -f $(EXAMPLE_OBJ) $(EXAMPLE_EXE)
