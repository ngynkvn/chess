CC = g++
FLAGS = -std=c++11 -Wall
ODIR = bin
SRC = src
INCLUDE = -I include
main: 
	$(CC) $(FLAGS) $(INCLUDE) $(SRC)/main.cpp -o $(ODIR)/a.exe  


.PHONY: clean
clean:
	@echo "\tCleaning..";
	rm -f $(ODIR)/*.o $(ODIR)/*.exe