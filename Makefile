.PHONY: all run clean

ifeq ($(OS), Windows_NT)
    CXX = g++ -static
    EXE_SUFFIX = .exe
else
    CXX = g++
    EXE_SUFFIX = .bin
endif

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)
TARGET = juamp$(EXE_SUFFIX)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)