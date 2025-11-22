CXX = clang++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = use
OBJECTS = my.o use.o

# Link object files into executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Compile my.cpp to my.o
my.o: my.cpp my.h
	$(CXX) $(CXXFLAGS) -c my.cpp

# Compile use.cpp to use.o
use.o: use.cpp my.h
	$(CXX) $(CXXFLAGS) -c use.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: clean