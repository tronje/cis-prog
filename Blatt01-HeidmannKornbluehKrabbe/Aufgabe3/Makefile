CC = gcc
CFLAGS = -Wall -Werror

all: minmax.x

%.x: %.c
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -f *.o *.x
