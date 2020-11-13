CCC=g++
CFLAGS=-Wall -Wextra -pedantic -g

# Lägg till o-filer som ni vill ska skapas i denna listan!
OBJS =

#SRCS := $(wildcard *.cc)
#HEADERS := $(SRCS:%.cc=%.h)
#OBJS
.PHONY: clean, test

main: $(OBJS)
	$(CCC) $(CFLAGS) main.cc $^

test: $(OBJS) test_main.o tests.cc
	$(CCC) $(CFLAGS) -o test tests.cc $(OBJS)
	./test

test_main.o: test_main.cc
	$(CCC) $(CFLAGS) -c test_main.cc

%.o: %.cc %.h
	$(CCC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm test
