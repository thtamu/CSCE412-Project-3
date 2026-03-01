CXX = g++
CXXFLAGS = -std=c++17
TARGET = test_program
OUTPUT = logs.txt

SRC = $(filter-out testing.cpp, $(wildcard *.cpp))

all: $(TARGET)

$(TARGET): testing.cpp $(SRC)
	$(CXX) $(CXXFLAGS) testing.cpp $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) > $(OUTPUT) 2>&1

clean:
	rm -f $(TARGET) $(OUTPUT)