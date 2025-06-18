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

TARGET: main_bst main_avl main_rbt

main_bst: main_bst.o tree_utils.o data.o bst.o
	g++ $(FLAGS) main_bst.o tree_utils.o data.o bst.o -o main_bst

main_avl: main_avl.o tree_utils.o data.o avl.o 
	g++ $(FLAGS) main_avl.o tree_utils.o data.o avl.o -o main_avl

main_rbt: main_rbt.o tree_utils.o data.o rbt.o
	g++ $(FLAGS) main_rbt.o tree_utils.o data.o rbt.o -o main_rbt

else

OBJS = main_$(tree).o $(tree).o tree_utils.o data.o
TARGET = main_$(tree)

TARGET: $(TARGET)
	./$(TARGET) $(cmd) $(num) $(path)

$(TARGET): $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

endif

%.o: %.cpp
	g++ $(FLAGS) -c $<

clean:
	$(RM) *.o main_bst$(EXT) main_avl$(EXT) main_rbt$(EXT)