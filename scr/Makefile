ifndef path
path = ../data/
endif

ifndef num
	ifeq ($(path), ../data/)
	num = 10103
	endif
	ifeq ($(path), ../data2/)
	num = 9999
	endif
endif

ifndef cmd
cmd = stats
endif

FLAGS = -Wall -Wextra
ALLMAIN = main_bst main_avl main_rbt
ALLTEST = test_bst test_avl test_rbt
all: TARGET

## JUST COMPILE
ifndef tree 

OBJS = bin/tree_utils.o bin/data.o

# Compile all main
TARGET: $(ALLMAIN)

main_bst: bin/main_bst.o bin/bst.o $(OBJS)
	g++ $(FLAGS) bin/main_bst.o bin/bst.o $(OBJS) -o $@

main_avl: bin/main_avl.o bin/avl.o $(OBJS) 
	g++ $(FLAGS) bin/main_avl.o bin/avl.o $(OBJS) -o $@

main_rbt: bin/main_rbt.o bin/rbt.o $(OBJS)
	g++ $(FLAGS) bin/main_rbt.o bin/rbt.o $(OBJS) -o $@

# Compile all test
test: $(ALLTEST)

test_bst: bin/test_bst.o bin/bst.o $(OBJS)
	g++ $(FLAGS) bin/test_bst.o bin/bst.o $(OBJS) -o $@

test_avl: bin/test_avl.o bin/avl.o $(OBJS) 
	g++ $(FLAGS) bin/test_avl.o bin/avl.o $(OBJS) -o $@

test_rbt: bin/test_rbt.o bin/rbt.o $(OBJS)
	g++ $(FLAGS) bin/test_rbt.o bin/rbt.o $(OBJS) -o $@

## RUN THE TREE CHOSEN
else

OBJS = bin/$(tree).o bin/tree_utils.o bin/data.o
TARGET = main_$(tree)
TESTTARGET = test_$(tree)

TARGET: $(TARGET)
	./$(TARGET) $(cmd) $(num) $(path)

$(TARGET): bin/main_$(tree).o $(OBJS)
	g++ $(FLAGS) bin/main_$(tree).o $(OBJS) -o $@

test: $(TESTTARGET)
	./$(TESTTARGET)

$(TESTTARGET): bin/test_$(tree).o $(OBJS)
	g++ $(FLAGS) bin/test_$(tree).o $(OBJS) -o $@

endif

bin/%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

ifeq ($(OS), Windows_NT)
clean:
	rm bin/*.o $(ALLMAIN) $(ALLTEST)

cleancsv:
	rm ../stats/*.csv
else
clean:
	cmd /C "del /Q" bin\\*.o main_bst.exe main_avl.exe main_rbt.exe test_bst.exe test_avl.exe test_rbt.exe

cleancsv:
	cmd /C "del /Q" ..\\stats\\*.csv
endif