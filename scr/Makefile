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
	rm -rf *.o $(TARGET) *.out