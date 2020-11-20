CCC=g++
CFLAGS=-std=c++17 -g -Wall -Wextra -pedantic -Werror -fmax-errors=1
LDFLAGS = -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system

# Lägg till o-filer som ni vill ska skapas i denna listan!
OBJS = Resource_manager.o Entity.o Tower.o

#SRCS := $(wildcard *.cc)
#HEADERS := $(SRCS:%.cc=%.h)
#OBJS
.PHONY: clean, test

main: $(OBJS)
	$(CCC) $(CFLAGS) main.cc $^ $(LDFLAGS)

test: $(OBJS) test_main.o tests.cc
	$(CCC) $(CFLAGS) -o test tests.cc $(OBJS) $(LDFLAGS)
	./test

test_main.o: test_main.cc
	$(CCC) $(CFLAGS) -c test_main.cc

%.o: %.cc %.h
	$(CCC) $(CFLAGS) -c $< $(LDFLAGS)

clean:
	rm *.o
	rm *.h.gch
	rm test
	rm a.out
