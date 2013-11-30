TARGET = libbrp.a

CFLAGS += -Wall -Wshadow -Wpointer-arith -Wcast-align
CFLAGS += -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wextra
CFLAGS += -Wnested-externs -Winline -Wno-long-long  -Wunused-variable
CFLAGS += -Wstrict-prototypes -pedantic -static -Wno-unused-function
CFLAGS += -Werror -ansi

all: $(TARGET)

$(TARGET): brp.o
	ar -crs $(TARGET) brp.o

brp_test: libbrp.a brp_test.c
	$(CC) $(CFLAGS) -o $@ brp_test.c -L. -lbrp

brp.o: brp.c brp.h
	$(CC) $(CFLAGS) -c brp.c

test: brp_test
	./brp_test

clean:
	rm -f *.o *.a brp_test

.PHONY:	all clean test
