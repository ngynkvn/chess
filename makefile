CC = g++-9
FLAGS = -std=c++17 -Wall -g

SRC = src
OUTDIR = bin
TESTDIR = test
OUTNAME = a.out

OBJS = Move.o Piece.o Board.o Search.o Evaluation.o

%.o: $(SRC)/%.cpp
	@mkdir -p bin
	$(CC) $(FLAGS) -c $< -o $(OUTDIR)/$@ 

main: $(OBJS)
	$(CC) $(FLAGS) $(SRC)/main.cpp $(addprefix $(OUTDIR)/,$^) -o $(OUTDIR)/$(OUTNAME) 

run: main
	./$(OUTDIR)/$(OUTNAME)

catch: 
	$(CC) $(FLAGS) -c $(TESTDIR)/test-main.cpp -o $(TESTDIR)/catch.o

test: $(OBJS)
	$(CC) $(FLAGS) $(addprefix $(TESTDIR)/, catch.o tests.cpp perft.cpp) $(addprefix $(OUTDIR)/, $^) -o $(TESTDIR)/runtest -I src
	@./$(TESTDIR)/runtest
	
time: main 
	time -p ./bin/a.out

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
	@mkdir -p ./snippets/profiling
	gprof ./$(OUTDIR)/$(OUTNAME) > ./snippets/profiling/result$(shell date "+%m-%T").gprof
	@head ./snippets/profiling/result$(shell date "+%m-%T").gprof

.PHONY: clean test