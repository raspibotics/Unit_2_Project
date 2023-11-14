# Define the compiler to use
CXX = g++

# Define the flags to use when compiling object files
CXXFLAGS = -c -Wall -std=c++11

# Define the flags to use when linking object files into an executable
LFLAGS = -Wall

# Define the source files to compile
SOURCES = $(wildcard *.cpp)

# Define the object files to create
OBJECTS = $(SOURCES:.cpp=.o)

# Define the name of the executable to create
EXECUTABLE = run

# Define the default target to build
all: $(EXECUTABLE)

# Define the rule to build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o $@

# Define the rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Define the rule to clean up generated files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
