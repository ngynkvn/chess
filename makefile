CC = g++
FLAGS = -std=c++11 -Wall
ODIR = bin
SRC = src
TESTDIR = test
INCLUDE = -I include
main: 
	$(CC) $(FLAGS) $(INCLUDE) $(SRC)/main.cpp -o $(ODIR)/a.exe  

test:
	$(CC) $(FLAGS) $(INCLUDE) $(TESTDIR)/test.cpp -o $(TESTDIR)/test.exe

clean:
	@echo "\tCleaning..";
	rm -f $(ODIR)/*.o $(ODIR)/*.exe
	rm -f $(TESTDIR)/test.exe


.PHONY: clean test