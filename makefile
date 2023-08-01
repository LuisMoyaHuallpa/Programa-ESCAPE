SOURCES = $(wildcard src/*.cpp)
all:
	g++ $(SOURCES) 
node:
	g++ src/main.cpp src/nodes.cpp src/node.cpp src/link.cpp src/links.cpp -o bin/sarsa
