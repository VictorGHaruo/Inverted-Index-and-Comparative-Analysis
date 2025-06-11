ifndef tree
tree = bst
endif

ifndef num
num = 10103
endif

ifndef cmd
cmd = search
endif

ifndef path
path = ../data/
endif

ifeq ($(OS),Windows_NT)
    RM = cmd /C "del /Q"
    EXT = .exe
else
    RM = rm -rf
    EXT =
endif

OBJS = main_$(tree).o $(tree).o tree_utils.o data.o
TARGET = main_$(tree)
FLAGS = -Wall -Wextra

all: TARGET

TARGET: $(TARGET)
	./$(TARGET) $(cmd) $(num) $(path)

$(TARGET): $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	g++ $(FLAGS) -c $<

clean:
	$(RM) *.o main_bst$(EXT) main_avl$(EXT) main_rbt$(EXT)