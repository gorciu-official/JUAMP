.PHONY: all run clean

ifeq ($(OS), Linux)
    CXX = g++
    EXE_SUFFIX = .bin
    FLAGS = -static
else
    CXX = g++
    EXE_SUFFIX = .exe
    FLAGS = -static
endif

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)
TARGET = juamp$(EXE_SUFFIX)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(FLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(FLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)