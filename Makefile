PROGRAM = game
OBJS = Main.o Game.o Snake.o Circle.o

CXX = c++ -Wall --std=c++17
LIBS = -lSDL2 -lSDL2_ttf

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
