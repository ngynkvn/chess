CC = g++
FLAGS = -std=c++11 -Wall -O3 -pg -g3

SRC = src
OUTDIR = bin
TESTDIR = test
OUTNAME = a.out
INCLUDE = -I include

OBJS = Move.o Piece.o Board.o Search.o Evaluation.o

%.o: $(SRC)/%.cpp
	@mkdir -p bin
	$(CC) $(FLAGS) -c $< -o $(OUTDIR)/$@ $(INCLUDE)

main: $(OBJS)
	$(CC) $(FLAGS) $(SRC)/main.cpp $(addprefix $(OUTDIR)/,$^) -o $(OUTDIR)/$(OUTNAME) $(INCLUDE)

run: main
	./$(OUTDIR)/$(OUTNAME)

catch: 
	$(CC) $(FLAGS) -c $(TESTDIR)/test-main.cpp -o $(TESTDIR)/catch.o

test: $(OBJS)
	$(CC) $(FLAGS) $(addprefix $(TESTDIR)/, catch.o tests.cpp perft.cpp) $(addprefix $(OUTDIR)/, $^) -o $(TESTDIR)/runtest $(INCLUDE)
	@./$(TESTDIR)/runtest
	
clean:
	@echo "\tCleaning..";
	rm -rf $(OUTDIR)
	rm -f $(addprefix $(TESTDIR)/,*.out *.exe, runtest)

callgrind: main
	@echo "\tRunning.."
	time -p valgrind --tool=callgrind ./$(OUTDIR)/$(OUTNAME)

gprof: main
	@echo "\tRunning.."
	@time -p ./$(OUTDIR)/$(OUTNAME)
	gprof ./$(OUTDIR)/$(OUTNAME) > ./snippets/profiling/result$(shell date "+%m-%e-%T").gprof
	@head ./snippets/profiling/result.gprof

.PHONY: clean test