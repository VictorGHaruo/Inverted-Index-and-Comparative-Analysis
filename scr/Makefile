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

ifeq ($(OS),Windows_NT)
RM = cmd /C "del /Q"
EXT = .exe
else
RM = rm -rf
EXT =
endif

FLAGS = -Wall -Wextra

all: TARGET

ifndef tree

OBJS = bin/tree_utils.o bin/data.o

TARGET: main_bst main_avl main_rbt

main_bst: bin/main_bst.o bin/bst.o $(OBJS)
	g++ $(FLAGS) bin/main_bst.o bin/bst.o $(OBJS) -o $@

main_avl: bin/main_avl.o bin/avl.o $(OBJS) 
	g++ $(FLAGS) bin/main_avl.o bin/avl.o $(OBJS) -o $@

main_rbt: bin/main_rbt.o bin/rbt.o $(OBJS)
	g++ $(FLAGS) bin/main_rbt.o bin/rbt.o $(OBJS) -o $@

else

OBJS = bin/main_$(tree).o bin/$(tree).o bin/tree_utils.o bin/data.o
TARGET = main_$(tree)

TARGET: $(TARGET)
	./$(TARGET) $(cmd) $(num) $(path)

$(TARGET): $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

endif

bin/%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

clean:
	$(RM) bin/*.o main_bst$(EXT) main_avl$(EXT) main_rbt$(EXT)

cleancsv:
	$(RM) ../stats/*.csv