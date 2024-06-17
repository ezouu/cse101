#Makefile

CXX = g++
CXXFLAGS = -Wall -g
TARGET = nqueens
OBJ = nqueens.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): nqueens.cpp
	$(CXX) $(CXXFLAGS) -c nqueens.cpp

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)