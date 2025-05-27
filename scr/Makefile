ifdef num
num = 
else
num = 10103
endif

OBJS_BST = main_bst.o tree_utils.o data.o bst.o
T_BST = main_bst
search_bst = main_bst
stats_bst = main_bst
FLAGS = -Wall -Wextra

all: search_bst

search_bst: $(T_BST)
	./$(T_BST) search $(num) ../data/

stats_bst: $(T_BST)
	./$(T_BST) stats $(num) ../data/

$(T_BST): $(OBJS_BST)
	g++ $(FLAGS) $(OBJS_BST) -o $(T_BST)

%.o: %.cpp
	g++ $(FLAGS) -c $<

clean:
	rm -rf *.o $(T_BST) *.out
