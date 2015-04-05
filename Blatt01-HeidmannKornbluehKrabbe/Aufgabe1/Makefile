CC = gcc
CFLAGS = -Wall -Werror

all: hello.x

%.x: %.c
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -f *.o *.x
