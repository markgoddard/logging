CC = gcc
CFLAGS = -g -std=c99 -fPIC
SOFLAGS =

LOGGING_FILES = logger.c log_level.c log_system.c log_source.c log_sink.c log_sink_stdout.c log_sink_file.c
LOGGING_SRC = $(LOGGING_FILES:%.c=src/%.c)
LOGGING_OBJ = $(LOGGING_FILES:%.c=obj/%.o)

LOGGING_INCLUDE = -I./include

LOGGING_LIB = obj/liblogging.a

src/%.c: include/%.h

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(LOGGING_INCLUDE) -c -o $@ $^

$(LOGGING_LIB): $(LOGGING_OBJ)
	$(AR) -cvq $@ $^

all: $(LOGGING_LIB)

clean:
	rm -f $(LOGGING_OBJ) $(LOGGING_LIB)
