CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -s

all: random.o linear.o main.o printrandom
printrandom: main.o random.o linear.o
	$(CC) $(LDFLAGS) main.o random.o linear.o -o printrandom -rdynamic
main.o: main.c random_source.h
	$(CC) $(CFLAGS) -c main.c -o main.o
random.o: random.c random_source.h
	$(CC) $(CFLAGS) -c random.c -o random.o
linear.o: linear.c random_source.h
	$(CC) $(CFLAGS) -c linear.c -o linear.o
clean:
	rm -f *.o printrandom