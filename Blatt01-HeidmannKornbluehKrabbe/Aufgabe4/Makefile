CC     = gcc
CFLAGS = -Wall -Werror -O3

all: leapyear.x

%.x: %.c
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -f *.o *.x 