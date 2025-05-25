OBJS_DATA = test.o data.o
DATA = data
FLAGS = -Wall -Wextra

all: Data

Data: $(DATA)
	./$(DATA)

$(DATA): $(OBJS_DATA)
	g++ $(FLAGS) $(OBJS_DATA) -o $(DATA)

%.o: %.cpp
	g++ $(FLAGS) -c $<

clean:
	rm -rf *.o $(DATA) *.out
