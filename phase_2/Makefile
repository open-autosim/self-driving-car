CXX = clang++
CXXFLAGS = -Iinclude -I/opt/homebrew/include -std=c++17
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

# List of source files
SOURCES = src/*.cpp
# Object files have the same name but with .o extensions
OBJECTS = $(SOURCES:.cpp=.o)
# Name of the final executable
EXECUTABLE = bin/main

all: build

build:	$(EXECUTABLE)

# install:
# 	brew install sfml && brew install nlohmann-json

run:
	./bin/main 

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o src/math/*.o src/primitives/*.o $(EXECUTABLE)
