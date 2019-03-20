CXX=g++
CXXFLAGS= -O2 -lm -lgsl -lgslcblas
OBJS= main.o
NAME= a.out

$(NAME): $(OBJS)
	$(CXX)  -o $@  $^ $(CXXFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
			
.PHONY: clean

clean:
	rm -f *o
	rm -f ./$(NAME)
					
run:
	./main
