.PHONY: all run clean download_toml

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)
TARGET = juamp$(EXE_SUFFIX)

ifeq ($(OS), Windows_NT)
    CXX = g++ -static
    EXE_SUFFIX = .exe
    CLEANCMD = del /Q $(subst /,\,$(OBJ_FILES)) $(subst /,\,$(TARGET))
else
    CXX = g++
    EXE_SUFFIX = .elf
    CLEANCMD = rm -f $(OBJ_FILES) $(TARGET)
endif

all: download_toml $(TARGET)

download_toml:
	curl -s https://raw.githubusercontent.com/marzer/tomlplusplus/master/toml.hpp -o src/toml.hpp

$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(CLEANCMD)