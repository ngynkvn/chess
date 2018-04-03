CC = g++
FLAGS = -std=c++11 -Wall
ODIR = bin
SRC = src
TESTDIR = test
INCLUDE = -I include
OBJS = Move.o Piece.o

%.o: $(SRC)/%.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(ODIR)/$@

main: $(OBJS)
	$(CC) $(FLAGS) $(INCLUDE) $(SRC)/main.cpp $(patsubst %.o,bin/%.o,$^) -o $(ODIR)/a.out  

buildtest: $(OBJS)
	$(CC) $(FLAGS) $(INCLUDE) $(TESTDIR)/test.cpp $(patsubst %.o,bin/%.o,$^) -o $(TESTDIR)/test.out

test: buildtest
	./test/test.out

clean:
	@echo "\tCleaning..";
	rm -f $(ODIR)/*.o $(ODIR)/*.exe
	rm -f $(TESTDIR)/test.exe


.PHONY: clean test