CC=gcc
CFLAGS= -lm -lgsl -lgslcblas
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
					
run:
	./main
