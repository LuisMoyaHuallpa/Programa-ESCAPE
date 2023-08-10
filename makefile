SOURCES = $(wildcard src/*.cpp)
all:
	g++ $(SOURCES) -o bin/sarsa
node:
	g++ src/main.cpp src/nodes.cpp src/node.cpp src/link.cpp src/links.cpp src/pedestrian.cpp src/pedestrians.cpp -o bin/sarsa
debug:

	g++ -g $(SOURCES) -o bin/sarsa
