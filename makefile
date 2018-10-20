CXX = clang

FLAGS = -ggdb -Wall -Wextra -Wpedantic -std=c++14

LINK = -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = $(wildcard src/*.cpp)

OBJ = $(SOURCES:.cpp=.o)

all: $(OBJ)
	$(CXX) $(FLAGS) -o statepet.bin $^ $(LINK)

clean:
	rm $(OBJ)
