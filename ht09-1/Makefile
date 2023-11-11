CC := gcc
LD := gcc
CFLAGS := -Wall -O2
LDFLAGS := -rdynamic -s

.PHONY: all clean

all: printrandom

printrandom: main.o linear.o random.o
	$(CC) $(LDFLAGS) main.o linear.o random.o -o printrandom

main.o: main.c random_source.h
	$(CC) $(CFLAGS) -c main.c

random.o: random.c random_source.h
	$(CC) $(CFLAGS) -c random.c

linear.o: linear.c random_source.h
	$(CC) $(CFLAGS) -c linear.c

clean:
	rm -f *.o printrandom
