CC = gcc
CFLAGS = -Wall -Werror -O3

all: celsiusToFahrenheit.x

%.x: %.c
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -f *.x *.o
