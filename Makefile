remove=rm -d
cc=gcc

CFLAGS+=-Wall -Wextra -O2
all: test

OBJS = test.o queue.o

test : ${OBJS}
	$(cc) -o $@ ${OBJS}
	
clean:
	$(remove) *.o test 
