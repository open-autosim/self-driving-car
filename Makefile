CXX = clang++
CXXFLAGS = -I/opt/homebrew/Cellar/sfml/2.6.1/include -std=c++17
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

# List of source files
SOURCES = main.cpp car.cpp controls.cpp
# Object files are the .cpp files, but with .o extensions
OBJECTS = $(SOURCES:.cpp=.o)
# Name of the final executable
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Generic rule for compiling .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

