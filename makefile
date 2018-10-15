FLAGS = -ggdb -Wall -Wextra -Wpedantic -std=c++14

SFML_LINK = -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = $(wildcard src/*.cpp)

OBJ = $(SOURCES:.cpp=.o)

all: $(OBJ)
	g++ $(FLAGS) -o statepet.bin $^ $(SFML_LINK)
