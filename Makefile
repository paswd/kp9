FLAGS=-Wextra -Wall -Werror -pedantic -std=c99

all: start

start: main.o key.o data.o table.o
	gcc $(FLAGS) -o kp9 key.o data.o table.o main.o -L. lib/libqueue.a

main.o: main.c
	gcc -c $(FLAGS) main.c

key.o: key.c
	gcc -c $(FLAGS) key.c

data.o: data.c
	gcc -c $(FLAGS) data.c

table.o: table.c
	gcc -c $(FLAGS) table.c

clear:
	-rm -f *.o *.gch kp9