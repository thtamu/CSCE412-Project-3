CXX = g++
CXXFLAGS = -std=c++17
TARGET = test_program
OUTPUT = logs.txt

SRC = $(filter-out testing.cpp, $(wildcard *.cpp))

all: $(TARGET)

$(TARGET): testing.cpp $(SRC)
	$(CXX) $(CXXFLAGS) testing.cpp $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) > $(OUTPUT) 

clean:
	rm -f $(TARGET) $(OUTPUT)