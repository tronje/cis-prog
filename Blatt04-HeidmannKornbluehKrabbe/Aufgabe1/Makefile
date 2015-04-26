.PHONY: all clean
CC=gcc
CFLAGS=-Wall -Werror -Wunused-parameter -O0 -g -ggdb

all: revcomp.x

%.x: %.c
	${CC} ${CFLAGS} $< -o $@

clean:
	${RM} -f *.x ecoli.seq.rc

test: revcomp.x
	valgrind --track-origins=yes ./revcomp.x ecoli.seq
	diff ecoli.seq.rc expected_output
