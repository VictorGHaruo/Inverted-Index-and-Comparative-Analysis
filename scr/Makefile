OBJS_DATA = test_data.o data.o
DATA = data

all: Data

Data: $(DATA)
	./$(DATA)

$(DATA): $(OBJS_DATA)
	g++ $(OBJS_DATA) -o $(DATA)

%.o: %.cpp
	g++ -c $<

clean:
	rm -rf *.o $(DATA)
