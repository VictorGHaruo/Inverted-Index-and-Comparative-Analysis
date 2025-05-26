OBJS_BST = main_bst.o tree_utils.o data.o bst.o
T_BST = main_bst
T_BST_Search = main_bst
T_BST_Stats = main_bst
FLAGS = -Wall -Wextra

all: T_BST_Search

T_BST_Search: $(T_BST)
	./$(T_BST) search 10103 ../data/

T_BST_Stats: $(T_BST)
	./$(T_BST) stats 10103 ../data/

$(T_BST): $(OBJS_BST)
	g++ $(FLAGS) $(OBJS_BST) -o $(T_BST)

%.o: %.cpp
	g++ $(FLAGS) -c $<

clean:
	rm -rf *.o $(T_BST) *.out
