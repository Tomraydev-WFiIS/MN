CC=gcc
CFLAGS= -lgsl -lgslcblas -lm -Wall -pedantic
OBJS=main.o
NAME=a.out

$(NAME): $(OBJS)
	$(CC)  -o $@  $^ $(CFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@
			
.PHONY: clean

clean:
	rm -f *o
	rm -f ./$(NAME)
	rm ./*.dat
					
run:
	./main
