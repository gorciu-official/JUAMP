.PHONY: all run

ifeq ($(OS), Linux)
    CXX = g++
    EXE_SUFFIX = .bin
    FLAGS = -static
else
    CXX = g++
    EXE_SUFFIX = .exe
    FLAGS = -static
endif

all:
	$(CXX) $(FLAGS) juamp.cpp -o juamp$(EXE_SUFFIX)

run:
	./juamp$(EXE_SUFFIX)