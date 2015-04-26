.PHONY: all clean test
CC=gcc
CFLAGS=-Wall -Werror -Wunused-parameter -ggdb -std=c11

all: enumkmers.x

# if int_conv is used, uncomment this line and have int_conv.[ch] in this
# directory
#
# enumkmers.x: int_conv.o

enumkmers.x: enumkmers.o
	${CC} -lm -o $@ $^

enumkmers.o: enumkmers.c malloc2d.h
	${CC} ${CFLAGS} -c $<

clean:
	${RM} *.x *.o

test: enumkmers.x
	./test.sh | diff test.out -
