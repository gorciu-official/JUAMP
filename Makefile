.PHONY = all run

all:
	g++ --static juamp.cpp -o juamp.exe 

run:
	./juamp.exe