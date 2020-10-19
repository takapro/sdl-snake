PROGRAM = game
OBJS = Game.o

CXX = c++ -Wall --std=c++17
LIBS = -lSDL2

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
