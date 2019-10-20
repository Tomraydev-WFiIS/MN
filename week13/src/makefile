CC = gcc
CFLAGS = -lm
DEPS =
OBJS = main.o
OUT = program

$(OUT): $(OBJS)
	$(CC)  -o $@  $^ $(CFLAGS)
			
.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) 
			
.PHONY: clean	
clean:
	rm -f *o
	rm -f *~
	rm -f $(OUT)
					
run:
	./program
