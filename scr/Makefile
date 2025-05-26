OBJS_BST = main_bst.o
T_BST = main_bst
FLAGS = -Wall -Wextra

all: T_BST

T_BST: $(T_BST)
	./$(T_BST)

$(T_BST): $(OBJS_BST)
	g++ $(FLAGS) $(OBJS_BST) -o $(T_BST)

%.o: %.cpp
	g++ $(FLAGS) -c $<

clean:
	rm -rf *.o $(T_BST) *.out
