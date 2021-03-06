CC = g++-9
FLAGS = -std=c++17 -Wall -g

SRC = src
OUTDIR = bin
TESTDIR = test
OUTNAME = a.out

OBJS = Move Piece Board Search Evaluation
TEST = tests.cpp perft.cpp
TEST_FILES = $(TEST:%=$(TESTDIR)/%)
OBJ_FILES = $(OBJS:%=$(OUTDIR)/%.o)

.PHONY: clean test

$(OUTDIR)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OUTDIR)
	$(CC) $(FLAGS) -c $< -o $@

main: $(OBJ_FILES)
	$(CC) $(FLAGS) $(SRC)/main.cpp $^ -o $(OUTDIR)/$(OUTNAME) 

run: main
	./$(OUTDIR)/$(OUTNAME)

$(TESTDIR)/catch.o: 
	$(CC) $(FLAGS) -c $(TESTDIR)/test-main.cpp -o $(TESTDIR)/catch.o

test: $(TESTDIR)/catch.o $(TEST_FILES) $(OBJ_FILES)
	$(CC) $(FLAGS) $^ -o $(TESTDIR)/runtest -I src
	@./$(TESTDIR)/runtest
	
time: main 
	time -p ./bin/a.out

clean:
	@echo "\tCleaning..";
	rm -rf $(OUTDIR)
	rm -f $(addprefix $(TESTDIR)/,*.out *.exe, runtest, *.o)

callgrind: main
	@echo "\tRunning.."
	time -p valgrind --tool=callgrind ./$(OUTDIR)/$(OUTNAME)

gprof: main
	@echo "\tRunning.."
	@time -p ./$(OUTDIR)/$(OUTNAME)
	@mkdir -p ./snippets/profiling
	gprof ./$(OUTDIR)/$(OUTNAME) > ./snippets/profiling/result$(shell date "+%m-%T").gprof
	@head ./snippets/profiling/result$(shell date "+%m-%T").gprof

